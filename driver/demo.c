#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/device.h>

#include <linux/semaphore.h>
#include <linux/fcntl.h>
#include <linux/moduleparam.h>
#include <linux/list.h>

#include <linux/timer.h>
#include <linux/timex.h>
#include <linux/rtc.h>

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
// static int signum = SIGRTMIN + 4; // 36
static int signum = SIGIO;

module_param(signum, int, S_IRUGO);

MODULE_PARM_DESC(signum, "signal number, SIGRTMIN ~ SIGRTMAX");

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
#define DEMO_NAME           "demo"          /* /dev/xxx */
#define DEMO_NUM_MINORS     1               /* number of minors */

struct demo_dev {
    dev_t devno;
    int major;
    int minor;

    struct cdev cdev;
    struct class *class;
    struct device *device;
    struct device_node *device_node;

    struct fasync_struct *async_queue;
    struct timer_list signal_timer;
};

struct demo_dev demo;

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* fasync callback */
static void fasync_callback(void)
{
#if 1
    static int cnt = 0;
    printk(KERN_ALERT "[%s] %d\n", __FUNCTION__, cnt++);
#endif

    if (demo.async_queue)
        kill_fasync(&demo.async_queue, signum, POLL_IN);
}

/* timer function */
static void signal_timer_function(struct timer_list *tim)
{
    fasync_callback();
    mod_timer(&(demo.signal_timer), jiffies + msecs_to_jiffies(10));
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* fops.fasync */
static int demo_fasync(int fd, struct file *filp, int on)
{
    struct demo_dev *dev = (struct demo_dev *)filp->private_data;
    return fasync_helper(fd, filp, on, &dev->async_queue);
}

/* fops.open */
static int demo_open(struct inode *inode, struct file *filp)
{
    filp->private_data = &demo;
    return 0;
}

/* fops.release */
static int demo_close(struct inode *inode, struct file *filp)
{
    return demo_fasync(-1, filp, 0);
}

/* file operations */
static struct file_operations demo_fops = {
    .owner = THIS_MODULE,
    .open = demo_open,
    .release = demo_close,
    .fasync = demo_fasync,
};
/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
static int demo_probe(void)
{
    int ret = 0;

    /* create dev */
    /* (1) register char device */
    if (demo.major) {
        demo.devno = MKDEV(demo.major, 0);
        register_chrdev_region(demo.devno, DEMO_NUM_MINORS, DEMO_NAME);
    } else {
        alloc_chrdev_region(&demo.devno, 0, DEMO_NUM_MINORS, DEMO_NAME);
        demo.major = MAJOR(demo.devno);
        demo.minor = MINOR(demo.devno);
    }
    if (0) printk("[%s]: major %d, minor %d\r\n", __FUNCTION__, demo.major, demo.minor);

    /* (2) init char device */
    demo.cdev.owner = THIS_MODULE;
    cdev_init(&demo.cdev, &demo_fops);
    ret = cdev_add(&demo.cdev, demo.devno, DEMO_NUM_MINORS);
    if (ret) {
        printk("[%s]: failed to open char device\r\n", __FUNCTION__);
        goto fail_cdev;
    }

    /* (3) create class */
    demo.class = class_create(THIS_MODULE, DEMO_NAME);
    if (IS_ERR(demo.class)) {
        printk("[%s]: failed to create class\r\n", __FUNCTION__);
        ret = PTR_ERR(demo.class);
        goto fail_class;
    }

    /* (4) create device */
    demo.device = device_create(demo.class, NULL, demo.devno, NULL, DEMO_NAME);
    if (IS_ERR(demo.device)) {
        printk("[%s]: failed to create device\r\n", __FUNCTION__);
        ret = PTR_ERR(demo.device);
        goto fail_device;
    }

    /* init */
    demo.signal_timer.function = signal_timer_function;
    add_timer(&(demo.signal_timer));

    return 0;

fail_device:
    device_destroy(demo.class, demo.devno);
fail_class:
    class_destroy(demo.class);
fail_cdev:
    cdev_del(&demo.cdev);
    unregister_chrdev_region(demo.devno, DEMO_NUM_MINORS);

    return ret;
}

static void demo_remove(void)
{
    /* exit */
    del_timer_sync(&(demo.signal_timer));

    /* delete dev */
    device_destroy(demo.class, demo.devno);
    class_destroy(demo.class);
    cdev_del(&demo.cdev);
    unregister_chrdev_region(demo.devno, DEMO_NUM_MINORS);
}

static int __init demo_init(void)
{
    printk(KERN_ALERT "[%s]\r\n", __FUNCTION__);
    return demo_probe();
}

static void __exit demo_exit(void)
{
    printk(KERN_ALERT "[%s]\r\n", __FUNCTION__);
    demo_remove();
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
MODULE_AUTHOR("tovax, 332451208@qq.com");
/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
