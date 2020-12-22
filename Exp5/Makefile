obj-m	:= myzr_zlg7290_student.o


#KERNELDIR ?= $(HOME)/my-work/02_sources/linux-3.14.52-myimx6a9
KERNELDIR ?= /home/zqy/my-imx6/02_sources/linux-3.14.52
PWD       := $(shell pwd)

default:
	make -C $(KERNELDIR) M=$(PWD) MOD_INC=$(PWD) modules ARCH=arm CROSS_COMPILE=/home/zqy/my-imx6/03_tools/gcc-linaro-5.4.1-2017.05-i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers *.order
