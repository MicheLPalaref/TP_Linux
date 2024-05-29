 // audio_ctrl.h

#if 0
#define  AUDIO_CONTROLLER_BASE AUDIO_AVALON_CONTROLLER_0_BASE
#define  AUDIO_CONTROLLER_IRQ AUDIO_AVALON_CONTROLLER_0_IRQ
#else
#define  AUDIO_CONTROLLER_BASE AUDIO_AVALON_CONTROLLER_BASE
#define  AUDIO_CONTROLLER_IRQ AUDIO_AVALON_CONTROLLER_IRQ
#endif

//#define WRITE_CORE_SGDMA_BASE SGDMA_FIR_WRITE_BASE
//#define READ_CORE_SGDMA_BASE SGDMA_FIR_READ_BASE 

//#define AUDIO_CLOCK_FREQ 60000000 // 60MHz
//#define AUDIO_CLOCK_FREQ (60000000*2) // 120MHz
#define AUDIO_CLOCK_FREQ (48000000) // 48MHz


#define itemsof(x) sizeof(x)/sizeof(x[0])

#define AUDIO_I2C_WRITE(a,d) i2c_write(0x1a,a,d)



#define IOWR_AUDIO_DAC_DATA(data) IOWR(AUDIO_CONTROLLER_BASE, 1, data)
#define IOWR_AUDIO_CONTROL(data) IOWR(AUDIO_CONTROLLER_BASE, 3, data)
#define IOWR_AUDIO_SAMPLING_RATE(data) IOWR(AUDIO_CONTROLLER_BASE, 5, data)
#define IORD_AUDIO_ADC_DATA() IORD(AUDIO_CONTROLLER_BASE, 0)
#define IORD_AUDIO_STATUS() IORD(AUDIO_CONTROLLER_BASE, 2)
#define IORD_AUDIO_CONTROL() IORD(AUDIO_CONTROLLER_BASE, 3)
#define IORD_AUDIO_SAMPLING_RATE() IORD(AUDIO_CONTROLLER_BASE, 5)



typedef struct s_LRch {
	short Rch; 
	short Lch;
} T_AUDIO_DATA;


void init_i2c();
void i2c_write( unsigned char i2c_address,  unsigned char addr, unsigned char data);

int get_codec_sampling_code(int freq);

int get_codec_sampling_divisor(int freq);

void set_audio_sampling_freq(int freq);
void audio_codec_write(int ad, int dt);
void audio_codec_init();

