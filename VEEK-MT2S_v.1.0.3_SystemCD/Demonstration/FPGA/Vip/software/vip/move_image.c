/*****************************************************************************
 *  File: move_image.c
 *
 *  This file is the top level of the application selector.
 *
 *  Control Scaler and Clipper and Mixer
 ****************************************************************************/


#include "move_image.h"


//#include <math.h>
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
//#include <sys/alt_dma.h>
//#include <altera_avalon_dma.h>

#include "system.h"

#include "altera_avalon_pio_regs.h"

#include "VIP_ctrl\vip_wrapper_for_c_func.h"


#define FM 1


extern int motion_count;
extern volatile int bg_col;

extern int title_bar_x;
extern int title_bar_y;
extern int title_bar_w;
extern int title_bar_h;
extern int pen_is_moving;

#define FRCTION_BITS 8
#define CALC_SC (1<<FRCTION_BITS)
#define W1_INT (w1>>FRCTION_BITS)
#define H1_INT (h1>>FRCTION_BITS)
#define X1_INT (x1>>FRCTION_BITS)
#define Y1_INT (y1>>FRCTION_BITS)
#define CLIPPER_X_INT (clipper_x>>FRCTION_BITS)
#define CLIPPER_Y_INT (clipper_y>>FRCTION_BITS)
#define CLIPPER_W_INT (clipper_w>>FRCTION_BITS)
#define CLIPPER_H_INT (clipper_h>>FRCTION_BITS)

const int w_max=IMAGE_AREA_W; // Max screen width 
const int h_max=IMAGE_AREA_H; // Max screen height
//const int w_max=LCD_DISPLAY_W; // Max screen width 
//const int h_max=LCD_DISPLAY_H; // Max screen height
const int clipper_w_max=CLIPPER_MAX_W; // Max clipper width 
const int clipper_h_max=CLIPPER_MAX_H; // Max clipper height

const int w_max_scl=IMAGE_AREA_W*CALC_SC; // Max screen width 
const int h_max_scl=IMAGE_AREA_H*CALC_SC; // Max screen height
//const int w_max_scl=LCD_DISPLAY_W*CALC_SC; // Max screen width 
//const int h_max_scl=LCD_DISPLAY_H*CALC_SC; // Max screen height
const int clipper_w_max_scl=CLIPPER_MAX_W*CALC_SC; // Max clipper width 
const int clipper_h_max_scl=CLIPPER_MAX_H*CALC_SC; // Max clipper height

static int direc=1;  // 0:stop, 1:right, 2:down, 3:left, 4:up, 5:zoom out, 6: zoom up

static int w1 = 720*CALC_SC; // frame width of scaler *CALC_SC
static int h1 = 480*CALC_SC; // frame height of scaler *CALC_SC
static int x1=0*CALC_SC ; // frame origin x *CALC_SC
static int y1=0*CALC_SC ; // frame origin y *CALC_SC

static int clipper_x=0*CALC_SC; // clipper offset x *CALC_SC
static int clipper_y=0*CALC_SC; // clipper offset y*CALC_SC
static int clipper_w=CLIPPER_MAX_W*CALC_SC; // clipper width *CALC_SC
static int clipper_h=CLIPPER_MAX_H*CALC_SC; // clipper height *CALC_SC

#define  MOVE_STEP (1*CALC_SC/1)
#define ZOOM_W_STEP (2*CALC_SC)
//#define CLIPPER_ZOOM_W_STEP 3
#define CLIPPER_ZOOM_WIDE_W_STEP (2*CALC_SC)

int ctrl_mode=0; // Control mode: 0: Move frame, 1: Pan image

extern int auto_timer;

static int pen_command=-1; 
static int move_offset_x;
static int move_offset_y;
// -1: no action 
//  0: grabbing center
//  1: grabbing left-upper coner
//  2: grabbing right-upper coner
//  3: grabbing left-lower coner
//  4: grabbing right-lower coner
//  5: grabbing Title bar

static int drag_strain=0;
static int sx,sy,sw,sh;

static int move_vel_x;
static int move_vel_y;
static int move_x;
static int move_y;

void pen_command_image(int x, int y);
int select_pen_command_image(int x, int y);
void bounce_image_reset();

void
pen_down(int pen_x, int pen_y){
  pen_command = select_pen_command_image(pen_x, pen_y);
  pen_is_moving = 0;
    bounce_image_reset();
//alt_printf("dn %x\n",pen_down);
//if(! pen_down) printf("dn %d %d %d %d\n",move_vel_x, move_vel_y, move_x>>8, move_y>>8);
}
void
pen_move(int pen_x, int pen_y){
  pen_command_image(pen_x, pen_y);
  if(pen_command==5)
    auto_timer = alt_ticks_per_second() * 1;
  else if (pen_command>=1)
    auto_timer = alt_ticks_per_second() * 2;
  else if (pen_command>=0){
    if (ctrl_mode)
      auto_timer = alt_ticks_per_second() * 1;
    else
      auto_timer = alt_ticks_per_second() * 10;
  }
//if(! pen_down) printf("mv %d %d %d %d\n",move_vel_x, move_vel_y, move_x>>8, move_y>>8);
}
void
pen_up(int pen_x, int pen_y){
  pen_command = -1;


 if (drag_strain){
   if (drag_strain &1 ) {
      move_vel_x = (sw - w1)>>2;
      move_vel_y = 0;
   }
   else {
     move_vel_x = 0;
     move_vel_y = (sh - h1)>>2;
   }
   drag_strain = 0;
   move_x = sx;
   move_y = sy;
   w1 = sw;
   h1 = sh;
   x1 = sx;
   y1 = sy;
   if(w1 >IMAGE_AREA_W *CALC_SC){
	   w1 = IMAGE_AREA_W *CALC_SC;
	   x1 = 0 *CALC_SC;
//	   printf("w1 out of range\n");
   }
   if((x1+w1) >IMAGE_AREA_W *CALC_SC){
	   x1 = IMAGE_AREA_W *CALC_SC - w1;
//	   printf("x1 + w1 out of range\n");
   }
   if(h1 >IMAGE_AREA_H *CALC_SC){
	   h1 = IMAGE_AREA_H *CALC_SC;
	   y1 = 0 *CALC_SC;
//	  printf("h1 out of range\n");
   }
   if((y1+h1) >IMAGE_AREA_H *CALC_SC){
	   y1 = IMAGE_AREA_H *CALC_SC - h1;
//	  printf("y1+h1 out of range\n");

   }
 }
  
//alt_printf("up %x\n",pen_down);
//if(! pen_down) printf("up %d %d %d %d\n",move_vel_x, move_vel_y, move_x>>8, move_y>>8);
}


