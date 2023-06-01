/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include <machine.h>
#include "iodefine.h"
#include "main.h"
#include "const_def.h"
#include "port_def.h"
#include "ram.h"
#include "table.h"

// Main routine
void main(void)
{
	unsigned short i;
	unsigned char dmy;
    
	/*OFF Protect Register*/
    SYSTEM.PRCR.WORD = 0xA507;
	
#if 1// setting clock
	set_psw(0x00000000);
	

	SYSTEM.SOSCCR.BYTE = 0x01;
	while(SYSTEM.SOSCCR.BYTE != 0x01);
	RTC.RCR3.BIT.RTCEN = 0;
	for(i=0;i<3;i++){
		dmy = RTC.RCR3.BIT.RTCEN;
	}
	while(RTC.RCR3.BIT.RTCEN != 0);
	RTC.RCR1.BYTE &= 0xFA;			// Disable AIE & PIE
    IEN(RTC,ALM) = 0;				// Disable Alarm interrupt
    IR(RTC,ALM) = 0;
    IEN(RTC,PRD) = 0;				// Disable Period interrupt
    IR(RTC,PRD) = 0;
	
	/*** Clock　***/
	SYSTEM.MOFCR.BYTE = 0x20;		// 10MHz~20MHz
	SYSTEM.MOSCWTCR.BYTE = 0x07;	// wait time = 65536 （16.384ms）
	SYSTEM.MOSCCR.BYTE = 0x00;		// Set the main clock to operating.
	while(SYSTEM.OSCOVFSR.BIT.MOOVF != 1);	// wait MOOVF = 1
	
	/*** PLL  ***/
	SYSTEM.PLLCR.WORD = 0x0B01;		// (14.7456 / 2) * 6 = 44.2368MHz
	SYSTEM.PLLCR2.BYTE = 0x00;		// 
	while (SYSTEM.OSCOVFSR.BIT.PLOVF != 1);	// PLL operating
	
	/*** DIV clock　***/
	SYSTEM.SCKCR.LONG = 0x11000101;		// ICLK,PCLKD,PCLKB,FCLK 44.2368 / 2 = 22.1184MHz）
	
	
	/*** PLL ***/
	SYSTEM.SCKCR3.WORD = 0x0400;		// PLL
	
	set_psw(0x00010000);
#endif
#if 1// CMT0 (Used as 10ms counter)
	MSTP(CMT0) = 0;					// Enable CMT0
	CMT0.CMCR.BIT.CMIE = 0;
	CMT.CMSTR0.BIT.STR0 = 0;		// Stop CMT0
	CMT0.CMCR.BIT.CKS = 1;			// 22.1184MHz / 32 = 691.200kHz
	CMT0.CMCOR = 6912 - 1;			// 691.200kHz / 6912 = 100Hz
	CMT0.CMCR.BIT.CMIE = 1;
	CMT0.CMCNT = 0;
	IR(CMT0,CMI0) = 0;              // flag timer
	IPR(CMT0,CMI0) = 0x01;          // Interupt priority
	//IEN(CMT0,CMI0) = 1;           // Enable Interupt
	CMT.CMSTR0.BIT.STR0 = 1;		// Start CMT0
#endif
#if 1// CMT1 (sampling cycle time of DAC)
	MSTP(CMT1) = 0;
	CMT1.CMCR.BIT.CMIE = 0;
	CMT.CMSTR0.BIT.STR1 = 0;
	CMT1.CMCR.BIT.CKS = 1;
	CMT1.CMCOR = 6912 -1;
	CMT1.CMCR.BIT.CMIE = 1;
	CMT1.CMCNT = 0;
	IR(CMT1,CMI1) = 0;
	IPR(CMT1,CMI1) = 0x02;
	IEN(CMT1,CMI1) = 1;
	CMT.CMSTR0.BIT.STR1 = 1;

#endif	
#if 1// setting Port
	PORTA.PDR.BIT.B0 = 1;   // PA0      Output
	PORTA.PMR.BIT.B0 = 0;
	PORTJ.PDR.BIT.B0 = 1;   // v2.0L
	PORTJ.PMR.BIT.B0 = 0;
	PORT0.PDR.BIT.B4 = 1;   // led sw
	PORT0.PMR.BIT.B4 = 0;
	PORT5.PDR.BIT.B3 = 1;   // P53      Output
	PORT5.PMR.BIT.B3 = 0;
	PORT1.PDR.BIT.B0 = 1;   // P10      Output
	PORT1.PMR.BIT.B0 = 0;
	PORT1.PDR.BIT.B1 = 1;   // P11      Output
	PORT1.PMR.BIT.B1 = 0;
	PORT1.PMR.BIT.B7 = 0;   // LX _GAIN
	PORT1.PDR.BIT.B7 = 1;
	
	PORTF.PDR.BIT.B7 = 1;   // PF7      Output RESET LED
	PORTF.PMR.BIT.B7 = 0;
	
	PORTC.PDR.BIT.B0 = 0;  	// SW2      Input
	PORTC.PDR.BIT.B1 = 0; 	// SW1
	PORTB.PDR.BIT.B7 = 0;  	// SW3
	PORTB.PDR.BIT.B6 = 0;  	// SW4
  
	PORTC.PMR.BIT.B0 = 0;  	// SW2
	PORTC.PMR.BIT.B1 = 0; 	// SW1
	PORTB.PMR.BIT.B7 = 0;  	// SW3
	PORTB.PMR.BIT.B6 = 0;   // SW4
	
	
	PORTJ.PODR.BIT.B0 = 0 ;  // source V2.0 
    PORT0.PODR.BIT.B4 = 0 ;
	PORTF.PODR.BIT.B7 = 0 ;
	PORTF.PODR.BIT.B7 = 1 ; //Reset LED 
	
	PORTJ.PMR.BIT.B2 = 1;  // D/A channel 1
	PORTJ.PDR.BIT.B2 = 1;
	
	
	PORTD.PODR.BIT.B3 = 1 ;  // source VR
    PORTD.PDR.BIT.B3 = 1 ;
	PORTD.PMR.BIT.B3 = 0 ;
	
	PORTD.PODR.BIT.B4 = 1 ;  // source VF
    PORTD.PDR.BIT.B4 = 1 ;
	PORTD.PMR.BIT.B3 = 0 ;
	
	PORT9.PODR.BIT.B2 = 0 ;  // TCX0
    PORT9.PDR.BIT.B2 = 1 ;
	PORT9.PMR.BIT.B2 = 0 ;
	 
#endif
#if 0// config RIIC
    RIIC0.ICCR1.BIT.ICE = 0;  //disable I2C
	RIIC0.ICCR1.BIT.IICRST = 1;  //RIIC reset
	RIIC0.SARU0.BYTE = 0x00;  // 7 Bits address
	RIIC0.SARL0.BYTE = 0x41;  //ADDRESS SLAVE 
	RIIC0.ICSER.BIT.SAR0E = 1;  //enable Slave address 0
	RIIC0.ICMR1.BIT.MTWP  = 1;  //ENABLE WRITTING TO THE ICCR2.MST and TRS BIT
	RIIC0.ICMR1.BIT.CKS   = 0x000b; // PCLK/1
	RIIC0.ICBRL.BYTE    = 0xF9U;   // 400 kbps 
	RIIC0.ICBRH.BYTE    = 0xEBU;    
	RIIC0.ICMR2.BIT.TMWE = 1;
	RIIC0.ICMR3.BIT.ACKWP = 0;  // disable ACKBT Write Protect
	RIIC0.ICMR3.BIT.WAIT = 1;   // WAIT
	RIIC0.TMOCNTL.BYTE = 0x00;
	RIIC0.TMOCNTU.BYTE = 0x00;
	RIIC0.ICFER.BIT.TMOE = 1;
	
	
	
    /* Set SSCL0 pin */
    MPC.P11PFS.BYTE = 0x0AU;
    PORT1.PMR.BYTE |= 0x02U;

    /* Set SSDA0 pin */
    MPC.P10PFS.BYTE = 0x0AU;
    PORT1.PMR.BYTE |= 0x01U; 
    
    
#endif
#if 1// DAC config
	SYSTEM.MSTPCRA.BIT.MSTPA18 = 0;	// enable DAC module
#endif


	/*** ON protect ***/
	SYSTEM.PRCR.WORD = 0xA500;
	//WDT_SET   watchdog timer
	//initDac();
    initRadioI2C();
	for(i=0;i<5;i++){
		while(IR(CMT0,CMI0) == 0);  //wait flag compare timer
		IR(CMT0,CMI0) = 0;			// reset flag timer
	}
	setLed7Output();
	// Main loop (10ms)
	glCount1Sec = 0;
	glCount10Ms = 100;

	operate();
	sinFreq =100;

	while(1){   
		while(IR(CMT0,CMI0) == 0);  //wait flag compare timer  
		IR(CMT0,CMI0) = 0;// reset flag timer
		//CMT1.CMCOR = 691200/(sinFreq*32)-1;
		//dmy = waveGenCon();

		
	}
}

