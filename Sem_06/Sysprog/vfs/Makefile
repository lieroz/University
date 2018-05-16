ifneq ($(KERNELRELEASE),)
	obj-m := vfs.o

else
	CURRENT = $(shell uname -r)
	KDIR = /lib/modules/$(CURRENT)/build
	PWD = $(shell pwd)

default:
	sudo $(MAKE) -C $(KDIR) M=$(PWD) modules
	sudo make clean

clean:
	rm -rf .tmp_versions
	rm .vfs.*
	rm *.o
	rm *.mod.c
	rm *.order

endif