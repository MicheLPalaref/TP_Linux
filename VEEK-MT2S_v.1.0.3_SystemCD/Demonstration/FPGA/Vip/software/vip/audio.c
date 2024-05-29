/*****************************************************************************
 *  File: sound_in_out.c
 *
 *  This file is the top level of the sound_in_out application.
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "io.h"
#include <sys/alt_irq.h>
#include "audio_tvdecoder/audio_ctrl.h"

// Select one out of six audio sampling freq candidates 
//#define SAMPLING_FREQ  8000 //  8k Sampling
//#define SAMPLING_FREQ 32000 // 32k Sampling
//#define SAMPLING_FREQ 44100 // 44k Sampling
#define SAMPLING_FREQ 48000 // 48k Sampling // Real Freq is 40kHz
//#define SAMPLING_FREQ 88200 // 88k Sampling
//#define SAMPLING_FREQ 96000 // 96k Sampling

#define AUDIO_BUF_SIZE 128
//#define AUDIO_DECIMATION_RATE 16
static int audio_data_index=0;
static alt_u32 audio_data[AUDIO_BUF_SIZE];
int audio_volume;
static void handle_audio_interrupts(void* context, alt_u32 id)
{
//  IOWR(LED_PIO_BASE, 0, 0x0); // debug

  alt_u32 data;
  data = IORD(AUDIO_CONTROLLER_BASE, 0);

  // TRDY should be 1 at this timing
  IOWR(AUDIO_CONTROLLER_BASE, 1, data);
  audio_volume -= abs( (short) (audio_data[audio_data_index]>>16) );
  audio_volume -= abs( (short) (audio_data[audio_data_index]&0xffff) );
  audio_data[audio_data_index] = data;
  audio_volume += abs( (short) (data>>16) );
  audio_volume += abs( (short) (data&0xffff) );
  audio_data_index = (audio_data_index+1)&(AUDIO_BUF_SIZE-1);

//  IOWR(LED_PIO_BASE, 0, 0xf); // debug
}

void audio_init(){

  printf("\naudio_init\n");

	init_i2c();

  IOWR_AUDIO_CONTROL( 0x0000); // Software reset

  printf("Start Audio CODEC settings through I2C bus.\n");
  audio_codec_init();

  printf("Audio Sampling Freq. is %d Hz.\n",SAMPLING_FREQ);
  set_audio_sampling_freq(SAMPLING_FREQ);

  IOWR_AUDIO_CONTROL( 0x8000 | 0x80); // remove Software reset and enable ADC interrupt

}


volatile  int isr_context=0;


int audio_in_out_start(){




  alt_irq_register( AUDIO_CONTROLLER_IRQ, (void *)&isr_context,
                      handle_audio_interrupts );

  audio_init();
  printf("Audio Start\n");
  return 0;
}

