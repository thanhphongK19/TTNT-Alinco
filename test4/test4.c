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
	
	/*** すべての割り込みを禁止　***/
	set_psw(0x00000000);
	
    /*** プロテクト解除 ***/
    SYSTEM.PRCR.WORD = 0xA507;
	
	/*** サブクロック停止 ***/ 
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
	
	/*** メインクロック動作設定　***/
	SYSTEM.MOFCR.BYTE = 0x20;		// 発信子、10MHz~20MHz
	SYSTEM.MOSCWTCR.BYTE = 0x07;	// 発信器ウェイト時間 = 65536サイクル（16.384ms）
	SYSTEM.MOSCCR.BYTE = 0x00;		// メインクロック発信器動作
	while(SYSTEM.OSCOVFSR.BIT.MOOVF != 1);	// メインクロックが安定するまで待つ
	
	/*** PLL回路設定 ***/
	SYSTEM.PLLCR.WORD = 0x0B01;		// (14.7456 / 2) * 6 = 44.2368MHz
	SYSTEM.PLLCR2.BYTE = 0x00;		// PLL回路動作
	while (SYSTEM.OSCOVFSR.BIT.PLOVF != 1);	// PLL回路が安定するまで待つ
	
	/*** クロック分周設定　***/
	SYSTEM.SCKCR.LONG = 0x11000101;		// ICLK,PCLKD,PCLKB,FCLK: 2分周（システムクロック：44.2368 / 2 = 22.1184MHz）
	//SYSTEM.SCKCR.LONG = 0x21000101;		// ICLK,PCLKD,PCLKB: 2分周（システムクロック：44.2368 / 2 = 22.1184MHz）, FCLK: 4分周
	
	/*** クロックソース設定***/
	SYSTEM.SCKCR3.WORD = 0x0400;		// PLL選択
	
#if 1// CMT0 (Used as 10ms counter)
	MSTP(CMT0) = 0;					// Enable CMT0
	CMT0.CMCR.BIT.CMIE = 0;
	CMT.CMSTR0.BIT.STR0 = 0;		// Stop CMT0
	CMT0.CMCR.BIT.CKS = 1;			// 22.1184MHz / 32 = 691.200kHz
	CMT0.CMCOR = 6912 - 1;			// 691.200kHz / 6912 = 100Hz
	CMT0.CMCR.BIT.CMIE = 1;
	CMT0.CMCNT = 0;
	IR(CMT0,CMI0) = 0;
	IPR(CMT0,CMI0) = 0x01;
	//IEN(CMT0,CMI0) = 1;
	CMT.CMSTR0.BIT.STR0 = 1;		// Start CMT0
#endif	

#if 1// 
	PORTA.PDR.BIT.B0 = 1;
	PORTA.PMR.BIT.B0 = 0;
	PORTC.PDR.BIT.B0 = 0;  	// SW2
	PORTC.PDR.BIT.B1 = 0; 	// SW1
	PORTB.PDR.BIT.B7 = 0;  	// SW3
	PORTB.PDR.BIT.B6 = 0;  	// SW4
  
	PORTC.PMR.BIT.B0 = 0;  	// SW2
	PORTC.PMR.BIT.B1 = 0; 	// SW1
	PORTB.PMR.BIT.B7 = 0;  	// SW3
	PORTB.PMR.BIT.B6 = 0;   // SW4
#endif
	
	/*** プロテクト有効 ***/
	SYSTEM.PRCR.WORD = 0xA500;
	//WDT_SET

	// Main loop (10ms)
	while(1)
	{
		while(IR(CMT0,CMI0) == 0);
		IR(CMT0,CMI0) = 0;
		getAllSwitchStatus();
		getAllSwitchLongPressStatus();
		operate();
		setAllLeds();
	}
}

void operate()
{
	if(glSwLongPressFlag[S_SW1]){
		if(glSwLongPressOn[S_SW1] && glSwLongPressOn[S_SW2]){
			glLed[L_LED_W] = ~glLed[L_LED_W];
		}
	}
	if(glSwLongPressFlag[S_SW2]){
		if(glSwLongPressOn[S_SW1] && glSwLongPressOn[S_SW2]){
			glLed[L_LED_W] = ~glLed[L_LED_W];
		}
	}
}

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



/* Set LEDs */
// Set all LEDs
void setAllLeds()
{
	LED_W = setSingleLed(L_LED_W);
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








