/*Filter Calculator Version 3.04*/
/*the time and date : 2018-2-14 20:00:47*/
/*FC filename : T5390_GL170907-1*/
/*fs,23437.5Hz*/
/*LSI No.,LC898201*/
/*Comment,*/

/* 8bit */
CAMINI__ const struct STMHLREG	CsMhlReg[]	= {
	{ 0x0041,	0x03 },	/*03,0041*/
	{ 0x0042,	0x03 },	/*03,0042*/
	{ 0x0021,	0x0F },	/*0F,0020*/
	{ 0x0022,	0x02 },	/*02,0021*/
	{ 0xFFFF,	0xFF }
} ;

/* 32bit */
CAMINI__ const struct STMHLFIL	CsMhlFil[]	= {
	{ 0x1001,	0x3F800000 },	/*3F800000,1001,0dB,invert=0*/
	{ 0x1002,	0x3F800000 },	/*3F800000,1002,0dB,invert=0*/
	{ 0x1003,	0x00000000 },	/*00000000,1003,Cutoff,invert=0*/
	{ 0x1004,	0x3F800000 },	/*3F800000,1004,0dB,invert=0*/
	{ 0x1005,	0x00000000 },	/*00000000,1005,Cutoff,invert=0*/
	{ 0x1006,	0x3F6CF1A0 },	/*3F6CF1A0,1006,HPF,600Hz,0dB,fs/1,invert=0*/
	{ 0x1007,	0xBF6CF1A0 },	/*BF6CF1A0,1007,HPF,600Hz,0dB,fs/1,invert=0*/
	{ 0x1008,	0x3F59E340 },	/*3F59E340,1008,HPF,600Hz,0dB,fs/1,invert=0*/
	{ 0x1009,	0x3DC6581D },	/*3DC6581D,1009,LPF,800Hz,0dB,fs/1,invert=0*/
	{ 0x100A,	0x3DC6581D },	/*3DC6581D,100A,LPF,800Hz,0dB,fs/1,invert=0*/
	{ 0x100B,	0x3F4E69F9 },	/*3F4E69F9,100B,LPF,800Hz,0dB,fs/1,invert=0*/
	{ 0x100C,	0x3D1E57B5 },	/*3D1E57B5,100C,LPF,300Hz,0dB,fs/1,invert=0*/
	{ 0x100D,	0x3D1E57B5 },	/*3D1E57B5,100D,LPF,300Hz,0dB,fs/1,invert=0*/
	{ 0x100E,	0x3F6C3509 },	/*3F6C3509,100E,LPF,300Hz,0dB,fs/1,invert=0*/
	{ 0x1010,	0x3D231090 },	/*3D231090,1010,DI,-28dB,fs/4,invert=0*/
	{ 0x1011,	0x00000000 },	/*00000000,1011,DI,-28dB,fs/4,invert=0*/
	{ 0x1012,	0x3F800000 },	/*3F800000,1012,DI,-28dB,fs/4,invert=0*/
	{ 0x1013,	0x3F800000 },	/*3F800000,1013,Through,0dB,fs/1,invert=0*/
	{ 0x1014,	0x00000000 },	/*00000000,1014,Through,0dB,fs/1,invert=0*/
	{ 0x1015,	0x00000000 },	/*00000000,1015,Through,0dB,fs/1,invert=0*/
	{ 0x1016,	0x4232AC66 },	/*4232AC66,1016,33dB,invert=0*/
	{ 0x1017,	0x4020C2BF },	/*4020C2BF,1017,8dB,invert=0*/
	{ 0x1018,	0x3F800000 },	/*3F800000,1018,0dB,invert=0*/
	{ 0x1019,	0x3EB5AA1A },	/*3EB5AA1A,1019,-9dB,invert=0*/
	{ 0x101A,	0x407EC9E1 },	/*407EC9E1,101A,12dB,invert=0*/
	{ 0x101B,	0x00000000 },	/*00000000,101B,Cutoff,invert=0*/
	{ 0x1020,	0x3C19AC6B },	/*3C19AC6B,1020,LPF,800Hz,0dB,0,fs/1,invert=0*/
	{ 0x1021,	0x3C99AC6B },	/*3C99AC6B,1021,LPF,800Hz,0dB,0,fs/1,invert=0*/
	{ 0x1022,	0x3FCE69F9 },	/*3FCE69F9,1022,LPF,800Hz,0dB,0,fs/1,invert=0*/
	{ 0x1023,	0x3C19AC6B },	/*3C19AC6B,1023,LPF,800Hz,0dB,0,fs/1,invert=0*/
	{ 0x1024,	0xBF266EB8 },	/*BF266EB8,1024,LPF,800Hz,0dB,0,fs/1,invert=0*/
	{ 0x102A,	0x3BAEC0EE },	/*3BAEC0EE,102A,LPF,10Hz,0dB,fs/4,invert=0*/
	{ 0x102B,	0x3BAEC0EE },	/*3BAEC0EE,102B,LPF,10Hz,0dB,fs/4,invert=0*/
	{ 0x102C,	0x3F7D44FC },	/*3F7D44FC,102C,LPF,10Hz,0dB,fs/4,invert=0*/
	{ 0x102D,	0xBF800000 },	/*BF800000,102D,0dB,invert=1*/
	{ 0x1030,	0x3F800000 },	/*3F800000,1030*/
	{ 0x1031,	0x00000000 },	/*00000000,1031*/
	{ 0x1032,	0x00000000 },	/*00000000,1032*/
	{ 0x1033,	0x3C0D8400 },	/*3C0D8400,1033,LPF,65Hz,0dB,fs/1,invert=0*/
	{ 0x1034,	0x3C0D8400 },	/*3C0D8400,1034,LPF,65Hz,0dB,fs/1,invert=0*/
	{ 0x1035,	0x3F7B93E0 },	/*3F7B93E0,1035,LPF,65Hz,0dB,fs/1,invert=0*/
	{ 0x1036,	0x3B833D7E },	/*3B833D7E,1036,LPF,30Hz,0dB,fs/1,invert=0*/
	{ 0x1037,	0x3B833D7E },	/*3B833D7E,1037,LPF,30Hz,0dB,fs/1,invert=0*/
	{ 0x1038,	0x3F7DF30A },	/*3F7DF30A,1038,LPF,30Hz,0dB,fs/1,invert=0*/
	{ 0x1039,	0x3AAF7496 },	/*3AAF7496,1039,LPF,10Hz,0dB,fs/1,invert=0*/
	{ 0x103A,	0x3AAF7496 },	/*3AAF7496,103A,LPF,10Hz,0dB,fs/1,invert=0*/
	{ 0x103B,	0x3F7F508B },	/*3F7F508B,103B,LPF,10Hz,0dB,fs/1,invert=0*/
	{ 0x103C,	0x3AAF7496 },	/*3AAF7496,103C,LPF,10Hz,0dB,fs/1,invert=0*/
	{ 0x103D,	0x3AAF7496 },	/*3AAF7496,103D,LPF,10Hz,0dB,fs/1,invert=0*/
	{ 0x103E,	0x3F7F508B },	/*3F7F508B,103E,LPF,10Hz,0dB,fs/1,invert=0*/
	{ 0x1041,	0x3F800000 },	/*3F800000,1041,0dB,invert=0*/
	{ 0x1042,	0x3F800000 },	/*3F800000,1042,0dB,invert=0*/
	{ 0x1043,	0x00000000 },	/*00000000,1043,Cutoff,invert=0*/
	{ 0x1044,	0x3F800000 },	/*3F800000,1044,0dB,invert=0*/
	{ 0x1045,	0x00000000 },	/*00000000,1045,Cutoff,invert=0*/
	{ 0x1046,	0x3EF5E3DE },	/*3EF5E3DE,1046,HBF,340Hz,680Hz,-6dB,fs/1,invert=0*/
	{ 0x1047,	0xBEE07461 },	/*BEE07461,1047,HBF,340Hz,680Hz,-6dB,fs/1,invert=0*/
	{ 0x1048,	0x3F553B05 },	/*3F553B05,1048,HBF,340Hz,680Hz,-6dB,fs/1,invert=0*/
	{ 0x1049,	0x3FBA2A90 },	/*3FBA2A90,1049,HBF,120Hz,800Hz,4dB,fs/1,invert=0*/
	{ 0x104A,	0xBFB445A9 },	/*BFB445A9,104A,HBF,120Hz,800Hz,4dB,fs/1,invert=0*/
	{ 0x104B,	0x3F4E69F9 },	/*3F4E69F9,104B,HBF,120Hz,800Hz,4dB,fs/1,invert=0*/
	{ 0x104C,	0x3F800000 },	/*3F800000,104C,Through,0dB,fs/1,invert=0*/
	{ 0x104D,	0x00000000 },	/*00000000,104D,Through,0dB,fs/1,invert=0*/
	{ 0x104E,	0x00000000 },	/*00000000,104E,Through,0dB,fs/1,invert=0*/
	{ 0x1050,	0x3D0186E2 },	/*3D0186E2,1050,DI,-30dB,fs/16,invert=0*/
	{ 0x1051,	0x00000000 },	/*00000000,1051,DI,-30dB,fs/16,invert=0*/
	{ 0x1052,	0x3F800000 },	/*3F800000,1052,DI,-30dB,fs/16,invert=0*/
	{ 0x1053,	0x3D507003 },	/*3D507003,1053,LPF,400Hz,0dB,fs/1,invert=0*/
	{ 0x1054,	0x3D507003 },	/*3D507003,1054,LPF,400Hz,0dB,fs/1,invert=0*/
	{ 0x1055,	0x3F65F200 },	/*3F65F200,1055,LPF,400Hz,0dB,fs/1,invert=0*/
	{ 0x1056,	0x410E99A3 },	/*410E99A3,1056,19dB,invert=0*/
	{ 0x1057,	0x00000000 },	/*00000000,1057,Cutoff,invert=0*/
	{ 0x1058,	0x3F800000 },	/*3F800000,1058,0dB,invert=0*/
	{ 0x1059,	0x3F800000 },	/*3F800000,1059,0dB,invert=0*/
	{ 0x105A,	0xBFFF64C1 },	/*BFFF64C1,105A,6dB,invert=1*/
	{ 0x105B,	0x00000000 },	/*00000000,105B,Cutoff,invert=0*/
	{ 0x105C,	0x00000000 },	/*00000000,105C,Cutoff,invert=0*/
	{ 0x1060,	0x3C64E589 },	/*3C64E589,1060,LPF,1000Hz,0dB,0,fs/1,invert=0*/
	{ 0x1061,	0x3CE4E589 },	/*3CE4E589,1061,LPF,1000Hz,0dB,0,fs/1,invert=0*/
	{ 0x1062,	0x3FC37B91 },	/*3FC37B91,1062,LPF,1000Hz,0dB,0,fs/1,invert=0*/
	{ 0x1063,	0x3C64E589 },	/*3C64E589,1063,LPF,1000Hz,0dB,0,fs/1,invert=0*/
	{ 0x1064,	0xBF15457A },	/*BF15457A,1064,LPF,1000Hz,0dB,0,fs/1,invert=0*/
	{ 0x106A,	0x3B5AE0FF },	/*3B5AE0FF,106A,LPF,8.3333Hz,0dB,fs/3,invert=0*/
	{ 0x106B,	0x3B5AE0FF },	/*3B5AE0FF,106B,LPF,8.3333Hz,0dB,fs/3,invert=0*/
	{ 0x106C,	0x3F7E4A3E },	/*3F7E4A3E,106C,LPF,8.3333Hz,0dB,fs/3,invert=0*/
	{ 0x106D,	0xBF800000 },	/*BF800000,106D,0dB,invert=1*/
	{ 0x107E,	0x00000000 },	/*00000000,107E,Cutoff,invert=0*/
	{ 0xFFFF,	0xFFFFFFFF }
} ;
