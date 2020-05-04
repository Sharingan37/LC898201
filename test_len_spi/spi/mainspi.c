
#include"spi1.h"
#include<stdio.h>
#include<string.h>

#define USE_OSC
#define S3_DN_MODE
#define   CAMIFT

int main()
{	
	
	int i =0;
	unsigned char value;
	printf("Set up LC898201\n");
	int fileMode3 = spi_init("/dev/spidev0.0",0);  
    RegWriteA(SPIMD3,MODE3);
	//IniSet();
	printf("Init Finished\n");
	
	printf("DCMDriFill Finished\n");
	RegWriteA(0x0240, 0x01);
	RegReadA(0x0240,&value);
	printf("Register: 0x0240 	Write : 0x01	Read: %02x\n", value);


}
