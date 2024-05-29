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
// 4/30/2016, init by richard


#include "terasic_includes.h"
#include "gui_gsensor.h"
#include "vip_fr.h"
#include "multi_touch2.h"
#include "simple_graphics.h"
#include "geometry.h"
#include "gesture.h"
#include "gimp_bmp.h"
#include "mpu9250.h"
#include "light_sensor.h"
#include <math.h>

#define COLOR_R 0xFF0000
#define COLOR_G 0x00FF00
#define COLOR_B 0x0000FF
#define COLOR_WHITE 0xFFFFFF
#define COLOR_BLACK 0x000000
#define COLOR_GRAY  0x7F7F7F

#define R 70


#define FR_FRAME_0  (SDRAM_BASE + SDRAM_SPAN/2)
#define FR_FRAME_1  (FR_FRAME_0 + FRAME_WIDTH*FRAME_HEIGHT*4)
#define FR_FRAME_BACKGROUND  (SDRAM_BASE + FRAME_WIDTH*FRAME_HEIGHT*4*2)

#define FRAME_WIDTH  800
#define FRAME_HEIGHT 480
#define DOT_SIZE    6


#define V_BAR_X  30
#define V_BAR_Y  (80-30)

#define H_BAR_X  140
#define H_BAR_Y  (428-30)

#define CENTER_BALL_X  180
#define CENTER_BALL_Y  (100-30)


//#define VALID_POINT(x,y) (((x)>=DOT_SIZE && (x)<FRAME_WIDTH-DOT_SIZE && (y)>=DOT_SIZE && (y)<FRAME_HEIGHT-DOT_SIZE)?TRUE:FALSE)



void DrawImage(VIP_FRAME_READER *pReader, struct gimp_image_struct* Terasic_image, int horiz, int vert )
{

  bitmap_struct* image;
  alt_u8 *pDes, *pSrc, *image_dest;
  int y;

  image = (bitmap_struct *)malloc(sizeof(bitmap_struct));
  
  if( image != NULL )
  {
    // Load the CIII logo
    load_gimp_bmp( Terasic_image, image, 32);

    image_dest = (alt_u8 *)VIPFR_GetDrawFrame(pReader) + (vert*pReader->width*pReader->bytes_per_pixel) + (horiz*pReader->bytes_per_pixel);

    pSrc = (alt_u8 *)image->data;
    pDes = image_dest;
    for(y=0;y<image->biHeight;y++){
        memcpy(pDes, pSrc, image->biWidth * 4);
        pSrc += image->biWidth * 4;
        pDes += pReader->width * 4;
    }

    free_gimp_bmp_data( image );
    free( image );
  }
}

void draw_array(unsigned int *buffer, int x_size, int y_size,
		VIP_FRAME_READER *pReader, int x_offset, int y_offset,
  unsigned int transparent_color)
{
  unsigned int *current_buffer;
//  int addr = ( (int)(display->buffer_ptrs[display->buffer_being_written]->buffer) );
//  int addr = (alt_u8 *)VIPFR_GetDrawFrame(pReader);

  int x_b,y_b;
  unsigned int color;

  current_buffer = (unsigned int*)VIPFR_GetDrawFrame(pReader);

  transparent_color = 0xFF000000 | transparent_color;

  for (x_b = 0; x_b<x_size; x_b++) {
    for (y_b = 0; y_b<y_size; y_b++) {
      color = buffer[y_b*x_size+x_b];
      if (color != transparent_color) {
        current_buffer[(y_b+y_offset)*pReader->width+(x_b+x_offset)] = color;
      }
    }
  }
}

void DrawTransparentImage( VIP_FRAME_READER *pReader, struct gimp_image_struct* Terasic_image, int horiz, int vert,unsigned int transparent_color )
{

  bitmap_struct* image;

  image = (bitmap_struct*)malloc(sizeof(bitmap_struct));

  if( image != NULL )
  {
    // Load the CIII logo
    load_gimp_bmp( Terasic_image, image, 32);

//      image_dest = (char*)(( display->buffer_ptrs[display->buffer_being_written]->buffer ) + (vert * (display->width * 4)) + horiz * 4);
   //   image_dest = (alt_u8 *)VIPFR_GetDrawFrame(pReader) + (vert*pReader->width*pReader->bytes_per_pixel) + (horiz*pReader->bytes_per_pixel);

    draw_array((unsigned int*)image->data,image->biWidth,image->biHeight,pReader,horiz,vert,transparent_color);

    free_gimp_bmp_data( image );
    free( image );
  }
}



