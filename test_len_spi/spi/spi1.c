/*
*Name: spi-linux.c 
*Purpose: Communicate SPI with LC898201s
*Author: ThangLMb
*Date: 12/06/2019
*Purpose: SPI communicate on Linux
*/
/*
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
*/
#include "spi1.h"

/*-------------------------------------------------------------------------*
*  Variable global
*---------------------------------------------------------------------------*/
/*
static int GPIOExport(int pin)
{
        char buffer[BUFFER_MAX];
        ssize_t bytes_written;
        int fd;

        fd = open("/sys/class/gpio/export", O_WRONLY);
        if (-1 == fd) {
                fprintf(stderr, "Failed to open export for writing!\n");
                return(-1);
        }

        bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
        write(fd, buffer, bytes_written);
        close(fd);
        return(0);
}

static int GPIOUnexport(int pin)
{
        char buffer[BUFFER_MAX];
        ssize_t bytes_written;
        int fd;

        fd = open("/sys/class/gpio/unexport", O_WRONLY);
        if (-1 == fd) {
                fprintf(stderr, "Failed to open unexport for writing!\n");
                return(-1);
        }

        bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
        write(fd, buffer, bytes_written);
        close(fd);
        return(0);
}

static int  GPIODirection(int pin, int dir)
{
        static const char s_directions_str[]  = "in\0out";
        char path[DIRECTION_MAX];
        int fd;

        snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
        fd = open(path, O_WRONLY);
        if (-1 == fd) {
                fprintf(stderr, "Failed to open gpio direction for writing!\n");
                return(-1);
        }

        if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) {
                fprintf(stderr, "Failed to set direction!\n");
                return(-1);
        }

        close(fd);
        return(0);
}

static int GPIOWrite(int pin, int value)
{
        static const char s_values_str[] = "01";

        char path[VALUE_MAX];
        int fd;

        snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
        fd = open(path, O_WRONLY);
        if (-1 == fd) {
                fprintf(stderr, "Failed to open gpio value for writing!\n");
                return(-1);
        }

        if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1))
        {
                fprintf(stderr, "Failed to write value!\n");
                return(-1);
        }

        close(fd);
        return(0);
}
void SelectExportLow()
{
    if (GPIOExport(SS) ==0)
    printf("Create GPIO Select is successfully\n");
    if(GPIODirection(SS,OUT) ==0)
    printf("GPIO Select is Output\n");
    if (GPIOWrite(SS,LOW)==0)
    printf("Pin select is LOW\n");

}
*/

