//********************************************************************************
//
//		<< LC898109 Evaluation Soft >>
//		Program Name	: CAMCMD.c
//		Design			: Y.Yamada
//		History			: First edition						2009.07.31 Y.Tashita
//********************************************************************************
//**************************
//	Include Header File		
//**************************
#define		CAMCMD
#define 	S3_DN_MODE
#include <stdio.h>

//#include	"Main.h"
//#include 	"timer.h"
//#include	"Cmd.h"
#include	"Cam.h"
#include	"CamDef.h"

//#include	"io.h"
#include	"spi.h"
//#include	"usb.h"

#ifndef S3_DN_MODE
void	SetSin( unsigned char );
void	SetMsf( unsigned char );
void	SetMmd( unsigned char );
#endif

unsigned char 	TngAdj( unsigned char , float , UnFltVal ) ;

unsigned char	StmDra( unsigned char, unsigned short, unsigned short );
unsigned char	StmDrb( unsigned char, unsigned short, unsigned short );
unsigned char	StmDrc( unsigned char, unsigned short, unsigned short );
unsigned char	VcmDrd( unsigned char, unsigned short, unsigned short );
unsigned char	VcmDrg( UnFltVal, UnFltVal, UnFltVal, unsigned char );

#define	INI_A_MDIS			0x0100
#define	INI_B_MDIS			0x0100
#define	INI_C_MDIS			0x1000

// MR OFFSET ADJUSTMENT
#define	MR_OFFSET_MARGIN	0x3C000000			//0.0078125F	// 0x0100 	0x3C000000
#define	MRA_OFFSET_DIV		0x3C000000			//0.0078125F	// 0x0100	0x3C000000
#define	MRB_OFFSET_DIV		0x3C000000			//0.0078125F	// 0x0100	0x3C000000

// HALL OFFSET & BIAS ADJUSTMENT
#define	OFFSET_MARGIN		0.0078125F			//0x0100 	0x3C000000
#define	BIAS_MARGIN			0.0244150F			//0x3CC801F7    //	// 0x0320	0x3CC7FFDE	
#define	TGT_PTP				0x3F59364E			// 0.8484849(About 85%)

#define	OFFSET_DIV		0.0078125F			// 0x0100	0x3C000000
#define	BIAS_DIV		0.0243164F			// 0x031D	0x3CC73259
#define	ADJ_COUNT		100

#define CW_DIR	0
#define CCW_DIR	1


//*************************************************************************************************
//	Local Function
//*************************************************************************************************
#ifndef S3_DN_MODE
//********************************************************************************
// Function Name 	: SetSin
// Retun Value		: NON
// Argment Value	: NON
// Explanation		: Sin Wave Setting
// History			: First edition 						2012.02.08 Y.Kim
//********************************************************************************
void	SetSin ( unsigned char	UcSinSwt )
{
	//Sine Wave Setting
	switch( UcSinSwt )	{
		case 0x00:
			RegWriteA( CM_SINON		, 0x00 ) ;
			RegWriteA( CM_SINGAIN	, 0x80 ) ;			// Sine Wave Gain	= 0dB
			RegWriteA( CM_SINFRQ0	, 0x7C ) ;			// Frequency 60Hz
			RegWriteA( CM_SINFRQ1	, 0x0A ) ;			// Frequency 60Hz    (SINFRQ = 65536*16 *Hz / Fs)
			RegWriteA( CM_SINPHSX	, 0x00 ) ;			// X Phase
			RegWriteA( CM_SINPHSY	, 0x20 ) ;			// Y Phase
			RegWriteA( CM_SINSTP	, 0x00 ) ;			// Sine Wave ON
			break;
		case 0x01:
			RamWrite32A( afsin	, 0x3DA3D70A ) ;
			RegWriteA( CM_SINON	, 0x05 ) ;				// Sine Wave Generator ON
			break;
		case 0x02:
			RamWrite32A( afsin	, 0x00000000 ) ;
			RegWriteA( CM_SINON	, 0x00 ) ;				// Sine Wave Generator OFF
			break;
		case 0x03:
			RegWriteA( CM_SINON		, 0x00 ) ;
			RegWriteA( CM_SINGAIN	, 0x80 ) ;			// Sine Wave Gain	= 0dB
			RegWriteA( CM_SINFRQ0	, 0x27 ) ;			// Frequency 81Hz
			RegWriteA( CM_SINFRQ1	, 0x0E ) ;			// Frequency 81Hz   (SINFRQ = 65536*16 *Hz / Fs)
			RegWriteA( CM_SINPHSX	, 0x00 ) ;			// X Phase
			RegWriteA( CM_SINPHSY	, 0x20 ) ;			// Y Phase
			RegWriteA( CM_SINSTP	, 0x00 ) ;			// Sine Wave ON
			break;
		case 0x04:
			RamWrite32A( glsin	, 0x3DA3D70A ) ;
			RegWriteA( CM_SINON	, 0x05 ) ;				// Sine Wave Generator ON
			break;
		case 0x05:
			RamWrite32A( glsin	, 0x00000000 ) ;
			RegWriteA( CM_SINON	, 0x00 ) ;				// Sine Wave Generator OFF
			break;
		default:
			break;
	}
}



