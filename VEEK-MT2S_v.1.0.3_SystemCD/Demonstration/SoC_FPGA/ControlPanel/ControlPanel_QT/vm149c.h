
#ifndef _VM149C_H
#define _VM149C_H

//#include "SPIdev.h"

class VM149C {
public:
    VM149C(const char *filename = "/dev/i2c-3");
    ~VM149C();
    bool IsReady(void);
    bool WriteFocus(uint16_t Data16);
    bool ReadFocus(uint16_t *Data16);


protected:
	enum{
		CONFIG_SPS = 0x00 // normal
	};
	enum{
		CONFiG_S = 0x00 // control step control:0, SRC STep period 64 us
	};
	int m_file;
	bool REG_READ16(int file, uint16_t *Value16);
	bool REG_WRITE16(int file, uint16_t Value16);
	
};

#endif //_VM149C_H

