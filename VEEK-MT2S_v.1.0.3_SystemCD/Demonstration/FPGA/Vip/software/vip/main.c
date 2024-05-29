/*****************************************************************************
 *  File: main.c for vip_demo
 *
 *  This file is the top level of the vip demo.
 *
 ****************************************************************************/

#include <string.h>
#include <io.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/alt_alarm.h>
#include "my_app.h"
#include "my_app_gui.h"
#include "alt_video_display/alt_video_display.h"
#include "alt_tpo_lcd/alt_tpo_lcd.h"
#include <sys/alt_cache.h>
#include "system.h"
#include "I2C_core.h"
#include "multi_touch2.h"
#include "altera_avalon_pio_regs.h"

#include "audio_tvdecoder/tvdecoder_ctrl.h"
#include "VIP_ctrl/vip_wrapper_for_c_func.h"

#include "move_image.h"
#include "my_graphics.h"

//#include "version_compatible.h"


extern void init_i2c();
extern void move_image(int xini, int yini, int wini, int hini, int direcini);

#define VFR1_SCREEN_0_BASE_ADDRESS ((int)(display->buffer_ptrs[display->buffer_being_written]->buffer))
#define VFR1_SCREEN_PIXEL_COUNT  ( FRAME_BUF_W * FRAME_BUF_H)

// This is our LCD display
alt_video_display* display;

MTC2_INFO *pTouch;
alt_u8 Event, TouchNum;

int motion_count=0;

int auto_timer=0;

int title_bar_x;
int title_bar_y;
int title_bar_w;
int title_bar_h;
int pen_is_moving=0;



#define ALARM_CYCLE_TIME_UPDATE 5 
#define ALARM_CYCLE_FRAME_UPDATE 1 
#define ALARM_CYCLE_PEN_UPDATE 10 

volatile int go_time_update_flag=0;
volatile int go_pen_update_flag=0;
volatile int ticks=0;
/*******************************************************/
volatile int time_sec=00;
volatile int time_min=00;
volatile int time_hour=12;
alt_u32 time_alarm_callback(void * context){

	go_time_update_flag = 1;

  ticks+=ALARM_CYCLE_TIME_UPDATE;
  if (ticks >= alt_ticks_per_second()){

    ticks -= alt_ticks_per_second();
    time_sec++;
    if (time_sec>=60) {
    	time_sec = 0;
    	time_min++;
    	if (time_min>=60){
    		time_min=0;
    		time_hour++;
    		if (time_hour>=24)
    			time_hour=0;
    	}
    }


  }
  return ALARM_CYCLE_TIME_UPDATE;
}    

alt_u32 pen_alarm_callback(void * context){

	go_pen_update_flag = 1;

  return ALARM_CYCLE_FRAME_UPDATE;
}
int bg_col=0;


void set_frame_color(alt_video_display* display, int col){
  vid_draw_box (0, 0, display->width, display->height, col, 1, display);
}


