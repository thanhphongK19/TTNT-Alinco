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
/************************************************************************
*
* Device     : RX/RX100/RX113
*
* File Name  : intprg.c
*
* Abstract   : Interrupt Program.
*
* History    : 1.00  (2013-11-18)  [Hardware Manual Revision : 0.40]
*            : 1.10  (2014-02-26)  [Hardware Manual Revision : 0.50]
*            : 1.1A  (2015-04-20)  [Hardware Manual Revision : 1.02]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2015 (2013 - 2014) Renesas Electronics Corporation.
*
************************************************************************/

#include <machine.h>
#include "vect.h"
#pragma section IntPRG

// Exception(Supervisor Instruction)
void Excep_SuperVisorInst(void){/* brk(){  } */}

// Exception(Undefined Instruction)
void Excep_UndefinedInst(void){/* brk(){  } */}

// NMI
void NonMaskableInterrupt(void){/* brk(){  } */}

// Dummy
void Dummy(void){/* brk(){  } */}

// BRK
void Excep_BRK(void){ wait(); }

// BSC BUSERR
void Excep_BSC_BUSERR(void){ }

// FCU FRDYI
void Excep_FCU_FRDYI(void){ }

// ICU SWINT
void Excep_ICU_SWINT(void){ }

// CMT0 CMI0
void Excep_CMT0_CMI0(void){ }

// CMT1 CMI1
void Excep_CMT1_CMI1(void){ }

// CMT2 CMI2
void Excep_CMT2_CMI2(void){ }

// CMT3 CMI3
void Excep_CMT3_CMI3(void){ }

// CAC FERRF
void Excep_CAC_FERRF(void){ }

// CAC MENDF
void Excep_CAC_MENDF(void){ }

// CAC OVFF
void Excep_CAC_OVFF(void){ }

// USB0 D0FIFO0
void Excep_USB0_D0FIFO0(void){ }

// USB0 D1FIFO0
void Excep_USB0_D1FIFO0(void){ }

// USB0 USBI0
void Excep_USB0_USBI0(void){ }

// RSPI0 SPEI0
void Excep_RSPI0_SPEI0(void){ }

// RSPI0 SPRI0
void Excep_RSPI0_SPRI0(void){ }

// RSPI0 SPTI0
void Excep_RSPI0_SPTI0(void){ }

// RSPI0 SPII0
void Excep_RSPI0_SPII0(void){ }

// DOC DOPCF
void Excep_DOC_DOPCF(void){ }

// CMPB CMPB0
void Excep_CMPB_CMPB0(void){ }

// CMPB CMPB1
void Excep_CMPB_CMPB1(void){ }

// CTSU CTSUWR
void Excep_CTSU_CTSUWR(void){ }

// CTSU CTSURD
void Excep_CTSU_CTSURD(void){ }

// CTSU CTSUFN
void Excep_CTSU_CTSUFN(void){ }

// RTC CUP
void Excep_RTC_CUP(void){ }

// ICU IRQ0
void Excep_ICU_IRQ0(void){ }

// ICU IRQ1
void Excep_ICU_IRQ1(void){ }

// ICU IRQ2
void Excep_ICU_IRQ2(void){ }

// ICU IRQ3
void Excep_ICU_IRQ3(void){ }

// ICU IRQ4
void Excep_ICU_IRQ4(void){ }

// ICU IRQ5
void Excep_ICU_IRQ5(void){ }

// ICU IRQ6
void Excep_ICU_IRQ6(void){ }

// ICU IRQ7
void Excep_ICU_IRQ7(void){ }

// ELC ELSR8I
void Excep_ELC_ELSR8I(void){ }

// LVD LVD1
void Excep_LVD_LVD1(void){ }

// LVD LVD2
void Excep_LVD_LVD2(void){ }

// USB0 USBR0
void Excep_USB0_USBR0(void){ }

// RTC ALM
void Excep_RTC_ALM(void){ }

// RTC PRD
void Excep_RTC_PRD(void){ }

// S12AD S12ADI0
void Excep_S12AD_S12ADI0(void){ }

// S12AD GBADI
void Excep_S12AD_GBADI(void){ }

// ELC ELSR18I
void Excep_ELC_ELSR18I(void){ }

// SSI0 SSIF0
void Excep_SSI0_SSIF0(void){ }

// SSI0 SSIRXI0
void Excep_SSI0_SSIRXI0(void){ }

// SSI0 SSITXI0
void Excep_SSI0_SSITXI0(void){ }

// MTU0 TGIA0
void Excep_MTU0_TGIA0(void){ }

// MTU0 TGIB0
void Excep_MTU0_TGIB0(void){ }

// MTU0 TGIC0
void Excep_MTU0_TGIC0(void){ }

// MTU0 TGID0
void Excep_MTU0_TGID0(void){ }

// MTU0 TCIV0
void Excep_MTU0_TCIV0(void){ }

// MTU0 TGIE0
void Excep_MTU0_TGIE0(void){ }

// MTU0 TGIF0
void Excep_MTU0_TGIF0(void){ }

// MTU1 TGIA1
void Excep_MTU1_TGIA1(void){ }

// MTU1 TGIB1
void Excep_MTU1_TGIB1(void){ }

// MTU1 TCIV1
void Excep_MTU1_TCIV1(void){ }

// MTU1 TCIU1
void Excep_MTU1_TCIU1(void){ }

// MTU2 TGIA2
void Excep_MTU2_TGIA2(void){ }

// MTU2 TGIB2
void Excep_MTU2_TGIB2(void){ }

