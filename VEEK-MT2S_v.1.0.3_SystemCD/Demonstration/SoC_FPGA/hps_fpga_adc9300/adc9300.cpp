/*
Written by Qiyong Mu (kylongmu@msn.com)
Adapted for Raspberry Pi by Mikhail Avkhimenia (mikhail.avkhimenia@emlid.com)
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "hwlib.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"
#include "adc9300.h"


#define COMMAND_CMD     0x80
#define COMMAND_CLEAR   0x40
#define COMMAND_WORD    0x20

#define ID_REG         0x0A
#define CONTROL_REG    0x00
#define THRESHLOWLOW_REG     0x02
#define THRESHLOWHIGH_REG    0x03
#define THRESHHIGHLOW_REG    0x04
#define THRESHHIGHHIGH_REG   0x05
#define INTERRUPT_REG        0x06
#define TIMING_REG           0x01

#define DATA0LOW       0x0C
#define DATA0HIGH      0x0D
#define DATA1LOW       0x0E
#define DATA1HIGH      0x0F


//int ADC9300::m_file=0;

//-----------------------------------------------------------------------------------------------

ADC9300::ADC9300(const char *filename)
{
	m_file = open(filename, O_RDWR);
	if (m_file < 0) {
	  /* ERROR HANDLING: you can check errno to see what went wrong */
		printf("Failed to open the i2c bus of gsensor.\n");
	}else{
		//int addr = 0b00111001;
		int addr = 0x29;
		if (ioctl(m_file, I2C_SLAVE, addr) < 0) {
  	  printf("Failed to acquire bus access and/or talk to slave.\n");
	    /* ERROR HANDLING; you can check errno to see what went wrong */
	    close(m_file);
	    m_file = -1;
  	}
	}
}

ADC9300::~ADC9300(){
	if (m_file > 0){
		close(m_file);
		m_file = -1;
	}
}

bool ADC9300::IsReady(void){
	if (m_file <= 0)
		return false;
	return true;
}

bool ADC9300::Get_ADCData(uint8_t RegLow,uint8_t RegHigh, uint16_t *pData16){
    bool bSuccess=false;
    uint8_t Data0Low, Data0High;
    uint8_t CommandCode;
    
    if (!IsReady())
    	return false;
    	
    CommandCode = COMMAND_CMD |  RegLow ;	
		bSuccess=REG_READ( m_file,CommandCode,&Data0Low);
    if(bSuccess){
			CommandCode = COMMAND_CMD |  RegHigh ;
			bSuccess=REG_READ( m_file,CommandCode,&Data0High);
	    *pData16 = (Data0High << 8) | Data0Low;
    }

    return bSuccess;	
}

bool ADC9300::Get_ADCData0(uint16_t *pData16){
    bool bSuccess;
    
    bSuccess = Get_ADCData(DATA0LOW, DATA0HIGH, pData16);
    
    return bSuccess;	
}

bool ADC9300::Get_ADCData1(uint16_t *pData16){
    bool bSuccess;
    
    bSuccess = Get_ADCData(DATA1LOW , DATA1HIGH , pData16);
    
    return bSuccess;		
}

bool ADC9300::Get_ID(uint8_t *pData8){
	bool bSuccess = false;
  uint8_t CommandCode;
  
    if (!IsReady())
    	return false;
  
  CommandCode = COMMAND_CMD | ID_REG ;
	bSuccess=REG_READ( m_file,  CommandCode, pData8);
  if(!bSuccess)  
  	*pData8 = 0;	
  return bSuccess;	
}

bool ADC9300::Set_PowerSwitch(bool bSwitch){
    bool bPass;
    uint8_t data = 0;
    uint8_t CommandCode;
    
    if (!IsReady())
    	return false; 
    
    CommandCode = COMMAND_CMD | CONTROL_REG ;
    data = bSwitch ? 0x03 : 0x00 ;
		bPass=REG_WRITE( m_file, CommandCode, data); 
    return bPass;	
}


bool ADC9300::REG_READ(int file, uint8_t CommandCode,uint8_t *value){
        uint8_t Value[1];
        bool bSuccess = false;
        
        // write to define register
        if (write(file, &CommandCode, sizeof(CommandCode)) == sizeof(CommandCode)){  
                // read back value
                if (read(file, &Value, sizeof(Value)) == sizeof(Value)){          
                        bSuccess = true;
                }
        }
				*value=Value[0];
        return bSuccess;    	
}

bool ADC9300::REG_WRITE(int file, uint8_t CommandCode, uint8_t value){
        bool bSuccess = false;
        uint8_t szValue[2];       
        // write to define register
        
        
        szValue[0] = CommandCode;
        szValue[1] = value;
        if (write(file, &szValue, sizeof(szValue)) == sizeof(szValue)){
                        bSuccess = true;
        }              
        return bSuccess;  	
}