////////////////////////////////////////////////
void update_grapics(int write_all){

static int w2 = FRAME_BUF_W;
static int h2 = FRAME_BUF_H;


static int col_var=0;


char strbuff[256];
int sw;

if (write_all){
  set_frame_color(display, GRAPH_BG_COL);

        snprintf(strbuff,256,"%s","VIP Suites");
        sw = vid_string_pixel_length_alpha( tahomabold_32, strbuff );
        vid_print_string_alpha(10, h2/2 -32/2 -1 +0, LIGHTGREEN_24, GRAPH_BG_COL,     
                      tahomabold_32, display, strbuff);   

        snprintf(strbuff,256,"%s","V16.1");
        sw = vid_string_pixel_length_alpha( tahomabold_32, strbuff );     
        vid_print_string_alpha(188, h2/2 -32/2 +11 , LIGHTGREEN_24, GRAPH_BG_COL,     
                      tahomabold_20, display, strbuff);   
        snprintf(strbuff,256,"%s","TERASIC");
        sw = vid_string_pixel_length_alpha( tahomabold_20, strbuff );
        vid_print_string_alpha((w2-sw)-8 -2, h2/2 -20/2-4 +0  , ALTERA_COLOR2, CLEAR_BACKGROUND, tahomabold_20, display, strbuff);   
        vid_print_string_alpha((w2-sw)-8   , h2/2 -20/2-4 +0-2, ALTERA_COLOR2, CLEAR_BACKGROUND, tahomabold_20, display, strbuff);   
        vid_print_string_alpha((w2-sw)-8 +2, h2/2 -20/2-4 +0  , ALTERA_COLOR2, CLEAR_BACKGROUND, tahomabold_20, display, strbuff);   
        vid_print_string_alpha((w2-sw)-8   , h2/2 -20/2-4 +0+2, ALTERA_COLOR2, CLEAR_BACKGROUND, tahomabold_20, display, strbuff);   
        vid_print_string_alpha((w2-sw)-8 -1, h2/2 -20/2-4 +0-1, ALTERA_COLOR1, CLEAR_BACKGROUND, tahomabold_20, display, strbuff);   
        vid_print_string_alpha((w2-sw)-8 -1, h2/2 -20/2-4 +0+1, ALTERA_COLOR1, CLEAR_BACKGROUND, tahomabold_20, display, strbuff);   
        vid_print_string_alpha((w2-sw)-8 +1, h2/2 -20/2-4 +0-1, ALTERA_COLOR1, CLEAR_BACKGROUND, tahomabold_20, display, strbuff);   
        vid_print_string_alpha((w2-sw)-8 +1, h2/2 -20/2-4 +0+1, ALTERA_COLOR1, CLEAR_BACKGROUND, tahomabold_20, display, strbuff);   

        vid_print_string_alpha((w2-sw)-8   , h2/2 -20/2-4 +0  , GRAPH_BG_COL, CLEAR_BACKGROUND, tahomabold_20, display, strbuff);   


}
      snprintf(strbuff,256,"%02d:%02d:%02d", time_hour, time_min, time_sec); 
      sw = 144;

      my_vid_print_string_alpha(   
      (w2-sw)/2+ 100, h2/2 -32/2 -1 +0, col_var, GRAPH_BG_COL,     
                      tahomabold_32, display, strbuff);   

  col_var = 255 - ticks * 2;
  if (col_var>255) col_var=255;
  col_var = (col_var<<16) | (col_var<<8) | col_var;

}
/*******************************************************/
/*******************************************************/
extern void pen_down( int pen_x, int pen_y);
extern void pen_move( int pen_x, int pen_y);
extern void pen_up( int pen_x, int pen_y);


int touchscreen_event_handling(MTC2_INFO *pTouch){

  int pen_x;
  int pen_y;
  int pen_is_down;
  static int pre_pen_x;
  static int pre_pen_y;
  static int pre_pen_x1;
  static int pre_pen_y1;
  static int pre_pen_x2;
  static int pre_pen_y2;
  static int pre_pen_x3;
  static int pre_pen_y3;
  static int pre_pen_x4;
  static int pre_pen_y4;
  static int pre_pen_is_down;
  //printf("pen is down\n");
  if (MTC2_GetStatus(pTouch, &Event, &TouchNum, &pen_x, &pen_y, &pre_pen_x1, &pre_pen_y1, &pre_pen_x2, &pre_pen_y2, &pre_pen_x3, &pre_pen_y3, &pre_pen_x4, &pre_pen_y4))
  {
    pen_is_down = 1;
  }
  else
  {
    pen_is_down = 0;
  }

  if ( pen_is_down ) {
    if (pre_pen_is_down) 
    {
      pen_move(pen_x, pen_y);
//      printf("pen is pre down\n");
    }
    else
    {
      pen_down(pen_x, pen_y);
      printf("\npen is down:\nx:%d,y:%d\n",pen_x,pen_y);

    }
  }
  else if (pre_pen_is_down) {
      pen_up(pen_x, pen_y);
  }

  pre_pen_x = pen_x;
  pre_pen_y = pen_y;
  pre_pen_is_down = pen_is_down;
  
//  printf("pre_pen_is_down:%d\n",pre_pen_is_down);
//  printf("pen_is_down:%d\n",pen_is_down);
//  usleep(15*1000);// this is  a must delay for mtlc's touch screen
  return pen_is_down;

}

#define VIDEO_DECODER_RESET_BIT 4
static alt_u32 pio_data=0;
void pio_write(alt_u32 base_addr, alt_u32 d){
  pio_data = d;
  IOWR(base_addr,0,pio_data);
}
void pio_bit_set(alt_u32 base_addr, alt_u32 d){
  pio_data |= d;
  IOWR(base_addr,0,pio_data);
}
void pio_bit_clr(alt_u32 base_addr, alt_u32 d){
  pio_data &= ~d;
  IOWR(base_addr,0,pio_data);
}

#define VIDEO_DECODER_RESET_ON IOWR_ALTERA_AVALON_PIO_DATA(TD_RESET_PIO_BASE, 0); 
#define VIDEO_DECODER_RESET_OFF IOWR_ALTERA_AVALON_PIO_DATA(TD_RESET_PIO_BASE, 1); 


