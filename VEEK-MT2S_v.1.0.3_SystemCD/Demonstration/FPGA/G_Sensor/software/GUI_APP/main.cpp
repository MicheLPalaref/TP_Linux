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
#include "gui_gsensor.h"
#include "system.h"
#include "system.h"

int main()
{

    // touch
    MTC2_INFO *pTouch;

    IOWR(LED_BASE, 0x00, 0xFF); // high-active
    printf("Terasic G-Sensor Demo\r\n");

    // init touch
    pTouch=MTC2_Init(TOUCH_I2C_OPENCORES_BASE,TOUCH_INT_N_BASE,TOUCH_INT_N_IRQ, TOUCH_INT_N_IRQ_INTERRUPT_CONTROLLER_ID);

    if (!pTouch){
        printf("Failed to init multi-touch\r\n");
    }else{
        printf("Init touch successfully\r\n");

    }
    GUI_GSensor(pTouch);
  return 0;
}




