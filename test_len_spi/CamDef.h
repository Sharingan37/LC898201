//********************************************************************************
//
//		<< LC898201 Evaluation Soft>>
//	    Program Name	: CamDef.h
// 		Explanation		: LC898201 Define Declaration
//		Design			: Y.Kim
//		History			: First edition						2012.02.08 
//                                                    : Second version    2017.10.10
//********************************************************************************
//REGISTER(VCM)
//#define			0x0000
#define	CM_EQON			0x0001
#define	CM_RAMINITON	0x0002
#define	CM_CPUOPEON		0x0003
//#define			0x0004
//#define			0x0005
//#define			0x0006
//#define			0x0007
#define	AF_EQSW			0x0008
#define	AF_STPMV		0x0009
#define	AF_STPMVSTP		0x000A
//#define			0x000B
#define	GL_EQSW			0x000C
#define	GL_STPMV		0x000D
#define	GL_STPMVSTP		0x000E
//#define			0x000F
#define	CM_RAMDLYMOD	0x0010
#define	CM_CPUOPE1ADD	0x0011
#define	CM_CPUOPE2ADD	0x0012
#define	CM_RAMACCMOD	0x0013
//#define			0x0014
//#define			0x0015
//#define			0x0016
//#define			0x0017
//#define			0x0018
//#define			0x0019
//#define			0x001A
//#define			0x001B
//#define			0x001C
//#define			0x001D
//#define			0x001E
//#define			0x001F
#define	AF_SRVMOD		0x0020
#define	AF_DWNSMP1		0x0021
#define	AF_DWNSMP2		0x0022
#define	AF_STPMVMOD		0x0023
#define	AF_LEVDIFTMR	0x0024
#define	AF_DWNSMP3		0x0025
#define	AF_LEVDIFSEL	0x0026
//#define			0x0027
#define	AF_ADINTEROL	0x0028
#define	AF_DEGCALMOD	0x0029
#define	AF_MIDCALMOD	0x002A
#define	AF_SRVOFSTON	0x002B
#define	AF_STPMVEXEMOD	0x002C
#define	AF_STPMVGANTMR	0x002D
#define	AF_INIPOSMOD	0x002E
#define	AF_INIMVSTATMR	0x002F
#define	AF_STTATMR		0x0030
#define	AF_INIMVTMR		0x0031
#define	AF_SHCKON		0x0032
#define	AF_KICKON		0x0033
#define	AF_KICKTMR		0x0034
#define	AF_ATOSINON		0x0035
#define	AF_ATOSINTMR	0x0036
#define	AF_NONMAG		0x0037
#define	AF_ATONONCNVON		0x0038
#define	AF_ATONONCNVTMR1	0x0039
#define	AF_NONCNVTMR2	0x003A
//#define			0x003B
//#define			0x003C
//#define			0x003D
//#define			0x003E
#define	AF_INIPOS	0x003F
#define	GL_SRVMOD	0x0040
#define	GL_DWNSMP1	0x0041
#define	GL_DWNSMP2	0x0042
#define	GL_STPMVMOD	0x0043
#define	GL_LEVDIFTMR	0x0044
#define	GL_DWNSMP3	0x0045
#define	GL_LEVDIFSEL	0x0046
//#define			0x0047
#define	GL_EQOVRSMP	0x0048
#define	GL_LMTMOD	0x0049
//#define			0x004A
//#define			0x004B
#define	GL_STPMVEXEMOD	0x004C
//#define			0x004D
//#define			0x004E
//#define			0x004F
#define	CM_DPI1ADD	0x0050
#define	CM_DPI2ADD	0x0051
#define	CM_DPO1ADD	0x0052
#define	CM_DPO2ADD	0x0053
//#define			0x0054
//#define			0x0055
//#define			0x0056
//#define			0x0057
#define	CM_SINON	0x0058
#define	CM_SINTST	0x0059
#define	CM_SINGAIN	0x005A
#define	CM_SINFRQ0	0x005B
#define	CM_SINFRQ1	0x005C
#define	CM_SINPHSX	0x005D
#define	CM_SINPHSY	0x005E
#define	CM_SINSTP	0x005F
#define	CM_MESMODE	0x0060
#define	CM_MESSINMODE	0x0061
#define	CM_MESLOOP0	0x0062
#define	CM_MESLOOP1	0x0063
#define	CM_MES1ADD	0x0064
#define	CM_MES2ADD	0x0065
#define	CM_MES3ADD	0x0066
//#define			0x0067
#define	CM_MESABS	0x0068
//#define			0x0069
#define	CM_MESHIST1ADD	0x006A
#define	CM_MESHIST2ADD	0x006B
#define	CM_MESHIST3ADD	0x006C
#define	CM_MESHIST4ADD	0x006D
#define	CM_MESHISTMOD	0x006E
//#define			0x006F
#define	CM_ADSMP	0x0070
#define	CM_ADSEL01	0x0071
#define	CM_ADSEL23	0x0072
#define	CM_ADSEL45	0x0073
#define	CM_DASEL01	0x0074
#define	CM_DASEL23	0x0075
#define	CM_DASEL45	0x0076
#define	H_ADMODE	0x0077
#define	H_DAV0		0x0078
#define	H_DAV1		0x0079
#define	H_DAV2		0x007A
#define	H_DAV3		0x007B
#define	H_DAV4		0x007C
//#define			0x007D
//#define			0x007E
//#define			0x007F
#define	H_PINMON0	0x0080
#define	H_PINMON1	0x0081
#define	H_PINMON2	0x0082
#define	H_PINMON3	0x0083
#define	H_DLYMON1	0x0084
#define	H_DLYMON2	0x0085
#define	H_DLYMON3	0x0086
#define	H_DLYMON4	0x0087
//#define			0x0088
//#define			0x0089
//#define			0x008A
//#define			0x008B
//#define			0x008C
#define	H_INTMSK0	0x008D
#define	H_INTMSK1	0x008E
//#define			0x008F
#define	H_FRCAD		0x0090
#define	H_FRCADEN	0x0091
#define	H_ADRES		0x0092
#define	H_TSTHMON	0x0093
#define	H_FRAC		0x0094
#define	H_FL2FXLMT	0x0095
#define	H_EXPLMTL	0x0096
#define	H_EXPLMTH	0x0097
#define	H_RAMACCTM0	0x0098
#define	H_RAMACCTM1	0x0099
//#define			0x009A
//#define			0x009B
//#define			0x009C
//#define			0x009D
//#define			0x009E
//#define			0x009F
//#define			0x00A0
//#define			0x00A1
//#define			0x00A2
//#define			0x00A3
//#define			0x00A4
//#define			0x00A5
//#define			0x00A6
//#define			0x00A7
//#define			0x00A8
//#define			0x00A9
//#define			0x00AA
//#define			0x00AB
//#define			0x00AC
//#define			0x00AD
//#define			0x00AE
//#define			0x00AF
//#define			0x00B0
//#define			0x00B1
//#define			0x00B2
//#define			0x00B3
//#define			0x00B4
//#define			0x00B5
//#define			0x00B6
//#define			0x00B7
//#define			0x00B8
//#define			0x00B9
//#define			0x00BA
//#define			0x00BB
//#define			0x00BC
//#define			0x00BD
//#define			0x00BE
//#define			0x00BF
//#define			0x00C0
//#define			0x00C1
//#define			0x00C2
//#define			0x00C3
//#define			0x00C4
//#define			0x00C5
//#define			0x00C6
//#define			0x00C7
//#define			0x00C8
//#define			0x00C9
//#define			0x00CA
//#define			0x00CB
//#define			0x00CC
//#define			0x00CD
//#define			0x00CE
//#define			0x00CF
//#define			0x00D0
//#define			0x00D1
//#define			0x00D2
//#define			0x00D3
//#define			0x00D4
//#define			0x00D5
//#define			0x00D6
//#define			0x00D7
//#define			0x00D8
//#define			0x00D9
//#define			0x00DA
//#define			0x00DB
//#define			0x00DC
//#define			0x00DD
//#define			0x00DE
//#define			0x00DF
//#define			0x00E0
//#define			0x00E1
//#define			0x00E2
//#define			0x00E3
//#define			0x00E4
//#define			0x00E5
//#define			0x00E6
//#define			0x00E7
//#define			0x00E8
//#define			0x00E9
//#define			0x00EA
//#define			0x00EB
//#define			0x00EC
//#define			0x00ED
//#define			0x00EE
//#define			0x00EF
//#define			0x00F0
//#define			0x00F1
//#define			0x00F2
//#define			0x00F3
//#define			0x00F4
//#define			0x00F5
//#define			0x00F6
//#define			0x00F7
//#define			0x00F8
//#define			0x00F9
//#define			0x00FA
//#define			0x00FB
//#define			0x00FC
//#define			0x00FD
//#define			0x00FE
//#define			0x00FF
#define	H_AFLEVDIF	0x00D0
#define	H_SHCK		0x00D1
#define	H_AFSTATE	0x00D2
#define	H_AFSELZ	0x00D3
#define	H_NONMAG	0x00D4
#define	H_GLLEVDIF	0x00D8
#define	H_AMJERROR	0x00E0
#define	H_MESLOOP0	0x00E1
#define	H_MESLOOP1	0x00E2
#define	H_RAMACC	0x00F0
#define	H_FLG0		0x00FD
#define	H_FLG1		0x00FE
#define	H_INT		0x00FF



