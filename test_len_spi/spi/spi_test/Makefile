#
# Makefile for the Microchip network device drivers.
#

obj-$(CONFIG_ENC28J60) += testspi.o
#obj-$(CONFIG_ENCX24J600) += encx24j600.o encx24j600-regmap.o
#obj-$(CONFIG_LAN743X) += lan743x.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