/* ペンの操作で何を行うかの判定ルーチン */
int select_pen_command_image(int x, int y){

int index;

  // check if title ber selection
  if (title_bar_x<x && x<(title_bar_x+title_bar_w)  && 
       title_bar_y<y && y<(title_bar_y+title_bar_h)  ){ // inside of the tilte bar
    index = 5;
    move_offset_x = x-title_bar_x;
    move_offset_y = y-title_bar_y;
    return index;
  }


  int dist[5];
  int x2_ep,y2_ep; // right-lower corner axis
  int x1i=X1_INT;
  int y1i=Y1_INT;

  if (ctrl_mode==1){ // Pan mode
    move_offset_x = x;
    move_offset_y = y;
    index = 0;  // always return 0
    return index;
  }
  if (ctrl_mode==2){ // Patial Pan mode
    move_offset_x = x;
    move_offset_y = y;
    index = 0;  // always return 0
    return index;
  }

  if (x<4) x=4;
  if (y<4) y=4;
  if (x> w_max-4) x=w_max-4;
  if (y> h_max-4) y=h_max-4;

  x2_ep = x1i+W1_INT;
  y2_ep = y1i+H1_INT;

// dist[0]: distance from: center
// dist[1]: distance from: left-upper coner
// dist[2]: distance from: right-upper coner
// dist[3]: distance from: left-lower coner
// dist[4]: distance from: right-lower coner

  dist[1] = (x1i-x)*(x1i-x) + (y1i-y)*(y1i-y);
  dist[2] = (x2_ep-x)*(x2_ep-x) + (y1i-y)*(y1i-y);
  dist[3] = (x1i-x)*(x1i-x) + (y2_ep-y)*(y2_ep-y);
  dist[4] = (x2_ep-x)*(x2_ep-x) + (y2_ep-y)*(y2_ep-y);
//  dist[0] = ((x1+x2_ep)/2 -x)*((x1+x2_ep)/2 -x) + ((y1+y2_ep)/2 -y)*((y1+y2_ep)/2 -y);

// Search nearest point
int min;
int i;

  index=1;
  min=dist[index];
  for(i=2;i<5;i++){
    if (min>dist[i]){
      index = i;
      min=dist[index];
    }
  }

  /* この距離(x^2+y^2) より遠かったらリサイズしない */
  if (min>3000) index=-1; // Too far from the control point

  if (drag_strain) {
      index = 0;
      move_offset_x = x-x1i;
      move_offset_y = y-y1i;
  }
  else if (index==-1 || min > 1500){
   if (x1i<x && x<x2_ep && y1i<y && y<y2_ep){ // inside of the image
      index = 0;
      move_offset_x = x-x1i;
      move_offset_y = y-y1i;
    }
  }

  return index;

}

#define BUFF_NUM 4 
static int save_vx[BUFF_NUM];
static int save_vy[BUFF_NUM];



static void
save_and_update_motion_data(int x,int y){
  static int pre_x;
  static int pre_y;
  static int index=0;

  int vx,vy;


  move_x = x ;
  move_y = y ;

  vx = x - pre_x; // diff x
  vy = y - pre_y; // diff y


  save_vx[index]=vx;
  save_vy[index]=vy;
  index = (index+1)&(BUFF_NUM-1);
  pre_x = x;
  pre_y = y;

  move_vel_x = 0;
  move_vel_y = 0;
  int i;
  for (i=0;i<BUFF_NUM;i++){
    move_vel_x += save_vx[i];
    move_vel_y += save_vy[i];
  }

  move_vel_x >>= 2;
  move_vel_y >>= 2;


//printf("%d %d\n",vx, move_vel_x);
}

void
bounce_image_reset(void){
  int i;
  for (i=0;i<BUFF_NUM;i++){
    save_vx[i]=save_vy[i]=0;
  }
  move_x = x1;
  move_y = y1;
  move_vel_x = 0;
  move_vel_y = 0;
//printf("ini b\n");
}