//REGISTER(STM)
#define	A_DIV		0x0100
#define	A_PC1		0x0101
#define	A_PC2		0x0102
#define	A_GN		0x0103
#define	A_MSPD1		0x0104
#define	A_MSPD2		0x0105
#define	A_MDIS1		0x0106
#define	A_MDIS2		0x0107
#define	A_LCTR1		0x0108
#define	A_LCTR2		0x0109
#define	A_LCTR3		0x010A
#define	A_ST		0x010B
#define	A_INIT		0x010C
#define	A_SPDIV		0x010D
#define	A_TRIG		0x010E
//#define			0x010F
#define	A_STSEL		0x0110
#define	A_SETUP0	0x0111
#define	A_SGAIN		0x0112
#define	A_VSMODE	0x0113
#define	A_MAGWT		0x0114
#define	A_HBSET		0x0115
#define	A_ADINV		0x0116
//#define			0x0117
#define	A_VIHL		0x0118
#define	A_VIHH		0x0119
#define	A_VILL		0x011A
#define	A_VILH		0x011B
//#define			0x011C
//#define			0x011D
//#define			0x011E
//#define			0x011F
//#define	A_GADJSW	0x0120
//#define	A_PCOEF		0x0121
//#define	A_ICOEF		0x0122
//#define	A_DCOEF		0x0123
//#define	A_FFCTL		0x0124
//#define	A_FFINI		0x0125
//#define	A_SFB		0x0126
//#define	A_SETUP1	0x0127
//#define	A_ADLLEVEL	0x0128
//#define	A_ADCTLEV	0x0129
//#define	A_AGAIN		0x012A
//#define	A_SPOUT		0x012B
//#define			0x012C
//#define			0x012D
//#define			0x012E
//#define			0x012F
//#define	A_AUP0L		0x0130
//#define	A_AUP0H		0x0131
//#define	A_ADWN0L	0x0132
//#define	A_ADWN0H	0x0133
//#define	A_MP1L		0x0134
//#define	A_MP1H		0x0135
//#define	A_MP2L		0x0136
//#define	A_MP2H		0x0137
//#define	A_DEBD1L	0x0138
//#define	A_DEBD1H	0x0139
//#define	A_DEBD2L	0x013A
//#define	A_DEBD2H	0x013B
//#define			0x013C
//#define			0x013D
//#define			0x013E
//#define			0x013F
#define	B_DIV		0x0140
#define	B_PC1		0x0141
#define	B_PC2		0x0142
#define	B_GN		0x0143
#define	B_MSPD1		0x0144
#define	B_MSPD2		0x0145
#define	B_MDIS1		0x0146
#define	B_MDIS2		0x0147
#define	B_LCTR1		0x0148
#define	B_LCTR2		0x0149
#define	B_LCTR3		0x014A
#define	B_ST		0x014B
#define	B_INIT		0x014C
#define	B_SPDIV		0x014D
#define	B_TRIG		0x014E
//#define			0x014F
#define	B_STSEL		0x0150
#define	B_SETUP0	0x0151
#define	B_SGAIN		0x0152
#define	B_VSMODE	0x0153
#define	B_MAGWT		0x0154
#define	B_HBSET		0x0155
#define	B_ADINV		0x0156
//#define			0x0157
#define	B_VIHL		0x0158
#define	B_VIHH		0x0159
#define	B_VILL		0x015A
#define	B_VILH		0x015B
//#define			0x015C
//#define			0x015D
//#define			0x015E
//#define			0x015F
//#define	B_GADJSW	0x0160
//#define	B_PCOEF		0x0161
//#define	B_ICOEF		0x0162
//#define	B_DCOEF		0x0163
//#define	B_FFCTL		0x0164
//#define	B_FFINI		0x0165
//#define	B_SFB		0x0166
//#define	B_SETUP1	0x0167
//#define	B_ADLLEVEL	0x0168
//#define	B_ADCTLEV	0x0169
//#define	B_AGAIN		0x016A
//#define	B_SPOUT		0x016B
//#define			0x016C
//#define			0x016D
//#define			0x016E
//#define			0x016F
//#define	B_AUP0L		0x0170
//#define	B_AUP0H		0x0171
//#define	B_ADWN0L	0x0172
//#define	B_ADWN0H	0x0173
//#define	B_MP1L		0x0174
//#define	B_MP1H		0x0175
//#define	B_MP2L		0x0176
//#define	B_MP2H		0x0177
//#define	B_DEBD1L	0x0178
//#define	B_DEBD1H	0x0179
//#define	B_DEBD2L	0x017A
//#define	B_DEBD2H	0x017B
//#define			0x017C
//#define			0x017D
//#define			0x017E
//#define			0x017F
#define	C_DIV		0x0180
#define	C_PC1		0x0181
#define	C_PC2		0x0182
#define	C_GN		0x0183
#define	C_MSPD1		0x0184
#define	C_MSPD2		0x0185
#define	C_MDIS1		0x0186
#define	C_MDIS2		0x0187
#define	C_LCTR1		0x0188
#define	C_LCTR2		0x0189
#define	C_LCTR3		0x018A
#define	C_ST		0x018B
#define	C_INIT		0x018C
#define	C_SPDIV		0x018D
#define	C_TRIG		0x018E
//#define			0x018F
#define	C_STSEL		0x0190
#define	C_SETUP0	0x0191
#define	C_SGAIN		0x0192
#define	C_VSMODE	0x0193
#define	C_MAGWT		0x0194
#define	C_HBSET		0x0195
#define	C_ADINV		0x0196
//#define			0x0197
#define	C_VIHL		0x0198
#define	C_VIHH		0x0199
#define	C_VILL		0x019A
#define	C_VILH		0x019B
//#define			0x019C
//#define			0x019D
//#define			0x019E
//#define			0x019F
#define	PISEN		0x01A0
//#define			0x01A1
//#define			0x01A2
//#define			0x01A3
//#define			0x01A4
//#define			0x01A5
//#define			0x01A6
//#define			0x01A7
#define	TSTDATL		0x01A8
#define	TSTDATH		0x01A9
//#define			0x01AA
#define	TSTREG_STM	0x01AB
//#define	EVC			0x01AC
#define	DSEL		0x01AD
#define	ADTIM		0x01AE
//#define			0x01AF
#define	DC1DIV		0x01B0
#define	DC1PC1		0x01B1
#define	DC1PC2		0x01B2
#define	DC1G		0x01B3
#define	DC1PWM		0x01B4
#define	DC1CNT1		0x01B5
#define	DC1CNT2		0x01B6
#define	DC1TRIG		0x01B7
#define	DC1VSMODE	0x01B8
//#define			0x01B9
//#define			0x01BA
//#define			0x01BB
//#define			0x01BC
//#define			0x01BD
//#define			0x01BE
//#define			0x01BF



