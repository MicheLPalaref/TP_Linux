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
#include "gui_compass.h"
#include "vip_fr.h"
#include "multi_touch2.h"
#include "simple_graphics.h"
#include "geometry.h"
#include "gesture.h"
#include "gimp_bmp.h"
#include "mpu9250.h"
#include "uart.h"
#include <math.h>


//#define USE_MAXTIX

#define PI	3.14159

#define COLOR_R 0xFF0000
#define COLOR_G 0x00FF00
#define COLOR_B 0x0000FF
#define COLOR_WHITE 0xFFFFFF
#define COLOR_BLACK 0x000000
#define COLOR_GRAY  0x7F7F7F
#define COLOR_YELLOW  (COLOR_R | COLOR_G)

//#define R 70


extern gimp_image_struct compass_image;
extern gimp_image_struct rotate_xyz_360_image;


#define FR_FRAME_0  (SDRAM_BASE + SDRAM_SPAN/2)
#define FR_FRAME_1  (FR_FRAME_0 + FRAME_WIDTH*FRAME_HEIGHT*4)
#define FR_FRAME_BACKGROUND  (SDRAM_BASE + FRAME_WIDTH*FRAME_HEIGHT*4*2)

#define FRAME_WIDTH  800
#define FRAME_HEIGHT 480
#define DOT_SIZE    6




float Compass_Calcuate(float pitch, float roll, float mx, float my, float mz){
	float xh, yh;
	float var_compass;


	//http://blog.sina.com.cn/s/blog_8240cbef0101i7gn.html


    xh=mx*cos(pitch)+my*sin(roll)*sin(pitch)-mz*sin(pitch)*cos(roll);
    yh=my*cos(roll)+mz*sin(roll);

  //  yh=my;
   // xh=mx;


    // xh is forward in VEEK-MTL2
    //                North
    //                mX
    //                |
    //                |
    //                |
    // mY  <--------- +
    //
    //

    var_compass=atan2((double)yh,(double)xh) * (180.0 / PI) ; // angle in degrees

    if (var_compass < 0.0)
    	var_compass += 360.0;

    return var_compass;
}


bool IsTouched(MTC2_INFO *pTouch, RECT &rc){
	bool bTouched = false;
	POINT pt;
	alt_u8 Event, TouchNum;
	int X1, Y1, X2, Y2, X3, Y3, X4, Y4, X5, Y5;

	   if (MTC2_GetStatus(pTouch, &Event, &TouchNum,&X1, &Y1,&X2, &Y2, &X3, &Y3, &X4, &Y4, &X5, &Y5)){
		   if (TouchNum == 1){
			   pt.x = X1;
			   pt.y = Y1;
			   if (IsPtInRect(&pt, &rc)){
				   bTouched = true;
				   MTC2_ClearEvent(pTouch);
			   }
		   }
	   }

	   return bTouched;
}

void DrawButton(VIP_FRAME_READER *pReader, RECT &rcButton, const char *pText){
	char szText[128];
	int text_length;
    vid_draw_round_corner_box (rcButton.left, rcButton.top,
    							rcButton.right, rcButton.bottom,
                               10, COLOR_WHITE,  DO_NOT_FILL, pReader);
    sprintf(szText, "%s", pText);
    text_length = vid_string_pixel_length_alpha(tahomabold_20, szText);
    vid_print_string_alpha(rcButton.left+((rcButton.right-rcButton.left)-text_length)/2, rcButton.top+15, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);

}

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