// min: 400*240  due to lack bandwidth of sdram x16
#define W_MIN 400
#define H_MIN 240
void pen_command_image(int x, int y){

  int x2_ep,y2_ep; // right-lower corner axis

  if (x<4) x=4;
  if (y<4) y=4;
  if (x> w_max-4) x=w_max-4;
  if (y> h_max-4) y=h_max-4;


  x2_ep = X1_INT+W1_INT;
  y2_ep = Y1_INT+H1_INT;


        
  switch (pen_command){
  case 0: // change pos

    if (ctrl_mode==1){ // while pan/zoom
      clipper_x += (move_offset_x -x)*CALC_SC* clipper_w/w1;
      clipper_y += (move_offset_y - y)*CALC_SC* clipper_w/w1;
      move_offset_x = x;
      move_offset_y = y;

      if (clipper_x< 0) clipper_x = 0; 
      if (clipper_y< 0) clipper_y = 0; 
      if (clipper_x> (clipper_w_max_scl-clipper_w ) ) clipper_x = (clipper_w_max_scl-clipper_w ); 
      if (clipper_y> (clipper_h_max_scl-clipper_h ) ) clipper_y = (clipper_h_max_scl-clipper_h ); 
    }
    if (ctrl_mode==2){ // while patial pan/zoom
      int pre_clipper_x = clipper_x;
      int pre_clipper_y = clipper_y;
//      clipper_x += (x - move_offset_x )*CALC_SC* clipper_w/w1;
//      clipper_y += (y - move_offset_y )*CALC_SC* clipper_w/w1;
      clipper_x += (x - move_offset_x )*CALC_SC;
      clipper_y += (y - move_offset_y )*CALC_SC;

      x1 += (x-move_offset_x)*CALC_SC;
      y1 += (y-move_offset_y)*CALC_SC;


      if (clipper_x< 0) clipper_x = 0; 
      if (clipper_y< 0) clipper_y = 0; 
      if (clipper_x> (clipper_w_max_scl-clipper_w ) ) clipper_x = (clipper_w_max_scl-clipper_w ); 
      if (clipper_y> (clipper_h_max_scl-clipper_h ) ) clipper_y = (clipper_h_max_scl-clipper_h ); 

      move_offset_x += (clipper_x - pre_clipper_x)/CALC_SC;
      move_offset_y += (clipper_y - pre_clipper_y)/CALC_SC;

//      if ( x1<0 ) { x1 = 0; }
      if ( x1<(LCD_DISPLAY_W-CLIPPER_MAX_W)/2*CALC_SC ) 
        { x1 = (LCD_DISPLAY_W-CLIPPER_MAX_W)/2*CALC_SC; }
//      if ( x1+w1 > w_max_scl ){ x1 = w_max_scl  - w1 ; }
      if ( x1+w1 > (LCD_DISPLAY_W - (LCD_DISPLAY_W-CLIPPER_MAX_W)/2)*CALC_SC )
        { x1 = (LCD_DISPLAY_W - (LCD_DISPLAY_W-CLIPPER_MAX_W)/2)*CALC_SC  - w1 ; }
      if ( y1 <0 ) { y1 = 0; }
      if ( y1+h1 > h_max_scl ){ y1 = h_max_scl  - h1 ; }    
    
    }
    else {
    
      x1 = (x-move_offset_x)*CALC_SC;
      y1 = (y-move_offset_y)*CALC_SC;


      int delta;
      if (!drag_strain){
        if (x1< 4*CALC_SC) { 
          drag_strain = 1; sx=x1;sy=y1;sw=w1;sh=h1;delta = 4*CALC_SC-x1;  h1 += delta; w1 -=delta; y1 -= delta>>1 ;x1 = 4*CALC_SC; 
        }
        if (y1< 4*CALC_SC) {
          drag_strain = 2; sx=x1;sy=y1;sw=w1;sh=h1;delta = 4*CALC_SC-y1;  w1 += delta; h1 -=delta; x1 -= delta>>1 ;y1 = 4*CALC_SC; 
        }
        if (x1> (w_max-W1_INT -4)*CALC_SC ) {
          drag_strain = 3; sx=x1;sy=y1;sw=w1;sh=h1;delta = (w_max-W1_INT -4)*CALC_SC-x1;  h1 += delta; w1 -=delta; y1 -= delta>>1 ;
          x1 = (w_max-W1_INT -4)*CALC_SC; 
        }
        if (y1> (h_max-H1_INT )*CALC_SC ) {
          drag_strain = 4; sx=x1;sy=y1;sw=w1;sh=h1;delta = (h_max-H1_INT )*CALC_SC-y1;  w1 += delta; h1 -=delta; x1 -= delta>>1;
          y1 = (h_max-H1_INT )*CALC_SC; 
        }
      }
      else if (drag_strain==1) {
        if (x1>= 0*CALC_SC) { drag_strain = 0; x1=sx;y1=sy;w1=sw;h1=sh; }
        else { 
          delta = 0*CALC_SC-x1; 
          x1 = 0*CALC_SC;
          if ( (sw-delta >= W_MIN*CALC_SC)  ) {
            h1 = sh+delta; w1 = sw-delta; y1 = sy - (delta>>1) ;
          }
          else {
            h1 = sh+delta; /*w1 = sw-delta;*/ y1 = sy - (delta>>1) ;
          }
        }
      }
      else if (drag_strain==2) {
        if (y1>= 4*CALC_SC) {drag_strain = 0; x1=sx;y1=sy;w1=sw;h1=sh; }
        else {
          delta = 4*CALC_SC-y1; 
          y1 = 4*CALC_SC; 
          if ( (sh-delta >= H_MIN*CALC_SC)  ) {
            w1 = sw+delta; h1 = sh-delta; x1 = sx - (delta>>1) ;
          }
          else {
            w1 = sw+delta; /*h1 = sh-delta;*/ x1 = sx - (delta>>1) ;
          }
        }
      }
      else if (drag_strain==3) {
        if (x1 <= w_max_scl -sw ) {drag_strain = 0; x1=sx;y1=sy;w1=sw;h1=sh; }
        else {
          delta = x1 - (w_max_scl  - sw) ; 
          if ( (sw-delta >= W_MIN*CALC_SC)  ) {
            h1 = sh+delta; w1 = sw-delta; y1 = sy - (delta>>1) ;
          }
          else {
            h1 = sh+delta; /*w1 = sw-delta;*/ y1 = sy - (delta>>1) ;
          }
          x1 = w_max_scl  - w1; 
        }
      }
      else if (drag_strain==4) {
        if (y1 <= h_max_scl -sh ) {drag_strain = 0; x1=sx;y1=sy;w1=sw;h1=sh; }
        else {
          delta = y1 - (h_max_scl  - sh); 
          if ( (sh-delta >= H_MIN*CALC_SC)  ) {
            w1 = sw+delta; h1 = sh-delta; x1 = sx - (delta>>1) ;
          }
          else {
            w1 = sw+delta; /*h1 = sh-delta;*/ x1 = sx - (delta>>1) ;
          }
          y1 = h_max_scl  - h1; 
        }
      }


      if ( x1<0 ) {
        x1 = 0;
      }
      if ( x1+w1 > w_max_scl ){
         w1 = w_max_scl  - x1 -1;
      }

      if ( y1 <0 ) {
        y1 = 0;
      }
      if ( y1+h1 > h_max_scl ){
         h1 = h_max_scl  - y1 -1;
      }

      if (w1 < W_MIN*CALC_SC) {
        w1 = W_MIN*CALC_SC;
      }
      if (w1 >= w_max_scl ) {
        w1 = w_max_scl -1;
      }

      if (h1 < H_MIN*CALC_SC) {
        h1 = H_MIN*CALC_SC;
      }
      if (h1 >= h_max_scl ) {
        h1 = h_max_scl -1;
      }

    }

    
    break;
  case 1: // change size by left-upper coner
    x1 = x*CALC_SC;
    y1 = y*CALC_SC;
    w1 = (x2_ep-x)*CALC_SC;
    h1 = (y2_ep-y)*CALC_SC;
    if (W1_INT<W_MIN) {w1 = W_MIN*CALC_SC; x1=x2_ep*CALC_SC-w1;}
    if (H1_INT<H_MIN) {h1 = H_MIN*CALC_SC; y1=y2_ep*CALC_SC-h1;}
    break;
  case 2: // change size by right-upper coner
    y1 = y*CALC_SC;
    w1 = x*CALC_SC - x1;
    h1 = y2_ep*CALC_SC - y1;
    if (W1_INT<W_MIN) {w1 = W_MIN*CALC_SC; }
    if (H1_INT<H_MIN) {h1 = H_MIN*CALC_SC; y1=(y2_ep-H1_INT)*CALC_SC;}
    break;
  case 3: // change size by left-lower coner
    x1 = x*CALC_SC;
    w1 = (x2_ep-x)*CALC_SC;
    h1 = (y)*CALC_SC - y1;
    if (W1_INT<W_MIN) {w1 = W_MIN*CALC_SC; x1=(x2_ep-W1_INT)*CALC_SC;}
    if (H1_INT<H_MIN) {h1 = H_MIN*CALC_SC; }
    break;
  case 4: // change size by right-lower coner
    w1 = (x)*CALC_SC-x1;
    h1 = (y)*CALC_SC-y1;
    if (W1_INT<W_MIN) {w1 = W_MIN*CALC_SC; }
    if (H1_INT<H_MIN) {h1 = H_MIN*CALC_SC; }
    break;

  case 5: // Title bar change pos
    title_bar_x = x-move_offset_x;
    title_bar_y = y-move_offset_y;
    if (title_bar_x< 0) title_bar_x = 0; 
    if (title_bar_y< 0) title_bar_y = 0; 
    if (title_bar_x> (w_max-title_bar_w) ) title_bar_x = w_max-title_bar_w; 
    if (title_bar_y> (h_max-title_bar_h) ) title_bar_y = h_max-title_bar_h; 
    break;
  }

  if (pen_command==5){
      Mixer_set_layer_position(2, title_bar_x, title_bar_y);
  }
  else {
  }

  if (pen_command==0){
      if (ctrl_mode != 2)
        bg_col = (bg_col&0xfcffffff) | 0x01000000;

      save_and_update_motion_data(x1,y1);
  }
  else if (pen_command>=1 && pen_command<=4){
      bg_col = (bg_col&0xfcffffff) | 0x02000000;
      bounce_image_reset();
  }


    if (X1_INT<0 || Y1_INT<0 || (X1_INT+W1_INT)>LCD_DISPLAY_W || (Y1_INT+H1_INT)>LCD_DISPLAY_H)
      printf("p %4d, %4d, %4d, %4d\n", X1_INT, Y1_INT ,(X1_INT+W1_INT), (Y1_INT+H1_INT));


}



