

/* Switch index */
#define S_SW1	0
#define S_SW2	1
#define S_SW3	2
#define S_SW4	3

/* LED index */
#define L_LED_W	0

#if 1
/* address i2c two device */
#define I2C_ADDR_TCA6416AR_L	0x40
#define	I2C_ADDR_TCA6416AR_H	0x42

/*** Command Byte  TCA6416ARTWR ***/
#define TCA6416A_INPUT_PORT_0 		0x00
#define TCA6416A_INPUT_PORT_1 		0x01
#define TCA6416A_OUTPUT_PORT_0 		0x02
#define TCA6416A_OUTPUT_PORT_1 		0x03
#define TCA6416A_POLARITY_PORT_0 	0x04
#define TCA6416A_POLARITY_PORT_1 	0x05
#define TCA6416A_CONFIG_PORT_0 		0x06
#define TCA6416A_CONFIG_PORT_1 		0x07

/* Led index */
#define Led7seg_1 0
#define Led7seg_2 1
#define Led7seg_3 2
#define Led7seg_4 3


#endif

/* Led7 charactor index */
#define LED7_0	0
#define LED7_A	10
#define LED7_B	11

#if 1 /* BK1086*/
/*** Power configuration ***/

#define	BK1086_POWER_OFF	    0x40		// DISABLE = 1 ENABLE = 0
#define	BK1086_POWER_ON			0x01		// DISABLE = 0 ENABLE = 1

/*** BK1086 AM FM ***/
#define	BK1086_FM		0
#define	BK1086_AM		1

/*** Default frequency setting ***/
#define	BK1086_FREQ_AD						0x03
#define	BK1086_FREQ_TUNE					0x8000
#define	BK1086_FREQ_MASK					0x7FFF

#define	BK1086_FM_MIN_FREQ		640			// 64.0MHz
#define	BK1086_AM_MIN_FREQ		522			// 522KHz

#define	FM_MIN_FREQ				760			// 76.0MHz
#define	AM_MIN_FREQ				522			// 522KHz

#define	FM_MAX_FREQ				1080		// 108.0MHz
#define	AM_MAX_FREQ				1710		// 1710KHz

#define	BK1086_FM_MAX_FREQ		1080		// 108.0MHz
#define	BK1086_AM_MAX_FREQ		1710		// 1710KHz
#endif