// Interrupt service routine 
void video_intr_task(){

    Control_Synchronizer_clear_interrupt();

    int touchscreen_event; 
    // handle touch screen event if any
    touchscreen_event = touchscreen_event_handling(pTouch) ; 

    // update frame size/pos variables
    if (! touchscreen_event){
        if (auto_timer<=0) {  // move by inertia
        {  bg_col &= 0x0;     //
     //     IOWR(ALT_VIP_CUSTOM_TPG_0_BASE,0,bg_col ) ;
         }
          if (motion_count==5) {
            free_fall_image();
//            printf("motion 5\n");
            }


          else if (motion_count==4) {
            move_image_top_center(-1,-1,-1,-1,-1);
//            printf("motion 4\n");
            }

          else if (motion_count==3) {
            pan_and_scroll_image(-1,-1,-1,-1,-1);
//            printf("motion 3\n");


            }

          else if (motion_count==2) {
            zoom_and_scroll_image(-1,-1,-1,-1,-1);
//            printf("motion 2\n");

            }

          else if (motion_count==1) {
            move_image_center(-1,-1,-1,-1,-1);
//            printf("motion 1\n");


           }

          else{
            motion_count=0;
            move_image(-1,-1,-1,-1,-1);
//            printf("motion 0\n");

          }
          bounce_image_reset();
        }
        else {
          bounce_image();
        }
    }  
   {
    set_hw(); // Set HW parameters and wait for next interrupt
   }
}