//REGISTER(TOP)
#define	CLKOFF		0x0200
//#define			0x0201
//#define			0x0202
//#define			0x0203
//#define			0x0204
//#define			0x0205
//#define			0x0206
//#define			0x0207
//#define			0x0208
//#define			0x0209
#define	CLKTST		0x020A
#define	CLKON		0x020B
//#define			0x020C
//#define			0x020D
//#define			0x020E
//#define			0x020F
#define	PWMDIV		0x0210
#define	SRVDIV		0x0211
#define	STMDIV		0x0212
//#define			0x0213
//#define			0x0214
//#define			0x0215
//#define			0x0216
//#define			0x0217
//#define			0x0218
//#define			0x0219
//#define			0x021A
//#define			0x021B
//#define			0x021C
//#define			0x021D
//#define			0x021E
//#define			0x021F
#define	PDON		0x0220
//#define			0x0221
//#define			0x0222
//#define			0x0223
//#define			0x0224
//#define			0x0225
//#define			0x0226
//#define			0x0227
//#define			0x0228
//#define			0x0229
//#define			0x022A
//#define			0x022B
//#define			0x022C
//#define			0x022D
//#define			0x022E
//#define			0x022F
#define	VSY1SEL		0x0230
#define	VSY2SEL		0x0231
#define	PIS1SEL		0x0232
#define	PIS2SEL		0x0233
#define	CLKO1SEL	0x0234
#define	CLKO2SEL	0x0235
#define	BSYSEL		0x0236
#define	MONSEL		0x0237
//#define			0x0238
//#define			0x0239
//#define			0x023A
//#define			0x023B
//#define			0x023C
//#define			0x023D
//#define			0x023E
//#define			0x023F
#define	DRVSEL		0x0240
//#define			0x0241
//#define			0x0242
//#define			0x0243
//#define			0x0244
//#define			0x0245
//#define			0x0246
//#define			0x0247
#define	SPIMD3		0x0248
//#define			0x0249
//#define			0x024A
//#define			0x024B
//#define			0x024C
//#define			0x024D
//#define			0x024E
#define	TSTREG_TOP	0x024F
#define	STM1VS		0x0250
#define	STM2VS		0x0251
#define	STM3VS		0x0252
#define	AFVS		0x0253
//#define			0x0254
//#define			0x0255
//#define			0x0256
//#define			0x0257
//#define			0x0258
//#define			0x0259
//#define			0x025A
//#define			0x025B
//#define			0x025C
//#define			0x025D
//#define			0x025E
//#define			0x025F
#define	STBB1		0x0260
#define	STBB2		0x0261
#define	CMSDAC		0x0262
#define	DACTEST		0x0263
#define	OP1SET		0x0264
#define	OP2SET		0x0265
#define	OP3SET		0x0266
#define	OP4SET		0x0267
#define	OSCSET		0x0268
#define	OSCCNTEN	0x0269
#define	TSDTEST		0x026A
//#define			0x026B
#define	OSCCK_CNTR0	0x026C
#define	OSCCK_CNTR1	0x026D
//#define			0x026E
//#define			0x026F
#define	MONSELA		0x0270
#define	MONSELB		0x0271
#define	MONSELC		0x0272
#define	MONSELD		0x0273
#define	MONSELE		0x0274
#define	MONTST		0x0275
//#define			0x0276
//#define			0x0277
#define	SOFTRES1	0x0278
//#define			0x0279
//#define			0x027A
//#define			0x027B
//#define			0x027C
//#define			0x027D
#define	CVER		0x027E
#define	TESTRD		0x027F