void operate()
{ 		
	readRadioI2C(glDeviceID,0x01);
	readRadioI2C(glChipID,0x03);
	setPowerRadio(BK1086_POWER_ON);
	
	setClockRadio(0x06,0x0000);   //External clock input
	setClockRadio(0x1D,0xA58F);   //Analog configuration 2
	setClockRadio(0x1C,0x0000);   //Analog configuration 2
	
	switchModeRadio(BK1086_FM);   // Radio in mode FM	
	configRadio(0x05,0x3C4F);     //BAND FM:64MHz-108MHz,Channel Spacing : 100KHz
	configRadio(0x03,0x1167);     // Frequency FM = 99.9 MHz
		
}	



//////////////////////////////////////////////////////////////////////////////////////////
/* Tranmitter and recevier I2C AM FM*/
/* init I2C */
void initRadioI2C()
{

	SDIO_WR = 0;
	SCLK = 0;
	SCLK_DIR = 1;
	SDIO_DIR = 0;
	SCLK_DIR = 0;	
		
}

/* Config power Radio */
unsigned char setPowerRadio(unsigned char data)
{
	unsigned char flg;
	
	startConditionRadio();
	flg = writeRadioI2C(0x80);   //device ID
	if(flg == 0){
		goto END;
	}
	
	flg = writeRadioI2C(0x02);   //Power Config
	if(flg == 0){
		goto END;
	}
	
	flg = writeRadioI2C(0x00);   
	if(flg == 0){
		goto END;
	}
	
	flg = writeRadioI2C(data);   
	if(flg == 0){
		goto END;
	}
		
END:// Issue a stop condition
	stopConditionRadio();
	return flg;
}

/* Start Condition I2C */
void startConditionRadio()
{
	SDIO_DIR = 0;      
	SCLK_DIR = 0;
	SDIO_DIR = 1;
	waitNmc(20);
}

/* Stop condition I2C */
void stopConditionRadio()
{
	SCLK_DIR = 1;     
	SDIO_DIR = 1;     
	waitNmc(5);
	SCLK_DIR = 0;
	SDIO_DIR = 0;
	waitNmc(5);
}

