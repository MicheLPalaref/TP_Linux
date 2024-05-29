/*****************************************************************************
 *  File: my_app.c
 *
 *  This file contains functions for performing general tasks associated
 *  with the application selector.
 *
 ****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/alt_alarm.h>
#include <string.h>
#include "system.h"
#include "alt_types.h"
#include "sys/alt_cache.h"
#include "io.h"
#include "my_app.h"
#include "my_app_gui.h"
#include "altera_avalon_pio_regs.h"
#include "alt_video_display/alt_video_display.h"
#include "alt_tpo_lcd/alt_tpo_lcd.h"


/*****************************************************************************
 *  Function: AsInitTpoLcd
 *
 *  Purpose: Initializes the gamma and resolution of the LCD screen
 *
 *  Returns: 0
 ****************************************************************************/
int AsInitTpoLcd( alt_tpo_lcd* lcd_serial )
{

  // Specify base addresses of the each communication bus PIO,
  // as defined in system.h
//  lcd_serial->scen_pio = LCD_I2C_EN_BASE;
//  lcd_serial->scl_pio  = LCD_I2C_SCL_BASE;
//  lcd_serial->sda_pio  = LCD_I2C_SDAT_BASE;

  // Write the default gamma curve, use 800x480 resolution (default),
  // and verify that the LCD is alive by reading back its Chip/ID
  // register. Most users will only need to call this routine, and
  // verify that it completed successfully.
  //alt_tpo_lcd_init( lcd_serial, ALT_VIDEO_DISPLAY_COLS, ALT_VIDEO_DISPLAY_ROWS );

  return( 0 );
}

#if 1
/*****************************************************************************
 *  Function: AsInitTouchscreen
 *
 *  Purpose: Initialize the touchscreen and set the calibration values.
 *
 *  Returns: 0
 ****************************************************************************/
 /*****************************************************************************
 *  Function: AsInitTouchscreen
 *
 *  Purpose: Initialize the touchscreen and set the calibration values.
 *
 *  Returns: 0
 ****************************************************************************/
//int AsInitTouchscreen( alt_touchscreen* touchscreen )
//{
//
//  // Initialize the touch panel
//  alt_touchscreen_init ( touchscreen,
//                         TOUCH_PANEL_SPI_BASE,
//                         MULTI_TOUCH_IRQ,
//                         TOUCH_PANEL_PEN_IRQ_N_BASE,
//                         60,    // 60 samples/sec
//                         ALT_TOUCHSCREEN_SWAP_XY);
//
//  // Calibrate the touch panel
//  alt_touchscreen_calibrate_upper_right (touchscreen,
//           3946,   3849,    // ADC readings
//            799,      0  ); // pixel coords
//  alt_touchscreen_calibrate_lower_left  (touchscreen,
//           132,    148,     // ADC readings
//             0,    599  );  // pixel coords
//
//  return( 0 );
//}
#endif
