
void main(void);

void operate();


/* Radio */
void initRadioI2C();
unsigned char setPowerRadio(unsigned char data);
void startConditionRadio();
void stopConditionRadio();
unsigned char writeRadioI2C(unsigned char data);
unsigned char readRadioI2C(unsigned char* des,unsigned char reg);
unsigned char setClockRadio(unsigned char reg,unsigned short data);
unsigned char switchModeRadio(unsigned char data);
unsigned char configRadio();
//unsigned char configRadio



/////////////////////////////////////////////////////////////////////////////////////
/* DAC practice*/
void initDac();
void sinGen(unsigned short* value);
unsigned char waveGenCon();
////////////////////////////////////////////////////////////////////////////////////////////////////////////



/* E2 DataFlash memmory CPU */
void initFlash();
void programingErasuareMode();
void switchingPeToRead();
unsigned char eraseFlash(unsigned char index);
unsigned char writeFlash(unsigned char* arrData,unsigned short len,unsigned short address);
unsigned char readFlash(unsigned char* arrReadData,unsigned short len, unsigned long address);
unsigned char saveDataPer(unsigned char* s_pos, unsigned short saveAdd, unsigned short dataLen);
void deleteData(unsigned char blk_loca, unsigned short len);
///////////////////////////////////////////////////////////////////////////////////////////////////////////

/* CRC flash memory*/
unsigned char decodeCRC(unsigned char* s_sour, unsigned short len); // len include crc code
void encodeCRC(unsigned char* s_pos, unsigned short len); // len not include crc code

	
/* Tranmitter and recevier I2C */
void initI2C();
void startCondition();
void stopCondition();
unsigned char writeI2C(unsigned char data);


/* Set LED7 output */
// Setting Led //
unsigned char setLed7Output();
void setSingleLed7(unsigned char index, unsigned char data);
void setAllLed7();


/* Counting Led 0000 - 9999 */
// Set LED7 segment
void setLed7();
#if 0
void initLed7();
void takeLed7Character (unsigned char index,unsigned char data);
unsigned char logicAnd(unsigned char data,unsigned char pos);
void counterLed7();
#endif
 

/* Switch check and proccess */
void getAllSwitchStatus();
void getSwitchStatus(unsigned char Index, unsigned char Value);
void getAllSwitchLongPressStatus();
void getSwitchLongPressStatus(unsigned char Index);

/* Set LEDs */
void setAllLeds();
unsigned char setSingleLed(unsigned char Index);


/* Calculator */
unsigned char xorLogic(unsigned short a,unsigned short b);
unsigned char andLogic(unsigned short data,unsigned short pos);


// Timer //
// Time counter
void timeCount();
void waitNmc(unsigned char interval);
void waitN10ms(unsigned char interval);
void waitNsec(unsigned char interval);