//********************************************************************************
// Function Name 	: SetMsf
// Retun Value		: NON
// Argment Value	: Measure Filter Select
// Explanation		: Measure Filter Setting
// History			: First edition 						2012.02.08 Y.Kim
//********************************************************************************
void	SetMsf( unsigned char	UcMscSwt )
{
	unsigned short	i = 0;
	unsigned short	UsStrAdr;
	static unsigned long	UlMsgTmp[12];
	
	UsStrAdr	= ms1aa ;
	
	switch( UcMscSwt ){
		case 0x00:
			for( i = 0 ; i < 12 ; i++ )
			{
				RamWrite32A( UsStrAdr + i , UlMsgTmp[i] ) ;
			}
			
			RegWriteA( CM_RAMDLYMOD	, 0x08 ) ;			// MS1, MS2 Clear
			RegWriteA( CM_RAMINITON	, 0x02 ) ;			// HRAM1 Clear
			WitTim( 5 ) ;
			break;
		case 0x01:										// Measure for MR-VCM OFFSET ADJUSTMENT
			for( i = 0 ; i < 12 ; i++ )
			{
				RamRead32A( UsStrAdr + i , &UlMsgTmp[i] );
			}
			
			RamWrite32A( ms1aa	, 0x3F800000 ) ;		//Through
			RamWrite32A( ms1ab	, 0x00000000 ) ;
			RamWrite32A( ms1ac	, 0x00000000 ) ;
			RamWrite32A( ms1ba	, 0x3F800000 ) ;		//Through
			RamWrite32A( ms1bb	, 0x00000000 ) ;
			RamWrite32A( ms1bc	, 0x00000000 ) ;
			
			RamWrite32A( ms2aa	, 0x3F800000 ) ;		//Through
			RamWrite32A( ms2ab	, 0x00000000 ) ;
			RamWrite32A( ms2ac	, 0x00000000 ) ;
			RamWrite32A( ms2ba	, 0x3F800000 ) ;		//Through
			RamWrite32A( ms2bb	, 0x00000000 ) ;
			RamWrite32A( ms2bc	, 0x00000000 ) ;
			
			RegWriteA( CM_RAMDLYMOD	, 0x08 ) ;			// MS1, MS2 Clear
			RegWriteA( CM_RAMINITON	, 0x02 ) ;			// HRAM1 Clear
			WitTim( 5 );
			break;
		
		case 0x02:
			for( i = 0 ; i < 12 ; i++ )
			{
				RamRead32A( UsStrAdr + i , &UlMsgTmp[i] );
			}
			
			RamWrite32A( ms1aa	, 0x3F7FD5DC ) ;		//HPF 5Hz
			RamWrite32A( ms1ab	, 0xBF7FD5DC ) ;
			RamWrite32A( ms1ac	, 0x3F7FABB9 ) ;
			RamWrite32A( ms1ba	, 0x3F800000 ) ;		//Through
			RamWrite32A( ms1bb	, 0x00000000 ) ;
			RamWrite32A( ms1bc	, 0x00000000 ) ;
			
			RamWrite32A( ms2aa	, 0x3F7FD5DC ) ;		//HPF 5Hz
			RamWrite32A( ms2ab	, 0xBF7FD5DC ) ;
			RamWrite32A( ms2ac	, 0x3F7FABB9 ) ;
			RamWrite32A( ms2ba	, 0x3F800000 ) ;		//Through
			RamWrite32A( ms2bb	, 0x00000000 ) ;
			RamWrite32A( ms2bc	, 0x00000000 ) ;
			
			RegWriteA( CM_RAMDLYMOD	, 0x08 ) ;			// MS1, MS2 Clear
			RegWriteA( CM_RAMINITON	, 0x02 ) ;			// HRAM1 Clear
			WitTim( 5 ) ;
			break;
		case 0x03:
			for( i = 0 ; i < 12 ; i++ )
			{
				RamRead32A( UsStrAdr + i , &UlMsgTmp[i] );
			}
			
			RamWrite32A( ms1aa	, 0x3F7FD5DC ) ;		// HPF 5Hz
			RamWrite32A( ms1ab	, 0xBF7FD5DC ) ;
			RamWrite32A( ms1ac	, 0x3F7FABB9 ) ;
			RamWrite32A( ms1ba	, 0x3E34D594 ) ;		// LPF 1600Hz
			RamWrite32A( ms1bb	, 0x3E34D594 ) ;
			RamWrite32A( ms1bc	, 0x3F259536 ) ;
			
			RamWrite32A( ms2aa	, 0x3F7FD5DC ) ;		// HPF 5Hz
			RamWrite32A( ms2ab	, 0xBF7FD5DC ) ;
			RamWrite32A( ms2ac	, 0x3F7FABB9 ) ;
			RamWrite32A( ms2ba	, 0x3E34D594 ) ;		// LPF 1600Hz
			RamWrite32A( ms2bb	, 0x3E34D594 ) ;
			RamWrite32A( ms2bc	, 0x3F259536 ) ;
			
			RegWriteA( CM_RAMDLYMOD	, 0x08 ) ;			// MS1, MS2 Clear
			RegWriteA( CM_RAMINITON	, 0x02 ) ;			// HRAM1 Clear
			WitTim( 5 ) ;
		default:
			break;
	}
}



//********************************************************************************
// Function Name 	: SetMmd
// Retun Value		: NON
// Argment Value	: Mode Select
// Explanation		: Measurement Mode Setting
// History			: First edition 						2012.02.08 Y.Kim
//********************************************************************************
void	SetMmd( unsigned char	UcMmdSwt )
{
	switch( UcMmdSwt )	{
		case 0x00:										// Measurment Setting for MR-VCM OFFSET ADJUSTMENT
			//Measurement in SineWave Mode
			RegWriteA( CM_MESSINMODE,	0x03 );			// Wait Sine Wave 0 Cross
			RegWriteA( CM_MESLOOP0,		0x30 );			// 49 Cycles
			RegWriteA( CM_MESLOOP1,		0x00 );			// 49 Cycles
			RegWriteA( CM_MES1ADD,		0x7E );			// CmMes1Add = AD2OFFZ
			RegWriteA( CM_MES2ADD,		0x7F );			// CmMes2Add = AD3OFFZ
			RegWriteA( CM_MES3ADD,		0x28 );
			RegWriteA( CM_MESABS,		0x00 );			// ABS Disable
			//RegWriteA( CM_MESHIST1ADD,	0x16 );		// A MAX	
			//RegWriteA( CM_MESHIST2ADD,	0x26 );		// A MIN
			//RegWriteA( CM_MESHIST3ADD,	0x56 );		// B MAX
			//RegWriteA( CM_MESHIST4ADD,	0x66 );		// B MIN
			//RegWriteA( CM_MESHISTMOD,	0x01 );			// MES History Mode
			RamWrite32A( msmean	, 0x3CA72EAE );			// 1/49Cycles
			break;
		case 0x01:										// Measurment Setting for MR-VCM LOOPGAIN ADJUSTMENT
			//AF Measurement in Normal Mode
			RegWriteA( CM_MESSINMODE, 0x10 );			// Wait Sine Wave 0 Cross
			RegWriteA( CM_MESLOOP0	, 0x90 );			// 400 Sampling
			RegWriteA( CM_MESLOOP1	, 0x01 );			// 400 Sampling
			RegWriteA( CM_MES1ADD	, 0x5B );			// CmMes1Add = AFG3Z
			RegWriteA( CM_MES2ADD	, 0x5A );			// CmMes2Add = AFG2Z
			RegWriteA( CM_MES3ADD	, 0x28 );
			RegWriteA( CM_MESABS	, 0x11 );			// ABS Disable
			RamWrite32A( msmean	, 0x3F800000 );			// Cumulative addition value measurement
			break;
		case 0x02:										// Measurment Setting for HALL-VCM LOOPGAIN ADJUSTMENT
			//GL Measurement in Normal Mode
			RegWriteA( CM_MESSINMODE, 0x10 );			// Wait Sine Wave 0 Cross
			RegWriteA( CM_MESLOOP0	, 0x90 );			// 400 Sampling
			RegWriteA( CM_MESLOOP1	, 0x01 );			// 400 Sampling
			RegWriteA( CM_MES1ADD	, 0x1B );			// CmMes1Add = GLG3Z
			RegWriteA( CM_MES2ADD	, 0x1A );			// CmMes2Add = GLG2Z
			RegWriteA( CM_MES3ADD	, 0x28 );
			RegWriteA( CM_MESABS	, 0x11 );			// ABS Disable
			RamWrite32A( msmean	, 0x3F800000 );			// Cumulative addition value measurement
			break;
		default:
			break;
	}
}



