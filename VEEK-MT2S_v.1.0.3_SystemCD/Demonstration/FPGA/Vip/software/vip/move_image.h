// move_image.h
// fuction decralations

#ifndef MOVE_IMAGE_H_
#define MOVE_IMAGE_H_

#define LCD_DISPLAY_W 800
#define LCD_DISPLAY_H 480
#define VGA_DISPLAY_W 800
#define VGA_DISPLAY_H 480

#define CLIPPER_MAX_W 720
#define CLIPPER_MAX_H 480

#define GRAPH_BG_COL 0x302080
#define ALTERA_COLOR1 DEEPSKYBLUE_24
#define ALTERA_COLOR2 BLUE_24

//#define LIVE_IMAGE_W (640*3/4)
//#define LIVE_IMAGE_H (480*3/4)
#define LIVE_IMAGE_W (640*8/10)
//#define LIVE_IMAGE_W (720*7/10)
#define LIVE_IMAGE_H (480*8/10)

//#define PAN_CLIP_W (640*5/10)
//#define PAN_CLIP_H (480*5/10)
//#define PAN_CLIP_W (440*640/480*5/10)

#define PAN_CLIP_W 500
#define PAN_CLIP_H 420


#define FRAME_BUF_W (800) // Width of Nios II Graphic Frame
#define FRAME_BUF_H (40)  // Height of Nios II Graphic Frame

#define IMAGE_AREA_W (LCD_DISPLAY_W)
#define IMAGE_AREA_H (LCD_DISPLAY_H)
#define IMAGE_AREA_MIXER_OFSET_X ((VGA_DISPLAY_W - IMAGE_AREA_W)/2 )
#define IMAGE_AREA_MIXER_OFSET_Y ((VGA_DISPLAY_H - IMAGE_AREA_H)/2 )

void set_hw(void);

void free_fall_image(void);

void move_image_top_center(int xini, int yini, int wini, int hini, int direcini);

void  zoom_and_scroll_image(int xini, int yini, int wini, int hini, int direcini);
void move_image_center(int xini, int yini, int wini, int hini, int direcini);

void bounce_image_reset(void);

void bounce_image(void);









#endif /*MOVE_IMAGE_H_*/
