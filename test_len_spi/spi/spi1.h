/*
*Name: spi-linux.c 
*Purpose: Communicate SPI with LC898201s
*Author: ThangLMb
*Date: 12/06/2019
*Purpose: SPI communicate on Linux
*/


#ifndef SPI1_H__
#define SPI1_H__

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <sys/stat.h>
#include <sys/types.h>

/*-------------------------------------------------------------------------*
* Defination
*---------------------------------------------------------------------------*/
static int file;
static struct spi_ioc_transfer xfer[2];

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

#define SS 25

#define BUFFER_MAX 3
#define DIRECTION_MAX 35
#define VALUE_MAX 30
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#define SPIMD3 0x0248 // thanh ghi set spi mode for LC898201
#define MODE0 0x00  // mode 0
#define MODE3 0x01  // mode 3


/*-------------------------------------------------------------------------
* Function: spi_init(char filename[40])
* Purpose:  Configuration for SPI interface
* Paramenter: char filename[40]
*
---------------------------------------------------------------------------*/
int spi_init(char filename[40], __u8 mode);


/*-------------------------------------------------------------------------
* Function: void RegReadA(unsigned long address,char *outData, int file)
* Purpose: Read SPI interface at Register
* Paramenter:
	 unsigned long address: addres of register ( 2 byte)
	 char *outData : array buffer data  (1 byte)
	 int file: file out of function spi_int()
*
---------------------------------------------------------------------------*/
void RegReadA(unsigned long address,unsigned char* outData);

/*-------------------------------------------------------------------------
* Function: RegWriteA(unsigned long address,char inData,int file)
* Purpose: Transmit SPI interface at Register
* Paramenter: 
	unsigned long address: addres of register ( 2byte)
	char inData:buffer data ( 1 byte)
	int file: file out of function spi_int()
*
---------------------------------------------------------------------------*/
void RegWriteA(unsigned long address,char inData);

/*-------------------------------------------------------------------------
* Function: RamWrite32A(unsigned long address,char* inData,int file)
* Purpose: Transmit SPI interface at RAM
* Paramenter:
	unsigned long address: addres of register ( 2byte)
	char inData: array buffer data ( 4 byte)
	int file: file out of function spi_int()
*
---------------------------------------------------------------------------*/
void RamWrite32A(unsigned long address,unsigned long  inData);
/*-------------------------------------------------------------------------
* Function: void RamRead32A(unsigned long address,unsigned char* outData, int file)
* Purpose: Read SPI interface at RAM
* Paramenter:
		- unsigned long address: addres of register ( 2 byte)
		- char *outData : buffer data  (4 byte)
		- int file: file out of function spi_int()
*
---------------------------------------------------------------------------*/
void RamRead32A(unsigned long address,unsigned long* outData);

#endif /* SPI_H__ */
