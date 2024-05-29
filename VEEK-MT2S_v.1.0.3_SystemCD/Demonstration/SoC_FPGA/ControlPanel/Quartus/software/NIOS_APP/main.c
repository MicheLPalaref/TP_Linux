
#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "io.h"

//#include "terasic_includes.h"
//#include "mipi_camera_config.h"
//#include "mipi_bridge_config.h"
#include "camera.h"

#define FRAME_WIDTH			800
#define FRAME_HEIGHT		480
#define FRAME_BACKGROUN_R		0
#define FRAME_BACKGROUN_G		0
#define FRAME_BACKGROUN_B		255

#define  PIP_WIDTH				270
#define  PIP_HEIGHT				200

void MIX_Reset(int bGo){
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 0, 0x00); // stop

	IOWR(ALT_VIP_CL_MIXER_0_BASE, 3, FRAME_WIDTH); // frame width
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 4, FRAME_HEIGHT); // frame height
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 5, FRAME_BACKGROUN_R);
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 6, FRAME_BACKGROUN_G);
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 7, FRAME_BACKGROUN_B);

	// layer 0
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 8+0, 0x00); // x offset
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 8+1, 0x00); // y offset
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 8+2, 0x00); // disable

	// layer 1
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 13+0, 0x00); // x offset
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 13+1, 0x00); // y offset
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 13+2, 0x00); // disable

	IOWR(ALT_VIP_CL_MIXER_0_BASE, 0x00, bGo?0x01:0x00); // go
}

// layer: background layer, layer0, layer1

// nLayer = 0: means layer 0
// nLayer = 1: means layer 1


void MIX_EnableLayer(int nLayer, int bEnable, int x, int y){
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 0x00, 0x00); // stop
	usleep(200*1000);
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 8+nLayer*5+ 2, bEnable?0x01:0x00); // layer disable
	if (bEnable){
		IOWR(ALT_VIP_CL_MIXER_0_BASE, 8+nLayer*5+ 0, x);
		IOWR(ALT_VIP_CL_MIXER_0_BASE, 8+nLayer*5+ 1, y);
	}
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 0x00, 0x01); // go
}

void MIX_MoveLayer(int nLayer, int bEnable, int x, int y){
//	IOWR(ALT_VIP_CL_MIXER_0_BASE, 0x00, 0x00); // stop
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 8+nLayer*5+ 0, x);
	IOWR(ALT_VIP_CL_MIXER_0_BASE, 8+nLayer*5+ 1, y);
//	IOWR(ALT_VIP_CL_MIXER_0_BASE, 0x00, 0x01); // go
}


#define LAYER_ENABLE 	0x01
#define LAYER_DISABLE 	0x00



int config_for_linux(){
	// config mixer
	const int bGo = 1; //1:go, 0:no-go
	const int nLayer1 = 0;
	const int nLayer2 = 1;

	printf("Init VIP\n");
	MIX_Reset(bGo);

	//printf("show background\r\n");
	usleep(3000*1000); // show color bar

	printf("enable layer 1(linux frame buffer)\r\n");
	MIX_EnableLayer(nLayer1, LAYER_ENABLE, 0, 0);



	////////////////////////////////
	// config TV_DECODER


	// config scaler. scale to (VIDEO_IN_WIDTH, VIDEO_IN_HEIGHT) and enable it
#if TV_DECODER_ALT_VIP_CL_SCL_0_BASE
	// video-in scaler
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_0_BASE, 0x03, PIP_WIDTH); // output width
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_0_BASE, 0x04, PIP_HEIGHT); // output height
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_0_BASE, 0x00, 0x01); // go
#endif

#if TV_DECODER_ALT_VIP_CL_SCL_1_BASE
	// camera scaler
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_1_BASE, 0x03, PIP_WIDTH); // output width
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_1_BASE, 0x04, PIP_HEIGHT); // output height
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_1_BASE, 0x00, 0x01); // go
#endif

#ifdef TV_DECODER_ALT_VIP_CL_SWI_0_BASE
	// set switch II input to camera & go
	IOWR(TV_DECODER_ALT_VIP_CL_SWI_0_BASE, 0x00, 0x00); // stop
	IOWR(TV_DECODER_ALT_VIP_CL_SWI_0_BASE, 0x04, 0x01); // dout0: din_0 as input (first one is din_0)
	IOWR(TV_DECODER_ALT_VIP_CL_SWI_0_BASE, 0x00, 0x01); // go