//#define			0x0300
#define	DRVFC7		0x0301
//#define			0x0302
//#define			0x0303
#define	PWMA7		0x0304
#define	PWMFC7		0x0305
#define	PWMDLY7		0x0306
#define	PWMFC72		0x0307
//#define			0x0308
//#define			0x0309
//#define			0x030A
//#define			0x030B
//#define			0x030C
//#define			0x030D
//#define			0x030E
//#define			0x030F
//#define			0x0310
#define	DRVFC6		0x0311
//#define			0x0312
//#define			0x0313
#define	PWMA6		0x0314
#define	PWMFC6		0x0315
#define	PWMDLY6		0x0316
#define	PWMFC62		0x0317
//#define			0x0318
//#define			0x0319
//#define			0x031A
//#define			0x031B
//#define			0x031C
//#define			0x031D
//#define			0x031E
//#define			0x031F
//#define			0x0320
//#define			0x0321
//#define			0x0322
//#define			0x0323
//#define			0x0324
//#define			0x0325
//#define			0x0326
//#define			0x0327
//#define			0x0328
//#define			0x0329
//#define			0x032A
//#define			0x032B
//#define			0x032C
//#define			0x032D
//#define			0x032E
//#define			0x032F
#define	PWMMONA		0x0330
#define	PWMMONFC	0x0331
#define	DACMONFC	0x0332
//#define			0x0333
//#define			0x0334
//#define			0x0335
//#define			0x0336
//#define			0x0337
//#define			0x0338
//#define			0x0339
//#define			0x033A
//#define			0x033B
//#define			0x033C
//#define			0x033D
//#define			0x033E
//#define			0x033F

