// audio_ctrl.c

#include "system.h"
#include "audio_ctrl.h"
//#include "altera_avalon_pio_regs.h"
#include "io.h"
#include <unistd.h>


static unsigned short wm8731_setting[]={
	0x1e,	0x000,	// RESET
//	0x0a,	0x006,	// Digital audio path: DAC soft mute off, De-emphasis off 
	0x0a,	0x000,	// Digital audio path: DAC soft mute off, De-emphasis off 
//	0x0a,	0x011,	// Digital audio path: DC store on, DAC soft mute off, De-emphasis off , High pass off
	0x0c,	0x062,	// power down control: CLKOUT-down, OSC-down, Mic-down 
	0x0e,	0x001,	// slave mode and left-justified

	0x08,	0x0d0,	// sound select: sidetone ATT -15dB, sidetone off, DAC select, LineIn to ADC, by-pass off
//	0x08,	0x0d5,	// sound select: sidetone ATT -15dB, sidetone off, DAC select, by-pass off, Mic to ADC, Mic mute off, Mic boost on
//	0x08,	0x018,	// sound select: sidetone ATT -0dB, sidetone off, DAC select, LineIn to ADC, by-pass on

	0x10,	0x001,	// mclk: 48  kHz sampling

//	0x00,	0x180,	// L/R input
//	0x00,	0x117,	// L/R input
	0x00,	0x117+6,	// L/R input

//	0x04,	0x180,	// L/R output vol
	0x04,	0x180+0x60,	// L/R output vol
//	0x04,	0x1f9,	// L/R output vol
	0x12,	0x001,	// activate digital interface
};



int get_codec_sampling_code(int freq){
	int rv;
	switch(freq) {
	case  8000:	rv = 0x0D; break; // 12MHz/(250*48/8) 
	case 32000:	rv = 0x19; break; // 12MHz/(250*48/32)
	case 44100:	rv = 0x23; break; // 12MHz/(272)
	case 48000:	rv = 0x01; break; // 12MHz/(250)
	case 88200:	rv = 0x3F; break; // 12MHz/(136)
	case 96000:	rv = 0x1D; break; // 12MHz/(125)
	default: rv = 0x01; break;
	}
	return rv;
}

int get_codec_sampling_divisor(int freq){
	int rv;
	int div;

	switch(freq) {
	case  8000:	div = 250*48/8; break; // 12MHz/(250*48/8) 
	case 32000:	div = 250*48/32; break; // 12MHz/(250*48/32)
	case 44100:	div = 272; break; // 12MHz/(272)
	case 48000:	div = 250; break; // 12MHz/(250)
	case 88200:	div = 136; break; // 12MHz/(136)
	case 96000:	div = 125; break; // 12MHz/(125)
	default: div = 272; break;
	}  

	rv = (div* AUDIO_CLOCK_FREQ / 12000000) -1;

	return rv;
}

void set_audio_sampling_freq(int freq){
//  IOWR_AUDIO_CONTROL( 0x0000); // remove reset for AUDIO controller

	AUDIO_I2C_WRITE( 0x12, 0); // stop audio processing
	AUDIO_I2C_WRITE( 0x10, get_codec_sampling_code(freq)); // restart audio processing

	IOWR_AUDIO_SAMPLING_RATE( get_codec_sampling_divisor(freq)); // sampling freq setting
	printf("Samplig_div:%d\n",get_codec_sampling_divisor(freq));

//	usleep(10000);

	AUDIO_I2C_WRITE( 0x12, 1); // restart audio processing
//  IOWR_AUDIO_CONTROL( 0x8000); // remove reset for AUDIO controller
}

void audio_codec_write(int ad, int dt){
		AUDIO_I2C_WRITE( ad | ((dt>>8)&1), dt);
}
void audio_codec_init(){
	int i;
	for (i=0; i< itemsof(wm8731_setting); i+=2){
		audio_codec_write( wm8731_setting[i] , wm8731_setting[i+1]);
	}
}

