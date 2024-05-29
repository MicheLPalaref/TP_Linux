#ifndef I2C_COMPONENT_HPP_
#define I2C_COMPONENT_HPP_

#include <io.h>

// Overall status and control
#define IOWR_I2C_PRERLO(port,data)  IOWR(port, 0, data)
#define IOWR_I2C_PRERHI(port,data)  IOWR(port, 1, data)
#define IOWR_I2C_CTR(port,data)  IOWR(port, 2, data)
#define IOWR_I2C_TXR(port,data)  IOWR(port, 3, data)
#define IOWR_I2C_CR(port,data)  IOWR(port, 4, data)
#define IORD_I2C_PRERLO  IORD(port, 0)
#define IORD_I2C_PRERHI  IORD(port, 1)
#define IORD_I2C_CTR  IORD(port, 2)
#define IORD_I2C_RXR  IORD(port, 3)
#define IORD_I2C_SR  IORD(port, 4)

#define I2C_CR_STA 0x80
#define I2C_CR_STO 0x40
#define I2C_CR_RD 0x20
#define I2C_CR_WR 0x10
#define I2C_CR_ACK 0x08
#define I2C_CR_IACK 0x01

#define I2C_SR_TIP 0x2

class I2C_Component
{
public:

    I2C_Component(long base_address) : base_address(base_address)
    {
        init_i2c(base_address);
    }

protected:

    void i2c_write(long port, unsigned char address, unsigned char reg, unsigned char data) {
      i2c_wait_tip(port);
      
      // write address
      IOWR_I2C_TXR(port, address<<1);
      IOWR_I2C_CR(port, I2C_CR_STA | I2C_CR_WR | I2C_CR_ACK);
      i2c_wait_tip(port);
    
      // write register address
      IOWR_I2C_TXR(port, reg);
      IOWR_I2C_CR(port, I2C_CR_WR | I2C_CR_ACK);
      i2c_wait_tip(port);
    
      // write data
      IOWR_I2C_TXR(port, data);
      IOWR_I2C_CR(port, I2C_CR_WR | I2C_CR_STO | I2C_CR_IACK);
      i2c_wait_tip(port);
    }

    unsigned char i2c_read(long port, unsigned char address, unsigned char reg) {
      i2c_wait_tip(port);
      
       // write address
      IOWR_I2C_TXR(port, address<<1);
      IOWR_I2C_CR(port, I2C_CR_STA | I2C_CR_WR);
      i2c_wait_tip(port);
    
      // write register address
      IOWR_I2C_TXR(port, reg);
      IOWR_I2C_CR(port, I2C_CR_WR);
      i2c_wait_tip(port);
    
      // write address for reading
      IOWR_I2C_TXR(port, (address<<1) | 1);
      IOWR_I2C_CR(port, I2C_CR_STA | I2C_CR_WR);
      i2c_wait_tip(port);
    
      // read data
      IOWR_I2C_CR(port, I2C_CR_RD | I2C_CR_ACK | I2C_CR_STO);
      i2c_wait_tip(port);
      
      return IORD_I2C_RXR;
    }
       
    void init_i2c(long port) {
      // Setup prescaler for 100KHz with sysclk of 75MHz
      int prescale = 150000000/(5*100000);
      IOWR_I2C_PRERLO(port, prescale & 0xff);
      IOWR_I2C_PRERHI(port, (prescale & 0xff00)>>8);
      // Enable core
      IOWR_I2C_CTR(port, 0x80);
    }
    
    void i2c_wait_tip(long port) {
      while (port, (IORD_I2C_SR & I2C_SR_TIP) > 0) {}
    }
    
    long base_address;  
    
};



#endif /*I2C_COMPONENT_HPP_*/
