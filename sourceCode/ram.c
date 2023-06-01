#include "const_def.h"

/* generate sinus wave */
unsigned short sinFreq;
unsigned char wavePos;

/* Switch status */
unsigned char glSw[4];                 //* read SW last
unsigned char glSwBak[4];              //* read SW first
unsigned char glSwFlag[4];             //* flag SW (signal change state of SW)
unsigned char glSwLongPressTimer[4];   //* set timer for LongPress SW1
unsigned char glSwLongPressOn[4];      //* SW is long pressed
unsigned char glSwLongPressFlag[4];    //* flag LongPress

/* LEDs output */
unsigned char glLed[8];

/* Data LED 7 segment */
unsigned char glLed7Data[4];
unsigned char glLed7Dis[4];


/* Count 1 second  */
unsigned char glCount10Ms;
unsigned short glCount1Sec;

/* External GPIO port for LED7 segment  */
struct stExtGpioPort {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B0:1;
			unsigned char B1:1;
			unsigned char B2:1;
			unsigned char B3:1;
			unsigned char B4:1;
			unsigned char B5:1;
			unsigned char B6:1;
			unsigned char B7:1;
		}BIT;
	}P0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char B0:1;
			unsigned char B1:1;
			unsigned char B2:1;
			unsigned char B3:1;
			unsigned char B4:1;
			unsigned char B5:1;
			unsigned char B6:1;
			unsigned char B7:1;
		}BIT;
	}P1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char B0:1;
			unsigned char B1:1;
			unsigned char B2:1;
			unsigned char B3:1;
			unsigned char B4:1;
			unsigned char B5:1;
			unsigned char B6:1;
			unsigned char B7:1;
		}BIT;
	}P2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char B0:1;
			unsigned char B1:1;
			unsigned char B2:1;
			unsigned char B3:1;
			unsigned char B4:1;
			unsigned char B5:1;
			unsigned char B6:1;
			unsigned char B7:1;
		}BIT;
	}P3;
};
struct stExtGpioPort extGpioPort;
struct stExtGpioPort led7DispData;

/* Array data flash */
unsigned char flgFlashCorret;

/* Radio */
unsigned char glDeviceID[2];
unsigned char glChipID[2];