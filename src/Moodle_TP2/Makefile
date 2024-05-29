obj-m:=hello.o

CFLAGS_MODULE=-fno-pic

KERNEL_SOURCE=/home/ensea/linux-socfpga

all :
	make -C $(KERNEL_SOURCE) M=$(PWD) modules
clean :
	make -C $(KERNEL_SOURCE) M=$(PWD) clean
install :
	make −C $(KERNEL_SOURCE) M=$(PWD) modules install