#define	TSTMOD		0x07F0



//RAM(VCM)
#define	msmean		0x1000
#define	glag		0x1001
#define	gldda		0x1002
#define	glddb		0x1003
#define	glppa		0x1004
#define	glppb		0x1005
#define	glda		0x1006
#define	gldb		0x1007
#define	gldc		0x1008
#define	glea		0x1009
#define	gleb		0x100A
#define	glec		0x100B
#define	glua		0x100C
#define	glub		0x100D
#define	gluc		0x100E
//#define			0x100F	//3f80_0000
#define	glia		0x1010
#define	glib		0x1011
#define	glic		0x1012
#define	glja		0x1013
#define	gljb		0x1014
#define	gljc		0x1015
#define	glfa		0x1016
#define	glfb		0x1017
#define	glfc		0x1018
#define	glg			0x1019
#define	glg2		0x101A
#define	glsin		0x101B
#define	tmp			0x101C
#define	glssmv1		0x101D
#define	glssmv2		0x101E
//#define			0x101F	//bf80_0000
#define	glpa		0x1020
#define	glpb		0x1021
#define	glpc		0x1022
#define	glpd		0x1023
#define	glpe		0x1024
#define	gllmt		0x1025
#define	glsjlev		0x1026
#define	GLSTMTGT	0x1027
#define	glsjdif		0x1028
#define	glshlev		0x1029
#define	glstma		0x102A
#define	glstmb		0x102B
#define	glstmc		0x102C
#define	glstmg		0x102D
#define	GLSTMTGTSS	0x102E
//#define			0x102F	//3f00_0000
#define	glfira		0x1030
#define	glfirb		0x1031
#define	glfirc		0x1032
#define	ms1aa		0x1033
#define	ms1ab		0x1034
#define	ms1ac		0x1035
#define	ms1ba		0x1036
#define	ms1bb		0x1037
#define	ms1bc		0x1038
#define	ms2aa		0x1039
#define	ms2ab		0x103A
#define	ms2ac		0x103B
#define	ms2ba		0x103C
#define	ms2bb		0x103D
#define	ms2bc		0x103E
//#define			0x103F	//0000_0000
#define	afmg		0x1040
#define	afag		0x1041
#define	afdda		0x1042
#define	afddb		0x1043
#define	afppa		0x1044
#define	afppb		0x1045
#define	afda		0x1046
#define	afdb		0x1047
#define	afdc		0x1048
#define	afea		0x1049
#define	afeb		0x104A
#define	afec		0x104B
#define	afua		0x104C
#define	afub		0x104D
#define	afuc		0x104E
#define	afatr0		0x104F
#define	afia		0x1050
#define	afib		0x1051
#define	afic		0x1052
#define	afja		0x1053
#define	afjb		0x1054
#define	afjc		0x1055
#define	affa		0x1056
#define	affb		0x1057
#define	affc		0x1058
#define	afg			0x1059
#define	afg2		0x105A
#define	afsin		0x105B
#define	afsin2		0x105C
#define	afssmv1		0x105D
#define	afssmv2		0x105E
#define	afbtr0		0x105F
#define	afpa		0x1060
#define	afpb		0x1061
#define	afpc		0x1062
#define	afpd		0x1063
#define	afpe		0x1064
#define	aflmt		0x1065
#define	afsjlev		0x1066
#define	AFSTMTGT	0x1067
#define	afsjdif		0x1068
#define	afshlev		0x1069
#define	afstma		0x106A
#define	afstmb		0x106B
#define	afstmc		0x106C
#define	afstmg		0x106D
#define	AFSTMTGTSS	0x106E
#define	afdeg		0x106F
#define	afmg2		0x1070
#define	aflmt2		0x1071
#define	dm1g		0x1072
#define	dm2g		0x1073
#define	dm3g		0x1074
#define	dm4g		0x1075
#define	afnonmaglev	0x1076
#define	AFINIPOS	0x1077
#define	afff4		0x1078
#define	afg_2		0x1079
#define	AFSTMTGTN	0x107A
#define	afstahis	0x107B
#define	afstahistmp	0x107C
#define	paag		0x107D
#define	afff3		0x107E
//#define			0x107F	//3f35_04f3
#define	GLSTMTGTBOK	0x1080
//#define			0x1081
//#define			0x1082
//#define			0x1083
//#define			0x1084
//#define			0x1085
//#define			0x1086
#define	AFPAMPZ2	0x1087
#define	AFSTMTGTBOK	0x1088
//#define			0x1089
#define	GLSTMTGTN	0x108A
//#define			0x108B
//#define			0x108C
//#define			0x108D
//#define			0x108E
#define	calsing		0x108F
#define	GLINZ		0x1200
#define	GLAGZ		0x1201
#define	MESHIST1	0x1202
#define	MESHIST2	0x1203
#define	MESHIST3	0x1204
#define	MESHIST4	0x1205
#define	MSABS1		0x1206
#define	GLDZ1		0x1207
#define	GLDZ2		0x1208
#define	GLTMP1Z		0x1209
#define	GLEZ1		0x120A
#define	GLEZ2		0x120B
#define	MSABS1AV	0x120C
#define	GLUZ1		0x120D
#define	GLUZ2		0x120E
//#define			0x120F	//3f80_0000h
#define	GLSINZ		0x1210
#define	GLIZ1		0x1211
#define	GLIZ2		0x1212
#define	GLTMP2Z		0x1213
#define	GLJZ1		0x1214
#define	GLJZ2		0x1215
#define	MSMAX1		0x1216
//#define			0x1217	//MS12
#define	GLFZ		0x1218
#define	GLGZ		0x1219
#define	GLG2Z		0x121A
#define	GLG3Z		0x121B
#define	MSMAX1AV	0x121C
#define	MSCT1AV		0x121D
#define	GLSTMZ1		0x121E
#define	GLSTMZ2		0x121F
//#define			0x1220
#define	GLPZ1		0x1221
#define	GLPZ2		0x1222
#define	GLPZ3		0x1223
#define	GLPZ4		0x1224
#define	GLLMTZ		0x1225
#define	MSMIN1		0x1226
#define	MS1AZ1		0x1227
#define	MS1AZ2		0x1228
#define	MS1BZ1		0x1229
#define	MS1BZ2		0x122A
#define	GLDIFTMP	0x122B
#define	MSMIN1AV	0x122C
//#define			0x122D	//MS
#define	GL2PWMZ		0x122E
#define	GLSTMSTP	0x122F
#define	AD1Z		0x1230
#define	AD2Z		0x1231
#define	AD3Z		0x1232
#define	AD1OFFZ2	0x1233
#define	OFF1Z		0x1234
#define	OFF2Z		0x1235
#define	OFF3Z		0x1236
#define	MS2AZ1		0x1237
#define	MS2AZ2		0x1238
#define	MS2BZ1		0x1239
#define	MS2BZ2		0x123A
#define	CALCOS		0x123B
#define	MSPP1AV		0x123C
#define	GLFIRZ1		0x123D
#define	GLFIRZ2		0x123E
#define	GLFIRZ3		0x123F
#define	AFINZ		0x1240
#define	AFAGZ		0x1241
#define	AFFF1Z1		0x1242
#define	AFFF1Z2		0x1243
#define	AFFF2Z1		0x1244
#define	AFFF2Z2		0x1245
#define	MSABS2		0x1246
#define	AFDZ1		0x1247
#define	AFDZ2		0x1248
#define	AFTMP1Z		0x1249
#define	AFEZ1		0x124A
#define	AFEZ2		0x124B
#define	MSABS2AV	0x124C
#define	AFUZ1		0x124D
#define	AFUZ2		0x124E
//#define			0x124F	//0000_0000h
#define	AFSINZ		0x1250
#define	AFIZ1		0x1251
#define	AFIZ2		0x1252
#define	AFTMP2Z		0x1253
#define	AFJZ1		0x1254
#define	AfJZ2		0x1255
#define	MSMAX2		0x1256
//#define			0x1257	//MS12
#define	AFFZ		0x1258
#define	AFGZ		0x1259
#define	AFG2Z		0x125A
#define	AFG3Z		0x125B
#define	MSMAX2AV	0x125C
#define	MSCT2AV		0x125D
#define	AFSTMZ1		0x125E
#define	AFSTMZ2		0x125F
#define	AFACZ		0x1260
#define	AFPZ1		0x1261
#define	AFPZ2		0x1262
#define	AFPZ3		0x1263
#define	AFPZ4		0x1264
#define	AFLMTZ		0x1265
#define	MSMIN2		0x1266
#define	AFFIX0Z		0x1267
#define	AFFIX1Z		0x1268
#define	AFDIFTMP	0x1269
#define	CALDEG		0x126A
#define	CALSIN		0x126B
#define	MSMIN2AV	0x126C
//#define			0x126D	//MS\81F
#define	AF2PWMZ		0x126E
#define	AFSTMTGT2	0x126F
#define	AFATRZ		0x1270
#define	AFPAZ		0x1271
#define	AFPAPBZ		0x1272
#define	AFSELZ		0x1273
#define	AFSTZ		0x1274
#define	AFSTZ2		0x1275
#define	AFMGZ		0x1276
#define	AFTTLZ		0x1277
#define	AFBTRZ		0x1278
#define	AFPBZ		0x1279
#define	AFPAMBZ		0x127A
#define	AD3OFFZ2	0x127B
#define	MSPP2AV		0x127C
#define	AD1OFFZ		0x127D
#define	AD2OFFZ		0x127E
#define	AD3OFFZ		0x127F
#define	GLSTMSTPBOK	0x1280
//#define			0x1281
//#define			0x1282
//#define			0x1283
//#define			0x1284
//#define			0x1285
//#define			0x1286
#define	AFMIDINZ	0x1287
#define	AFSTMSTPBOK	0x1288
//#define			0x1289
//#define			0x128A
//#define			0x128B
//#define			0x128C
//#define			0x128D
//#define			0x128E	//3f80_0100h
//#define			0x128F	//3f7f_ff00h



//END OF FILE
