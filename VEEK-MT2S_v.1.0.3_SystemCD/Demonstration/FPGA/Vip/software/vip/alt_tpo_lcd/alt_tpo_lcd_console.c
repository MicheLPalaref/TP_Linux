/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2007 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
*                                                                             *
******************************************************************************/

/*
 * The folllowing code is for Altera internal use only. If 
 * we decide to ship this code as part of a software example,
 * several fixes and cleanups are necessary. As it is, it is 
 * a useful tool for debugging and configuring the TPO LCD
 * configuraion register contents
 */

#include <string.h>
#include <stdio.h>
#include "alt_tpo_lcd.h"

/* Serial input buffer size. We don't need much room. */
#define LINE_BUFFER_LENGTH 64

/*
 * alt_tpo_lcd_console_do_help
 * 
 * Display help menu for the TPO LCD register monitor
 */
void alt_tpo_lcd_console_do_help()
{
  printf ("\n");
  printf ("# +-------------------------- HELP --------------------------\n");
  printf ("# | The following commands are available:\n");
  printf ("# |   r <addr>           -- Read register at address.\n");
  printf ("# |   w <addr> <data>    -- Write register at address with data\n");
  printf ("# |   h                  -- Show this help.\n");
  printf ("# |   q                  -- Quit monitor.\n");
  printf ("# |\n");
  printf ("# | Enter addresses and data in hex. Be sure to omit '0x'!\n");
  printf ("# +----------------------------------------------------------\n");
}

/*
 * alt_tpo_lcd_console_get_hex_number_from_buffer_and_eat
 * 
 * Attempt to extract a hex number (Note: leading "0x" not supported)
 * from buffer at **sp. 0-9 and a-f are extracted. Largest number is
 * what will fit in an int (32-bits on Nios II); the routine will attempt
 * to continuously parse data in the buffe until a space, null, or
 * \r or \n is encontered.
 * 
 * This routine *will* modify the original buffer such that subsequent 
 * calls look at new data (hence "and_eat").
 * 
 * Returns: integer containing hex data from buffer or "-1" if a parse error
 * occured. I suppose that means "ffffffff" isn't valid input from the stream
 */
int alt_tpo_lcd_console_get_hex_number_from_buffer_and_eat(char **sp)
{
  char *s = *sp;
  int result = 0x0;
  
  /* Nios II IDE habitually sends \r\n pairs. Best to handle them both */  
  while( (*s != ' ' ) && (*s != 0) && (*s != '\r') && (*s != '\n') ) {    
    if(*s >= '0' && *s <= '9') {
      *s -= '0';
    }
    else if(*s >= 'a' && *s <= 'f') {
      *s -= 'a';
      *s += 10;    
    }
    else{
      printf(" --> Error: What you typed doesn't look like '0-9' or 'a-f' \n");
      return -1;
    }
    
    /* Shift, mask, and 'OR' to capture nibble */
    result = result << 4;
    *s &= 0x0F;
    result |= *s;
    
    /* Goto next char & "eat" input buffer */
    s++;
    *sp = (*sp + 1);
  }
  
  return result;
}  

/*
 * alt_tpo_lcd_console_do_command
 * 
 */
int alt_tpo_lcd_console_do_command(char *command, alt_tpo_lcd *lcd)
{
  int result = 0;
  char command_letter;
  unsigned char addr, data, readback_data;

  /* No command letter? Do nothing! */
  if(*command == 0) 
    return 0;
  
  command_letter = command[0];
  if(command_letter >= 'A' && command_letter <= 'Z')
    command_letter += 'a' - 'A';
  
  /* Dont pass the command letter on. */
  command++;

  switch(command_letter)
  {
    case 'r':
    {
      command++; // dont pass space after command letter on
      result = alt_tpo_lcd_console_get_hex_number_from_buffer_and_eat(&command);
      if(result != -1) {
        addr = (unsigned char)(result);
        data = alt_tpo_lcd_read_config_register(lcd, addr);
        printf(" READ COMMAND: Address: 0x%x. Read data: 0x%x\n", addr, data);
      }
      else {
        printf(" READ COMMAND: Error extracting address\n");
        return -1;
      }
      break;
    }
    case 'w':
    {
      command++;
      result = alt_tpo_lcd_console_get_hex_number_from_buffer_and_eat(&command);
      if(result != -1) {
        addr = (unsigned char)(result);
      }
      else {
        printf(" WRITE COMMAND: Error extracting address\n");
      }
      
      command++;
      result = alt_tpo_lcd_console_get_hex_number_from_buffer_and_eat(&command);
      if(result != -1) {
        data = (unsigned char)(result);
      }
      else {
        printf(" WRITE COMMAND: Error extracting data\n");
      }
      
      printf(" WRITE COMMAND: Address: 0x%x, Write data: 0x%x\n",
        addr, data);
      printf(" --> Writing...");
      alt_tpo_lcd_write_config_register(lcd, addr, data);

      /* Read back to verify */
      readback_data = alt_tpo_lcd_read_config_register(lcd, addr);
      if(data == readback_data) {
        printf("Verified successfully\n");
      } else {
        printf("Verification error: Read back 0x%x\n", readback_data);
      }
      break;
    }
    case '?':
    case 'h':
     alt_tpo_lcd_console_do_help();
     break;

    default:
    {
      printf("Unrecognized command. Try 'h' for help)\n");
      result = -1;
    }
  }

  return result;
}

/*
 * alt_tpo_lcd_config_monitor
 * 
 * Simple console-io processor that accepts STDIN input to
 * attempt to extract commands. This routine is generic, with 
 * the actual command set defined and handled elsewhere
 * 
 * This routine is written single-theaded as-is, but can be
 * modified relatively simply to be an RTOS task running at 
 * low priority. Modifying this to be an RTOS task/thread 
 * would be useful for debugging display issues
 * in a complex system.
 */
void alt_tpo_lcd_config_monitor(alt_tpo_lcd *lcd)
{ 
  /*
   * Input buffer stored on the stack. If more room is needed, consider
   * using a global. If an OS is used, care should be taken to ensure
   * task stack size is large enough.
   */
  unsigned char serial_input_buffer[LINE_BUFFER_LENGTH];
  int result = 0, buf_index = 0; 
  char c = 0; 
  
  printf("LCD Config register monitor. Enter 'q' to exit\n");
  alt_tpo_lcd_console_do_help();
  
  while(c != 'q')
  {   
    c = getchar();
    
    /* If getchar() returns 0xFF (-1) it means EOF... ignore */
    if(c != EOF)
    {      
      /* People just love to hear themselves talk. */
      putchar(c); 
      
      /* Don't trash what's not ours. */
      if (buf_index >= LINE_BUFFER_LENGTH - 1) 
      {
        printf("Serial buffer overflow. Command ignored.\n");
        buf_index = 0;
      }
      else
      {       
        /* Process command when the user presses return */
        if ((c == '\n')) 
        {
          serial_input_buffer[buf_index] = 0; 
          result = alt_tpo_lcd_console_do_command(serial_input_buffer, lcd);
          buf_index = 0;
          printf("+");
        }
        /* Handle backspaces.  How civilized. */
        else if ((c == 0x08) && (buf_index > 0)) 
        {
          buf_index--;
        }
        else 
        {
          serial_input_buffer[buf_index++] = c;
        }
      }
    }
  } /* while(c != 'q') */
  
  /* Done. Erase the evidence */
  serial_input_buffer[0] = 0;
}
