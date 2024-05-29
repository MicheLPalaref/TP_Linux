// ============================================================================
// Copyright (c) 2016 by Terasic Technologies Inc.
// ============================================================================
//
// Permission:
//
//   Terasic grants permission to use and modify this code for use
//   in synthesis for all Terasic Development Boards and Altera Development
//   Kits made by Terasic.  Other use of this code, including the selling
//   ,duplication, or modification of any portion is strictly prohibited.
//
// Disclaimer:
//
//   This VHDL/Verilog or C/C++ source code is intended as a design reference
//   which illustrates how these types of functions can be implemented.
//   It is the user's responsibility to verify their design for
//   consistency and functionality through the use of formal
//   verification methods.  Terasic provides no warranty regarding the use
//   or functionality of this code.
//
// ============================================================================
//
//  Terasic Technologies Inc
//  9F., No.176, Sec.2, Gongdao 5th Rd, East Dist, Hsinchu City, 30070. Taiwan
//
//
//
//                     web: http://www.terasic.com/
//                     email: support@terasic.com
//
// --------------------------------------------------------------------


#include "terasic_includes.h"
#include "I2C_core.h"
#include "multi_touch2.h"
#include "gui_compass.h"
#include "system.h"
#include "mpu9250.h"
#include "uart.h"


void MagViewer(void){
	MPU9250 mpu(MPU_I2C_OPENCORES_BASE);
	float ax, ay, az, gx, gy, gz, mx, my, mz;
	char szText[128];
	int hUart;
/*
	printf("Make sure the associated COM-Port number is less then 16 in PC.\r\n");
	mpu.initialize();

	hUart = UART_Open((char *)UART_NAME);

	while(hUart){
		mpu.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
		//sprintf(szText, "%.2f\t%.2f\t%.2f\r\n", mx, my, mz);
		sprintf(szText, "%.2f,%.2f,%.2f\r\n", mx, my, mz);
		printf(szText);
		UART_Write(hUart, szText, strlen(szText));
		usleep(100*1000);
	}

	if (hUart)
		UART_Close(hUart);
*/
}


int main()
{

    // touch
    MTC2_INFO *pTouch;


    IOWR(LED_BASE, 0x00, 0xFF); // high-active


    //MagViewer();

    // init touch
    pTouch=MTC2_Init(TOUCH_I2C_OPENCORES_BASE,TOUCH_INT_N_BASE,TOUCH_INT_N_IRQ, TOUCH_INT_N_IRQ_INTERRUPT_CONTROLLER_ID);
    if (!pTouch){
        printf("Failed to init multi-touch\r\n");
    }else{
        printf("Init touch successfully\r\n");

    }
    GUI_Compass(pTouch);
  return 0;
}