void InitBackGround(VIP_FRAME_READER *pReader)
{
    extern gimp_image_struct H_Bar;
    extern gimp_image_struct V_Bar;
    extern gimp_image_struct ball;
    extern gimp_image_struct bright;
    
    vid_clean_screen(pReader, COLOR_WHITE);
        
        //draw v_Bar , h_Bar, Ball
        DrawImage(pReader, &V_Bar, V_BAR_X,V_BAR_Y);
        DrawImage(pReader, &ball, CENTER_BALL_X, CENTER_BALL_Y);
        DrawImage(pReader, &H_Bar, H_BAR_X,H_BAR_Y);
        DrawImage(pReader, &bright,  570, 30);
              
     //  memcpy(temp_Buffer, (void*)(display->buffer_ptrs[display->buffer_being_written]->buffer),display->bytes_per_frame);
}


bool Get_light(alt_u16 *light0, alt_u16 *light1)
{
    bool bPass = FALSE;
    alt_u8 device_Id = 0;

    alt_u16 ChannelData0;
    alt_u16 ChannelData1;

    //get light sensor Id
    Light_GetID(&device_Id);
    if(device_Id == 0)
    {
        printf("read id fail \n");
        return FALSE;
    }else{
    	//printf("Light Sensor ID=%xh\r\n", device_Id); //
    }


    //get adc channel 0 data
    bPass = Light_Get_ADCData0(&ChannelData0);
    if(!bPass)
    {
        printf("Get ADC Channle 0 data fail \n");
        return FALSE;
    }
    *light0 = ChannelData0;

    //get adc channel 1 data
    bPass = Light_Get_ADCData1(&ChannelData1);
    if(!bPass)
    {
        printf("Get ADC Channle 1 data fail \n");
        return FALSE;
    }
    *light1 = ChannelData1;
    return TRUE;
}


typedef struct {
    int horiz;
    int vert;
    int Bar_Width;
    int origin_x;
    int origin_y;
} ICON_LOCATION;



extern gimp_image_struct ball_water;
extern gimp_image_struct v_bar_water;
extern gimp_image_struct h_bar_water;
extern gimp_image_struct h_Bar_Line;
extern gimp_image_struct v_Bar_Line;
extern gimp_image_struct ring;
extern gimp_image_struct dot;