#endif

#ifdef ALT_VIP_CL_MIXER_0_BASE
	// move layer to center of screen
#endif

	////////////////////////////////
	// enable camera for test
	printf("enable camera display\r\n");
	MIX_EnableLayer(nLayer2, LAYER_ENABLE, (FRAME_WIDTH-PIP_WIDTH)/2, (FRAME_HEIGHT-PIP_HEIGHT)/2);
	usleep(2*1000*1000);
	printf("disable camera display\r\n");
	MIX_EnableLayer(nLayer2, LAYER_DISABLE, 0, 0);

	return 0;

}


int test_camera(){

	int led_mask, i;
	const int bGo = 1; //1:go, 0:no-go
	const int nLayer1 = 0; // linux frame buffer
	const int nLayer2 = 1; // camera
	const int nLayer3 = 2; // NTSC/PAL

	printf("Init VIP\n");

#if TV_DECODER_ALT_VIP_CL_CVI_0_BASE
	IOWR(TV_DECODER_ALT_VIP_CL_CVI_0_BASE, 0x00, 0x01); // go
#endif

#if TV_DECODER_ALT_VIP_CL_SCL_0_BASE
	// scale NTSL/PAL
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_0_BASE, 0x03, PIP_WIDTH); // output width
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_0_BASE, 0x04, PIP_HEIGHT); // output height
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_0_BASE, 0x00, 0x01); // go
#endif

#ifdef TV_DECODER_ALT_VIP_CL_SCL_1_BASE
	// scale d8m
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_1_BASE, 0x03, PIP_WIDTH); // output width
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_1_BASE, 0x04, PIP_HEIGHT); // output height
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_1_BASE, 0x00, 0x01); // go
#endif

#ifdef TV_DECODER_ALT_VIP_CL_SWI_0_BASE
	// set switch II input to camera & go
	IOWR(TV_DECODER_ALT_VIP_CL_SWI_0_BASE, 0x00, 0x00); // stop
	IOWR(TV_DECODER_ALT_VIP_CL_SWI_0_BASE, 0x04, 0x01); // dout0: din_0 as input (first one is din_0)
	IOWR(TV_DECODER_ALT_VIP_CL_SWI_0_BASE, 0x00, 0x01); // go
#endif

	MIX_Reset(bGo);

	//


  // init VIP mixer II

	printf("show background\r\n");
	usleep(3000*1000); // show color bar

	//MIX_EnableLayer(nLayer1, LAYER_ENABLE, 0, 0);


	printf("show layer 2\r\n");
	MIX_EnableLayer(nLayer2, LAYER_ENABLE, 10, 10); // cannot be (0,0)

	usleep(5000*1000);

#ifdef TV_DECODER_ALT_VIP_CL_SWI_0_BASE
	int nSel = 1;
	while(1){
		printf("switch %d\r\n", nSel);
		IOWR(TV_DECODER_ALT_VIP_CL_SWI_0_BASE, 0x00, 0x00); // stop
		IOWR(TV_DECODER_ALT_VIP_CL_SWI_0_BASE, 0x04, nSel); // dout0: din_0 as input (first one is din_0)
		IOWR(TV_DECODER_ALT_VIP_CL_SWI_0_BASE, 0x00, 0x01); // go

		usleep(3*1000*1000);
		if (nSel == 1)
			nSel = 2;
		else
			nSel = 1;
	}
#endif
	int x=1, y=1;
	while(1){
		MIX_MoveLayer(nLayer2, LAYER_ENABLE, x, y); // cannot be (0,0)
		usleep(2000);
		x++;
		if (x > 400)
			x = 1;
	}

}


int test()
{
	int led_mask, i;
	const int bGo = 1; //1:go, 0:no-go
	const int nLayer1 = 0;
	const int nLayer2 = 1;
	const int nLayer3 = 2;

	printf("Init VIP\n");

#if TV_DECODER_ALT_VIP_CL_CVI_0_BASE
	IOWR(TV_DECODER_ALT_VIP_CL_CVI_0_BASE, 0x00, 0x01); // go
#endif

#if TV_DECODER_ALT_VIP_CL_SCL_0_BASE
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_0_BASE, 0x03, 270+200); // output width
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_0_BASE, 0x04, 200+200); // output height
	IOWR(TV_DECODER_ALT_VIP_CL_SCL_0_BASE, 0x00, 0x01); // go
