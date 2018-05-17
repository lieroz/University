ifneq ($(KERNELRELEASE),)
	obj-m := work_queue.o

else
	CURRENT = $(shell uname -r)
	KDIR = /lib/modules/$(CURRENT)/build
	PWD = $(shell pwd)

default:
	sudo $(MAKE) -C $(KDIR) M=$(PWD) modules
	sudo make clean

clean:
	rm -rf .tmp_versions
	rm .work_queue.*
	rm *.o
	rm *.mod.c
	rm *.order

endif
