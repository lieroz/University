ifneq ($(KERNELRELEASE),)
	obj-m := tasklet.o

else
	CURRENT = $(shell uname -r)
	KDIR = /lib/modules/$(CURRENT)/build
	PWD = $(shell pwd)

default:
	sudo $(MAKE) -C $(KDIR) M=$(PWD) modules
	sudo make clean

clean:
	rm -rf .tmp_versions
	rm .tasklet.*
	rm *.o
	rm *.mod.c
	rm *.order

endif
