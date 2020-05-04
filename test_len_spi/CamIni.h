//********************************************************************************
//
//		<< LC898201 Evaluation Soft >>
//	    Program Name	: CamIni.c
//		Design			: Y.Sha
//		History			: First edition	       2017.10.17 
//********************************************************************************


//**************************
//	Define
//**************************
#define		CAMINI
#define 	CAMIFT

#define		USE_OSC					// In case of use the OSC, Enable it.
									// In case of use a crystal, Disable it.

#ifndef S2_H_MODE
	#define	PI_A_POL	0x10		// CW Direction Move : PI Signal is Low -> High
	#define	PI_B_POL	0x10		// CW Direction Move : PI Signal is Low -> High
         #define	PI_C_POL	0x00		// CW Direction Move : PI Signal is High -> Low
#else
	#define	PI_A_POL	0x10		// CW Direction Move : PI Signal is Low -> High
	#define	PI_B_POL	0x00		// CW Direction Move : PI Signal is High -> Low
#endif

//Analog Setting
#define	BIAS_CURRENT_GL			0x02		// BIAS Current   0x00 : 0.5mA / 0x01 : 1.0mA / 0x02 : 1.5mA / 0x03 : 2.0mA
#define	BIAS_GL					0x80		// BIAS for 	GL(IRIS)
#define	OFFSET_GL				0x80		// OFFSET for	GL(IRIS)
#define	OPAMP_GL				0x00		// Iris VGA Gain 0x25



#ifndef S2_H_MODE
	#define	INI_A_PC2	0x19			// 512u-step Mode
	#define	INI_B_PC2	0x19			// 512u-step Mode
	#define	INI_C_PC2	0x19			// 512u-step Mode

	#define	INI_A_MSPD	0x00BA			// 1000pps Move Speed For Initialization
	#define	INI_B_MSPD	0x00BA			// 1000pps Move Speed For Initialization
	#define	INI_C_MSPD	0x0176			//  500pps Move Speed For Initialization

	#define	INI_A_MDIS	0x0100
	#define	INI_B_MDIS	0x0100
	#define	INI_C_MDIS	0x1000
#else
	#define	INI_A_PC2	0x19			// 512u-step Mode
	#define	INI_B_PC2	0x19			// 512u-step Mode
	
	#define	INI_A_MSPD	0x00BA			// 1000pps Move Speed For Initialization
	#define	INI_B_MSPD	0x0176			//  500pps Move Speed For Initialization
	
	#define	INI_A_MDIS	0x0100
	#define	INI_B_MDIS	0x1000
#endif


//**************************
//	Local Function Prottype	
//**************************
void	IniCmd( void ) ;		// Command Execute Process Initial
void	IniFil( void ) ;		// Initialize Filter
void	IniRst( void ) ;		// Software Reset
void	IniOsc( void ) ;		// Oscilator Setting
void	IniClk( void ) ;		// Clock Setting
void	IniCha( void ) ;		// Driver-Channel Setting
void	IniEqc( void ) ;		// Equalizer Clear
void	IniAna( void ) ;		// Analog Circuit Setting
void	IniMon( void ) ;		// Monitor Setting
void	IniPWM( void ) ;		// PWM Setting

void	InsCha(	void ) ;		// Stepping Channel Setting
void	InsPds(	void ) ;		// PI Detection Setting

#ifndef  S2_H_MODE
	void	InsPdx(	unsigned char, unsigned char, unsigned char ) ;		// Excute PI Detection
	void           InsPdxC (unsigned char);
#else
	void	InsPdx(	unsigned char, unsigned char ) ;		// Excute PI Detection
#endif
	void           InsPdxA (unsigned char);
	void           InsPdxB (unsigned char);

void	InsBpx(	void ) ;		// Base Position

void	IngCha(	void ) ;		// HALL-VCM Channel Setting
void	IngBpx(	void ) ;		// Base Position

#ifdef S3_DN_MODE
void	IniDN( void ) ;			// DN Initialization for Hall-VCM Channel
#endif

void	IniVsc(	void ) ;		// VSYNC Setting
