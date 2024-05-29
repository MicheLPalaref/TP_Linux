#include <stdio.h>
#include "alt_types.h"
#include "terasic_includes.h"
#include "I2C_core.h"
#include "system.h"
#include "light_sensor.h"



bool I2C_Write_Light(alt_8 DeviceAddr, alt_u8 CommandCode, alt_u8 ControlData);
bool I2C_Write_Light16(alt_8 DeviceAddr, alt_u8 CommandCode, alt_u8 *pControlData);
bool I2C_Read_Light(alt_8 DeviceAddr, alt_u8 CommandCode, alt_u8 *pControlData);




////////////////////////////////////////
// export API
static alt_u32 Light_I2C_Controller_Base = LIGHT_I2C_OPENCORES_BASE;

void Light_Init(alt_u32 I2C_Controller_Base){
	const int Ref_CLK = 50*1000*1000; // 50MHz
	const int I2C_CLK = 400*1000; // 400KHz

	Light_I2C_Controller_Base = I2C_Controller_Base;
	oc_i2c_init_ex(Light_I2C_Controller_Base, Ref_CLK, I2C_CLK);
}

void Light_GetID(alt_u8 *data)
{
    bool bPass;
    alt_u8 CommandCode = COMMAND_CMD | ID_REG ;
    //read ID
    bPass = I2C_Read_Light( DEVICE_ADDR,CommandCode , data);
    if(!bPass)  *data = 0;

}

void Light_GetTiming(alt_u8 *data)
{
    bool bPass;
    alt_u8 CommandCode = COMMAND_CMD | TIMING_REG ;
    //read ID
    bPass = I2C_Read_Light( DEVICE_ADDR,CommandCode , data);
    if(!bPass)  *data = 0;

}

bool Light_PowerSwitch(bool bSwitch)
{
    bool bPass;
    alt_u8 data = 0;
    alt_u8 CommandCode = COMMAND_CMD | CONTROL_REG ;
    
    data = bSwitch ? 0x03 : 0x00 ;
   
    bPass = I2C_Write_Light( DEVICE_ADDR,CommandCode , data);
    
    return bPass;
}

bool Light_Get_ADCData0(alt_u16 *pChannelData)
{
    bool bPass;
    alt_u8 Data0Low, Data0High;
    alt_u8 CommandCode = COMMAND_CMD |  DATA0LOW ;
    //alt_u8 CommandCode = 0x8C;
    
    bPass = I2C_Read_Light( DEVICE_ADDR,CommandCode , &Data0Low);
    if(!bPass) 
    {
         return FALSE;
    }
    else *pChannelData = Data0Low;
    
    if(bPass)
    {
        CommandCode = COMMAND_CMD |  DATA0HIGH ;
        //CommandCode = 0x8D;
  
        bPass = I2C_Read_Light( DEVICE_ADDR,CommandCode , &Data0High);
        if(!bPass)  
        {
            return FALSE;
        }
        else *(pChannelData+1) = Data0High;
    }
    
    *pChannelData = (Data0High << 8) | Data0Low;
    
    return TRUE;
}

bool Light_Get_ADCData1(alt_u16 *pChannelData)
{
    bool bPass;
    alt_u8 Data1Low, Data1High;
    alt_u8 CommandCode = COMMAND_CMD |  DATA1LOW ;
    
    bPass = I2C_Read_Light( DEVICE_ADDR,CommandCode , &Data1Low);
    if(!bPass) 
    {
         return FALSE;
    }
    else *pChannelData = Data1Low;
    
    if(bPass)
    {
        CommandCode = COMMAND_CMD |  DATA1HIGH ;
  
        bPass = I2C_Read_Light(DEVICE_ADDR,CommandCode , &Data1High);
        if(!bPass)  
        {
            return FALSE;
        }
        else *(pChannelData+1) = Data1High;
    }
    
    *pChannelData = (Data1High << 8) | Data1Low;
    
    return TRUE;
}

bool Light_SetThreshLow(alt_u8 *pData)
{
    bool bPass;
    alt_u8 CommandCode = COMMAND_CMD | COMMAND_WORD | THRESHLOWLOW_REG ;
    
    bPass = I2C_Write_Light16( DEVICE_ADDR, CommandCode, pData);
    
//    data = *pData;
//   
//    bPass = I2C_Write_Light(LIGHT_SENSOR_SCL_BASE, LIGHT_SENSOR_SDA_BASE, DEVICE_ADDR,CommandCode , data);
//    
//    if(bPass)
//    {
//        CommandCode = COMMAND | THRESHLOWHIGH_REG;
//        
//        data = *(pData+1);
//        bPass = I2C_Write_Light(LIGHT_SENSOR_SCL_BASE, LIGHT_SENSOR_SDA_BASE, DEVICE_ADDR,CommandCode , data);
//    }
    
    return bPass;
}

bool Light_SetThreshHigh(alt_u8 *pData)
{
    bool bPass;
    alt_u8 CommandCode = COMMAND_CMD | COMMAND_WORD | THRESHHIGHLOW_REG ;
    
    bPass = I2C_Write_Light16( DEVICE_ADDR, CommandCode, pData);
    
//    data = *pData;
//   
//    bPass = I2C_Write_Light(LIGHT_SENSOR_SCL_BASE, LIGHT_SENSOR_SDA_BASE, DEVICE_ADDR,CommandCode , data);
//    
//    if(bPass)
//    {
//        CommandCode = COMMAND | THRESHHIGHHIGH_REG;
//        
//        data = *(pData+1);
//        bPass = I2C_Write_Light(LIGHT_SENSOR_SCL_BASE, LIGHT_SENSOR_SDA_BASE, DEVICE_ADDR,CommandCode , data);
//    }
    
    return bPass;
}

bool Light_SetInterrupt(alt_u8 data)
{
    bool bPass;
    alt_u8 CommandCode = COMMAND_CMD | INTERRUPT_REG ;
    
    bPass = I2C_Write_Light(DEVICE_ADDR,CommandCode , data);
    
    return bPass;
}

void Light_GetInterrupt(alt_u8 *data)
{
    bool bPass;
    alt_u8 CommandCode = COMMAND_CMD | INTERRUPT_REG ;
    //read ID
    bPass = I2C_Read_Light( DEVICE_ADDR,CommandCode , data);
    if(!bPass)  *data = 0;
}

bool Light_SetTiming(alt_u8 data)
{
    bool bPass;
    alt_u8 CommandCode = COMMAND_CMD | TIMING_REG ;
    
    bPass = I2C_Write_Light( DEVICE_ADDR,CommandCode , data);
    
    return bPass;
}

/////////////////////////////////////////////
// internal
////////////////light sensor
bool I2C_Write_Light(alt_8 DeviceAddr, alt_u8 CommandCode, alt_u8 ControlData){
	bool bSuccess;

	bSuccess = OC_I2C_Write(Light_I2C_Controller_Base,DeviceAddr,CommandCode, &ControlData, 1);

    return bSuccess;


}

bool I2C_Write_Light16(alt_8 DeviceAddr, alt_u8 CommandCode, alt_u8 *pControlData){
	bool bSuccess;

	bSuccess = OC_I2C_Write(Light_I2C_Controller_Base,DeviceAddr,CommandCode, pControlData, 2);

    return bSuccess;


}

bool I2C_Read_Light(alt_8 DeviceAddr, alt_u8 CommandCode, alt_u8 *pControlData){
    bool bSuccess;

    bSuccess = OC_I2C_Read(Light_I2C_Controller_Base,DeviceAddr,CommandCode, pControlData, 1);

    return bSuccess;
}