//*************************************************************************************************
// HALL-VCM(IRIS)
//*************************************************************************************************
//********************************************************************************
// Function Name 	: TneRun
// Retun Value		: NON
// Argment Value	: NON
// Explanation		: Hall Adjustment Excute Function
// History			: First edition 						2012.02.08 Y.Kim
//********************************************************************************
void	TneRun ( void )
{
	UcTofRst	= 1;
	UcTbiRst	= 1;
	UcTneRst	= 1;
	
	printf("TneRun..............\n");
	RegWriteA( 0x000C	, 0x00 );
	TnePtp();
	printf("TnePtp..............\n");
	TneCen();
	printf("TneCen..............\n");
	RegWriteA( 0x000C	, 0x07 );
}



//********************************************************************************
// Function Name 	: TneCen
// Retun Value		: NON
// Argment Value	: NON
// Explanation		: Hall-Signal Offset&Bias Adjustment Function
// History			: First edition 						2012.02.08 Y.Kim
//********************************************************************************
void	TneCen ( void )
{
	unsigned char	UcCntFlg ;
	UnFltVal		UlOffMrg ;
	UnFltVal		UlBiaMrg ;
	
	UlOffMrg.SfFltVal	= OFFSET_MARGIN ;
	UlBiaMrg.SfFltVal	= BIAS_MARGIN ;
	
	UcCntFlg	= 1;
	
	while( UcTneRst && UcCntFlg ){
		switch( UcTneRst )
		{
			case 0 :
				printf("Case Zero..............\n");
				break;
			case 1 :
			         printf("Case One..............\n");
				//UcTofRst	= TneOff();
				UcTofRst	= TngAdj( H_DAV1, OFFSET_DIV, UlHalCen );      // At first  // H_DAV1(0x0079) => Offset DAC ;  OFFSET_DIV = )(0.0078125F) => configure value ; UIHalCen => current center value
				TnePtp() ;
				UcCntFlg++;
				if( UcTofRst == 0 ){			// Offset Adjustment OK?
					UcTneRst = 2 ;				// YES	: Bias ADJ
				} else {
					UcTneRst = 1 ;				// NO	: Offset ADJ
				}
				break;
			case 2 :
			        printf("Case Two..............\n");
				if( (UlTgtDif.SfFltVal < UlBiaMrg.SfFltVal)  && (UlTgtDif.SfFltVal > -UlBiaMrg.SfFltVal) ){ // Bias OK?
					UcTneRst = 0 ;				// YES	: Adjustment Finish
				}else{
					UcTneRst = 3 ;				// NO	: Bias ADJ
				}
				break;
			case 3 :
				//UcTbiRst	= TneBia();
				printf("Case Three..............\n");
				UcTbiRst	= TngAdj( H_DAV4, BIAS_DIV, UlTgtDif );      // BIAS     (H_DAV4 = 0x007C,  BIAS_DIV)
				TnePtp() ;
				UcCntFlg++;
				if( UcTbiRst == 0 ){			// Bias Adjustment OK?
					UcTneRst = 4 ;				// YES	: ADJ Result Check
				} else {
					UcTneRst = 1 ;				// NO	: Offset ADJ
				}
				break;
			case 4 :
			        printf("Case Four..............\n");
				if( (UlHalCen.SfFltVal < UlOffMrg.SfFltVal) && (UlHalCen.SfFltVal > -UlOffMrg.SfFltVal) ){ // Offset OK?
					UcTneRst = 0 ;				// YES	: Adjustment Finish
				} else {
					UcTneRst = 1 ;				// NO	: Offset ADJ
				}
				break;
			default:
				break;
		}
		
		//RamWrite32A( 0x1079	, UcCntFlg );
		if( ( UcCntFlg - 1 ) >= ADJ_COUNT ){
			UcCntFlg = 0;
		}
		printf("\nCase Switch..............\n");
	}
}


//********************************************************************************
// Function Name 	: TnePtp
// Retun Value		: NON
// Argment Value	: NON
// Explanation		: Hall-Signal Peak to Peak Measure Function
// History			: First edition 						2012.02.08 Y.Kim
//********************************************************************************
void TnePtp( void )
{
	//RamWrite32A( GL2PWMZ	, 0xBF800000 );
	RamWrite32A( GL2PWMZ	, 0x3F800000 );
	WitTim(50);
	RamRead32A( AD1Z	, &UlHalMax.UlLngVal );
	
	printf("UlHalMax.UlLngVal=%x\n",UlHalMax.UlLngVal);
	
	RamWrite32A( GL2PWMZ	, 0xBF800000 );
	//RamWrite32A( GL2PWMZ	, 0x3F800000 );
	WitTim(50);
	RamRead32A( AD1Z	, &UlHalMin.UlLngVal );
	printf("UlHalMin.UlLngVal=%x\n",UlHalMin.UlLngVal);
	
	
	UlHalSum.SfFltVal = UlHalMax.SfFltVal + UlHalMin.SfFltVal ;		
	
	if (UlHalMax.SfFltVal > 0) {
	    UlHalPtp.SfFltVal = (UlHalMax.SfFltVal - UlHalMin.SfFltVal)/2 ;		// Hall Signal Amplitude    (All Pluse side)
	}else{
	    UlHalPtp.SfFltVal = (UlHalMin.SfFltVal - UlHalMax.SfFltVal)/2 ;		// Hall Signal Amplitude    (All Pluse side)
	}
	UlHalCen.SfFltVal = UlHalSum.SfFltVal / 2 ;						// Hall Signal Center
	
	
	printf("UlHalPtp.UlLngVal=%x\n",UlHalPtp.UlLngVal);
	printf("UlHalCen.UlLngVal =%x\n",UlHalCen.UlLngVal );
	
	UlTgtPtp.UlLngVal	= TGT_PTP ;									// Target Hall Amplitude
	printf("UlTgtPtp.UlLngVal=%x\n",UlTgtPtp.UlLngVal );
//	printf("UlTgtPtp.SfFltVal=%x\n",UlTgtPtp.SfFltVal );
//	UlTgtPtp.SfFltVal = TGT_PTP;
//	printf("UlTgtPtp.SfFltVal=%x\n",UlTgtPtp.SfFltVal );
	
	UlTgtDif.SfFltVal	= UlHalPtp.SfFltVal -  UlTgtPtp.SfFltVal;	// Current Target Amplitude
	printf("UlTgtDif.UlLngVal=%x\n",UlTgtDif.UlLngVal );
}



