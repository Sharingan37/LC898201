#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <linux/tcp.h>
#include <linux/skbuff.h>
#include <linux/delay.h>
#include <linux/spi/spi.h>
#include <linux/of_net.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/spi/spi.h>

#define DEVICE_NAME "LC898201"

struct spi_board_info spi_board_info[] __initdata = {
    .modalias = "LC898201",
    .bus_num =1,
    .chip_select =1,
};
struct spi_device spi;
{
    /* data */
};


spi_register_board_info(spi_board_info, 1);

static struct spi_driver LC898201_driver = {
    .driver = {
    .name = "DEVICE_NAME",
    .owner = THIS_MODULE,
},
    .probe = LC898201_probe,
};

module_spi_driver(LC898201_driver);

static int LC898201_write_reg(struct device *dev, unsigned long address, char inData)
{
    struct spi_device *spi = to_spi_device(dev);
    unsigned char   arData[10];
    int status;
    arData[0]= 0x7f & (address>>8);
    arData[1] = 0xff & (address);
    arData[2]= inData;

 
int status = spi_write_then_read(spi, arData, 3, NULL, 0);
    if (status < 0) {
		return status;
	}

	return 0;
}


static int LC898201_read_reg(struct device *dev, unsigned long address, char* outData)
{
    struct spi_device *spi = to_spi_device(dev);
    int status;
    char arAddress[2];
 
    arAddress[0] = 0x80 | (address>>8);
    arAddress[1] = 0xff & (address);


 
int status = spi_write_then_read(spi, arAddress, 2, outData, 1);
    if (status < 0) {
		return status;
	}

	return 0;
}
static int LC898201_probe(struct spi_device *spi)
{
    struct device *dev = &spi->dev;
    int ret, ret1;
    __u8 val;

    spi->mode = SPI_MODE_3;
    spi->bits_per_word = 8;
    spi_setup(spi);

    ret = LC898201_write_reg(spi, 0x0240, 0x01);
    if (ret < 0) {
		return ret;
	}

    
    ret = LC898201_read_reg(spi, 0x0240, &val);
    if (ret < 0) {
		return ret;
	}

	return 0;

  
}

MODULE_AUTHOR("HaiHV");
MODULE_DESCRIPTION("TI LC898201 A/D driver");
MODULE_LICENSE("GPL");

