/*
Written by Qiyong Mu (kylongmu@msn.com)
Adapted for Raspberry Pi by Mikhail Avkhimenia (mikhail.avkhimenia@emlid.com)
*/

#ifndef _ADC9300_H
#define _ADC9300_H

//#include "SPIdev.h"

class ADC9300 {
public:
    ADC9300(const char *filename = "/dev/i2c-5");
    ~ADC9300();
    bool IsReady(void);
    bool Get_ADCData0(uint16_t *pData16);
    bool Get_ADCData1(uint16_t *pData16);
    bool Get_ID(uint8_t *pData8);
    bool Set_PowerSwitch(bool bSwitch);


protected:
	int m_file;
	bool REG_READ(int file, uint8_t CommandCode,uint8_t *value);
	bool REG_WRITE(int file, uint8_t CommandCode, uint8_t value);
	bool Get_ADCData(uint8_t RegLow,uint8_t RegHigh, uint16_t *pData16);
	
};

#endif //_ADC9300_H