bool MagCalibrate(VIP_FRAME_READER *pReader, MTC2_INFO *pTouch, float *pfXoffset, float *pfYoffset, float *pfZoffset){
	MPU9250 mpu(MPU_I2C_OPENCORES_BASE);
	bool bSuccess = false, bDone = false;
	float fXmaxi=-999, fXmini=999;
	float fYmaxi=-999, fYmini=999;
	float fZmaxi=-999, fZmini=999;
	float ax, ay, az, gx, gy, gz, mx, my, mz;
	float fXavg,fYavg,fZavg;
	POINT pt, ptStart = {100,120};
	char szText[256];
	int count = 0;

    // touch
	alt_u8 Event, TouchNum;
	int X1, Y1, X2, Y2, X3, Y3, X4, Y4, X5, Y5;

	RECT rcFinished = {400, 600, 250, 310};
	RECT rcYes = {100, 300, 350, 410};
	RECT rcNo = {500, 700, 350, 410};

	/////////////////////////////////////
	// show hint
	vid_clean_screen(pReader, COLOR_BLACK);
	VIPFR_ActiveDrawFrame(pReader);

	vid_clean_screen(pReader, COLOR_BLACK);
	pt = ptStart;

    sprintf(szText, "%s", "Rotate the VEEK-MTL2 1-2 times around each of");
    vid_print_string_alpha(pt.x, pt.y, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);

    sprintf(szText, "%s", "its 3 axes then press FINISH button.");
    vid_print_string_alpha(pt.x, pt.y+30, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);

    // draw hint graphic
    DrawImage(pReader, &rotate_xyz_360_image, pt.x+30, pt.y+90);

    // draw Finished button
    DrawButton(pReader, rcFinished, "Finished");

	VIPFR_ActiveDrawFrame(pReader);



	// recode data
	mpu.initialize();
	while(!bDone){
		count++;
		mpu.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
		printf("%.2f,%.2f,%.2f\r\n", mx, my, mz);

		// x
		if (mx > fXmaxi)
			fXmaxi = mx;
		else if (mx < fXmini)
			fXmini = mx;

		// y
		if (my > fYmaxi)
			fYmaxi = my;
		else if (my < fYmini)
			fYmini = my;

		// z
		if (mz > fZmaxi)
			fZmaxi = mz;
		else if (mx < fZmini)
			fZmini = mz;

		bDone = IsTouched(pTouch, rcFinished);

	}

	/////////////////////////////////////
	// show result and ask to confirm the result
	vid_clean_screen(pReader, COLOR_BLACK);

	fXavg = (fXmaxi + fXmini)/2.0;
	fYavg = (fYmaxi + fYmini)/2.0;
	fZavg = (fZmaxi + fZmini)/2.0;

	// count
    sprintf(szText, "Sample Number: %d", count);
    vid_print_string_alpha(pt.x, pt.y-30, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);



    // mini
    pt.x += 50;
    sprintf(szText, "%s", "Minimum");
    vid_print_string_alpha(pt.x, pt.y, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);
    sprintf(szText, "x:%.2f", fXmini);
    vid_print_string_alpha(pt.x, pt.y+30, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);
    sprintf(szText, "y:%.2f", fYmini);
    vid_print_string_alpha(pt.x, pt.y+60, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);
    sprintf(szText, "z:%.2f", fZmini);
    vid_print_string_alpha(pt.x, pt.y+90, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);

    // max
    pt.x += 180;
    sprintf(szText, "%s", "Maximum");
    vid_print_string_alpha(pt.x, pt.y, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);
    sprintf(szText, "x:%.2f", fXmaxi);
    vid_print_string_alpha(pt.x, pt.y+30, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);
    sprintf(szText, "y:%.2f", fYmaxi);
    vid_print_string_alpha(pt.x, pt.y+60, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);
    sprintf(szText, "z:%.2f", fZmaxi);
    vid_print_string_alpha(pt.x, pt.y+90, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);

    // avg
    pt.x += 180;
    sprintf(szText, "%s", "Average");
    vid_print_string_alpha(pt.x, pt.y, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);
    sprintf(szText, "x:%.2f", fXavg);
    vid_print_string_alpha(pt.x, pt.y+30, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);
    sprintf(szText, "y:%.2f", fYavg);
    vid_print_string_alpha(pt.x, pt.y+60, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);
    sprintf(szText, "z:%.2f", fZavg);
    vid_print_string_alpha(pt.x, pt.y+90, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);

    pt.x = ptStart.x;
    pt.y = ptStart.y + 150;
    sprintf(szText, "%s", "Do you want to apply this calibration result?");
    vid_print_string_alpha(pt.x, pt.y, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);

    // draw buttons
    DrawButton(pReader, rcYes, "Yes");
    DrawButton(pReader, rcNo, "No");


    VIPFR_ActiveDrawFrame(pReader);

    //////////////////////////////
    // wait user confirm
    bDone = false;
    while(!bDone){
	   if (MTC2_GetStatus(pTouch, &Event, &TouchNum,&X1, &Y1,&X2, &Y2, &X3, &Y3, &X4, &Y4, &X5, &Y5)){
		   if (TouchNum == 1){
			   pt.x = X1;
			   pt.y = Y1;
			   if (IsPtInRect(&pt, &rcYes)){
				   bSuccess = true;
				   bDone = true;
			   }else  if (IsPtInRect(&pt, &rcNo)){
				   bDone = true;
			   }
		   } // if
	   }  // if
	} // while
    MTC2_ClearEvent(pTouch);


	if (bSuccess){
		*pfXoffset = fXavg;
		*pfYoffset = fYavg;
		*pfZoffset = fZavg;
	}


	return bSuccess;
}