void GUI_GSensor(MTC2_INFO *pTouch){
    VIP_FRAME_READER *pReader;
    int text_length;
   // void *pBackgroundBuffer; // use sram as buffer
    void *pBackgroundBuffer = (void *)FR_FRAME_BACKGROUND;  // use sdram as buffer

    // mpu
    MPU9250 mpu(MPU_I2C_OPENCORES_BASE);
    float ax, ay, az, gx, gy, gz, mx, my, mz;
    float x_angle, y_angle;
    const float x_offset_angle = 0.0, y_offset_angle = 0.0;
    const float to_radius = 180.0/M_PI;

    // light
    alt_u16 light0 = 0, light1 = 0;
    bool bPass = FALSE;
    char szText[128], szText2[128];

    int nX= 0, nY = 0;
    int center_x=400, center_y =400;

    ICON_LOCATION h_Bar = {0,0, 600, 325, 438-30 };
    ICON_LOCATION v_Bar = {0, 0, 600, 40,  265-30};
    ICON_LOCATION center_Ball = {0,0, 125, 289, 210-30};

    // graphic


    printf("===== Welcome to G_sensor demo program =====\n");
    
    // init light sensor i2c and power on
    Light_Init(LIGHT_I2C_OPENCORES_BASE);
    Light_PowerSwitch(TRUE);


    // init frame reader
    pReader =  VIPFR_Init(ALT_VIP_VFR_0_BASE, (void *)FR_FRAME_0, (void *)FR_FRAME_1, FRAME_WIDTH, FRAME_HEIGHT);
    VIPFR_Go(pReader, TRUE);
    
  //  pBackgroundBuffer = (void *)malloc(VIPFR_GetFrameSize(pReader));
  //  if (!pBackgroundBuffer){
    //	printf("failed to allocate buffer!\r\n");
    	//return;
    //}


    
   // draw desktop background
    InitBackGround(pReader);
    VIPFR_ReadDrawFrame(pReader, pBackgroundBuffer); // save background
  //  VIPFR_ActiveDrawFrame(pReader);
    

   mpu.initialize();

   while(1){

  		////////////////////////////
  		// handle gsensor

	   mpu.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);

	   if (az != 0){
		   x_angle = atan(ax/az)*to_radius - x_offset_angle;
		   y_angle = y_offset_angle - atan(ay/az)*to_radius;
	   }else{
		   printf("-------------------- az is zero\r\n");
		   x_angle = 0.0;
		   y_angle = 0.0;
	   }

       nX = (int)(x_angle * 140 /90);
       nY = (int)(y_angle * 140 /90);

        // calculate ball location
        if(nX >= 0)
            center_x = nX > R? R:nX;
        else
            center_x = nX < R*(-1) ? R*(-1) : nX;

        if(nY >= 0)
            center_y = nY > R ? R : nY;
        else
            center_y = nY < R*(-1) ? R*(-1) : nY;

        printf("x_angle=%.3f, y_angle=%.3f, ax=%.3f, ay=%.3f, az=%.3f\r\n", x_angle, y_angle, ax, ay, az);

        // draw back ground
        VIPFR_WriteDrawFrame(pReader, pBackgroundBuffer); /// restore background

        //draw ball water
        DrawTransparentImage(pReader, &ball_water, center_x+center_Ball.origin_x, center_Ball.origin_y-center_y, 0x0073c301);
       
         //draw ring
        DrawTransparentImage(pReader, &ring, center_Ball.origin_x-13, center_Ball.origin_y-13, 0x0073c301);
        
        DrawImage(pReader, &v_bar_water, v_Bar.origin_x, v_Bar.origin_y-nY);
        DrawImage(pReader, &h_bar_water, nX+h_Bar.origin_x, h_Bar.origin_y);

        //draw Line
        DrawImage(pReader, &h_Bar_Line, h_Bar.origin_x-5, h_Bar.origin_y-2);
        DrawImage(pReader, &h_Bar_Line, h_Bar.origin_x+41, h_Bar.origin_y-2);
        
        DrawImage(pReader, &v_Bar_Line, v_Bar.origin_x-2, v_Bar.origin_y-6);
        DrawImage(pReader, &v_Bar_Line, v_Bar.origin_x-2, v_Bar.origin_y+40);

        //display x angle
        sprintf(szText, "%d", (int)(x_angle));
        vid_print_string_alpha(480, 380-30, COLOR_BLACK,COLOR_WHITE, tahomabold_32, pReader, szText);
        text_length = vid_string_pixel_length_alpha(tahomabold_32, szText);
        DrawImage(pReader, &dot, 480+text_length, 390-30);
        
        //display y angle
        sprintf(szText, "%d", (int)(y_angle));
        vid_print_string_alpha(90, 100-30, COLOR_BLACK,COLOR_WHITE, tahomabold_32, pReader, szText);
        text_length = vid_string_pixel_length_alpha(tahomabold_32, szText);
        DrawImage(pReader, &dot, 90+text_length, 110-30);


   		////////////////////////////
   		// handle light sensor
        
        sprintf(szText, "%d", 0);
        sprintf(szText2, "%d", 0);
        bPass = Get_light(&light0,&light1);
        if(bPass)
        {
            sprintf(szText,  "%d", light0);
            sprintf(szText2, "%d", light1);
            printf("light0=%d, light1=%d\r\n", light0, light1);
        }else{
        	//printf("light sensor i2c fail.....................\r\n");
        	//break;
        }
        vid_print_string_alpha(630, 55, COLOR_WHITE,-1, tahomabold_32, pReader, szText);
        vid_print_string_alpha(630, 115, COLOR_WHITE,-1, tahomabold_32, pReader, szText2);
        

        // update gui now
        VIPFR_ActiveDrawFrame(pReader);
   }

 //  free(pBackgroundBuffer);
    
    
}

