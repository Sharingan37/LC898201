/*
Name: main.c
Author:	ThangLMb
Date: 06/07/2019
Explanation: 
*/
#include"CamDef.h"
//#include"CamFil.h"
#include"spi.h"
#include"Cam.h"
#include"CamIni.h"
#include<stdio.h>
#include<string.h>

//#define  S2_H_MODE
#define USE_OSC
#define S3_DN_MODE
#define   CAMIFT

int main()
{	
	
	int i =0;
	unsigned char value;
	printf("Set up LC898201\n");
	int fileMode3 = spi_init("/dev/spidev0.0",3);  
        RegWriteA(SPIMD3,MODE3);
	IniSet();
	printf("Init Finished\n");
	//DCMDriFil();
	printf("DCMDriFill Finished\n");
	RegWriteA(0x0240, 0x01);
	RegReadA(0x0240,&value);
	printf("Register: 0x0240 	Write : 0x01	Read: %02x\n", value);
	//SetSin(0x00);
	//SetMsf(0x00);
	//SetMmd(0x00);
        while(1)
	{     
	printf(" --------------------------------------------------\n");
	printf(" Rotation Forward\n");
	//UcDCMCWFlg=1;
  	//i = VcmDrg( 0xffff0000, 0x00000000 , 0x0fff0000, 0x0f );
	//i = VcmDrg( 0x0fff0000, 0x0fff0000 , 0x0fff0000, 0x0f );
	//DCMDriFil();
       // StmDra( 1, 0x000a, 0x0fff);          
 	//StmDrb( 1, 0x00ff, 0x1fff);   
	//StmDrc( 1, 0x00ff, 0xffff);  
      //  sleep(2);	
	printf(" Rotation Reserve\n");
	//UcDCMCWFlg=0;
	//i = VcmDrg( 0xffff0000, 0x00000000 , 0x0fff0000, 0x0f );
	//i = VcmDrg( 0x0fff0000, 0x0fff0000 , 0x0fff0000, 0x0f );
	//DCMDriFil();
       // StmDra( 0, 0x000a, 0x0fff);      
 	//StmDrb( 0, 0x00ff, 0x1fff);   
	//StmDrc( 0, 1080, 0xFfff);  
      	// sleep(2);
     }



}