void GUI_Compass(MTC2_INFO *pTouch){
    VIP_FRAME_READER *pReader;
    void *pBackgroundBuffer = (void *)FR_FRAME_BACKGROUND;
    int text_length;
    float dx, dy, fHead, dh, dv;
    POINT pt;
    const int nPenSize = 1;
    float pitch, roll;

    // mpu
    MPU9250 mpu(MPU_I2C_OPENCORES_BASE);
    float ax, ay, az, gx, gy, gz, mx, my, mz;
    float var_compass;
    char szText[128];

#ifdef USE_MATRIX
    // matrix is calculated by MagMaster
    // http://diydrones.com/m/blogpost?id=705844%3ABlogPost%3A1676387&maxDate=2014-10-22T17%3A27%3A53.045Z
    const float B[] = {-8.201, 57.871, -74.313};
    const float M[3][3] = {
    		{3.046,-4.621, 0.661},
    		{-0.225,5.423,-0.144},
    		{0.93,2.079,4.539}
    };
#else

    float fmxOffset = 8.0;
    float fmyOffset = 75.395;
    float fmzOffset = -30.575;
#endif


    // magnetometer
    POINT ptStart, ptEnd, ptCenter={FRAME_WIDTH/2, FRAME_HEIGHT/2};
    const int nRadius = 200;

    // accelerometer
    POINT ptCenter_GSensor = {90,90}, ptBubble;
    const int nRadius_GSensor = 40;
    const int nBarGap_GSensor = 15;
    const int nBarWidth_GSensor = 20;
    const int nAreaSize_GSensor = 20;

    // calibration button
    RECT rcCalibrate = {600, 780, 400, 460};



    printf("===== Welcome to E-Compass demo program =====\n");

    // init frame reader
    pReader =  VIPFR_Init(ALT_VIP_VFR_0_BASE, (void *)FR_FRAME_0, (void *)FR_FRAME_1, FRAME_WIDTH, FRAME_HEIGHT);
    VIPFR_Go(pReader, TRUE);
    
    
   // draw desktop background
    vid_clean_screen(pReader, COLOR_BLACK);

    ////////////////////////////////////////
    // draw back ground of accelerometer

    // big circle
    vid_draw_circle(ptCenter_GSensor.x, ptCenter_GSensor.y, nRadius_GSensor, COLOR_G, DO_FILL, pReader);
    vid_draw_circle(ptCenter_GSensor.x, ptCenter_GSensor.y, nAreaSize_GSensor/2, COLOR_BLACK, DO_NOT_FILL, pReader);
    vid_draw_line(ptCenter_GSensor.x, ptCenter_GSensor.y-nRadius_GSensor, ptCenter_GSensor.x, ptCenter_GSensor.y+nRadius_GSensor, 3, COLOR_BLACK, pReader);
    vid_draw_line(ptCenter_GSensor.x-nRadius_GSensor, ptCenter_GSensor.y, ptCenter_GSensor.x+nRadius_GSensor, ptCenter_GSensor.y, 3, COLOR_BLACK, pReader);

    // right box
    vid_draw_round_corner_box (ptCenter_GSensor.x + nRadius_GSensor + nBarGap_GSensor, ptCenter_GSensor.y- nRadius_GSensor,
    		                   ptCenter_GSensor.x + nRadius_GSensor + nBarGap_GSensor+nBarWidth_GSensor, ptCenter_GSensor.y + nRadius_GSensor,
                               10, COLOR_G,  DO_FILL, pReader);
    vid_draw_line(ptCenter_GSensor.x + nRadius_GSensor + nBarGap_GSensor, ptCenter_GSensor.y-nAreaSize_GSensor/2,
    		      ptCenter_GSensor.x + nRadius_GSensor + nBarGap_GSensor+nBarWidth_GSensor, ptCenter_GSensor.y-nAreaSize_GSensor/2,
    		      3, COLOR_BLACK, pReader);
    vid_draw_line(ptCenter_GSensor.x + nRadius_GSensor + nBarGap_GSensor, ptCenter_GSensor.y+nAreaSize_GSensor/2,
    		      ptCenter_GSensor.x + nRadius_GSensor + nBarGap_GSensor+nBarWidth_GSensor, ptCenter_GSensor.y+nAreaSize_GSensor/2,
    		      3, COLOR_BLACK, pReader);

    // bottom box
    vid_draw_round_corner_box (ptCenter_GSensor.x - nRadius_GSensor, ptCenter_GSensor.y + nRadius_GSensor + nBarGap_GSensor,
    		                   ptCenter_GSensor.x + nRadius_GSensor, ptCenter_GSensor.y + nRadius_GSensor + nBarGap_GSensor+nBarWidth_GSensor,
                               10, COLOR_G,  DO_FILL, pReader);
    vid_draw_line(ptCenter_GSensor.x - nAreaSize_GSensor/2, ptCenter_GSensor.y + nRadius_GSensor + nBarGap_GSensor,
		              ptCenter_GSensor.x - nAreaSize_GSensor/2, ptCenter_GSensor.y + nRadius_GSensor + nBarGap_GSensor+nBarWidth_GSensor,
		              3, COLOR_BLACK, pReader);
    vid_draw_line(ptCenter_GSensor.x + nAreaSize_GSensor/2, ptCenter_GSensor.y + nRadius_GSensor + nBarGap_GSensor,
		              ptCenter_GSensor.x + nAreaSize_GSensor/2, ptCenter_GSensor.y + nRadius_GSensor + nBarGap_GSensor+nBarWidth_GSensor,
		              3, COLOR_BLACK, pReader);

    ////////////////////////////////////////
    // draw back ground of magnetometer

    // draw compass
    DrawImage(pReader, &compass_image, FRAME_WIDTH/2-nRadius, FRAME_HEIGHT/2-nRadius);


    // draw calibration button
    DrawButton(pReader, rcCalibrate, "Calibrate");


    ////////////////////////////////////////
    // save background to a buffer
    VIPFR_ReadDrawFrame(pReader, pBackgroundBuffer);
    VIPFR_ActiveDrawFrame(pReader);

    mpu.initialize();


   while(1){
	   if (IsTouched(pTouch, rcCalibrate)){
		   float x, y, z;
		   if (MagCalibrate(pReader, pTouch, &x, &y, &z)){
			   fmxOffset = x;
			   fmyOffset = y;
			   fmzOffset = z;
		   }
	   }


	   mpu.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);

#ifdef USE_MAXTRIX
		  float mxb, myb, mzb;
		  mxb = mx - B[0];
		  myb = my - B[1];
		  mzb = mz - B[2];
		  mx = M[0][0]*mxb + M[0][1]*myb+M[0][2]*mzb;
		  my = M[1][0]*mxb + M[1][1]*myb+M[1][2]*mzb;
		  mz = M[2][0]*mxb + M[2][1]*myb+M[2][2]*mzb;
#else
	  mx = mx - fmxOffset;
	  my = my - fmyOffset;
	  mz = mz - fmzOffset;
#endif

	  pitch = atan(ay/sqrt(ax*ax+az*az));
	  roll = atan(ax/sqrt(ax*ax+az*az));

	 // printf("pitch:%.1f, roll:%.1f\r\n", pitch*(180.0 / PI), roll*(180.0 / PI));

	  var_compass = Compass_Calcuate(pitch, roll, mx, my, mz);


	   // printf("  acceleromter(m/s^2): ax=%f, ay=%f, az=%f\r\n", ax, ay, az);
	   // printf("  gyroscope (degree/second): gx=%f, gy=%f, gz=%f\r\n", gx, gy, gz);
	   // printf("  magnetometer(uT ?): mx=%f, my=%f, mz=%f\r\n", mx, my, mz);
	    printf("compass:%.1f\r\n", var_compass);



	    // restore background
        VIPFR_WriteDrawFrame(pReader, pBackgroundBuffer); /// restore background

        ///////////////////////////////////
        // accelerometer

        // draw text
        pt.x = ptCenter_GSensor.x - nRadius_GSensor;
        pt.y = ptCenter_GSensor.y +  nRadius_GSensor + nBarGap_GSensor + nBarWidth_GSensor*2;
        sprintf(szText, "x:%.2f", ax);
        vid_print_string_alpha(pt.x, pt.y, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);
        sprintf(szText, "y:%.2f", ay);
        vid_print_string_alpha(pt.x, pt.y+30, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);
        sprintf(szText, "z:%.2f", az);
        vid_print_string_alpha(pt.x, pt.y+60, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);


        // draw bubble
        dh = nRadius_GSensor * sin(roll); // horizontal
        dv = nRadius_GSensor * sin(pitch); // vertical

        // x/y 2-d
        ptBubble.x = ptCenter_GSensor.x - dh;
        ptBubble.y = ptCenter_GSensor.y - dv;
        vid_draw_circle(ptBubble.x, ptBubble.y, nAreaSize_GSensor/2-1, COLOR_WHITE, DO_FILL, pReader);
        vid_draw_circle(ptBubble.x, ptBubble.y, nAreaSize_GSensor/2-1, COLOR_BLACK, DO_NOT_FILL, pReader);

        // y (right)
        ptBubble.x = ptCenter_GSensor.x + nRadius_GSensor + nBarGap_GSensor + nBarWidth_GSensor/2;
        ptBubble.y = ptCenter_GSensor.y - dv;
        vid_draw_circle(ptBubble.x, ptBubble.y, nAreaSize_GSensor/2-1, COLOR_WHITE, DO_FILL, pReader);
        vid_draw_circle(ptBubble.x, ptBubble.y, nAreaSize_GSensor/2-1, COLOR_BLACK, DO_NOT_FILL, pReader);

        // x (bottom)
        ptBubble.x = ptCenter_GSensor.x - dh;
        ptBubble.y = ptCenter_GSensor.y + nRadius_GSensor + nBarGap_GSensor+nBarWidth_GSensor/2;
        vid_draw_circle(ptBubble.x, ptBubble.y, nAreaSize_GSensor/2-1, COLOR_WHITE, DO_FILL, pReader);
        vid_draw_circle(ptBubble.x, ptBubble.y, nAreaSize_GSensor/2-1, COLOR_BLACK, DO_NOT_FILL, pReader);



        ///////////////////////////////////
        // magnetometer
        fHead = var_compass/180.0*PI;

	    // display text
        sprintf(szText, "%d", (int)(var_compass + 0.5));
        text_length = vid_string_pixel_length_alpha(tahomabold_20, szText);
        vid_print_string_alpha(ptCenter.x-text_length/2, 10, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);



        pt.x = ptCenter.x + nRadius + 30;
        pt.y = ptCenter.y - 45;
        sprintf(szText, "x:%.2f", mx);
        vid_print_string_alpha(pt.x, pt.y, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);
        sprintf(szText, "y:%.2f", my);
        vid_print_string_alpha(pt.x, pt.y+30, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);
        sprintf(szText, "z:%.2f", mz);
        vid_print_string_alpha(pt.x, pt.y+60, COLOR_WHITE,COLOR_BLACK, tahomabold_20, pReader, szText);

        // draw graphic
       // vid_draw_circle(ptCenter.x, ptCenter.y, nRadius, COLOR_WHITE, 0x00 /* not fill */, pReader);

        dx = (28.0)*sin(fHead);
        dy = (28.0)*cos(fHead);
        ptStart.x = ptCenter.x - dx;
        ptStart.y = ptCenter.y - dy;

        dx = (nRadius-50.0)*sin(fHead);
        dy = (nRadius-50.0)*cos(fHead);
        ptEnd.x = ptCenter.x - dx;
        ptEnd.y = ptCenter.y - dy;
        vid_draw_line(ptStart.x, ptStart.y, ptEnd.x, ptEnd.y, nPenSize , COLOR_B, pReader);

        // draw arrow
        ptStart.x = ptEnd.x + 10.0*sin(fHead-PI/6.0);
        ptStart.y = ptEnd.y + 10.0*cos(fHead-PI/6.0);
        vid_draw_line(ptStart.x, ptStart.y, ptEnd.x, ptEnd.y, nPenSize , COLOR_B, pReader);

        ptStart.x = ptEnd.x + 10.0*sin(fHead+PI/6.0);
        ptStart.y = ptEnd.y + 10.0*cos(fHead+PI/6.0);
        vid_draw_line(ptStart.x, ptStart.y, ptEnd.x, ptEnd.y, nPenSize , COLOR_B, pReader);



        // update gui now
        VIPFR_ActiveDrawFrame(pReader);
   }
    
    
}


