obj-m += hello.o
KERNEL_DIR ?= /workspaces/linux-kernel

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
