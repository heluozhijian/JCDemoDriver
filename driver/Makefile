obj-m += demo.o
	CURRENT_PATH:=$(shell pwd)
	LINUX_KERNEL_PATH:=/lib/modules/$(shell uname -r)/build
all:
	$(MAKE) -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
insmod:
	sudo cp -rf demo.ko /lib/modules/$(shell uname -r)
	sudo insmod demo.ko
	sudo chmod 777 /dev/demo
rmmod:
	sudo rmmod demo.ko
	sudo rm -rf /lib/modules/$(shell uname -r)/demo.ko
	sudo rm -rf /dev/demo
clean:
	@rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions
