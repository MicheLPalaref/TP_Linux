#ifndef HSMC_QUAD_VIDEO_HPP_
#define HSMC_QUAD_VIDEO_HPP_

#include "I2C_Component.hpp"

class HSMC_Quad_Video: public I2C_Component
{
public:
   
    HSMC_Quad_Video(long base_address) : I2C_Component(base_address)
    {
    }
   
    void init()
    {
/*        i2c_write(base_address, 0xea>>1, 0x15, 0x00 );

        i2c_write(base_address, 0xea>>1, 0x31, 0x00 ); // 
        i2c_write(base_address, 0xea>>1, 0x32, 0x23 ); //
        i2c_write(base_address, 0xea>>1, 0x33, 0x08 ); //
        i2c_write(base_address, 0xea>>1, 0x34, 0x16 ); //
        i2c_write(base_address, 0xea>>1, 0x35, 0x30 ); // chrontel
      
        i2c_write(base_address, 0xea>>1, 0x36, 0x60 ); //
        i2c_write(base_address, 0xea>>1, 0x37, 0x00 ); //
    
        i2c_write(base_address, 0xea>>1, 0x49, 0xc0 ); // Set DVI MODE 
      
       
        i2c_write(base_address, 0xea>>1, 0x21, 0x01 | 0x08 ); // DAC bypass
        i2c_write(base_address, 0xea>>1, 0x22, 0x16 ); // BCO = VSYNC
      
        i2c_write(base_address, 0xea>>1, 0x1f, 0x80 ); // Set Internal buffer
        i2c_write(base_address, 0xea>>1, 0x1c, 0x04 ); // Invert XCLK Polarity
*/

  i2c_write(QUAD_VIDEO_I2C_MASTER_BASE, 0xea>>1, 0x15, 0x00 );

  i2c_write(QUAD_VIDEO_I2C_MASTER_BASE, 0xea>>1, 0x31, 0x00 ); //
  i2c_write(QUAD_VIDEO_I2C_MASTER_BASE, 0xea>>1, 0x32, 0x23 ); //
  i2c_write(QUAD_VIDEO_I2C_MASTER_BASE, 0xea>>1, 0x33, 0x04 ); //
  i2c_write(QUAD_VIDEO_I2C_MASTER_BASE, 0xea>>1, 0x34, 0x26 ); //
  i2c_write(QUAD_VIDEO_I2C_MASTER_BASE, 0xea>>1, 0x35, 0x30 ); // chrontel

  i2c_write(QUAD_VIDEO_I2C_MASTER_BASE, 0xea>>1, 0x36, 0x60 ); //
  i2c_write(QUAD_VIDEO_I2C_MASTER_BASE, 0xea>>1, 0x37, 0x00 ); //

  i2c_write(QUAD_VIDEO_I2C_MASTER_BASE, 0xea>>1, 0x49, 0xc0 ); // Set DVI MODE


  i2c_write(QUAD_VIDEO_I2C_MASTER_BASE, 0xea>>1, 0x21, 0x01 | 0x08 ); // DAC bypass
  i2c_write(QUAD_VIDEO_I2C_MASTER_BASE, 0xea>>1, 0x22, 0x16 ); // BCO = VSYNC

  i2c_write(QUAD_VIDEO_I2C_MASTER_BASE, 0xea>>1, 0x1f, 0x80 ); // Set Internal buffer
  i2c_write(QUAD_VIDEO_I2C_MASTER_BASE, 0xea>>1, 0x1c, 0x04 ); // Invert XCLK Polarity


    
         // Initialise input channels
         unsigned int i,j;
      i=0;
      do{
        do{
          i2c_write(base_address, 0xb8>>1, 0xfe, (1<<i) ); //
          i2c_write(base_address, 0xb8>>1, 0x7f, 0x00 ); // 
          i2c_write(base_address, 0xb8>>1, 0xff, (1<<i) ); //
          if((j = i2c_read(base_address, 0xb8>>1, 0x81)) !=  0x54){
            /*IOWR(PIO_BASE, 0x0 , 0x00 ); // reset
            for(i=0;i<1000;i++) ;
            IOWR(PIO_BASE, 0x0 , 0xff ); // clr reset
            for(i=0;i<10000;i++) ;  */
            i = 0;
          }
        } while( j != 0x54); //  
        i++; j = 0;
      } while( i < 4);
        
      for(i=0;i<4;i++){
        i2c_write(base_address, 0xb8>>1, 0xfe, (1<<i) ); // 
        i2c_write(base_address, 0xb8>>1, 0x7f, 0x00 ); // 
           
        i2c_write(base_address, 0xb8>>1, 0x03,0x0D);  // Enable YCbCr, sync, control outputs  
        //keep SCLK disabled i2c_write(base_address, 0xb8>>1, 0x05,0x08);  // Enable Clock 2 output    
        i2c_write(base_address, 0xb8>>1, 0x17,0x5B);  // scaler powerdown for ROM2.0 and enable SAV/EAV codes, BLK set to powerdown scaler
        i2c_write(base_address, 0xb8>>1, 0x15,0x81);  // Enable Stable Sync mode 
        i2c_write(base_address, 0xb8>>1, 0x00,0x00);  // Select video source  
      }
    
      for(i=0;i<4;i++){ 
        i2c_write(base_address, 0xb8>>1, 0xff, (1<<i) ); // 
        if(i2c_read(base_address, 0xb8>>1, 0x88) & 0x06)  // Has vsync and hsync locked for this channel?
          i2c_write(base_address, 0xb8>>1, 0xfe, (1<<i) ); // 
      }
   }      
    
    
    

 
   
    
};

#endif /*HSMC_QUAD_VIDEO_HPP_*/
