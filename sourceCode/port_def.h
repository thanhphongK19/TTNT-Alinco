#include "iodefine.h"
//#include "ram.h"

/* Switch port */
#define	SW1	PORTC.PIDR.BIT.B1
#define	SW2	PORTC.PIDR.BIT.B0
#define	SW3	PORTB.PIDR.BIT.B7
#define	SW4	PORTB.PIDR.BIT.B6

/**/
#define	LED_W PORTA.PODR.BIT.B0
#define LED_5G PORT5.PODR.BIT.B3

/* RIIC */
#define SDA_WR PORT1.PODR.BIT.B0
#define SDA_RD PORT1.PIDR.BIT.B0
#define SDA_DIR PORT1.PDR.BIT.B0
#define SCL PORT1.PODR.BIT.B1
#define SCL_DIR PORT1.PDR.BIT.B1

/* RIIC FM AM */
#define SDIO_WR PORT5.PODR.BIT.B0
#define SDIO_RD PORT5.PIDR.BIT.B0
#define SDIO_DIR PORT5.PDR.BIT.B0
#define SCLK PORT5.PODR.BIT.B2
#define SCLK_DIR PORT5.PDR.BIT.B2

#define 	LED_AM 			PORTA.PODR.BIT.B4 // Pin No.66
#define 	LED_FM 			PORTA.PODR.BIT.B5 // Pin No.65



 
		