/*-------------------------------------------------------------------------
* Function: spi_init(char filename[40])
* Purpose:  Configuration for SPI interface
* Paramenter: char filename[40]
*
---------------------------------------------------------------------------*/
int spi_init(char filename[40], __u8 mode)
    {
    __u8    lsb, bits;
    __u32 speed=2000000;
 
        if ((file = open(filename,O_RDWR)) < 0)
        {
            printf("Failed to open the bus.");
            /* ERROR HANDLING; you can check errno to see what went wrong */
            exit(1);
            }
 
        ///////////////
        // Verifications
        ///////////////
        //possible modes: mode |= SPI_LOOP; mode |= SPI_CPHA; mode |= SPI_CPOL; mode |= SPI_LSB_FIRST; mode |= SPI_CS_HIGH; mode 	|= SPI_3WIRE; mode |= SPI_NO_CS; mode |= SPI_READY;
        //multiple possibilities using |
        
            if (ioctl(file, SPI_IOC_WR_MODE, &mode)<0)   {
                perror("can't set spi mode");
                //return;
                }
        
 
            if (ioctl(file, SPI_IOC_RD_MODE, &mode) < 0)
                {
                perror("SPI rd_mode");
                //return;
                }
            if (ioctl(file, SPI_IOC_RD_LSB_FIRST, &lsb) < 0)
                {
                perror("SPI rd_lsb_fist");
                //return;
                }
        //sunxi supports only 8 bits
        
            if (ioctl(file, SPI_IOC_WR_BITS_PER_WORD, (__u8[1]){8})<0)   
                {
                perror("can't set bits per word");
                //return;
                }
        
            if (ioctl(file, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) 
                {
                perror("SPI bits_per_word");
                //return;
                }
        
            if (ioctl(file, SPI_IOC_WR_MAX_SPEED_HZ, &speed)<0)  
                {
                perror("can't set max speed hz");  
                //return;
                }
        
            if (ioctl(file, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0) 
                {
                perror("SPI max_speed_hz");
                //return;
                }    
    printf("%s: spi mode %d, %d bits %sper word, %d Hz max\n",filename, mode, bits, lsb ? "(lsb first) " : "", speed); 
    return file;
    }

/*-------------------------------------------------------------------------
* Function: void RegReadA(unsigned long address,char *outData, int file)
* Purpose: Read SPI interface at Register
* Paramenter:
	 unsigned long address: addres of register ( 2 byte)
	 char *outData : array buffer data  (1 byte)
	 int file: file out of function spi_int()
*
---------------------------------------------------------------------------*/
void RegReadA(unsigned long address,unsigned char* outData)
{
    int status;
    char arAddress[2];
    //outData = (unsigned char *) malloc( sizeof( unsigned char));
    //memset(outData, 0,  sizeof(*outData));
    arAddress[0] = 0x80 | (address>>8);
    arAddress[1] = 0xff & (address);
    xfer[0].tx_buf = (unsigned long)arAddress;
    xfer[0].len =2; /* Length of  command to write*/
    xfer[1].rx_buf = (unsigned long)outData;
    xfer[1].len = 1; /* Length of Data to read */
    status = ioctl(file, SPI_IOC_MESSAGE(2), xfer);
    if (status < 0)
        {
        perror("SPI_IOC_MESSAGE");
        //return;
        }

}
/*-------------------------------------------------------------------------
* Function: RegWriteA(unsigned long address,char inData,int file)
* Purpose: Transmit SPI interface at Register
* Paramenter: 
	unsigned long address: addres of register ( 2byte)
	char inData:buffer data ( 1 byte)
	int file: file out of function spi_int()
*
---------------------------------------------------------------------------*/
void RegWriteA(unsigned long address,char inData)
{
    unsigned char   arData[10];
    int status;
    arData[0]= 0x7f & (address>>8);
    arData[1] = 0xff & (address);
    arData[2]= inData;
    xfer[0].tx_buf = (unsigned long)arData;
    xfer[0].len = 3; /* Length of  command to write*/
    status = ioctl(file, SPI_IOC_MESSAGE(1), xfer);
    if (status < 0)
        {
        perror("SPI_IOC_MESSAGE");
       // return;
        }
}
/*-------------------------------------------------------------------------
* Function: RamWrite32A(unsigned long address,char* inData,int file)
* Purpose: Transmit SPI interface at RAM
* Paramenter:
	unsigned long address: addres of register ( 2byte)
	char inData: array buffer data ( 4 byte)
	int file: file out of function spi_int()
*
---------------------------------------------------------------------------*/
void RamWrite32A(unsigned long address,unsigned long  inData)
{
    unsigned char   arData[10];
    int status;
    arData[0]= 0x7f & (address>>8);
    arData[1] = 0xff & (address);
    arData[2] = 0xFF& (inData>>24);
    arData[3] = 0xFF& (inData>>16);
    arData[4] = 0xFF& (inData>>8);
    arData[5] = 0xFF& (inData);
    xfer[0].tx_buf = (unsigned long)arData;
    xfer[0].len = 6; /* Length of  command to write*/
    status = ioctl(file, SPI_IOC_MESSAGE(1), xfer);
    if (status < 0)
        {
        perror("SPI_IOC_MESSAGE");
       // return;
        }
}
/*-------------------------------------------------------------------------
* Function: void RamRead32A(unsigned long address,unsigned char* outData, int file)
* Purpose: Read SPI interface at RAM
* Paramenter:
		- unsigned long address: addres of register ( 2 byte)
		- char *outData : buffer data  (4 byte)
		- int file: file out of function spi_int()
*
---------------------------------------------------------------------------*/
void RamRead32A(unsigned long address,unsigned long* outData)
{
    int status;
    char arAddress[2];
    unsigned char* data;
    data = (unsigned char *) malloc( 4*sizeof( unsigned char));
    //memset(outData, 0,  sizeof(*outData));
    arAddress[0] = 0x80 | (address>>8);
    arAddress[1] = 0xff & (address);
    xfer[0].tx_buf = (unsigned long)arAddress;
    xfer[0].len =2; /* Length of  command to write*/
    xfer[1].len = 4; /* Length of Data to read */
    xfer[1].rx_buf = (unsigned long)outData;
    status = ioctl(file, SPI_IOC_MESSAGE(2), xfer);
    if (status < 0)
        {
            perror("SPI_IOC_MESSAGE");
            //return;
        }
    *outData= *(data) ;
    *outData= (*(outData)<<8)|(*data+1) ;
    *outData= (*(outData)<<8)|(*data+2) ;
    *outData= (*(outData)<<8)|(*data+3) ;
    free(data);

}