//********************************************************************************
// Function Name 	: AdjHlg
// Retun Value		: NON
// Argment Value	: NON
// Explanation		: Hall-VCM Servo Loopgaine Adjustment Function
// History			: First edition 						2012.02.08 Y.Kim
//********************************************************************************
void	AdjHlg ( void )
{
	UnFltVal	UlMs1Cum			= {0x00000000};
	UnFltVal	UlMs2Cum			= {0x00000000};
	UnFltVal	UlM12Div			= {0x00000000};
	UnFltVal	UlCrtLpg			= {0x00000000};
	
	unsigned char	UcAsmTmp, UcMa1Tmp, UcMa3Tmp, UcGsmTmp, UcVscTmp ;
	
	RegReadA( GL_STPMVMOD	, &UcGsmTmp ) ;
	RegReadA( AF_STPMVMOD	, &UcAsmTmp );
	RegReadA( CM_MES1ADD	, &UcMa1Tmp );
	RegReadA( CM_MES3ADD	, &UcMa3Tmp );
	RegReadA( GL_STPMVEXEMOD	, &UcVscTmp ) ;
	
	RegWriteA( GL_STPMVEXEMOD	, 0x00 );
	RegWriteA( GL_STPMVMOD	, 0x00 ) ;
	RegWriteA( AF_STPMVMOD	, 0x00 );
	
	SetSin( 0x03 );										// Sine Wave Setting
	SetSin( 0x04 );										// Sine Wave On
	
	SetMsf( 0x03 );										// Set MS Filter For Through(or HPF)
	SetMmd( 0x02 );										// Normal mode
	
	WitTim( 1000 );
	RegWriteA( CM_MESMODE,	0x01 );					// Start Measurement
	WitClr( CM_MESMODE, 0x01 , 0 );
	
	RamRead32A( MSABS1AV	, &UlMs1Cum.UlLngVal );
	RamRead32A( MSABS2AV	, &UlMs2Cum.UlLngVal );
	RamRead32A( glg2		, &UlCrtLpg.UlLngVal );
	
	UlM12Div.SfFltVal	= UlMs1Cum.SfFltVal / UlMs2Cum.SfFltVal;
	UlCrtLpg.SfFltVal	= UlCrtLpg.SfFltVal * UlM12Div.SfFltVal;
	
	RamWrite32A( glg2 , UlCrtLpg.UlLngVal );
	
	SetSin( 0x05 );
	
	WitTim(30);
	SetMsf( 0x00 );
	RegWriteA( CM_MES1ADD	, UcMa1Tmp );				// CmMes1Add = AFSTMZ2
	RegWriteA( CM_MES3ADD	, UcMa3Tmp );
	
	WitTim(30);
	RegWriteA( AF_STPMVMOD	, UcAsmTmp );
	RegWriteA( GL_STPMVMOD	, UcGsmTmp ) ;
	RegWriteA( AF_STPMVEXEMOD	, UcVscTmp ) ;
}



//********************************************************************************
// Function Name 	: TngAdj
// Retun Value		: NON
// Argment Value	: D/A Register Address, Adjustment DIV, Reference Data
// Explanation		: Signal Offset/Bias Adjustment Function
// History			: First edition 						2012.02.08 Y.Kim
//********************************************************************************
unsigned char TngAdj( unsigned char UcRegAdr , float SfSigDiv , UnFltVal UlRefDat )
{
	unsigned char	UcLevStt ;							// Adjustment State
	unsigned char	UcRedLev ;							// D/A Read Data
	signed long		SlRedLev ;							// D/A Read Data
	signed long		SlAdjLev ;							// Adjust Value
	
	// Rounding Off
	UnFltVal		UlLevVal ;
	UnFltVal		UlLevQuo ;
	UnFltVal		UlLevRem ;
	signed char		ScResCmp ;
	
	UcLevStt	= 0x00;									// State Clear
	
	RegReadA(  UcRegAdr	,  &UcRedLev );
	SlRedLev	= UcRedLev;
	
	printf("UlRefDat =%x\n",UlRefDat  );
	printf("UcRedLev=%x\n",UcRedLev );
	printf("SlRedLev=%x\n",SlRedLev );
	
	UlLevVal.SfFltVal	= UlRefDat.SfFltVal / SfSigDiv ;
	UlLevQuo.SfFltVal	= ( signed long )( UlLevVal.SfFltVal ) ;
	UlLevRem.SfFltVal	= UlLevVal.SfFltVal - UlLevQuo.SfFltVal ;
	
	// Overflow handling 1
	if( UlLevQuo.SfFltVal > 254 ){
		UlLevQuo.SfFltVal	= 255 ;
		ScResCmp = 0 ;
	}else if( UlLevQuo.SfFltVal < -254 ){
		UlLevQuo.SfFltVal	= -255 ;
		ScResCmp = 0 ;
	}else{
		// Rounding off to the nearest integer   
		if( UlLevRem.SfFltVal > 0){
			if( UlLevRem.SfFltVal >= 0.5F ){
				ScResCmp = 1 ;
			}else if( UlLevRem.SfFltVal < 0.5F ){
				ScResCmp = 0 ;
			}
		}else if( UlLevRem.SfFltVal < 0 ){
			if( UlLevRem.SfFltVal <= -0.5F ){
				ScResCmp = -1 ;
			}else if( UlLevRem.SfFltVal > -0.5F ){
				ScResCmp = 0 ;
			}
		} else {
			ScResCmp = 0 ;
		}
	}
	
	SlAdjLev	= UlLevQuo.SfFltVal + ScResCmp ;
	printf("SIAdjLev=%x\n",SlAdjLev );
	
	printf("SlRedLev=%x\n", SlRedLev);
	
	// Overflow Handling 2
	if( ( SlRedLev - SlAdjLev ) >= 255 ){
		UcRedLev	= 255 ;
	}else if( ( SlRedLev - SlAdjLev ) <= 0 ){
		UcRedLev	= 0 ;
	}else{
		UcRedLev	-= ( signed char )( SlAdjLev );
		//UcRedLev	-= ( (signed char)( UlLevVal.SfFltVal ) + ScResCmp ) ;
	}
	
	printf("UcRedLev=%x\n", UcRedLev);
	
	RegWriteA(  UcRegAdr	, UcRedLev );
	
	if( (signed char)( UlLevVal.SfFltVal ) != 0 ){ UcLevStt	|= 0x10 ; }		//Quo = 0     
	if( ScResCmp != 0 ){ UcLevStt	|= 0x01 ; }						//Rem = 0　　
	
	return	UcLevStt ;
}
#endif



