

/* generate sinus wave */
extern unsigned short sinFreq;
extern unsigned char wavePos;

/* Switch status */
extern unsigned char glSw[4];                 
extern unsigned char glSwBak[4];
extern unsigned char glSwFlag[4];
extern unsigned char glSwLongPressTimer[4];
extern unsigned char glSwLongPressOn[4];
extern unsigned char glSwLongPressFlag[4];

/* LEDs output */
extern unsigned char glLed[8];

/* Data LED 7 segment */
extern unsigned char glLed7Data[4];
extern unsigned char glLed7Dis[4];	


/* Count 1 second  */
extern unsigned char glCount10Ms;
extern unsigned short glCount1Sec;

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
extern struct stExtGpioPort extGpioPort;   
extern struct stExtGpioPort led7DispData;

/* Array data flash */
extern unsigned char flgFlashCorret;

/* Radio */
extern unsigned char glDeviceID[2];
extern unsigned char glChipID[2];