/* Write bus I2C */
unsigned char writeRadioI2C(unsigned char data)
{
	
	unsigned char timeout;
	unsigned char dmy;
	unsigned char pos;
	
	pos = 0x80;
	while(pos){
		SCLK_DIR = 1;
		waitNmc(5);
		if(pos & data){
			SDIO_DIR = 0;
		}
		else{
			SDIO_DIR = 1;
		}
		SCLK_DIR = 0;
		waitNmc(5);
		pos = pos >> 1;
	}
	
	// Wait for ACK
	SCLK_DIR = 1;
	SDIO_DIR = 0;
	waitNmc(5);
	SCLK_DIR = 0;
	timeout = 100;
	while(SDIO_RD && --timeout);
	if(SDIO_RD){
		dmy = 0;
	}
	else{
		dmy = 1;
	}	
	
	return dmy;
}

/*Read bus I2C*/
unsigned char readRadioI2C(unsigned char* des,unsigned char reg)
{
	unsigned char pos;
	unsigned char flg;
	unsigned char i;
	
	startConditionRadio();

	flg = writeRadioI2C(0x80);
	if(flg == 0){
		goto END;
	}

	flg = writeRadioI2C(reg);
	if(flg == 0){
		goto END;
	}
	
	SDIO_DIR = 0; //READ
	
	for(i=0;i<2;i++){
		pos =0x80;
		while(pos){
			SCLK_DIR = 1;
			waitNmc(5);
			SCLK_DIR = 0;
			waitNmc(5);
			if(SDIO_RD){
				*(des+i) |= pos;
			}
			pos = pos >>1;
		}
		SCLK_DIR = 1;
		waitNmc(20);
		if(i==0){
			// return ACK
			SDIO_DIR = 1;
			waitNmc(20);
			SCLK_DIR = 0;
			waitNmc(20);
			SCLK_DIR = 1;
			waitNmc(20);
			SDIO_DIR = 0;
		}
		else{
			// return NACK
			SDIO_DIR = 0;
			waitNmc(20);
			SCLK_DIR = 0;
			waitNmc(20);
		}
	}
	
	
END:	
	stopConditionRadio();
	return flg;
}

/* Setting Clock Radio */
unsigned char setClockRadio(unsigned char reg,unsigned short data)
{
	
	unsigned char flg;
	unsigned short pos;
	unsigned short data1;
	
	startConditionRadio();
	flg = writeRadioI2C(0x80);   //device ID
	if(flg == 0){
		goto END;
	}
	/* Config Clock Radio*/
	flg = writeRadioI2C(reg);   
	if(flg == 0){
		goto END;
	}
	
	pos   = 0xFF00;
	data1 = data&pos;
	data1 = (unsigned char)(data1 >> 8);
	flg = writeRadioI2C(data1);   
	if(flg == 0){
		goto END;
	}
	
	pos   = 0x00FF;
	data1 = data&pos;
	data1 = (unsigned char)(data1);
	flg = writeRadioI2C(data1);   
	if(flg == 0){
		goto END;
	}
		
END:// Issue a stop condition
	stopConditionRadio();
	return flg;
}

/* Mode AM / FM Radio */
unsigned char switchModeRadio(unsigned char data)
{
	unsigned char flg;
	unsigned char pos;
	
	pos = 0x20;
	data = data & pos;
	
	startConditionRadio();
	flg = writeRadioI2C(0x80);   //device ID
	if(flg == 0){
		goto END;
	}
	/* Config Clock Radio*/
	flg = writeRadioI2C(0x07);   // System Configuration 4

	if(flg == 0){
		goto END;
	}
	
	flg = writeRadioI2C(data);   
	if(flg == 0){
		goto END;
	}
	
	flg = writeRadioI2C(0x00);   
	if(flg == 0){
		goto END;
	}
		
END:// Issue a stop condition
	stopConditionRadio();
	return flg;
}