void bounce_image(void){
 if (ctrl_mode) return;
  move_x += move_vel_x ;
  move_y += move_vel_y ;

  move_vel_x = (move_vel_x * 253) >> 8;
  move_vel_y = (move_vel_y * 253) >> 8; 

    if (move_x< (4<<8)) {move_x = 4<<8; move_vel_x = (move_vel_x * -1)  ;} 
    if (move_y< (4<<8)) {move_y = 4<<8; move_vel_y = (move_vel_y * -1)  ;}

    if (move_x> ((w_max-W1_INT -4)<<8) ) {move_x = ((w_max-W1_INT -4)<<8); move_vel_x = (move_vel_x * -1) ;}
    if (move_y> ((h_max-H1_INT )<<8) ) {move_y = ((h_max-H1_INT )<<8);  move_vel_y = (move_vel_y * -1) ;}

  x1 = move_x ;
  y1 = move_y ;

    if (X1_INT<0 || Y1_INT<0 || (X1_INT+W1_INT)>LCD_DISPLAY_W || (Y1_INT+H1_INT)>LCD_DISPLAY_H){
      printf("b %4d, %4d, %4d, %4d\n", X1_INT, Y1_INT ,(X1_INT+W1_INT), (Y1_INT+H1_INT));
      if(x1<0) x1=0;
      if(y1<0) y1=0;
    }

//  Mixer_set_layer_position(FM, X1_INT, Y1_INT);
}


// VIP hardware access routine
void set_hw(void){

//    Clipper_set_xywh(CLIPPER_X_INT, CLIPPER_Y_INT, CLIPPER_W_INT, CLIPPER_H_INT); 
//    Scaler_set_output_size( W1_INT, H1_INT);
//    Mixer_set_layer_position(FM, X1_INT, Y1_INT);
//    IOWR(ALT_VIP_CUSTOM_TPG_0_BASE,0, bg_col);

    
//    Control_Synchronizer_set_number_of_writes(8);
    Control_Synchronizer_set_number_of_writes(8);
    Control_Synchronizer_setup_write(0, ALT_VIP_CLIP_0_BASE+3*4, CLIPPER_X_INT + 0);
    Control_Synchronizer_setup_write(1, ALT_VIP_CLIP_0_BASE+4*4, CLIPPER_W_INT);
    Control_Synchronizer_setup_write(2, ALT_VIP_CLIP_0_BASE+5*4, CLIPPER_Y_INT + 0);
    Control_Synchronizer_setup_write(3, ALT_VIP_CLIP_0_BASE+6*4, CLIPPER_H_INT);

    Control_Synchronizer_setup_write(4, ALT_VIP_SCL_0_BASE+3*4, W1_INT);
    Control_Synchronizer_setup_write(5, ALT_VIP_SCL_0_BASE+4*4, H1_INT);

    // layer 0
    Control_Synchronizer_setup_write(6, ALT_VIP_CL_MIXER_0_BASE+(8 + 5*0)*4, X1_INT+ IMAGE_AREA_MIXER_OFSET_X);
    Control_Synchronizer_setup_write(7, ALT_VIP_CL_MIXER_0_BASE+(9 + 5*0)*4, Y1_INT + IMAGE_AREA_MIXER_OFSET_Y);

    Control_Synchronizer_enable_trigger();
    //IOWR(ALT_VIP_CTS_0_BASE,3, 0);

}

#define Y_TOP ((1)*CALC_SC)
#define Y_GND ((IMAGE_AREA_H-0 -0)*CALC_SC)
//#define Y_GND ((LCD_DISPLAY_H-0 -0)*CALC_SC)
//#define GRAVITY 25 //1200
//#define STRAIN_ALPHA 35// 1600
#define GRAVITY (25*4) //1200
#define STRAIN_ALPHA (35*4)// 1600
#define DUMPER 1 // 6

static int gravity_vel=0;


void free_fall_image(void){
static int bounce_count=0;
int pre_vel;
static int strain_mode=0;
static int strain=0;
static int strain_vel=0;
static int x_save,y_save,h_save,w_save;

  if (!strain_mode){
    pre_vel = gravity_vel;
    gravity_vel += GRAVITY;
    gravity_vel -= (gravity_vel*DUMPER)>>9;

    if (pre_vel<0 && gravity_vel>=0 ) {
      bounce_count++;
      if (bounce_count>6){
        bounce_count=0;
        motion_count++;
        gravity_vel = 0;
      }
    }
    y1 += gravity_vel ;

    if ((y1+h1) > Y_GND) {
      y1 = Y_GND - h1 ;

// printf("   %4d\n", (Y1_INT+H1_INT));
      strain_mode=1;
      x_save=x1;
      y_save=y1;
      w_save=w1;
      h_save=h1;
      strain = 0;
      strain_vel = gravity_vel;

      gravity_vel *= -1;
    }

    if ( y1 <= Y_TOP){
      y1 = Y_TOP;
      gravity_vel = 0;
    }

//    Mixer_set_layer_position(FM, X1_INT, Y1_INT);

  }
  else { // strain mode
    strain_vel -= STRAIN_ALPHA; 
    strain += strain_vel;

    x1 = x_save - strain/2;
//    y1 = y_save + strain;
    w1 = w_save + strain;
    h1 = h_save - strain;
    if (h1<H_MIN*CALC_SC){
      h1 = H_MIN*CALC_SC;
    }

    y1 = Y_GND - H1_INT*CALC_SC ;

    if ( x1<0 ) {
      w1 -= x1;
      x1 = 0;
    }
    if ( x1+w1 > w_max_scl ){
       w1 = w_max_scl  - x1 -1;
    }




//     Mixer_stop(1);
//      Scaler_stop(1);
//      Scaler_start();
//      Mixer_start();

    
//     Mixer_stop(1);
//      Scaler_stop(1);
//    Scaler_set_output_size( W1_INT, H1_INT);
//    Mixer_set_layer_position(FM, X1_INT, Y1_INT);
//      Mixer_start();
//      Scaler_start();

    if (strain <= 0) {
      strain_mode = 0;
      x1 = x_save;
      y1 = y_save;
      w1 = w_save;
      h1 = h_save;
    }

// printf("   %4d\n", (Y1_INT+H1_INT));
  }


}


//print_debug(){
//  printf("x1 %d,%d\n",X1_INT,x1);
//}