/////////////////////////////////////////////////////////////////////////////
int main()
{

  VIDEO_DECODER_RESET_ON; // reset TV Decoder chip
  usleep(500*1000);
  // Release reset for TV decoder chip
  VIDEO_DECODER_RESET_OFF;
  usleep(500*1000);
  // Stop VIP cores
  Clipper_stop(0);
  //IOWR(ALT_VIP_SCL_0_BASE,0, 0x0);
  Scaler_stop(0);
  Mixer_stop(0);




  printf("\n\n\n\n");
  printf("**********************************************************\n");
  printf("*VIP DEMO LCD_SVGA version rev.1 has been started! *\n");
  printf("**********************************************************\n\n");

//  display = alt_video_display_only_frame_init(
//                                    FRAME_BUF_W,                          // int width
//                                    FRAME_BUF_H,                          // int height
//                                    ALT_VIDEO_DISPLAY_COLOR_DEPTH,        // int color_depth
//                                    SDRAM_BASE + 0x02000000,              // int buffer_location
//                                    1 );                                  // int num_buffers
//

  // use on-chip memory as frame reader buffer .due to lack bandwidth of sdram x16
 display = alt_video_display_only_frame_init(
                                      FRAME_BUF_W,                          // int width
                                      FRAME_BUF_H,                          // int height
                                      ALT_VIDEO_DISPLAY_COLOR_DEPTH,        // int color_depth
                                      ONCHIP_MEMORY2_0_BASE + 0x0,              // int buffer_location
                                      1 );                                  // int num_buffers


  if (display == NULL){
    printf("Memory Alloc error !\n");
    while(1){}
  }

  // a debug message
  printf("go\n");

  VIDEO_DECODER_RESET_ON; // reset TV Decoder chip
  usleep(500*1000);
  // Release reset for TV decoder chip
  VIDEO_DECODER_RESET_OFF;
  usleep(200*1000);
  // set hardware adderss of I2C port 
  init_i2c();
  // initialize TV decoder chip
  tv_decoder_init();
  //touch i2c initial
  oc_i2c_init(TOUCH_I2C_OPENCORES_BASE);

  // monitor TV decoder status for debug
  int ad;
  ad = 0x0f; printf("ADV7180[%02x]=0x%02x\n",ad,tv_decoder_read(ad));
  ad = 0x10; printf("ADV7180[%02x]=0x%02x\n",ad,tv_decoder_read(ad));
  ad = 0x10; printf("ADV7180[%02x]=0x%02x\n",ad,tv_decoder_read(ad));
  ad = 0x13; printf("ADV7180[%02x]=0x%02x\n",ad,tv_decoder_read(ad));
  printf("\n");

   //initial MULTI-touch 
   pTouch = MTC2_Init(TOUCH_I2C_OPENCORES_BASE, TOUCH_INT_N_BASE, TOUCH_INT_N_IRQ);
    if (!pTouch){
        printf("Failed to init multi-touch\r\n");
    }else{
        printf("Init touch successfully\r\n");
    }

  //bg_col = 0x24888444;
 // bg_col = 0x11111111;
 // IOWR(ALT_VIP_CUSTOM_TPG_0_BASE,0,bg_col);

  // LCD display area size
  int w_max=LCD_DISPLAY_W;
  int h_max=LCD_DISPLAY_H;

  // Live image  default size/pos
  int w1 = LIVE_IMAGE_W;
  int h1 = LIVE_IMAGE_H;
  int x1 = (w_max - w1)/2;
  int y1 = (h_max - h1)/2;

  // NiosII default size/pos
  title_bar_w = FRAME_BUF_W;
  title_bar_h = FRAME_BUF_H;
  title_bar_x = (w_max - title_bar_w)/2;
  title_bar_y = 0;

  // Set up Nios II frame buffer background color
  set_frame_color(display, GRAPH_BG_COL);


  // Start alarm for Clock display function
  alt_alarm alarm_time_update;
  if (alt_alarm_start(&alarm_time_update, ALARM_CYCLE_TIME_UPDATE, time_alarm_callback, NULL) < 0 ){ 
    printf("No system Clock\n");
  }

  Control_Synchronizer_init();
  
  Frame_Reader_init();
  Frame_Reader_set_frame_0_properties( VFR1_SCREEN_0_BASE_ADDRESS,
     VFR1_SCREEN_PIXEL_COUNT, VFR1_SCREEN_PIXEL_COUNT,
     FRAME_BUF_W, FRAME_BUF_H, 3); // 3=progressive video
  Frame_Reader_switch_to_pb0();
  Frame_Reader_start();


  // Start VIP Cores

  Clipper_init();
  Scaler_init();
  Mixer_init();
  //printf("scale II IP status reg bit 0 =0x%02x\n",IORD(ALT_VIP_SCL_0_BASE,0 ));
 // printf("scale II IP status reg bit 0 =0x%02x\n",IORD(ALT_VIP_SCL_0_BASE,1 ));
  //while(!IORD(ALT_VIP_SCL_0_BASE,1 )){IOWR(ALT_VIP_SCL_0_BASE,0, 0x0) ;IOWR(ALT_VIP_SCL_0_BASE,0, 0x1);};
 // printf("mix IP status reg bit 0 =0x%02x\n",IORD(ALT_VIP_CTS_0_BASE,1 ));

  //Mixer_set_layer_position(0, 0, 0);

  Mixer_set_layer_position(1, x1, y1);
  Scaler_set_output_size( w1, h1);
  Mixer_set_layer_position(2, title_bar_x, title_bar_y);
  move_image(x1, y1, w1, h1, 1);

  update_grapics(1);

  // debug message
  printf("ok1\n");

  int button=0xf;

  int loop_cnt=0;
  int pre_time_sec=-1;

   // alt_ic_isr_register(0, ALT_VIP_CTS_0_IRQ, video_intr_task, NULL, NULL);

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
  if ((alt_ic_isr_register(ALT_VIP_CTS_0_IRQ_INTERRUPT_CONTROLLER_ID,
		                   ALT_VIP_CTS_0_IRQ,
		                   video_intr_task,
		                   NULL,
		                   NULL
		                   ) != 0)){
 #else
  if ((alt_irq_register(p->INT_IRQ_NUM, (void *)p, mtc2_ISR) != 0)){
 #endif

	  printf(("[VTS]register IRQ fail\n"));
		  }else{
			  printf(("[VTS]register IRQ success\n"));
		  }

 // alt_ic_irq_enable(ALT_VIP_CTS_0_IRQ_INTERRUPT_CONTROLLER_ID,ALT_VIP_CTS_0_IRQ);
    set_hw();

  while(1) {

    // update Nios II frame
    if(go_time_update_flag) {
      // update Nios II frame
      update_grapics(0);

      // for debug  
      if(pre_time_sec != time_sec){
        if (button == 0xe) {  // debug print
          int ad=0x10;
          printf("lp:%d, ADV7180[%02x]=0x%02x \n",loop_cnt, ad, tv_decoder_read(ad));
        }
        loop_cnt=0;
        pre_time_sec = time_sec;
      }

      go_time_update_flag=0;
      if (auto_timer>0) auto_timer -= ALARM_CYCLE_TIME_UPDATE;
    }
//    else
//    {
//      update_grapics(0);
//    }

    // push button handling
    button = IORD(BUTTON_PIO_BASE,0) & 0xf;
    if (button != 0xf) {
      switch (button) {
      case 0xd :
        title_bar_y+=4;
        if( title_bar_y > (h_max - FRAME_BUF_H) ) title_bar_y = (h_max - FRAME_BUF_H);
          Mixer_set_layer_position(2, title_bar_x, title_bar_y);
        usleep(1000*5);
        break;
      case 0xe :
        title_bar_y-=4;
        if (title_bar_y<0) title_bar_y=0;
          Mixer_set_layer_position(2, title_bar_x, title_bar_y);
        usleep(1000*5);
        break;
      case 0x7 :
        time_min++;
        if (time_min>59) time_min = 0;
        update_grapics(0);
        usleep(1000*200);
        break;
      case 0xb :
        time_hour++;
        if (time_hour>23) time_hour = 0;
        update_grapics(0);
        usleep(1000*200);
        break;
      }
    }
    
  } // end of while(1) loop

  return ( 0 );
}