#endif

	MIX_Reset(bGo);


	// led blink
	led_mask = 0x01;
	for(i=0;i<10;i++){
		IOWR(LEDR_BASE, 0x00, led_mask);
		led_mask <<= 1;
		usleep(20*1000);
	}

	led_mask = 0x01 << 9;
	for(i=0;i<10;i++){
		IOWR(LEDR_BASE, 0x00, led_mask);
		led_mask >>= 1;
		usleep(20*1000);
	}
	IOWR(LEDR_BASE, 0x00, 0x00);


  // init VIP mixer II

	printf("show background\r\n");
	usleep(3000*1000); // show color bar

	//MIX_EnableLayer(nLayer1, LAYER_ENABLE, 0, 0);

	printf("show layer 1\r\n");
	MIX_EnableLayer(nLayer1, LAYER_ENABLE, 0, 0);
	usleep(5000*1000);

	printf("show layer 2\r\n");
	MIX_EnableLayer(nLayer2, LAYER_ENABLE, 10, 10); // cannot be (0,0)

	usleep(5000*1000);

	printf("show layer 3\r\n");
	MIX_EnableLayer(nLayer3, LAYER_ENABLE, 300, 300); // cannot be (0,0)


	int x=1, y=1;
	while(1){
		MIX_MoveLayer(nLayer2, LAYER_ENABLE, x, y); // cannot be (0,0)
		usleep(2000);
		x++;
		if (x > 400)
			x = 1;
	}



}

#define REG_DAC_FIFO_ADDR		0
#define REG_ADC_FIFO_ADDR		1
#define REG_CMD_ADDR				2
#define REG_STATUS_ADDR			3

#define DAC_FIFO_FULL_BIT	0x01
#define ADC_FIFO_EMPTY_BIT	0x02

// http://tmrc1.tp.edu.tw/HTML/RSR20081124231639YLZ/content/wave3-1-4.html
int test_audio()
{
	int status;
	unsigned int cnt = 0;
	unsigned int vol=0;
	float szToneFreq[] = {261.6, 293.7, 329.6, 349.2, 392.0, 440, 493.9, 523.3, 523.3};
	int max_cnt, nIndex=0;
	int sample_cnt = 0;
	const int nDataRate = 48000;

	// clear fifo
	IOWR(AUDIO_BASE, REG_CMD_ADDR, 0x01);
	IOWR(AUDIO_BASE, REG_CMD_ADDR, 0x00);

	printf("Audio Player...\r\n");
	printf("Please make sure a speaker is connected to the line-out audio jack.\r\n");
	// dac (play sound)
	max_cnt = (float)nDataRate/szToneFreq[nIndex];
	while(1){
		status = IORD(AUDIO_BASE, REG_STATUS_ADDR);

		if ((status & DAC_FIFO_FULL_BIT) != DAC_FIFO_FULL_BIT){
			if (cnt < max_cnt/2)
				vol = 0;
			else
				vol = 0x0FFF0FFF;
			IOWR(AUDIO_BASE, REG_DAC_FIFO_ADDR, vol);

			//
			sample_cnt++;
			cnt++;
			if (cnt >= max_cnt){
				cnt = 0;
			}


			if (sample_cnt >= nDataRate){
				max_cnt = (float)nDataRate/szToneFreq[nIndex];
				sample_cnt = 0;
				nIndex++;
				if (nIndex >= sizeof(szToneFreq)/sizeof(szToneFreq[0]))
					nIndex = 0;
			}



		}
	}
}


void led_blink(void){
	int i;
	for(i=0;i<6;i++){
		IOWR(LEDR_BASE, 0x00, (i%2 ==0)?0xFF:0x00);
		usleep(100*1000);
	}
}



int main(){
	int result;

	// nios welcome led
	led_blink();

	// init MIPI
	Init_mipi_d8m();


	// clear adc fifo
	IOWR(AUDIO_BASE, REG_CMD_ADDR, 0x01);
	IOWR(AUDIO_BASE, REG_CMD_ADDR, 0x00);

	//result = test_audio();
	//result = test_camera();
	result = config_for_linux();


	return result;
}