void  
move_image(int xini, int yini, int wini, int hini, int direcini){


  if (xini*CALC_SC>0) x1 = xini*CALC_SC;
  if (yini*CALC_SC>0) y1 = yini*CALC_SC;
  if (wini>0) w1 = wini*CALC_SC;
  if (hini>0) h1 = hini*CALC_SC;
  if (direcini>=0) direc = direcini;
   
  if (x1> (w_max_scl -w1 ) ) x1 = (w_max_scl -w1 );
//  if (x1> (w_max_scl -w1 -1) ) x1 = (w_max_scl -w1 -1);
  if (y1> (h_max_scl -h1 ) ) y1 = (h_max_scl -h1 );

// bit31-28: select the frame pattern cycle
// bit26: frame on/off
// bit25-24: test pattern select: 00:bit11-0, 01:color_pat1, 10:color_pat2
// bit23-12: frame color
// bit11-0: bg color when bit25-24 is 00
#define SET_BG_COL { int xcol = 0x888|(rand()&0x333) ; xcol = (xcol<<12)|(rand()&0x777)|0x888 ; bg_col = ( xcol | 0x24000000 );}

  switch(direc) {
  case 1:
    // move right
    x1+=MOVE_STEP;
//    if (x1 < (w_max_scl -w1 -2)) {
    if (x1 < (w_max_scl -w1)) {
    }
    else {
//      x1 = (w_max_scl -w1 -1);
      x1 = (w_max_scl -w1 );
      SET_BG_COL;
      direc = 2;
    }
    break;

  case 2:
    y1+=MOVE_STEP;
    if (y1 < (h_max_scl-h1 )) {
    }
    else {
      y1 = (h_max_scl-h1 ) ;
      SET_BG_COL;
      direc = 3;
    }
    break;

  case 3:
    // move left
    x1-=MOVE_STEP;
    if ( x1> 0){
    }
    else {
      x1 = 0;
      SET_BG_COL;
      direc = 4;
    }
    break;

  case 4:
    // move up
    y1-=MOVE_STEP;
    if (y1> 0){
    }
    else {
      y1 = 0;
      SET_BG_COL;
      direc = 5;
    }
    break;

  case 5:
    // move horizontal center
    x1+=MOVE_STEP;
    if ( x1< (w_max_scl-w1 )/2 ) {
    }
    else {
      x1= (w_max_scl-w1 )/2;
      SET_BG_COL;
      direc = 1;
      motion_count++;
    }
    break;

  }

}
void
move_image_center(int xini, int yini, int wini, int hini, int direcini){

//static int direc=1;  // 0:stop, 1:right, 2:down, 3:left, 4:up, 5:zoom out, 6: zoom up

  if (xini>0) x1 = xini;
  if (yini>0) y1 = yini;
  if (wini>0) w1 = wini*CALC_SC;
  if (hini>0) h1 = hini*CALC_SC;
  if (direcini>=0) direc = direcini;

int center_x;
int center_y;

int step_x=0;
int step_y=0;

  center_x = (w_max_scl-w1)>>1;
  center_y = (h_max_scl-h1)>>1;

  if (x1 < center_x-MOVE_STEP) step_x=MOVE_STEP;
  else if (x1 > center_x+MOVE_STEP) step_x=-MOVE_STEP;

  if (y1 < center_y-MOVE_STEP) step_y=MOVE_STEP;
  else if (y1 > center_y+MOVE_STEP) step_y=-MOVE_STEP;
   

  if (step_x == 0 && step_y ==0){
    x1 = center_x;
    y1 = center_y;
    motion_count++;
  }
  else {
    x1+=step_x;
    y1+=step_y;
  }

}

void
move_image_top_center(int xini, int yini, int wini, int hini, int direcini){

//static int direc=1;  // 0:stop, 1:right, 2:down, 3:left, 4:up, 5:zoom out, 6: zoom up

  if (xini>0) x1 = xini;
  if (yini>0) y1 = yini;
  if (wini>0) w1 = wini*CALC_SC;
  if (hini>0) h1 = hini*CALC_SC;
  if (direcini>=0) direc = direcini;

int center_x;
int center_y;

int step_x=0;
int step_y=0;

  center_x = (w_max_scl-w1)>>1;
  center_y = 0;

  if (x1 < center_x-MOVE_STEP) step_x=MOVE_STEP;
  else if (x1 > center_x+MOVE_STEP) step_x=-MOVE_STEP;

  if (y1 < center_y-MOVE_STEP) step_y=MOVE_STEP;
  else if (y1 > center_y+MOVE_STEP) step_y=-MOVE_STEP;
   

  if (step_x == 0 && step_y ==0){
    x1 = center_x;
    y1 = center_y;
    motion_count++;
  }
  else {
    x1+=step_x;
    y1+=step_y;
  }

}



void 
zoom_image(int xini, int yini, int wini, int hini, int direcini){

//const int w_max=800;
//const int h_max=480-40;

static int direc=6;  // 0:stop, 1:right, 2:down, 3:left, 4:up, 5:zoom out, 6: zoom up
 
 int w_step = 4*CALC_SC /2;
 int h_step = 3*CALC_SC /2;

  if (xini>0) x1 = xini*CALC_SC;
  if (yini>0) y1 = yini*CALC_SC;
  if (wini>0) w1 = wini*CALC_SC;
  if (hini>0) h1 = hini*CALC_SC;
  if (direcini>=0) direc = direcini;

//  int wait = 100000;

  switch(direc) {
  case 5:
    // make smaller size 
    w1-=w_step, h1-=h_step;
    x1 = (w_max_scl - w1)/2;
    y1 = (h_max_scl - h1)/2;
    if (W1_INT<W_MIN || H1_INT<H_MIN) {
      direc = 6;
    }
    else {
    }
    break;

  case 6:
    // make lager size until either length get in limit
    w1+=w_step, h1+=h_step;
    x1 = (w_max_scl - w1)/2;
    y1 = (h_max_scl - h1)/2;

    if (W1_INT>=w_max ) {
      w1 = w_max_scl ;
      x1 = (w_max_scl - w1)/2;
      direc = 7;
    }
    else if (H1_INT>=h_max) {
      h1 = h_max_scl;
      y1 = (h_max_scl - h1)/2;
      direc = 8;
    }
    else {
    }
    break;

  case 7:
    // enlarge h size 
    h1+=h_step;
    y1 = (h_max_scl - h1)/2;
    if (H1_INT>=h_max) {
      h1 = h_max_scl;
      y1 = (h_max_scl - h1)/2;
      direc = 9;
    }
    else {
    }
    break;

  case 8:
    // enlarge w size 
    w1+=w_step;
    x1 = (w_max_scl - w1)/2;

   if (w1>h_max_scl*4/3)  {
        w1=h_max_scl*4/3;
        x1 = (w_max_scl - w1)/2;
        direc = 9;
    }
    else {
    }
    break;

  case 9:
    // make smaller and to be normal size
    if ( w1>h_max_scl*4/3) {
      w1-=w_step;
      x1 = (w_max_scl - w1)/2;
    }
    else {
      w1-=w_step, h1-=h_step;
      x1 = (w_max_scl - w1)/2;
      y1 = (h_max_scl - h1)/2;
    }

    if (W1_INT<= LIVE_IMAGE_W  || H1_INT<= LIVE_IMAGE_H) {
      direc = 10;
    }
    else {
    }
    break;

  case 10:
    // make smaller size 
    w1-=w_step, h1-=h_step;
    x1 = (w_max_scl - w1)/2;
    y1 = (h_max_scl - h1)/2;
    if (W1_INT<W_MIN || H1_INT<H_MIN) {
      direc = 11;
    }
    else {
    }
    break;


  case 11:
    // make lager size until either length get in limit
    w1+=w_step, h1+=h_step;
    x1 = (w_max_scl - w1)/2;
    y1 = (h_max_scl - h1)/2;

    if (W1_INT>= LIVE_IMAGE_W  || H1_INT>= LIVE_IMAGE_H) {
//      direc = 5;
      direc = 6;
      w1 = LIVE_IMAGE_W*CALC_SC;
      h1 = LIVE_IMAGE_H*CALC_SC;
      motion_count++;
    }
    else {
    }
    break;


  }

}




