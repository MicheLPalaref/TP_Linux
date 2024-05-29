#ifndef HSMC_DUAL_DVI_HPP_
#define HSMC_DUAL_DVI_HPP_

#include "I2C_Component.hpp"

class HSMC_Dual_DVI: public I2C_Component
{
public:
   
    HSMC_Dual_DVI(long base_address) : I2C_Component(base_address)
    {
    }
   
    void enable_output()
    {
        i2c_write(base_address, 0x70>>1, 0x08, 0xBF ); // Set TFP410 Mode
        i2c_write(base_address, 0x70>>1, 0x09, 0x20 ); // Set TFP410 Mode
    }      
   
    
};

#endif /*HSMC_DUAL_DVI_HPP_*/