// MTU2 TCIV2
void Excep_MTU2_TCIV2(void){ }

// MTU2 TCIU2
void Excep_MTU2_TCIU2(void){ }

// MTU3 TGIA3
void Excep_MTU3_TGIA3(void){ }

// MTU3 TGIB3
void Excep_MTU3_TGIB3(void){ }

// MTU3 TGIC3
void Excep_MTU3_TGIC3(void){ }

// MTU3 TGID3
void Excep_MTU3_TGID3(void){ }

// MTU3 TCIV3
void Excep_MTU3_TCIV3(void){ }

// MTU4 TGIA4
void Excep_MTU4_TGIA4(void){ }

// MTU4 TGIB4
void Excep_MTU4_TGIB4(void){ }

// MTU4 TGIC4
void Excep_MTU4_TGIC4(void){ }

// MTU4 TGID4
void Excep_MTU4_TGID4(void){ }

// MTU4 TCIV4
void Excep_MTU4_TCIV4(void){ }

// MTU5 TGIU5
void Excep_MTU5_TGIU5(void){ }

// MTU5 TGIV5
void Excep_MTU5_TGIV5(void){ }

// MTU5 TGIW5
void Excep_MTU5_TGIW5(void){ }

// POE OEI1
void Excep_POE_OEI1(void){ }

// POE OEI2
void Excep_POE_OEI2(void){ }

// TMR0 CMIA0
void Excep_TMR0_CMIA0(void){ }

// TMR0 CMIB0
void Excep_TMR0_CMIB0(void){ }

// TMR0 OVI0
void Excep_TMR0_OVI0(void){ }

// TMR1 CMIA1
void Excep_TMR1_CMIA1(void){ }

// TMR1 CMIB1
void Excep_TMR1_CMIB1(void){ }

// TMR1 OVI1
void Excep_TMR1_OVI1(void){ }

// TMR2 CMIA2
void Excep_TMR2_CMIA2(void){ }

// TMR2 CMIB2
void Excep_TMR2_CMIB2(void){ }

// TMR2 OVI2
void Excep_TMR2_OVI2(void){ }

// TMR3 CMIA3
void Excep_TMR3_CMIA3(void){ }

// TMR3 CMIB3
void Excep_TMR3_CMIB3(void){ }

// TMR3 OVI3
void Excep_TMR3_OVI3(void){ }

// SCI2 ERI2
void Excep_SCI2_ERI2(void){ }

// SCI2 RXI2
void Excep_SCI2_RXI2(void){ }

// SCI2 TXI2
void Excep_SCI2_TXI2(void){ }

// SCI2 TEI2
void Excep_SCI2_TEI2(void){ }

// SCI0 ERI0
void Excep_SCI0_ERI0(void){ }

// SCI0 RXI0
void Excep_SCI0_RXI0(void){ }

// SCI0 TXI0
void Excep_SCI0_TXI0(void){ }

// SCI0 TEI0
void Excep_SCI0_TEI0(void){ }

// SCI1 ERI1
void Excep_SCI1_ERI1(void){ }

// SCI1 RXI1
void Excep_SCI1_RXI1(void){ }

// SCI1 TXI1
void Excep_SCI1_TXI1(void){ }

// SCI1 TEI1
void Excep_SCI1_TEI1(void){ }

// SCI5 ERI5
void Excep_SCI5_ERI5(void){ }

// SCI5 RXI5
void Excep_SCI5_RXI5(void){ }

// SCI5 TXI5
void Excep_SCI5_TXI5(void){ }

// SCI5 TEI5
void Excep_SCI5_TEI5(void){ }

// SCI6 ERI6
void Excep_SCI6_ERI6(void){ }

// SCI6 RXI6
void Excep_SCI6_RXI6(void){ }

// SCI6 TXI6
void Excep_SCI6_TXI6(void){ }

// SCI6 TEI6
void Excep_SCI6_TEI6(void){ }

// SCI8 ERI8
void Excep_SCI8_ERI8(void){ }

// SCI8 RXI8
void Excep_SCI8_RXI8(void){ }

// SCI8 TXI8
void Excep_SCI8_TXI8(void){ }

// SCI8 TEI8
void Excep_SCI8_TEI8(void){ }

// SCI9 ERI9
void Excep_SCI9_ERI9(void){ }

// SCI9 RXI9
void Excep_SCI9_RXI9(void){ }

// SCI9 TXI9
void Excep_SCI9_TXI9(void){ }

// SCI9 TEI9
void Excep_SCI9_TEI9(void){ }

// SCI12 ERI12
void Excep_SCI12_ERI12(void){ }

// SCI12 RXI12
void Excep_SCI12_RXI12(void){ }

// SCI12 TXI12
void Excep_SCI12_TXI12(void){ }

// SCI12 TEI12
void Excep_SCI12_TEI12(void){ }

// SCI12 SCIX0
void Excep_SCI12_SCIX0(void){ }

// SCI12 SCIX1
void Excep_SCI12_SCIX1(void){ }

// SCI12 SCIX2
void Excep_SCI12_SCIX2(void){ }

// SCI12 SCIX3
void Excep_SCI12_SCIX3(void){ }

// RIIC0 EEI0
void Excep_RIIC0_EEI0(void){ }

// RIIC0 RXI0
void Excep_RIIC0_RXI0(void){ }

// RIIC0 TXI0
void Excep_RIIC0_TXI0(void){ }

// RIIC0 TEI0
void Excep_RIIC0_TEI0(void){ }

