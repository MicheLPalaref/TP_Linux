#ifndef __MY_GRAPHICS_H__
#define __MY_GRAPHICS_H__

// JCJB:  Adding inclusion of the graphics driver header
#include "alt_video_display.h"
#include "fonts.h"  // modify this file to add/remove fonts

int my_vid_print_string_fast(int horiz_offset, int vert_offset, int color, int background_color, struct abc_font_struct font[], alt_video_display * display, char string[]);

int my_vid_print_string_alpha(int horiz_offset, int vert_offset, int color, int background_color, struct abc_font_struct font[], alt_video_display * display, char string[]);

#endif // __MY_GRAPHICS_H__
