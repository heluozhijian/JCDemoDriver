obj-m += demo.o
	CURRENT_PATH:=$(shell pwd)
	LINUX_KERNEL_PATH:=/lib/modules/$(shell uname -r)/build
all:
	$(MAKE) -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
	sudo cp -rf demo.ko /lib/modules/$(shell uname -r)
insmod:
	sudo insmod demo.ko
	sudo chmod 777 /dev/demo
rmmod:
	sudo rmmod demo.ko
clean:
	@rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions
