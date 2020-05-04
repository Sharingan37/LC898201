//********************************************************************************
//
//		<< LC898201 Evaluation Soft>>
//	    Program Name	: Cam.h
// 		Explanation		: LC898201 Global Declaration & ProtType Declaration
//		Design			: Y.Yamada
//		History			: First edition						2011.06.06 
//********************************************************************************
#define 	CAMIFT
#define 	S3_DN_MODE

#define	FW_VER			0x0005
//#define	S2_H_MODE		// Stepping2ch + Hall-VCM + MR-VCM Mode
#undef	S2_H_MODE		// Stepping3ch + Hall-VCM Mode
#define		S3_DN_MODE	// Stepping 3ch + DN Mode

#ifdef	CAMINI
	#define	CAMINI__
#else
	#define	CAMINI__		extern
#endif

#ifdef	CAMIFT
	#define	CAMIFT__
#else
	#define	CAMIFT__		extern
#endif

#ifdef	CAMCMD
	#define	CAMCMD__
#else
	#define	CAMCMD__		extern
#endif


#define	NOP_TIME		0.00004166F
#define		EXE_END		0x02		// Execute End (Adjust OK)

// Buffer Size
#define		RCVBUFSIZE	14
#define     SNDBUFSIZE	14


struct STMHLREG {
	unsigned short	UsRegAdd ;
	unsigned char	UcRegDat ;
} ;													// Hall Register Data Table

struct STMHLFIL {
	unsigned short	UsRamAdd ;
	unsigned long	UlRamDat ;
} ;	

struct STCMDTBL
{
	unsigned short Cmd ;
	unsigned int UiCmdStf ;
	void ( *UcCmdPtr )( void ) ;
} ;



// Float Data Union
union	FLTVAL {
	float			SfFltVal ;
	unsigned long	UlLngVal ;
	unsigned short	UsDwdVal[ 2 ] ;
	struct {
		unsigned short	UsLowVal ;
		unsigned short	UsHigVal ;
	} StFltVal ;
} ;

typedef union FLTVAL	UnFltVal ;



CAMIFT__ unsigned char	UcCmdStp ;								// Command Execute Phase
CAMIFT__ unsigned char	UcRcvPtr ;								// Recieve Data Pointer
CAMIFT__ unsigned char	UcRcvVal[ RCVBUFSIZE ] ;				// Recieve Data Buffer
CAMIFT__ unsigned char	UcSndVal[ SNDBUFSIZE ] ;				// Send Data Buffer
CAMIFT__ unsigned char	UcSndPtr ;								// Send Buffer Data Pointer



// Prottype Declation
CAMINI__ void	IniSet( void ) ;											// Initial Top Function
CAMINI__ void	MemClr( unsigned char *, unsigned short ) ;					// Memory Clear Function
CAMINI__ void	WitTim( unsigned short ) ;									// Wait
CAMINI__ void	WitClr( unsigned short, unsigned char, unsigned short );	// Operation Waiting
CAMIFT__ void	RcvChk( void ) ;											// Recieve Data Check Function

CAMCMD__	unsigned char	UcQutFlg;
CAMCMD__	unsigned char	UcFnbWit;
CAMCMD__	UnFltVal	UlFnbSiz;
CAMCMD__	UnFltVal	UlFarBor;
CAMCMD__	UnFltVal	UlNerBor;
CAMCMD__ unsigned long	UlCycCnt;
CAMCMD__ unsigned long	UlCycSet;
CAMCMD__ unsigned char UcTp1Flg;
CAMCMD__ unsigned char UcTp2Flg;
CAMCMD__ unsigned char UcTspItv;

//STM TEST
CAMCMD__ unsigned char UcVs1Flg;			// VSYNC1 1:Occured	0:Reset
CAMCMD__ unsigned char UcPt1Flg	;		// Test Pattern1 Flag
CAMCMD__ unsigned char UcPt2Flg	;		// Test Pattern2 Flag
CAMCMD__ unsigned char UcPt3Flg	;		// Test Pattern3 Flag


//GL ADJUSTMENT
CAMCMD__ UnFltVal	UlHalMax ;
CAMCMD__ UnFltVal	UlHalMin ;
CAMCMD__ UnFltVal	UlHalSum ;
CAMCMD__ UnFltVal	UlHalPtp ;
CAMCMD__ UnFltVal	UlHalCen ;
CAMCMD__ UnFltVal	UlTgtPtp ;
CAMCMD__ UnFltVal	UlTgtDif ;
#ifndef S3_DN_MODE
CAMCMD__ void	TneCen ( void ) ;		// IRIS HALL ADJUSTMENT
CAMCMD__ void	TneRun ( void ) ;		// IRIS HALL ADJUSTMENT
CAMCMD__ void	TnePtp ( void ) ;		// IRIS HALL ADJUSTMENT
CAMCMD__ void	AdjHlg ( void ) ;		// IRIS HALL Loopgain Adjustment for HALL-VCM
#endif
CAMCMD__ void	ActTp1 ( void ) ;		// Actuator(STM3ch&HALL-VCM) Test Pattern
CAMCMD__ void	ActTp2 ( void ) ;
CAMCMD__ void	ActTp3 ( void ) ;

CAMCMD__ unsigned char	UcTofRst ;
CAMCMD__ unsigned char	UcTbiRst ;
CAMCMD__ unsigned char	UcTneRst ;

//VCM Driver TEST
#ifndef S3_DN_MODE
CAMCMD__ void     DCMDri(void);
#else
CAMCMD__ void     DCMDriFil(void);
#endif
CAMCMD__ unsigned char UcDCMCWFlg;