void pan_and_scroll_image(int xini, int yini, int wini, int hini, int direcini){

static int direc=1;  // 0:stop, 1:image area clip, 2: pan(move circle), 3: pan(move circle), 4: image size to default,
 
 int w_step = ZOOM_W_STEP;
// int h_step = ZOOM_H_STEP;

  if (xini>0) x1 = xini*CALC_SC;
  if (yini>0) y1 = yini*CALC_SC;
  if (wini>0) w1 = wini*CALC_SC;
  if (hini>0) h1 = hini*CALC_SC;
  if (direcini>=0) direc = direcini;

/*
#define CALC_SC (1<<FRCTION_BITS)
#define W1_INT (w1>>FRCTION_BITS)
#define H1_INT (h1>>FRCTION_BITS)
#define X1_INT (x1>>FRCTION_BITS)
#define Y1_INT (y1>>FRCTION_BITS)
#define CLIPPER_X_INT (clipper_x>>FRCTION_BITS)
#define CLIPPER_Y_INT (clipper_y>>FRCTION_BITS)
#define CLIPPER_W_INT (clipper_w>>FRCTION_BITS)
#define CLIPPER_H_INT (clipper_h>>FRCTION_BITS)
*/
double sin(double);
double cos(double);
double radians;
double x_delta = 0;
double y_delta = 0;
static unsigned int degrees = 0;

const unsigned int start_x = ((IMAGE_AREA_H*CLIPPER_MAX_W/CLIPPER_MAX_H)-PAN_CLIP_W)/2;
const unsigned int start_y = (IMAGE_AREA_H-PAN_CLIP_H)/2;

const int max_image_w = IMAGE_AREA_H*CLIPPER_MAX_W/CLIPPER_MAX_H;
const int max_image_h = IMAGE_AREA_H;


  switch(direc) {
  case 1: 
    // make full LIVE_IMAGE size
    w1+=w_step;  
    h1=w1*LIVE_IMAGE_H/LIVE_IMAGE_W;
    x1 = (w_max_scl - w1)/2;
    y1 = (h_max_scl - h1)/2;
    
//    clipper_w = w1 * CLIPPER_MAX_W * LIVE_IMAGE_H / LIVE_IMAGE_W / CLIPPER_MAX_H ;
//    clipper_h = clipper_w * CLIPPER_MAX_H / CLIPPER_MAX_W;
//    clipper_x = (clipper_w_max_scl -clipper_w)/2;
//    clipper_y = (clipper_h_max_scl -clipper_h)/2;
    if ( H1_INT >= IMAGE_AREA_H ) {
      h1 = IMAGE_AREA_H * CALC_SC;
      w1 = h1 * LIVE_IMAGE_W/LIVE_IMAGE_H;
      x1 = (w_max_scl - w1)/2;
      y1 = (h_max_scl - h1)/2;

      direc ++;
    }
    break;

  case 2:
    // make full input image size : Scaler should be 1:1 rate
    w1+=w_step;  
    x1 = (w_max_scl - w1)/2;
    if ( W1_INT >= CLIPPER_MAX_W ) {
//      h1 = IMAGE_AREA_H * CALC_SC;
      w1 = h1 * CLIPPER_MAX_W/CLIPPER_MAX_H;
      x1 = (w_max_scl - w1)/2;
//      y1 = (h_max_scl - h1)/2;
      direc ++;
    }
    break;

  case 3:
    w1-=w_step;  
    h1=w1*CLIPPER_MAX_H/CLIPPER_MAX_W;
    x1 = (max_image_w*CALC_SC - w1)/2;
    y1 = (max_image_h*CALC_SC - h1)/2;
    
//    clipper_w = w1 * CLIPPER_MAX_W * LIVE_IMAGE_H / LIVE_IMAGE_W / CLIPPER_MAX_H ;
    clipper_w = w1 * CLIPPER_MAX_W / max_image_w ;
//    clipper_h = clipper_w * CLIPPER_MAX_H / CLIPPER_MAX_W;
    clipper_h = h1  * CLIPPER_MAX_H / max_image_h;

//    clipper_x = (clipper_w_max_scl -clipper_w)/2;
//    clipper_y = (clipper_h_max_scl -clipper_h)/2;
    clipper_x = x1 * CLIPPER_MAX_W / max_image_w ;
    clipper_y = y1 * CLIPPER_MAX_H / max_image_h ;
//printf("%d %d, %d %d, %d %d, %d %d\n", W1_INT, H1_INT, X1_INT, Y1_INT, CLIPPER_W_INT, CLIPPER_H_INT, CLIPPER_X_INT, CLIPPER_Y_INT);
    x1 += (VGA_DISPLAY_W - (IMAGE_AREA_H*CLIPPER_MAX_W/CLIPPER_MAX_H))/2 * CALC_SC;
    if ( W1_INT < PAN_CLIP_W ) {
      direc ++;
      ctrl_mode=2;
    }
    break;

  case 4:
//    w1-=w_step;  
//    h1=w1*CLIPPER_MAX_H/CLIPPER_MAX_W;
//    x1 = (w_max_scl - w1)/2;
    y1 += MOVE_STEP;
    
//    clipper_w = w1 * CLIPPER_MAX_W * CLIPPER_MAX_H / CLIPPER_MAX_W / CLIPPER_MAX_H ;
//    clipper_h = clipper_w * CLIPPER_MAX_H / CLIPPER_MAX_W;
//    clipper_x = (clipper_w_max_scl -clipper_w)/2;
//    clipper_y =  y1 * CLIPPER_MAX_W * CLIPPER_MAX_H / CLIPPER_MAX_W / CLIPPER_MAX_H ;
//    clipper_y =  y1 ;
    clipper_y = y1 * CLIPPER_MAX_H / max_image_h ;
    if ( y1+h1 >= h_max_scl ) {
      y1 = h_max_scl-h1 ;
      clipper_y = y1 * CLIPPER_MAX_H / max_image_h ;
      direc ++;
    }
    break;

  case 5:


    radians = (double) 2 * 3.14159 * degrees/360/2;
    x_delta = -1 * sin(radians) * start_x;
    y_delta =      cos(radians) * start_y;

    x1 = (start_x + x_delta) * CALC_SC;
    y1 = (start_y + y_delta) * CALC_SC;

//    clipper_x = x1 * CLIPPER_MAX_W * CLIPPER_MAX_H / CLIPPER_MAX_W / CLIPPER_MAX_H ;
//    clipper_y = y1 * CLIPPER_MAX_W * CLIPPER_MAX_H / CLIPPER_MAX_W / CLIPPER_MAX_H ;
//    clipper_x = x1  * CLIPPER_MAX_W * CLIPPER_MAX_H / IMAGE_AREA_H / CLIPPER_MAX_W ;
//    clipper_y = y1 * 1 ;
    clipper_x = x1 * CLIPPER_MAX_W / max_image_w ;
    clipper_y = y1 * CLIPPER_MAX_H / max_image_h ;

//    clipper_x = x1 ;
//    clipper_y = y1 ;

    x1 += (VGA_DISPLAY_W - (IMAGE_AREA_H*CLIPPER_MAX_W/CLIPPER_MAX_H))/2 * CALC_SC;

    degrees ++;

    if (degrees == 360*2) {
      direc ++;
      degrees = 0;
    }

    break;

  case 6:
//    w1-=w_step;  
//    h1=w1*CLIPPER_MAX_H/CLIPPER_MAX_W;
//    x1 = (w_max_scl - w1)/2;
    y1 -= MOVE_STEP;
    
//    clipper_w = w1 * CLIPPER_MAX_W * CLIPPER_MAX_H / CLIPPER_MAX_W / CLIPPER_MAX_H ;
//    clipper_h = clipper_w * CLIPPER_MAX_H / CLIPPER_MAX_W;
//    clipper_x = (clipper_w_max_scl -clipper_w)/2;
//    clipper_y =  y1 * CLIPPER_MAX_W * CLIPPER_MAX_H / CLIPPER_MAX_W / CLIPPER_MAX_H ;
//    clipper_y =  y1 ;
    clipper_y = y1 * CLIPPER_MAX_H / max_image_h ;
    if ( y1 <= (h_max_scl - h1)/2 ) {
      y1 = (h_max_scl - h1)/2 ;
      clipper_y = y1 * CLIPPER_MAX_H / max_image_h ;
      direc ++;
      ctrl_mode=0;
    }
    break;

  case 7:
    w1+=w_step;  
    h1=w1*CLIPPER_MAX_H/CLIPPER_MAX_W;
    x1 = (max_image_w*CALC_SC - w1)/2;
    y1 = (max_image_h*CALC_SC - h1)/2;
    
//    clipper_w = w1 * CLIPPER_MAX_W * CLIPPER_MAX_H / IMAGE_AREA_H / CLIPPER_MAX_W ;
//    clipper_h = clipper_w * CLIPPER_MAX_H / CLIPPER_MAX_W;  
    clipper_w = w1 * CLIPPER_MAX_W / max_image_w ;
    clipper_h = h1 * CLIPPER_MAX_H / max_image_h;  
//    clipper_x = (clipper_w_max_scl -clipper_w)/2;
//    clipper_y = (clipper_h_max_scl -clipper_h)/2;
    clipper_x = x1 * CLIPPER_MAX_W / max_image_w ;
    clipper_y = y1 * CLIPPER_MAX_H / max_image_h ;
    x1 += (VGA_DISPLAY_W - (IMAGE_AREA_H*CLIPPER_MAX_W/CLIPPER_MAX_H))/2 * CALC_SC;
    if ( W1_INT >= (IMAGE_AREA_H*CLIPPER_MAX_W/CLIPPER_MAX_H) ) {
      w1 = max_image_w*CALC_SC;
      h1 = max_image_h*CALC_SC;
      clipper_w = clipper_w_max_scl ;
      clipper_h = clipper_h_max_scl;
      clipper_x = 0;
      clipper_y = 0;
      direc ++;
    }
    break;

  case 8:
    // make normal aspect
    w1-=w_step;  // h1=w1*CLIPPER_MAX_H/CLIPPER_MAX_W;
    x1 = (w_max_scl  - w1)/2;
//    y1 = (h_max_scl  - h1)/2;
    if (w1<= h1 * LIVE_IMAGE_W / LIVE_IMAGE_H) {
      w1 = h1 * LIVE_IMAGE_W / LIVE_IMAGE_H;
//      h1 = LIVE_IMAGE_H*CALC_SC;
      x1 = (w_max_scl  - w1)/2;
//      y1 = (h_max_scl  - h1)/2;
      direc ++;
    }
    break;

  case 9:
    // make normal size
    w1-=w_step; h1=w1*LIVE_IMAGE_H/LIVE_IMAGE_W;
    x1 = (w_max_scl  - w1)/2;
    y1 = (h_max_scl  - h1)/2;
    if (w1< LIVE_IMAGE_W*CALC_SC  || h1< LIVE_IMAGE_H*CALC_SC) {
      w1 = LIVE_IMAGE_W*CALC_SC;
      h1 = LIVE_IMAGE_H*CALC_SC;
      x1 = (w_max_scl  - w1)/2;
      y1 = (h_max_scl  - h1)/2;
      direc = 1;
      motion_count++;
//printf("direc %d\n",direc);
    }
    break;

  }

}




