KDIR := /home/bhargav/WSL2-Linux-Kernel-6.18.40.1
PWD := $(shell pwd)

obj-m += slf_audit.o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