//*************************************************************************************************
// STM3ch & HALL-VCM(IRIS)
//*************************************************************************************************
//********************************************************************************
// Function Name 	: ActTp1
// Retun Value		: NON
// Argment Value	: NON
// Explanation		: Actuator Test Pattern1
// History			: First edition 						2012.02.08 Y.Kim
//********************************************************************************
void	ActTp1( void )
{
	unsigned char	UcMonBta, UcMonBtb, UcMonBtc, UcMonBtd ;
	
	unsigned char	UcPc2Rga, UcPc2Rgb, UcPc2Rgc ;
	unsigned char	UcLctR1a, UcLctR2a, UcLctR3a ;
	unsigned char	UcLctR1b, UcLctR2b, UcLctR3b ;
	unsigned char	UcLctR1c, UcLctR2c, UcLctR3c ;
	
	//unsigned long	UlLmtCha	= 0x00033000;
	//unsigned long	UlLmtChb	= 0x0001C800;
	//unsigned long	UlLmtChc	= 0x00011000;
	
	//UnFltVal	UlStmZ2g	= {0x00000000};						// Current Position
	static	UnFltVal	UlStmTgt	= {0x00000000};				// Target Position
	static	UnFltVal	UlTgtInc	= {0x00000000};				// Target Increase
	static	UnFltVal	UlSmvSiz	= {0x00000000};				// StepMove Size
	//UnFltVal	UlStmSiz	= {0x00000000};						// StepMove Size
	
	switch( UcPt1Flg ) {
		case 0 :
			break;
		case 1 :
			if( UcVs1Flg == 1 ){
				//Ch A
				RegReadA( 0x0102	, &UcPc2Rga );
				UcPc2Rga	&= 0x7F ; 					//CW
				RegWriteA( 0x0102	, UcPc2Rga ) ;
				RegWriteA( 0x010E	, 0x01 );
				//Ch B
				RegReadA( 0x0142	, &UcPc2Rgb );
				UcPc2Rgb	&= 0x7F ; 					//CW
				RegWriteA( 0x0142	, UcPc2Rgb ) ;
				RegWriteA( 0x014E	, 0x01 );
				
				//Ch C                                                                               //addede by sha  
				RegReadA( 0x0182	, &UcPc2Rgc );
				UcPc2Rgc	&= 0x7F ; 					//CW
				RegWriteA( 0x0182	, UcPc2Rgb ) ;
				RegWriteA( 0x018E	, 0x01 );				
				
				//Ch D
				UlStmTgt.UlLngVal = 0x00000000;
				UlTgtInc.UlLngVal = 0x3D400000;
				UlSmvSiz.UlLngVal = 0x3A51B717;
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );
				
				UcPt1Flg	= 2 ;
			}
			break;
		case 2 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 3 ;
			}
			break;
		case 3 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				RegWriteA( 0x014E	, 0x01 );					//Ch C
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 4 ;
			}
			break;
		case 4 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 5 ;
			}
			break;
		case 5 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 6 ;
			}
			break;
		case 6 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 7 ;
			}
			break;
		case 7 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 ); //Ch D
				UcPt1Flg	= 8 ;
			}
			break;
		case 8 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 9 ;
			}
			break;
		case 9 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 10 ;
			}
			break;
		case 10 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 11 ;
			}
			break;
		case 11 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 12 ;
			}
			break;
		case 12 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 13 ;
			}
			break;
		case 13 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 14 ;
			}
			break;
		case 14 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 15 ;
			}
			break;
		case 15 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 16 ;
			}
			break;
		case 16 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 17 ;
			}
			break;
		case 17 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 18 ;
			}
			break;
		case 18 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 19 ;
			}
			break;
		case 19 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 20 ;
			}
			break;
		case 20 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 21 ;
			}
			break;
		case 21 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 22 ;
			}
			break;
		case 22 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 23 ;
			}
			break;
		case 23 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 24 ;
			}
			break;
		case 24 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 25 ;
			}
			break;
		case 25 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 26 ;
			}
			break;
		case 26 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 27 ;
			}
			break;
		case 27 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 28 ;
			}
			break;
		case 28 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 29 ;
			}
			break;
		case 29 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 30 ;
			}
			break;
		case 30 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 31 ;
			}
			break;
		case 31 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 32 ;
			}
			break;
		case 32 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 33 ;
			}
			break;
		case 33 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 34 ;
			}
			break;
		case 34 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 35 ;
			}
			break;
		case 35 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 36 ;
			}
			break;
		case 36 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 37 ;
			}
			break;
		case 37 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 38 ;
			}
			break;
		case 38 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 39 ;
			}
			break;
		case 39 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				RegReadA( 0x0182	, &UcPc2Rgc );
				UcPc2Rgc	&= 0x7F ; 							//CW
				RegWriteA( 0x0182	, UcPc2Rgc ) ;
				RegWriteA( 0x018E	, 0x01 );					//Ch C
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 40 ;
			}
			break;
		case 40 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 41 ;
			}
			break;
		case 41 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 42 ;
			}
			break;
		case 42 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 43 ;
			}
			break;
		case 43 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 44 ;
			}
			break;
		case 44 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 45 ;
			}
			break;
		case 45 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 46 ;
			}
			break;
		case 46 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 47 ;
			}
			break;
		case 47 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 48 ;
			}
			break;
		case 48 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 49 ;
			}
			break;
		case 49 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 50 ;
			}
			break;
		case 50 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 51 ;
			}
			break;
		case 51 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 52 ;
			}
			break;
		case 52 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 53 ;
			}
			break;
		case 53 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 54 ;
			}
			break;
		case 54 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 55 ;
			}
			break;
		case 55 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 56 ;
			}
			break;
		case 56 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 57 ;
			}
			break;
		case 57 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 58 ;
			}
			break;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case 58 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 59 ;
			}
			break;
		case 59 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegReadA( 0x0142	, &UcPc2Rgb );
				UcPc2Rgb	|= 0x80 ; 						//CCW
				RegWriteA( 0x0142	, UcPc2Rgb ) ;
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				
				UcPt1Flg	= 60 ;
			}
			break;
		case 60 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 61 ;
			}
			break;
		
		case 61 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 62 ;
			}
			break;
		case 62 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 63 ;
			}
			break;
		case 63 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 64 ;
			}
			break;
		case 64 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 65 ;
			}
			break;
		case 65 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 66 ;
			}
			break;
		case 66 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 67 ;
			}
			break;
		case 67 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 68 ;
			}
			break;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case 68 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 69 ;
			}
			break;
		case 69 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );					//Ch A
				RegWriteA( 0x014E	, 0x01 );					//Ch B
				UlStmTgt.UlLngVal = 0xBF4C0000;
				UlTgtInc.UlLngVal = 0x00000000;
				UlSmvSiz.UlLngVal = 0x38D1B717;
				VcmDrg( UlStmTgt , UlTgtInc, UlSmvSiz , 0x02 );	//Ch D
				UcPt1Flg	= 70 ;
			}
			break;
		case 70 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 71 ;
			}
			break;
		case 71 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 72 ;
			}
			break;
		case 72 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 73 ;
			}
			break;
		case 73 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 74 ;
			}
			break;
		case 74 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 75 ;
			}
			break;
		case 75 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 76 ;
			}
			break;
		case 76 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 77 ;
			}
			break;
		case 77 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 78 ;
			}
			break;
		case 78 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 79 ;
			}
			break;
		case 79 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 80 ;
			}
			break;
		case 80 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 81 ;
			}
			break;
		case 81 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 82 ;
			}
			break;
		case 82 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 83 ;
			}
			break;
		case 83 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 84 ;
			}
			break;
		case 84 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 85 ;
			}
			break;
		case 85 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 86 ;
			}
			break;
		case 86 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 87 ;
			}
			break;
		case 87 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 88 ;
			}
			break;
		case 88 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 89 ;
			}
			break;
		case 89 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 90 ;
			}
			break;
		case 90 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 91 ;
			}
			break;
		case 91 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 92 ;
			}
			break;
		case 92 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 93 ;
			}
			break;
		case 93 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 94 ;
			}
			break;
		case 94 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 95 ;
			}
			break;
		case 95 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 96 ;
			}
			break;
		case 96 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 97 ;
			}
			break;
		case 97 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 98 ;
			}
			break;
		case 98 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 99 ;
			}
			break;
		case 99 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 100 ;
			}
			break;
		case 100 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 101 ;
			}
			break;
		case 101 :
			if( UcVs1Flg == 1 ){
				RegWriteA( 0x010E	, 0x01 );				//Ch A
				RegWriteA( 0x014E	, 0x01 );				//Ch B
				UcPt1Flg	= 102 ;
			}
			break;
		case 102 :
			if( UcVs1Flg == 1 ){
				UcPt1Flg	= 103 ;
			}
			break;
		//Return To Base Position
		case 103 :
			if( UcVs1Flg == 1 ){
				RegReadA( 0x0102	, &UcPc2Rga ) ;
				RegReadA( 0x0142	, &UcPc2Rgb ) ;
				RegReadA( 0x0182	, &UcPc2Rgc ) ;
				RegReadA( 0x010E	, &UcMonBta );
				RegReadA( 0x014E	, &UcMonBtb );
				RegReadA( 0x018E	, &UcMonBtc );
				RegReadA( 0x000D	, &UcMonBtd );
				
				if( UcMonBta | UcMonBtb | UcMonBtc | UcMonBtd ){
					UcPt1Flg	= 103 ;
				} else {
					RegReadA( A_LCTR1	, &UcLctR1a );
					RegReadA( A_LCTR2	, &UcLctR2a );
					RegReadA( A_LCTR3	, &UcLctR3a );
					RegReadA( B_LCTR1	, &UcLctR1b );
					RegReadA( B_LCTR2	, &UcLctR2b );
					RegReadA( B_LCTR3	, &UcLctR3b );
					RegReadA( C_LCTR1	, &UcLctR1c );
					RegReadA( C_LCTR2	, &UcLctR2c );
					RegReadA( C_LCTR3	, &UcLctR3c );
					
					RegWriteA( A_MDIS1	, (unsigned char)(UcLctR2a << 4 | UcLctR1a >> 4) );
					RegWriteA( A_MDIS2	, (unsigned char)(UcLctR3a << 4 | UcLctR2a >> 4) );
					
					RegWriteA( B_MDIS1	, (unsigned char)(UcLctR2b << 4 | UcLctR1b >> 4) );
					RegWriteA( B_MDIS2	, (unsigned char)(UcLctR3b << 4 | UcLctR2b >> 4) );
					
					RegWriteA( C_MDIS1	, (unsigned char)(UcLctR2c << 4 | UcLctR1c >> 4) );
					RegWriteA( C_MDIS2	, (unsigned char)(UcLctR3c << 4 | UcLctR2c >> 4) );
					
					RamWrite32A( 0x1027	, 0xBF4C0000 );		//Base Position
					RamWrite32A( 0x122F	, 0x38D1B717 );
					
					UcPc2Rga	|= 0x80 ;
					UcPc2Rgb	|= 0x80 ;
					UcPc2Rgc	|= 0x80 ;
					RegWriteA( 0x0102	, UcPc2Rga );
					RegWriteA( 0x0142	, UcPc2Rgb );
					RegWriteA( 0x0182	, UcPc2Rgc );
					
					RegWriteA( A_TRIG	, 0x01 );
					RegWriteA( B_TRIG	, 0x01 );
					RegWriteA( C_TRIG	, 0x01 );
					RegWriteA( GL_STPMV	, 0x01 );
					UcPt1Flg	= 104 ;
				}
			}
			break;
		case 104 :
			if( UcVs1Flg == 1 ){
				RegReadA( 0x010E	, &UcMonBta );
				RegReadA( 0x014E	, &UcMonBtb );
				RegReadA( 0x018E	, &UcMonBtc );
				
				if( UcMonBta | UcMonBtb | UcMonBtc ){
					UcPt1Flg	= 104 ;
				} else {
					RegWriteA( A_MDIS1	, (unsigned char)(INI_A_MDIS) );
					RegWriteA( A_MDIS2	, (unsigned char)(INI_A_MDIS >> 8) );
					RegWriteA( B_MDIS1	, (unsigned char)(INI_B_MDIS) );
					RegWriteA( B_MDIS2	, (unsigned char)(INI_B_MDIS >> 8) );
					RegWriteA( C_MDIS1	, (unsigned char)(INI_C_MDIS) );
					RegWriteA( C_MDIS2	, (unsigned char)(INI_C_MDIS >> 8) );
					UcPt1Flg	= 0 ;
				}
				
			}
		default:
			break;
	}
}



