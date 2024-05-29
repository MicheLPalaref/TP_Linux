#include "io.h"
#include "simple_graphics.h"



// ALT_VIDEO_DISPLAY_COLOR_DEPTH must be 32
// faster version


int my_vid_print_char (int horiz_offset, int vert_offset, int color, char character, int background_color, struct abc_font_struct font[], alt_video_display * display)
{

  int i, j;
  unsigned char * alpha;
  int new_color;

  // Assign the pointer of the font bitmap
  alpha = font[character-33].char_alpha_map;


  for(i = 0; i < font[character-33].bounds_height; i++) {
    for (j = 0; j < font[character-33].bounds_width; j++) {

      if ( (*alpha) &0x80)
        new_color = color;     
      else
        new_color = background_color;

      vid_set_pixel((horiz_offset + j), (vert_offset + i), new_color, display);     

      alpha++;
    }
  }

  return(0);
}


int my_vid_print_string_fast(int horiz_offset, int vert_offset, int color, int background_color, struct abc_font_struct font[], alt_video_display * display, char string[])
{
  int i = 0;
  int tab;
  int original_horiz_offset;

  original_horiz_offset = horiz_offset;

  // Print until we hit the '\0' char.
  while (string[i]) {
    //Handle newline char here.
    if (string[i] == '\n') {
      horiz_offset = original_horiz_offset;
      vert_offset += font['|' - 33].bounds_height;  // we'll use "|" to add the line to line spacing
      i++;
      continue;
    }
    // Lay down that character and increment our offsets.
    if(string[i] == 32)  // this is a space in ASCII
    {
      if(background_color != CLEAR_BACKGROUND)  // need to fill in this spot (setting foreground to background color so that it looks like a drawn in box)
      {
        my_vid_print_char (horiz_offset, vert_offset, background_color, '-', background_color, font, display);
      }
      horiz_offset += font[45 - 33].bounds_width;  // using the width of the '-' character for the space width since it's not present in the font
    }
    else if(string[i] == '\t')  // this is a tab
    {
      for( tab = 0; tab < TAB_SPACING; tab++ )
      {
        if(background_color != CLEAR_BACKGROUND)  // need to fill in this spot (setting foreground to background color so that it looks like a drawn in box)
        {
          my_vid_print_char (horiz_offset, vert_offset, background_color, '-', background_color, font, display);
        }
        horiz_offset += font[45 - 33].bounds_width;  // using the width of the '-' character for the space width since it's not present in the font
      }
    }
    else
    {
      my_vid_print_char (horiz_offset, vert_offset, color, string[i], background_color, font, display);
      horiz_offset += font[string[i] - 33].bounds_width;
    }
    i++;
  }
  return (0);
}



int my_alpha_blending (int horiz_offset, int vert_offset, int background_color, unsigned char alpha, unsigned char *red, unsigned char *green, unsigned char *blue, alt_video_display * display)
{
  int return_value;
  unsigned char background_red, background_green, background_blue;
//  unsigned int blended_red, blended_green, blended_blue;  // short since there may be overflow to be clipped
  


  
  background_red = (background_color>>16) & 0xff;
  background_green = (background_color>>8) & 0xff;
  background_blue = (background_color) & 0xff;

  *red = (((*red) * alpha) + (background_red * (255 - alpha)))>>8;
  *green = (((*green) * alpha) + (background_green * (255 - alpha)))>>8;
  *blue = (((*blue) * alpha) + (background_blue * (255 - alpha)))>>8;

    return_value = 1;            
  
/*
  if(display->color_depth == 16)
  {
    *red = (blended_red > 0x1F)? 0x1F: blended_red;
    *green = (blended_green > 0x3F)? 0x3F: blended_green;
    *blue = (blended_blue > 0x1F)? 0x1F: blended_blue; 
    return_value = 1;        
  }
  else if((display->color_depth == 24) || (display->color_depth == 32))
  {
    *red = (blended_red > 0xFF)? 0xFF: blended_red;
    *green = (blended_green > 0xFF)? 0xFF: blended_green;
    *blue = (blended_blue > 0xFF)? 0xFF: blended_blue; 
    return_value = 1;            
  }
  else
  {
    *red = (blended_red > 0xFF)? 0xFF: blended_red;
    return_value = 1;     
  }  
*/ 
  return return_value;
} 



int my_vid_print_char_alpha (int horiz_offset, int vert_offset, int color, char character, int background_color, struct abc_font_struct font[], alt_video_display * display)
{

  int i, j;
  unsigned char * alpha;
  unsigned char original_red, original_blue, original_green;
  unsigned char red, green, blue;
  int new_color;

  // Assign the pointer of the font bitmap
  alpha = font[character-33].char_alpha_map;

  // set red, green, and blue of the font color  
  seperate_color_channels(display->color_depth, (char *)&color, &original_red, &original_green, &original_blue);

  for(i = 0; i < font[character-33].bounds_height; i++) {
    for (j = 0; j < font[character-33].bounds_width; j++) {

 if ( (*alpha) > 0xf0) {
    new_color = color;
 }
 else if ((*alpha) < 0x0f) {
// else if (1) {
    new_color = background_color;
 }
 else {
      red = original_red;
      green = original_green;
      blue = original_blue;
      // send in the font alpha channel and the colour channels for the blending to occur
      my_alpha_blending ((horiz_offset + j), (vert_offset + i), background_color, *alpha, &red, &green, &blue, display);

      // take the blended pixel and merge the color channels back into a single pixel value 
      merge_color_channels(display->color_depth, red, green, blue, (char *)&new_color);
//     new_color = (red<<16) | (green<<8) | blue;

      
 }
      // write the new pixel value out to memory overwriting the current background     
      vid_set_pixel((horiz_offset + j), (vert_offset + i), new_color, display);     

      alpha++;
    }
  }

  return(0);
}

int my_vid_print_string_alpha(int horiz_offset, int vert_offset, int color, int background_color, struct abc_font_struct font[], alt_video_display * display, char string[])
{
  int i = 0;
  int tab;
  int original_horiz_offset;

  original_horiz_offset = horiz_offset;

  // Print until we hit the '\0' char.
  while (string[i]) {
    //Handle newline char here.
    if (string[i] == '\n') {
      horiz_offset = original_horiz_offset;
      vert_offset += font['|' - 33].bounds_height;  // we'll use "|" to add the line to line spacing
      i++;
      continue;
    }
    // Lay down that character and increment our offsets.
    if(string[i] == 32)  // this is a space in ASCII
    {
      if(background_color != CLEAR_BACKGROUND)  // need to fill in this spot (setting foreground to background color so that it looks like a drawn in box)
      {
        my_vid_print_char_alpha (horiz_offset, vert_offset, background_color, '-', background_color, font, display);
      }
      horiz_offset += font[45 - 33].bounds_width;  // using the width of the '-' character for the space width since it's not present in the font
    }
    else if(string[i] == '\t')  // this is a tab
    {
      for( tab = 0; tab < TAB_SPACING; tab++ )
      {
        if(background_color != CLEAR_BACKGROUND)  // need to fill in this spot (setting foreground to background color so that it looks like a drawn in box)
        {
          my_vid_print_char_alpha (horiz_offset, vert_offset, background_color, '-', background_color, font, display);
        }
        horiz_offset += font[45 - 33].bounds_width;  // using the width of the '-' character for the space width since it's not present in the font
      }
    }
    else
    {
      my_vid_print_char_alpha (horiz_offset, vert_offset, color, string[i], background_color, font, display);
      horiz_offset += font[string[i] - 33].bounds_width;
    }
    i++;
  }
  return (0);
}



