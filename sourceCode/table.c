
/* LED 7 segment character table */
/* LED 1,3 */
const unsigned char led7CharacterTable1[10] = {
	0xC0, //0
	0xF9, //1
	0xA4, //2
	0xB0, //3
	0x99, //4
	0x92, //5
	0x82, //6
	0xF8, //7
	0x80, //8	
	0x90  //9
};

/* Start Address for E2 DataFlash programming/erasure */
const unsigned short blockAddr[8] = {
	0x1000, //block 1
	0x1400, //block 2
	0x1800, //block 3
	0x1C00, //block 4
	0x2000, //block 5
	0x2400, //block 6
	0x2800, //block 7
	0x2C00, //block 8
};

/* function Cyclic Redundancy Check CRC - 8 */
const unsigned char CRC8[9] = {1,1,1,0,1,0,1,0,1};

/*sin value*/
extern const unsigned short sinPos[32] ={
	2048,	//Vref/2
	2448,
	2832,
	3186,
	3496,
	3751,
	3940,
	4057,
	4095,	//Vref
	4057,
	3940,
	3751,
	3496,
	3185,
	2832,
	2448,
	2048,	//Vref/2
	1648,
	1264,
	910,
	600,
	345,
	156,
	39,
	0,	// 0V
	39,
	156,
	345,
	600,
	910,
	1264,
	1648
	
};



unsigned char text[101] ={
	100,2,3,4,5,6,7,8,9,0,
	1,2,3,4,5,6,7,8,9,50,
	1,2,3,45,5,6,7,8,9,0,
	1,2,3,4,5,6,7,88,9,0,
	1,2,3,4,50,6,7,8,9,0,
	1,2,3,4,5,62,7,8,9,0,
	1,2,3,4,5,6,7,8,9,0,
	160,2,3,4,5,6,7,8,9,0,
	1,250,3,4,5,6,7,8,9,0,
	1,2,3,40,5,6,7,8,9,2,100
};

	/* 0x0800,  // 1.65V
	0x0DAC,  // 2.82V
	0x0FFF,	 // 3.3V
	0x0DAC,	 // 2.82V
	0x0800,	 // 1.65V
	0x0254,  // 0.48V
	0x0000,  // 0V
	0x0254   // 0.48V */