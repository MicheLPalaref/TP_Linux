

#ifndef MIPI_CAMERA_CONFIG_H_
#define MIPI_CAMERA_CONFIG_H_

#define MIPI_I2C_ADDR   0x6C
#define MIPI_AF_I2C_ADDR 0x18

#define BYD_MODE_SELECT   0x0100
#define BYD_SOFTWARE_SET  0x0103
#define BYD_STREAMING     0x301A


#define CAMERA_BIN_LEVEL_MAX    	3
#define CAMERA_BIN_LEVEL_MIN    	1
#define CAMERA_BIN_LEVEL_DEFAULT    CAMERA_BIN_LEVEL_MAX



void OV8865_FOCUS_Move_to(alt_u16 a_u2MovePosition);
void MIPI_BIN_LEVEL(alt_u8 level);
void BLC_LEVEL(alt_u8 level);

void MipiCameraInit(void);


#endif /* MIPI_CAMERA_CONFIG_H_ */