//********************************************************************************
// Function Name 	: ActTp2
// Retun Value		: NON
// Argment Value	: NON
// Explanation		: Aging Test Pattern1
// History			: First edition 						2012.04.05 Y.Kim
//********************************************************************************
void ActTp2( void )
{
	//unsigned char	UcPc2Rgb ;
	unsigned char	UcSpdHig, UcSpdLow ;
	unsigned char	UcDisHig, UcDisLow ;
	static unsigned short	UsCurDis , UsCurSpd ;
	
	switch( UcPt2Flg ) {
		case 0 :
			break;
		case 1 :
			RegReadA( B_MSPD1 , &UcSpdLow );
			RegReadA( B_MSPD2 , &UcSpdHig );
			//RegReadA( B_MDIS1 , &UcDisLow );
			//RegReadA( B_MDIS2 , &UcDisHig );
			RegReadA( 0x008D , &UcDisLow );				//Setting a distance with Interrupt mask register
			RegReadA( 0x008E , &UcDisHig );
			UsCurSpd = ( UcSpdHig << 8) | UcSpdLow ;
			UsCurDis = ( UcDisHig << 8) | UcDisLow ;
			if( UsCurDis == 0xFFFF ){
				UsCurDis = 0 ;
			}
			UcPt2Flg += 1;
			break;
		case 2 :
			if( UcVs1Flg == 1 ){
				StmDrb( CW_DIR, UsCurSpd, UsCurDis ) ;
				UcPt2Flg += 1;
			}
			break;
		case 3 :
			if( UcVs1Flg == 1 ){
				StmDrb( CCW_DIR, UsCurSpd, UsCurDis*2 ) ;
				UcPt2Flg += 1;
			}
			break;
		case 4 :
			if( UcVs1Flg == 1 ){
				
				UcPt2Flg += 1;
			}
			break;
		case 5 :
			if( UcVs1Flg == 1 ){
				StmDrb( CW_DIR, UsCurSpd, UsCurDis ) ;
				UcPt2Flg += 1;		
			}
			break;
		case 6:
			if( UcVs1Flg == 1 ){
				
				UcPt2Flg = 2;
				//UcPt2Flg += 1;		
			}
			break;
		default:
			break;
	}
}



