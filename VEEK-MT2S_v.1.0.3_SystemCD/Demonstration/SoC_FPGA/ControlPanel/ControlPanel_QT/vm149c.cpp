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

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "hwlib.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"
#include "vm149c.h"


#define DEVICE_I2C_ADDR	0x0C  // 7-bit addr

//-----------------------------------------------------------------------------------------------

VM149C::VM149C(const char *filename)
{
	m_file = open(filename, O_RDWR);
	if (m_file < 0) {
	  /* ERROR HANDLING: you can check errno to see what went wrong */
		printf("Failed to open the i2c bus of gsensor.\n");
	}else{
		//int addr = 0b00111001;
		int addr = 0x0C;
		if (ioctl(m_file, I2C_SLAVE, addr) < 0) {
  	  printf("Failed to acquire bus access and/or talk to slave.\n");
	    /* ERROR HANDLING; you can check errno to see what went wrong */
	    close(m_file);
	    m_file = -1;
  	}
	}
}

VM149C::~VM149C(){
	if (m_file > 0){
		close(m_file);
		m_file = -1;
	}
}

bool VM149C::IsReady(void){
	if (m_file <= 0)
		return false;
	return true;
}


bool VM149C::WriteFocus(uint16_t Focus16){
	uint16_t Value16;
	bool bSuccess;
	
	if (!IsReady())
		return false;
	
	if (Focus16 >= 1024)
		Focus16 = 1023;
	
	Value16 = Focus16 << 4;
	Value16 |= CONFIG_SPS;
	Value16 |= CONFiG_S;
	bSuccess = REG_WRITE16(m_file, Value16);
	return bSuccess;
}

bool VM149C::ReadFocus(uint16_t *Data16){
	bool bSuccess;
	uint16_t Value;
	bSuccess = REG_READ16(m_file, &Value);
	if (bSuccess)
		*Data16 = (Value >> 4) & 0x3FF;
	return bSuccess;
}

bool VM149C::REG_READ16(int file, uint16_t *Value16){
#if 1
	  bool bSuccess = false;
    static struct i2c_msg msgs;
    int r;

    struct i2c_rdwr_ioctl_data msgset = { &msgs, 1 };
    unsigned char buf[2];

    	msgs.addr = DEVICE_I2C_ADDR;
    	msgs.flags = I2C_M_RD;
    	msgs.buf = (__u8 *) buf;
    	msgs.len = 2;

    	r = ioctl(file, I2C_RDWR, &msgset);
    	if (r != 0) {
	        bSuccess = true;
	  	  	*Value16 = buf[0] * 256 + buf[1];
  	  }

    return bSuccess; ;
#else	
        uint8_t Value[2];
        bool bSuccess = false;
        
        if (read(file, &Value, sizeof(Value)) == sizeof(Value)){   
        		*Value16 = Value[0]*256 + Value[1];      
            bSuccess = true;
        }
        return bSuccess;    	
#endif        
}

bool VM149C::REG_WRITE16(int file, uint16_t Value16){
        bool bSuccess = false;
        uint8_t szValue[2];       
        // write to define register
        
        
        szValue[0] = (Value16 >> 8) & 0xFF;
        szValue[1] = Value16 & 0xFF;
        if (write(file, &szValue, sizeof(szValue)) == sizeof(szValue)){
                        bSuccess = true;
        }              
        return bSuccess;  	
}