void 
zoom_and_scroll_image(int xini, int yini, int wini, int hini, int direcini){

static int direc=1;  // 0:stop, 1:right, 2:down, 3:left, 4:up, 5:reduce size, 6: enlarge size , 7: reduce to default,
 
 int w_step = ZOOM_W_STEP;
// int h_step = ZOOM_H_STEP;

  if (xini>0) x1 = xini*CALC_SC;
  if (yini>0) y1 = yini*CALC_SC;
  if (wini>0) w1 = wini*CALC_SC;
  if (hini>0) h1 = hini*CALC_SC;
  if (direcini>=0) direc = direcini;

  switch(direc) {
  case 1:
    // make smaller frame size 
      w1-=w_step; h1=w1*LIVE_IMAGE_H/LIVE_IMAGE_W;
      x1 = (w_max_scl - w1)/2;
      y1 = (h_max_scl - h1)/2;
    if (W1_INT<W_MIN || H1_INT<H_MIN) {
      direc = 2;
//printf("direc %d\n",direc);
    }
    break;

  case 2:
    // make lager frame size
      w1+=w_step; h1=w1*LIVE_IMAGE_H/LIVE_IMAGE_W;
      x1 = (w_max_scl - w1)/2;
      y1 = (h_max_scl - h1)/2;
    if (w1>=w_max_scl || h1>=h_max_scl) {
      direc = 3;
      w1=h_max_scl*LIVE_IMAGE_W/LIVE_IMAGE_H;h1=h_max_scl;
      x1 = (w_max_scl - w1)/2;
      y1 = (h_max_scl - h1)/2;
//printf("C_X,Y,W,H:%d,%d, %d,%d\n",CLIPPER_X_INT, CLIPPER_Y_INT, CLIPPER_W_INT,CLIPPER_H_INT);
//printf("2 direc %d\n",direc);
    }
    break;

  case 3:
    // make far lager size and clip
      w1+=w_step; 
//      h1=w1*3/4;
      x1 = (w_max_scl - w1)/2;
//      y1 = (h_max - h1)/2;
    if (w1<(w_max_scl-0*CALC_SC) ) {
//      h1=h_max;
//      y1 = (h_max - h1)/2;
//      clipper_h = clipper_h_max *h1*4/w1/3;
      clipper_h = (clipper_w_max *h1/LIVE_IMAGE_H*LIVE_IMAGE_W/CLIPPER_MAX_W*CLIPPER_MAX_H/w1) * CALC_SC;
      clipper_y = (clipper_h_max_scl - clipper_h)/2;    

    }
    else /* (w1>=w_max)*/ {
      w1=w_max_scl;
      x1 = (w_max_scl - w1)/2;

//      h1=h_max;
//      y1 = (h_max - h1)/2;
//      clipper_h = clipper_h_max *h1*4/w1/3;
      clipper_h = (clipper_w_max *h1/LIVE_IMAGE_H*LIVE_IMAGE_W/CLIPPER_MAX_W*CLIPPER_MAX_H/w1) * CALC_SC;
      clipper_y = (clipper_h_max_scl - clipper_h)/2;    

//printf("C_X,Y,W,H:%d,%d, %d,%d\n",CLIPPER_X_INT, CLIPPER_Y_INT, CLIPPER_W_INT,CLIPPER_H_INT);
//printf("x1,y1,w1,h1:%d,%d, %d,%d,tw %d, th %d\n",X1_INT, Y1_INT, W1_INT,H1_INT,X1_INT+W1_INT,Y1_INT+H1_INT);
      direc = 4;
ctrl_mode=1;
//printf("ctrl_mode %d\n",ctrl_mode );
//printf("3 direc %d\n",direc);
    }
    break;

  case 4:
    // zoom in 
    // make smaller clipper size : zoom in 
      clipper_w-=CLIPPER_ZOOM_WIDE_W_STEP;
//      clipper_h=clipper_w*384/800;
      clipper_h=clipper_w*IMAGE_AREA_H/LIVE_IMAGE_H*LIVE_IMAGE_W/CLIPPER_MAX_W*CLIPPER_MAX_H/IMAGE_AREA_W;
//      clipper_h=clipper_w*LCD_DISPLAY_H*8/LCD_DISPLAY_W/9;
      clipper_x = (clipper_w_max_scl - clipper_w)/2;
      clipper_y = (clipper_h_max_scl - clipper_h)/2;
    if (clipper_w<700*CALC_SC ) {
      direc = 5;
//printf("4 direc %d\n",direc);
    }
    break;

  case 5:
    // scrolling right
    clipper_x+=MOVE_STEP;
    // move right
    if (clipper_x > (clipper_w_max_scl -clipper_w )) {
      clipper_x = clipper_w_max_scl -clipper_w;
      direc = 6;
//printf("5 direc %d\n",direc);
    }
    break;


  case 6:
    // scrolling down
    clipper_y+=MOVE_STEP;
    if (clipper_y > (clipper_h_max_scl -clipper_h )) {
      clipper_y = clipper_h_max_scl -clipper_h;
      direc = 7;
//printf("6 direc %d\n",direc);
    }
    break;

  case 7:
    // scrolling left
    clipper_x-=MOVE_STEP;
    if (clipper_x< 0) {
      clipper_x = 0;
      direc = 8;
//printf("7 direc %d\n",direc);
    }
    break;

  case 8:
    // scrolling up
    clipper_y-=MOVE_STEP;
    if (clipper_y< 0) {
      clipper_y = 0;
      direc = 9;
//printf("8 direc %d\n",direc);
    }
    break;


  case 9:
    // scrolling right & center
    clipper_x+=MOVE_STEP;
    // move right
    if (clipper_x > (clipper_w_max_scl -clipper_w )/2) {
      clipper_x = (clipper_w_max_scl -clipper_w)/2;
      direc = 10;
//printf("9 direc %d\n",direc);
    }
    break;

  case 10:
    // scrolling down & center
    clipper_y+=MOVE_STEP;
    // move right
    if (clipper_y > (clipper_h_max_scl -clipper_h )/2) {
      clipper_y = (clipper_h_max_scl -clipper_h)/2;
      direc = 11;
//printf("10 direc %d\n",direc);
    }
    break;


  case 11:
    // zoom out
    clipper_w+=CLIPPER_ZOOM_WIDE_W_STEP;
//    clipper_h=clipper_w*384/800;
    clipper_h=clipper_w*IMAGE_AREA_H/LIVE_IMAGE_H*LIVE_IMAGE_W/CLIPPER_MAX_W*CLIPPER_MAX_H/IMAGE_AREA_W;
//    clipper_h=clipper_w*LCD_DISPLAY_H*8/LCD_DISPLAY_W/9;
    clipper_x = (clipper_w_max_scl  - clipper_w)/2;
    clipper_y = (clipper_h_max_scl  - clipper_h)/2;
    // move right
//printf("direc %d, %d,%d\n",direc,clipper_w,clipper_h );
    if (clipper_w > clipper_w_max_scl ) {

      clipper_w=clipper_w_max_scl ;
      clipper_h = (clipper_w_max  *h1/LIVE_IMAGE_H*LIVE_IMAGE_W/CLIPPER_MAX_W*CLIPPER_MAX_H/w1)*CALC_SC;

      clipper_x = (clipper_w_max_scl  - clipper_w)/2;
      clipper_y = (clipper_h_max_scl  - clipper_h)/2;

ctrl_mode=0;
//printf("ctrl_mode %d\n",ctrl_mode );
      direc = 12;
//printf("direc %d, %d,%d\n",direc,clipper_w,clipper_h );
    }
    break;




  case 12:
//usleep(10000000);
    // make far small size and clip
      w1-=w_step;
//      h1-=h_step;
      x1 = (w_max_scl  - w1)/2;
//      y1 = (h_max_scl  - h1)/2;
    if (w1>(h_max_scl *LIVE_IMAGE_W/LIVE_IMAGE_H)) {
      clipper_h = (clipper_w_max *h1/LIVE_IMAGE_H*LIVE_IMAGE_W/CLIPPER_MAX_W*CLIPPER_MAX_H/w1) *CALC_SC;
      clipper_y = (clipper_h_max_scl  - clipper_h)/2;    
    }
    if (w1<=(h_max_scl *LIVE_IMAGE_W/LIVE_IMAGE_H)) {
      w1=(h_max_scl *LIVE_IMAGE_W/LIVE_IMAGE_H);
      h1=h_max_scl ;
      x1 = (w_max_scl  - w1)/2;
      y1 = (h_max_scl  - h1)/2;

      clipper_w = clipper_w_max_scl ;
      clipper_h = clipper_h_max_scl ;
      clipper_x = (clipper_w_max_scl  - clipper_w)/2;
      clipper_y = (clipper_h_max_scl  - clipper_h)/2;    

      direc = 13;
//printf("direc %d\n",direc);
    }
    break;


  case 13:
    // make normal size
      w1-=w_step; h1=w1*LIVE_IMAGE_H/LIVE_IMAGE_W;
      x1 = (w_max_scl  - w1)/2;
      y1 = (h_max_scl  - h1)/2;
    if (w1< LIVE_IMAGE_W*CALC_SC  || h1< LIVE_IMAGE_H*CALC_SC) {
      direc = 1;
      w1 = LIVE_IMAGE_W*CALC_SC;
      h1 = LIVE_IMAGE_H*CALC_SC;
      x1 = (w_max_scl  - w1)/2;
      y1 = (h_max_scl  - h1)/2;
      motion_count++;
//printf("direc %d\n",direc);
    }
    break;


  }

}