//********************************************************************************
// Function Name 	: ActTp3
// Retun Value		: NON
// Argment Value	: NON
// Explanation		: Aging Test Pattern2
// History			: First edition 						2012.04.05 Y.Kim
//********************************************************************************
void ActTp3( void )
{
	//unsigned char	UcPc2Rgb ;
	unsigned char	UcSpdHig, UcSpdLow ;
	unsigned char	UcDisHig, UcDisLow ;
	static unsigned short	UsCurDis , UsCurSpd ;
	
	switch( UcPt3Flg ) {
		case 0 :
			break;
		case 1 :
			RegReadA( B_MSPD1 , &UcSpdLow );
			RegReadA( B_MSPD2 , &UcSpdHig );
			//RegReadA( B_MDIS1 , &UcDisLow );
			//RegReadA( B_MDIS2 , &UcDisHig );
			RegReadA( 0x008D , &UcDisLow );				//Setting a distance with Interrupt mask register
			RegReadA( 0x008E , &UcDisHig );
			UsCurSpd = ( UcSpdHig << 8) | UcSpdLow ;
			UsCurDis = ( UcDisHig << 8) | UcDisLow ;
			if( UsCurDis == 0xFFFF ){
				UsCurDis = 0 ;
			}
			UcPt3Flg += 1;
			break;
		case 2 :
			if( UcVs1Flg == 1 ){
				StmDrb( CW_DIR, UsCurSpd, UsCurDis ) ;
				UcPt3Flg += 1;
			}
			break;
		case 3 :
			if( UcVs1Flg == 1 ){
				
				UcPt3Flg += 1;
			}
			break;
		case 4 :
			if( UcVs1Flg == 1 ){
				StmDrb( CCW_DIR, UsCurSpd, UsCurDis*2 ) ;
				UcPt3Flg += 1;
			}
			break;
		case 5 :
			if( UcVs1Flg == 1 ){
				
				UcPt3Flg += 1;
			}
			break;
		case 6 :
			if( UcVs1Flg == 1 ){
				StmDrb( CW_DIR, UsCurSpd, UsCurDis ) ;
				//UcPt3Flg += 1;
				UcPt3Flg = 2;		
			}
			break;
		default:
			break;
		}
}



//********************************************************************************
// Function Name 	: VcmDrg
// Retun Value		: NON
// Argment Value	: NON
// Explanation		: H-VCM Driver
// History			: First edition 						2012.04.05 Y.Kim
//********************************************************************************
unsigned char	VcmDrg( UnFltVal UlTgtPos, UnFltVal UlTgtInc, UnFltVal UlSmvSiz, unsigned char UcSmvItv )
{
	UnFltVal	UlStmZ2g;
	
	if( UlTgtInc.UlLngVal == 0x00000000 ){
		RegWriteA( GL_DWNSMP2	, UcSmvItv ) ;							// Set StepMove Interval
		RamWrite32A( GLSTMSTP	, UlSmvSiz.UlLngVal );					// Set StepMove Size
		
		RamWrite32A( GLSTMTGT	, UlTgtPos.UlLngVal );					// Set Target Position
		RegWriteA( GL_STPMV	, 0x01 );// Enable Move Register 0x000D				// Go
	}
	else
	{
		RegWriteA( GL_DWNSMP2	, UcSmvItv ) ;							// Set StepMove Interval
		RamWrite32A( GLSTMSTP	, UlSmvSiz.UlLngVal );					// Set StepMove Size
		
		//RamWrite32A( 0x1072 , UlTgtPos.UlLngVal );
		//RamWrite32A( 0x1073 , UlTgtInc.UlLngVal );
		
		RamRead32A( GLSTMZ2		, &UlStmZ2g.UlLngVal ) ;				// Get Current Position
		
		//RamWrite32A( 0x1074 , UlStmZ2g.UlLngVal );
		
		UlStmZ2g.SfFltVal	+= UlTgtInc.SfFltVal ;	// Cal Target Postion
		
		//RamWrite32A( 0x1075 , UlStmZ2g.UlLngVal );
		
		
		RamWrite32A( GLSTMTGT	, UlStmZ2g.UlLngVal );					// Set Target Position
		RegWriteA( GL_STPMV	, 0x01 );									// Go
	}
	printf("VCMDrg Finished\n");
	return 1;
}



//********************************************************************************
// Function Name 	: StmDra
// Retun Value		: NON
// Argment Value	: NON
// Explanation		: STM Channel-A Driver
// History			: First edition 						2012.04.05 Y.Kim
//********************************************************************************
unsigned char	StmDra( unsigned char UcSetDir, unsigned short UsSetSpd, unsigned short UsSetDis )
{
	unsigned char	UcPc2Rga;
	
	RegReadA( A_PC2 , &UcPc2Rga );
	if( UcSetDir == CW_DIR ){
		UcPc2Rga	&= 0x7F ;
	}else{
		UcPc2Rga	|= 0x80 ;
	}
	
	RegWriteA( A_PC2 , UcPc2Rga );
	RegWriteA( A_MSPD1 , (unsigned char)( UsSetSpd ) );
	RegWriteA( A_MSPD2 , (unsigned char)( UsSetSpd >> 8 ) ) ;
	if( UsSetDis != 0 ){
		RegWriteA( A_MDIS1 , (unsigned char)( UsSetDis ) ) ;
		RegWriteA( A_MDIS2 , (unsigned char)( UsSetDis >> 8 ) ) ;
	}
	RegWriteA( A_TRIG , 0x01 );			//Ch A
	
	return 1;
}



//********************************************************************************
// Function Name 	: StmDrb
// Retun Value		: NON
// Argment Value	: NON
// Explanation		: STM Channel-B Driver
// History			: First edition 						2012.04.05 Y.Kim
//********************************************************************************
unsigned char	StmDrb( unsigned char UcSetDir, unsigned short UsSetSpd, unsigned short UsSetDis )
{
	unsigned char	UcPc2Rgb;
	
	RegReadA( B_PC2 , &UcPc2Rgb );
	if( UcSetDir == CW_DIR ){
		UcPc2Rgb	&= 0x7F ;
	}else{
		UcPc2Rgb	|= 0x80 ;
	}
	
	RegWriteA( B_PC2 , UcPc2Rgb );
	RegWriteA( B_MSPD1 , (unsigned char)( UsSetSpd ) ) ;
	RegWriteA( B_MSPD2 , (unsigned char)( UsSetSpd >> 8 ) ) ;
	if( UsSetDis != 0 ){
		RegWriteA( B_MDIS1 , (unsigned char)( UsSetDis ) ) ;
		RegWriteA( B_MDIS2 , (unsigned char)( UsSetDis >> 8 ) ) ;
	}
	RegWriteA( B_TRIG , 0x01 );			//Ch B
	
	return 1;
}