/* Config band,channel spacing, Volume, frequency*/
unsigned char configRadio(unsigned char reg,unsigned short data)	
{
	unsigned char flg;
	unsigned short pos;
	unsigned short data1;
	
	startConditionRadio();
	flg = writeRadioI2C(0x80);   //device ID
	if(flg == 0){
		goto END;
	}
	/* Config Clock Radio*/
	flg = writeRadioI2C(reg);   
	if(flg == ){
		goto END;
	}
	
	pos   = 0xFF00;
	data1 = data&pos;
	data1 = (unsigned char)(data1 >> 8);
	flg = writeRadioI2C(data1);   
	if(flg == 0){
		goto END;
	}
	
	pos   = 0x00FF;
	data1 = data&pos;
	data1 = (unsigned char)(data1);
	flg = writeRadioI2C(data1);   
	if(flg == 0){
		goto END;
	}
		
END:// Issue a stop condition
	stopConditionRadio();
	return flg;
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*DAC practice*/
/* initiate DAC channel*/
void initDac(){		
	DA.DADPR.BYTE = 0x00;	    // choose right-justified	
	DA.DAVREFCR.BYTE = 0x00;	// Reset DAVREFCR register 	
	while(DA.DAVREFCR.BYTE);	// Wait for DAVREFCR register reseted	
	DA.DAVREFCR.BYTE = 0x01;	// Vref = AVCC0	
	if(DA.DAVREFCR.BYTE == 0){ 	
		waitNmc(1000);	// Wait for DAVREFCR register changed
	}
	DA.DAADSCR.BIT.DAADST = 0;
	DA.DACR.BIT.DAOE1 = 1;	// enable DAC
}

/*output sampling value*/
void sinGen(unsigned short* value)
{
	if(wavePos<32){
		DA.DADR1 = *(value + wavePos);	// output sampling value
		wavePos++;
	}
	if(wavePos>31){
		wavePos = 0;
	}
	IR(CMT1,CMI1) = 0;	// reset CMT0 interupt flag
}

/* change freqz */
unsigned char waveGenCon(){
	static unsigned char oldFreq;
	unsigned char flg;
	flg = 0;
	if(oldFreq != sinFreq){
		DA.DACR.BIT.DAOE1 = 0;
		waitNmc(1000);
		oldFreq = sinFreq;
		flg =1;
	}
	
	DA.DACR.BIT.DAOE1 = 1;	// enable DAC
	return flg;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////




/* Data FLASH memmory CPU */
/* Init flash memmory */
void initFlash()
{   
	/* E2 DataFlash Access enable */
	if(FLASH.DFLCTL.BIT.DFLEN == 0){
		FLASH.DFLCTL.BIT.DFLEN = 1;
		while(FLASH.DFLCTL.BIT.DFLEN == 0){
			nop();
		}
		waitNmc(1000);
		
	}
	FLASH.FRESETR.BIT.FRESET = 0;   //Disable reset flash 
	FLASH.FASR.BIT.EXS       = 0;   //user area and data area
}

/* Mode Write / Erase  Flash memmory */
void programingErasuareMode()
{
	FLASH.FENTRYR.WORD = 0xAA00;
	while(FLASH.FENTRYR.WORD != 0x0000);
	FLASH.FENTRYR.WORD     = 0xAA80;     //E2 DataFlash in P/E mode and ROM is in read mode.
	if(SYSTEM.OPCCR.BIT.OPCM == 0){
		FLASH.FPR   = 0xA5;   //Protection Unlock Register
		FLASH.FPMCR.BYTE = 0x10;   //E2 DataFlash P/E mode
		FLASH.FPMCR.BYTE = 0xEF;   //the inverted set value
		FLASH.FPMCR.BYTE = 0x10;
	}
	else{
		FLASH.FPR              = 0xA5;   //Protection Unlock Register
		FLASH.FPMCR.BYTE       = 0x50;   //E2 DataFlash P/E mode
		FLASH.FPMCR.BYTE       = 0xAF;   //the inverted set value
		FLASH.FPMCR.BYTE       = 0x50;
	}
	FLASH.FISR.BYTE = 0x15;	 //set the frequency of the FlashIF clock when programming/erasing
}

/* Transition from E2 DataFlash P/E Mode to ROM/E2 DataFlash Read Mode */
void switchingPeToRead()
{
	/* Disable Write/Erase of DATA Flash */
	FLASH.FPR        = 0xA5;   //Protection Unlock Register
	FLASH.FPMCR.BYTE = 0x08;   //ROM/E2 DataFlash read mode
	FLASH.FPMCR.BYTE = 0xF7;   //the inverted set value
	FLASH.FPMCR.BYTE = 0x08;
	waitNmc(1000);       
	FLASH.FENTRYR.WORD = 0xAA00;
	while(FLASH.FENTRYR.WORD != 0x0000);	
}

/* Erase Flash */
unsigned char eraseFlash(unsigned char index)
{
	unsigned char flg;
	
	initFlash();
    programingErasuareMode();
	FLASH.FRESETR.BIT.FRESET = 0;   //Disable reset flash 
	FLASH.FASR.BIT.EXS       = 0;   //user area and data area
	
	FLASH.FSARH  = 0x0F;    //Start Address Register H
    FLASH.FSARL  = blockAddr[index];  //Start Address Register L
	
	FLASH.FEARH  = 0x0F;    //End Address Register H
	FLASH.FEARL  = blockAddr[index] + 0x3FF;  //End Address Register L
	
	FLASH.FCR.BYTE = 0x84; 
	waitN10ms(30);          //Wait 300ms for erase 
	if(FLASH.FSTATR0.BIT.ERERR){  
		flg = 0;            //An error occurs during erasure.
	}
	else{
		flg = 1;            //Erasure terminates normally
	}
	while(FLASH.FSTATR1.BIT.FRDY == 0); //processing to complete the software command ?

	FLASH.FCR.BYTE = 0x00;     // Stop processing
	while(FLASH.FSTATR1.BIT.FRDY != 0);
	if((FLASH.FSTATR0.BIT.ILGLERR == 1) || (FLASH.FSTATR0.BIT.ERERR == 1)){
		FLASH.FRESETR.BIT.FRESET = 1;
		nop();
		nop();
		FLASH.FRESETR.BIT.FRESET = 0;
	}  
	switchingPeToRead();
	return flg;
}

/* write flash memmory */ 
unsigned char writeFlash(unsigned char* arrData,unsigned short len,unsigned short address)
{   
	unsigned char flg;
	unsigned short i;
	unsigned long Daddr;
	
	initFlash();
    programingErasuareMode();
	Daddr = address;
	for(i=0;i<len;i++,Daddr++){
		/* Write start address setting */
		FLASH.FSARH  = 0x0F;    //Start Address Register H   
		FLASH.FSARL  = Daddr;   //Start Address Register L 
		
		/* Write data setting */
		FLASH.FWBH = 0x0000;
		FLASH.FWBL = *(arrData + i);    //Data in buffer
		
		/* Execute Write command */
		FLASH.FCR.BYTE = 0x81;
		//waitN10ms(50);           // wait 500ms for write 1 byte flash
		
		if(FLASH.FSTATR0.BIT.PRGERR){  
			flg = 0;
			break;  			//An error occurs during programming.
		}
		else{
			flg = 1;            //Programming terminates normally.
		}
		while(FLASH.FSTATR1.BIT.FRDY == 0); //processing to complete the software command ?

		FLASH.FCR.BYTE = 0x00;     // Stop processing
		while(FLASH.FSTATR1.BIT.FRDY != 0);
		if((FLASH.FSTATR0.BIT.ILGLERR == 1) || (FLASH.FSTATR0.BIT.ERERR == 1)){
				FLASH.FRESETR.BIT.FRESET = 1;
				nop();
				nop();
				FLASH.FRESETR.BIT.FRESET = 0;
				
				flg = 0;
				break;
		}
	}
	switchingPeToRead();
	return flg;
    	
}

/* read flash memmory */
unsigned char readFlash(unsigned char* arrReadData,unsigned short len,unsigned long address)
{
	
	unsigned char* pos;
	unsigned short i;
	if(address < 0x100000 || address > 0x101FFF){
		return 0;
	}
	initFlash();
	pos = (unsigned char*)address;
	for(i=0;i<len;i++){
		*(arrReadData + i) = *(pos + i);
	}
	return 1;
}

/* Save data permanent*/
unsigned char saveDataPer(unsigned char* data, unsigned short saveAdd, unsigned short dataLen) // dataLen not include CRC code's length
{	
	unsigned char flg;
	unsigned char i;
	unsigned char blk;
	unsigned char readDataTemp[1];
	unsigned short bitPos;
	unsigned short remainder;
	unsigned short crcFormula;
#if 1// Block selecting(blk)
	if((saveAdd >= blockAddr[0]) && (saveAdd < blockAddr[1])){
		blk = 0;
	}
	else if((saveAdd >= blockAddr[1]) && (saveAdd < blockAddr[2])){
		blk = 1;
	}
	else if((saveAdd >= blockAddr[2]) && (saveAdd < blockAddr[3])){
		blk = 2;
	}
	else if((saveAdd >= blockAddr[3]) && (saveAdd < blockAddr[4])){
		blk = 3;
	}
	else if((saveAdd >= blockAddr[4]) && (saveAdd < blockAddr[5])){
		blk = 4;
	}
	else if((saveAdd >= blockAddr[5]) && (saveAdd < blockAddr[6])){
		blk = 5;
	}
	else if((saveAdd >= blockAddr[6]) && (saveAdd < blockAddr[7])){
		blk = 6;
	}
	else if((saveAdd >= blockAddr[7]) && (saveAdd < 0xF2FF)){
		blk = 7;
	}
	

#endif
	// save data
	eraseFlash(blk); // erase block contain saveAdd
	encodeCRC(data,dataLen); // encode data
	while(!(writeFlash(data,dataLen+1,saveAdd))); // write encoded data to flash
	
	//check data saving correction
	crcFormula = 0x01D5;	//CRC key generate code
	remainder = 0x0000;     // crc code container
	
	for(i = 0; i<dataLen+1; i++){
		readFlash(readDataTemp,1,saveAdd+0xF000+i); // read single element from flash
		bitPos = 0x80;
		while(bitPos){
			remainder = remainder<< 1;
			if( readDataTemp[0] & bitPos){
				remainder = remainder | 1;
			}
			if(remainder & 0x0100){                  
				remainder = remainder^crcFormula;
			}
			bitPos = bitPos >> 1;
		}
	}
	
	if(remainder){
		flg = 0; // saving data incorrectly
	}
	else{
		flg = 1; // saving data correctly
	}	
	return flg;
		
}

/* Decode Cyclic Redundancy Check */
unsigned char decodeCRC(unsigned char* s_sour, unsigned short len) // len include crc code
{	
	unsigned char flg;
	unsigned short bytePos;
	unsigned short bitPos;
	unsigned short crcDmy;
	unsigned short crcFormula;
	crcFormula = 0x01D5;
	crcDmy = 0x0000;     // crc code contain
	for(bytePos=0; bytePos<len; bytePos++){
		bitPos = 0x80;
		while(bitPos){
			crcDmy = crcDmy<< 1;
			if(*(s_sour + bytePos) & bitPos){
				crcDmy = crcDmy | 1;
			}
			if(crcDmy & 0x0100){                  
				crcDmy = crcDmy^crcFormula;
			}
			bitPos = bitPos >> 1;
		}
	}
	if(crcDmy){
		flg = 0;
	}
	else{
		flg = 1;
	}	
	return flg;
	


	
}

/* Encode Cyclic Redundancy Check */
void encodeCRC(unsigned char* s_pos, unsigned short len) // len not include crc
{
	unsigned char crcCode;
	unsigned char i;
	unsigned short crcFormula;
	unsigned short bytePos;
	unsigned short bitPos;
	unsigned short crcDmy;
	
   
	crcFormula = 0x01D5; // 111010101
   	crcDmy = 0x0000;
	for(bytePos=0; bytePos<len; bytePos++){
		bitPos = 0x80;
		while(bitPos){
			crcDmy = crcDmy<< 1;
			if(*(s_pos + bytePos) & bitPos){
				crcDmy = crcDmy | 1;
			}
			if(crcDmy & 0x0100){
				crcDmy = crcDmy^crcFormula;
			}
			bitPos = bitPos >> 1;
		}
	}
   
	for(i=0; i<8; i++){
		crcDmy = crcDmy << 1;
		if(crcDmy & 0x0100){
			crcDmy = crcDmy^crcFormula;
		}
	}
	
	crcCode = (unsigned char)(crcDmy & 0xFF);
	*(s_pos + bytePos) = crcCode;


}


///////////////////////////////////////////////////////////////////////////////////////////////////////
	

/* Tranmitter and recevier I2C */
/* init I2C */
void initI2C()
{
	SCL = 0;
	SDA_WR = 0;     //SDA output data = 0z
	SDA_DIR = 0;
	SCL_DIR = 0;
}

/* Start Condition I2C */
void startCondition()
{
	SDA_DIR = 0;      //SDA = 1
	SCL_DIR = 0;
	SDA_DIR = 1;
	waitNmc(5);
}

/* Stop condition I2C */
void stopCondition()
{
	SCL_DIR = 1;     //SCL output = 0 always
	SDA_DIR = 1;     //SDA output = 0 always
	waitNmc(5);
	SCL_DIR = 0;
	SDA_DIR = 0;
	waitNmc(5);
}

/* Write bus I2C */
unsigned char writeI2C(unsigned char data)
{
	unsigned char timeout;
	unsigned char dmy;
	unsigned char pos;
	
	pos = 0x80;
	while(pos){
		SCL_DIR = 1;
		waitNmc(5);
		if(pos & data){
			SDA_DIR = 0;
		}
		else{
			SDA_DIR = 1;
		}
		SCL_DIR = 0;
		waitNmc(5);
		pos = pos >> 1;
	}
	
	// Wait for ACK
	SCL_DIR = 1;
	SDA_DIR = 0;
	waitNmc(5);
	SCL_DIR = 0;
	timeout = 100;
	while(SDA_RD && --timeout);
	if(SDA_RD){
		dmy = 0;
	}
	else{
		dmy = 1;
	}	
	
	return dmy;
}

/* Read bus I2C */
unsigned char readI2C(unsigned char data)
{
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////


// Set LED7 output
unsigned char setLed7Output()
{
	unsigned char addr;
	unsigned char data;
	unsigned char cmd;
	unsigned char flg;
	
	// Issue a start condition
	startCondition();
	
	// Set Port 0 and Port 1 of IC7002 to output port
	addr = I2C_ADDR_TCA6416AR_L;
	flg = writeI2C(addr);
	if(flg == 0){
		goto END;
	}
	
	cmd = TCA6416A_CONFIG_PORT_0;
	flg = writeI2C(cmd);
	if(flg == 0){
		goto END;
	}
	
	data = 0;
	flg = writeI2C(data);	// PORT 0
	if(flg == 0){
		goto END;
	}
	
	flg = writeI2C(data);	// PORT 1
	if(flg == 0){
		goto END;
	}
	
	// Issue a stop condition
	stopCondition();
	
	waitNmc(100);
#if 1	
	// Issue a start condition
	startCondition();
	
	// Set Port 0 and Port 1 of IC7003 to output port
	addr = I2C_ADDR_TCA6416AR_H;
	flg = writeI2C(addr);
	if(flg == 0){
		goto END;
	}
	
	cmd = TCA6416A_CONFIG_PORT_0;
	flg = writeI2C(cmd);
	if(flg == 0){
		goto END;
	}
	
	data = 0;
	flg = writeI2C(data);	// PORT 0
	if(flg == 0){
		goto END;
	}
	
	flg = writeI2C(data);	// PORT 1
	if(flg == 0){
		goto END;
	}
#endif
	
END:
	// Issue a stop condition
	stopCondition();
	
	return flg;
}	

/* Set Single Led 7 segment */
void setSingleLed7(unsigned char index, unsigned char data)
{
	unsigned char addr;
	unsigned char cmd;
	unsigned char flg;
	
	// Issue a start condition
	startCondition();
	
	// Write Address byte
	if(index < 2){
		addr = I2C_ADDR_TCA6416AR_H;
	}
	else{
		addr = I2C_ADDR_TCA6416AR_L;	
	}
	flg = writeI2C(addr);
	if(flg == 0){
		goto END;
	}
	
	// Write command byte
	if(index % 2){
		cmd = TCA6416A_OUTPUT_PORT_0;
	}
	else{
		cmd = TCA6416A_OUTPUT_PORT_1;
	}
	flg = writeI2C(cmd);
	if(flg == 0){
		goto END;
	}
	
	// Write data byte
	flg = writeI2C(data);
	if(flg == 0){
		goto END;
	}
	
END:
	// Issue a stop condition
	stopCondition();
}

/* Set all Led 7 segment */
void setAllLed7()
{      

	setSingleLed7(Led7seg_1,extGpioPort.P0.BYTE);
	setSingleLed7(Led7seg_2,extGpioPort.P1.BYTE);
	
	setSingleLed7(Led7seg_3,extGpioPort.P2.BYTE);
	setSingleLed7(Led7seg_4,extGpioPort.P3.BYTE);
    setLed7Output();
}

/* Counting Led 0000 - 9999 */
// Set LED7 segment
void setLed7()
{
	unsigned short data;
	unsigned char dmy;
	unsigned char i;
	
	// Get display value
	data = glCount1Sec;
	if(data > 999){	// 1xxx
		dmy = (char)((data - (data % 1000)) / 1000);
	}
	else{
		dmy = 0;
	}
	glLed7Data[3] = dmy;
	data = data % 1000;// xxx
	if(data > 99){	// 1xx
		dmy = (char)((data - (data % 100)) / 100);
	}
	else{
		dmy = 0;
	}
	glLed7Data[2] = dmy;
	data = data % 100;// xx
	if(data > 9){	// 1x
		dmy = (char)((data - (data % 10)) / 10);
	}
	else{
		dmy = 0;
	}
	glLed7Data[1] = dmy;
	data = data % 10;// x
	glLed7Data[0] = (char)(data);
	
	// Get LED7 charactor
	for(i=0;i<4;i++){
		glLed7Dis[i] = led7CharacterTable1[glLed7Data[i]];
	}
	
	// Put display data into bit access structure array
	led7DispData.P0.BYTE = glLed7Dis[0]; 
	led7DispData.P1.BYTE = glLed7Dis[1];
	led7DispData.P2.BYTE = glLed7Dis[2];
	led7DispData.P3.BYTE = glLed7Dis[3];
#if 1	
	// Re-assign GPIO ports to LED7 segments
	// LED 1 //
	extGpioPort.P0.BIT.B5 = led7DispData.P0.BIT.B7; //DP    1
	extGpioPort.P0.BIT.B0 = led7DispData.P0.BIT.B6; //G     0
	extGpioPort.P0.BIT.B2 = led7DispData.P0.BIT.B5; //F     1
	extGpioPort.P1.BIT.B4 = led7DispData.P0.BIT.B4; //E     
	extGpioPort.P0.BIT.B1 = led7DispData.P0.BIT.B3; //D     1
	extGpioPort.P0.BIT.B6 = led7DispData.P0.BIT.B2; //C     0
	extGpioPort.P0.BIT.B4 = led7DispData.P0.BIT.B1; //B     0
	extGpioPort.P0.BIT.B3 = led7DispData.P0.BIT.B0; //A     1
	
	// LED 2 //
	extGpioPort.P0.BIT.B7 = led7DispData.P1.BIT.B7; //DP    0
	extGpioPort.P1.BIT.B2 = led7DispData.P1.BIT.B6; //G
	extGpioPort.P1.BIT.B7 = led7DispData.P1.BIT.B5; //F
	extGpioPort.P1.BIT.B1 = led7DispData.P1.BIT.B4; //E
	extGpioPort.P1.BIT.B0 = led7DispData.P1.BIT.B3; //D
	extGpioPort.P1.BIT.B5 = led7DispData.P1.BIT.B2; //C
	extGpioPort.P1.BIT.B3 = led7DispData.P1.BIT.B1; //B
	extGpioPort.P1.BIT.B6 = led7DispData.P1.BIT.B0; //A
	
	// LED 3 //
	extGpioPort.P2.BIT.B5 = led7DispData.P2.BIT.B7; //DP
	extGpioPort.P2.BIT.B0 = led7DispData.P2.BIT.B6; //G
	extGpioPort.P2.BIT.B2 = led7DispData.P2.BIT.B5; //F
	extGpioPort.P3.BIT.B4 = led7DispData.P2.BIT.B4; //E
	extGpioPort.P2.BIT.B1 = led7DispData.P2.BIT.B3; //D
	extGpioPort.P2.BIT.B6 = led7DispData.P2.BIT.B2; //C
	extGpioPort.P2.BIT.B4 = led7DispData.P2.BIT.B1; //B
	extGpioPort.P2.BIT.B3 = led7DispData.P2.BIT.B0; //A
	
	// LED 4 //
	extGpioPort.P2.BIT.B7 = led7DispData.P3.BIT.B7; //DP
	extGpioPort.P3.BIT.B2 = led7DispData.P3.BIT.B6; //G
	extGpioPort.P3.BIT.B7 = led7DispData.P3.BIT.B5; //F
	extGpioPort.P3.BIT.B1 = led7DispData.P3.BIT.B4; //E
	extGpioPort.P3.BIT.B0 = led7DispData.P3.BIT.B3; //D
	extGpioPort.P3.BIT.B5 = led7DispData.P3.BIT.B2; //C
	extGpioPort.P3.BIT.B3 = led7DispData.P3.BIT.B1; //B
	extGpioPort.P3.BIT.B6 = led7DispData.P3.BIT.B0; //A	
#endif	
	// Set all LED7 (Write data to external GPIO driver)
	setAllLed7();
}

#if 0
/* Init Led 7 segment */
void initLed7()
{
	glLed7Dis[0] = 0;
	glLed7Dis[1] = 0;
	glLed7Dis[2] = 0;
	glLed7Dis[3] = 0;
	
}

/* take led 7 character */
void takeLed7Character (unsigned char index,unsigned char data)
{   
        
		if(index == 1){      // led 2
			LED2_Dp = logicAnd(led7CharacterTable1[data],0x80);
		    LED2_G  = logicAnd(led7CharacterTable1[data],0x40); 
		    LED2_F  = logicAnd(led7CharacterTable1[data],0x20);
			LED2_E  = logicAnd(led7CharacterTable1[data],0x10);
			LED2_D  = logicAnd(led7CharacterTable1[data],0x08);
		    LED2_C  = logicAnd(led7CharacterTable1[data],0x04);
			LED2_B  = logicAnd(led7CharacterTable1[data],0x02);
			LED2_A  = logicAnd(led7CharacterTable1[data],0x01);
        }
        else if(index == 3){      // led 4
			LED4_Dp = logicAnd(led7CharacterTable1[data],0x80);
		    LED4_G  = logicAnd(led7CharacterTable1[data],0x40); 
		    LED4_F  = logicAnd(led7CharacterTable1[data],0x20);
			LED4_E  = logicAnd(led7CharacterTable1[data],0x10);
			LED4_D  = logicAnd(led7CharacterTable1[data],0x08);
		    LED4_C  = logicAnd(led7CharacterTable1[data],0x04);
			LED4_B  = logicAnd(led7CharacterTable1[data],0x02);
			LED4_A  = logicAnd(led7CharacterTable1[data],0x01);
		}		
		else if(index == 0 ) {    // led 1
		    LED1_Dp = logicAnd(led7CharacterTable1[data],0x80);
		    LED1_G  = logicAnd(led7CharacterTable1[data],0x40); 
		    LED1_F  = logicAnd(led7CharacterTable1[data],0x20);
			LED1_E  = logicAnd(led7CharacterTable1[data],0x10);
			LED1_D  = logicAnd(led7CharacterTable1[data],0x08);
		    LED1_C  = logicAnd(led7CharacterTable1[data],0x04);
			LED1_B  = logicAnd(led7CharacterTable1[data],0x02);
			LED1_A  = logicAnd(led7CharacterTable1[data],0x01);
		}
		else if(index == 2){      // led 3
			LED3_Dp = logicAnd(led7CharacterTable1[data],0x80);
		    LED3_G  = logicAnd(led7CharacterTable1[data],0x40); 
		    LED3_F  = logicAnd(led7CharacterTable1[data],0x20);
			LED3_E  = logicAnd(led7CharacterTable1[data],0x10);
			LED3_D  = logicAnd(led7CharacterTable1[data],0x08);
		    LED3_C  = logicAnd(led7CharacterTable1[data],0x04);
			LED3_B  = logicAnd(led7CharacterTable1[data],0x02);
			LED3_A  = logicAnd(led7CharacterTable1[data],0x01);
		}
        			
}	


/* Function counter Led 7 segment */
void counterLed7()
{
	if((++glLed7Dis[0])>9){
		glLed7Dis[0] = 0;
		if((++glLed7Dis[1])>9){
			glLed7Dis[1] = 0;
			if((++glLed7Dis[2])>9){
				glLed7Dis[2] = 0;
				if((++glLed7Dis[3])>9){
					glLed7Dis[3] = 0;
				}
				else{
					goto OUT;
				}
			}
			else{
				goto OUT;
			}
		}
		else{
			goto OUT;
		}
	}	
OUT:	
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////	
		


	
/* Switch check and proccess */
// Get status of all switches
void getAllSwitchStatus()
{
	getSwitchStatus(S_SW1,SW1);
	getSwitchStatus(S_SW2,SW2);
	getSwitchStatus(S_SW3,SW3);
	getSwitchStatus(S_SW4,SW4);
}

// Get status of single switch
void getSwitchStatus(unsigned char Index, unsigned char Value)
{
	glSwFlag[Index] = 0;
	if(Value == 0){		// Switch ON
		if(glSwBak[Index] == 0){
			glSwBak[Index] = 1;
		}
		else{
			if(glSw[Index] == 0){
				glSw[Index] = 1;
				glSwFlag[Index] = 1;
			}
		}
	}
	else{				// Switch OFF
		if(glSwBak[Index] == 1){
			glSwBak[Index] = 0;
		}
		else{
			if(glSw[Index] == 1){   
				glSw[Index] = 0;
				glSwFlag[Index] = 1;
			}
		}
	}
}

// Get long press status of all switches
void getAllSwitchLongPressStatus()
{
	getSwitchLongPressStatus(S_SW1);
	getSwitchLongPressStatus(S_SW2);
	getSwitchLongPressStatus(S_SW3);
	getSwitchLongPressStatus(S_SW4);
}

// Get long press status of single switch
void getSwitchLongPressStatus(unsigned char Index)
{
	glSwLongPressFlag[Index] = 0;
	
	if(glSwFlag[Index]){
		if(glSw[Index] == 1){
			glSwLongPressTimer[Index] = 100;
			glSwLongPressOn[Index] = 0;
		}
	}
	
	if(glSw[Index] == 1){
		if(glSwLongPressOn[Index] == 0){
			if(glSwLongPressTimer[Index]){
				glSwLongPressTimer[Index]--;
				if(glSwLongPressTimer[Index] == 0){
					glSwLongPressOn[Index] = 1;
					glSwLongPressFlag[Index] = 1;
				}
			}
		}
	}
	else{
		glSwLongPressTimer[Index] = 0;
		glSwLongPressOn[Index] = 0;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////


/* Set LEDs */
// Set all LEDs
void setAllLeds()
{
	//LED_W = setSingleLed(L_LED_W);
}

// Set output of single LED
unsigned char setSingleLed(unsigned char Index)
{
	unsigned char dmy;
	
	if(glLed[Index]){
		dmy = 1;
	}
	else{
		dmy = 0;
	}
	
	return dmy;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////


/* Calculator */
/* XOR logic */
unsigned char xorLogic(unsigned short a,unsigned short b)
{
	if(a == 0 && b == 0){
		return 0;
	}
	else if( a == 0 && b == 1){
		return 1;
	}
	else if( a == 1 && b == 0){
		return 1;
	}
	else if( a == 1 && b == 1){
		return 0;
	}
}

/* And logic */
unsigned char andLogic(unsigned short data,unsigned short pos)
{
	if(data & pos){
		data = 1;
	}
	else{
		data = 0;
	}
	return data;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////


// Timer //
// Time counter
void timeCount()
{
	if(glCount10Ms){ 
		glCount10Ms--;
		if(glCount10Ms == 0){
			glCount1Sec++;
			if(glCount1Sec > 9999){
				glCount1Sec = 0;
			}
			glCount10Ms = 100;
		}
	}
}

/* Wait MC */
void waitNmc (unsigned char interval)
{
	while(interval > 0){
	   nop();
	   interval--;
	}
}

/* Wait ms */
void waitN10ms (unsigned char interval)
{
	while(interval > 0)
	{
	while(IR(CMT0,CMI0) == 0);  //wait flag compare timer
    IR(CMT0,CMI0) = 0;			// reset flag timer
	interval --;
	}
}

/* wait second */
void waitNsec (unsigned char interval)
{  
	unsigned char loop;
	loop = 100;
	while(interval){
		while(loop > 0){
			while(IR(CMT0,CMI0) == 0);  //wait flag compare timer
			IR(CMT0,CMI0) = 0;			// reset flag timer
			loop --;
		}
		interval --;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////