//********************************************************************************
// Function Name 	: StmDrc
// Retun Value		: NON
// Argment Value	: NON
// Explanation		: STM Channel-C Driver
// History			: First edition 						2012.04.05 Y.Kim
//********************************************************************************
unsigned char	StmDrc( unsigned char UcSetDir, unsigned short UsSetSpd, unsigned short UsSetDis )
{
	unsigned char	UcPc2Rgc;
	
	RegReadA( C_PC2 , &UcPc2Rgc );
	if( UcSetDir == CW_DIR ){
		UcPc2Rgc	&= 0x7F ;
	}else{
		UcPc2Rgc	|= 0x80 ;
	}
	
	RegWriteA( C_PC2 , UcPc2Rgc );
	RegWriteA( C_MSPD1 , (unsigned char)( UsSetSpd ) ) ;
	RegWriteA( C_MSPD2 , (unsigned char)( UsSetSpd >> 8 ) ) ;
	if( UsSetDis != 0 ){
		RegWriteA( C_MDIS1 , (unsigned char)( UsSetDis ) ) ;
		RegWriteA( C_MDIS2 , (unsigned char)( UsSetDis >> 8 ) ) ;
	}
	RegWriteA( C_TRIG , 0x01 );			//Ch C
	
	return 1;
}


#ifndef S3_DN_MODE
//*******************************************************************************
//Function              :  DCMDri
//Rerun Value       :   NON
//Argument Value :   NON 
//Explanation        :   VCM  channel 5A/B Driver
//History                :   First  version
//*******************************************************************************
void DCMDri(void)
{
       if( UcDCMCWFlg == CW_DIR )
	{                    // CW_DIR = 0
         RegWriteA(DC1PC2, 0x01);                       //  CW_DIR
       }else{
         RegWriteA(DC1PC2, 0x81);                       //  CCW_DIR     
       }

          RegWriteA(DC1DIV, 0x3C);                        // Div
          RegWriteA(DC1PC1, 0x80);                       // Enable, Standby mode
          RegWriteA(DC1G, 0xFF);                           // PWM gain
          RegWriteA(DC1PWM, 0x7F);                    // Output Value
          RegWriteA(DC1CNT1, 0xDC);                  // Timer setting
          RegWriteA(DC1CNT2, 0x0C);                   //VCM PWM output unit
          // 4*128*64*220/12M  =  600ms
          RegWriteA(DC1TRIG, 0x01);                     // Pulse output Start 

}
#else
//*******************************************************************************
//Function			: DCMDriFil
//Rerun Value		: NON
//Argument Value	: NON 
//Explanation		: VCM  channel 5A/B Driver  (For D/N operation)
//History			: First  version
//*******************************************************************************
void DCMDriFil(void)
{
	unsigned char     UcSinOn = 0x01;

	//--------------------D/N Motor Operation--------------------//
	if( UcDCMCWFlg == CW_DIR ) 
	{									// CW_DIR = 0
		RamWrite32A( glg, 0x3F800000 ) ;
	printf("Forward\n");							// 1019     glg = (+1)
	} 
	else
	{
		RamWrite32A( glg, 0xBF800000 ) ;
		printf("Reserve\n");							// 1019     glg = (-1)
	}
	
	RegWriteA(CM_EQON, 0x01);          // 0001   EQ ON
	RegWriteA(PWMA6, 0x80);               // 0314 PWM ON
	RegWriteA(CM_SINON, 0x11);         // 0058 SIN 1wave ON
	
		//WitTim(5);
	/*
	while (UcSinOn && 0x01)
	{
		RegReadA(CM_SINON, &UcSinOn);    //
		//printf("DC motor is Running \n");
	}
	*/
	RegWriteA(PWMA6, 0x80);         //00           // PWM OFF
	RegWriteA(CM_SINON, 0x11);          //00    // EQ OFF
	printf("DCM ICcut\n");
}


void cmdDCMDriFil(void)
{
		unsigned char	UcRamIni0 = 0x02;
		unsigned char	UcRamIni1 = 0x01;
		unsigned char     UcSinOn = 0x01;

		//-----------PWM Set up for D/N  with IRIS EQ output ch7----------// 
		RegWriteA(DRVFC6, 0x00);                        // 0311
		RegWriteA(PWMFC6, 0x1D);                      // 0315
		
		//----------HRAM1 Clear----------//
		RegWriteA(CM_RAMINITON, 0x02);           // 0002
		//WitTim(5);                                                       // two fs is necessary
		while (UcRamIni0 && 0x02)
		{
			RegReadA(CM_RAMINITON, &UcRamIni0);
		}
		
		RegWriteA(CM_RAMINITON, 0x01);           // 0002
		//WitTim(5);                                                       // two fs is necessary
		while (UcRamIni1 && 0x01)
		{
			RegReadA(CM_RAMINITON, &UcRamIni1);
		}
		
		//----------------Sinve Wave Setup--------------//
		RegWriteA(CM_SINTST, 0x08);              // 0059
		RegWriteA(CM_SINGAIN, 0xFF);           // 005A
		RegWriteA(CM_SINFRQ0, 0x25);          // 005B   0.83Hz   2C=>1Hz
		RegWriteA(CM_SINFRQ1, 0x00);          // 005C
		RegWriteA(CM_SINPHSX, 0x20);          // 005D
		
		RamWrite32A(OFF1Z, 0x3F800000);    // 1234      Offset + 1
		//-----------------------Coefficient  Set up------------------------//
		RamWrite32A(afatr0, 0x00000000);      // 104F
		RamWrite32A(afbtr0, 0x00000000);      // 105F
		RamWrite32A(afmg, 0x00000000);      // 1040
		RamWrite32A(afmg2, 0x00000000);      // 1070
		/*
		//------------------Analog Monitor-------------------//
		// For debug( If needed )
		RegWriteA(H_DLYMON1, 0x2E);          // 0084    Delay Monitor 1,  GL2PWM
		RegWriteA(VSY1SEL, 0x21);                // 0230, select MONC
		RegWriteA(VSY2SEL, 0x31);                // 0231, select MOND
		RegWriteA(MONSEL, 0x40);                //  0237, MONSEL, select MONE  
		RegWriteA(MONSELC, 0x08);             //  0272, MONSELC, DASDO
		RegWriteA(MONSELD, 0x09);             //  0273, MONSELD, DASCLK
		RegWriteA(MONSELE, 0x0A);             //  0274, MONSELE, DASYNCB
		RegWriteA(DACMONFC, 0x85);          //  DACMONFC, ON, PWMCLK/2, OP=01
		*/
		//--------------------D/N Motor Operation--------------------//
		if( UcDCMCWFlg == CW_DIR ) {									// CW_DIR = 0
			RamWrite32A( glg, 0x3F800000 ) ;							// 1019     glg = (+1)
		} else {
			RamWrite32A( glg, 0xBF800000 ) ;							// 1019     glg = (-1)
		}
        RegWriteA(CM_EQON, 0x01);          // 0001   EQ ON
        RegWriteA(PWMA6, 0x80);               // 0314 PWM ON
        RegWriteA(CM_SINON, 0x11);         // 0058 SIN 1wave ON
        
         //WitTim(5);
        while (UcSinOn && 0x01)
        {
            RegReadA(CM_SINON, &UcSinOn);    //
		//printf("DC motor is Running \n");
        }

        RegWriteA(PWMA6, 0x00);                    // PWM OFF
        RegWriteA(CM_SINON, 0x00);              // EQ OFF
      	printf("DCM ICcut\n");
}

#endif




