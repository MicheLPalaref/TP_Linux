
#include <stdio.h>

#include "common.h"
#include "system.h"
#include "math.h"



#include "terasic_includes.h"
#include "mipi_camera_config.h"
#include "mipi_bridge_config.h"

#include "auto_focus.h"
#include "multi_touch2.h"
#include "I2C_core.h"

#define ADV7513_SALVE_ADDR7		0x39										// 0x39)PD-low 0x3D)PD-high
#define ADV7513_SALVE_ADDR8		((alt_u8)(ADV7513_SALVE_ADDR7) << 1)		// 0x72)PD-low 0x7A)PD-high

#define ADV7513_EDID_ADDR8		0x7e



//#define DEFAULT_LEVEL 1  // if change resolution please make sure  bin  x1 x2 x4 not out of range.

#define MIPI_REG_PHYClkCtl		0x0056
#define MIPI_REG_PHYData0Ctl	0x0058
#define MIPI_REG_PHYData1Ctl	0x005A
#define MIPI_REG_PHYData2Ctl	0x005C
#define MIPI_REG_PHYData3Ctl	0x005E
#define MIPI_REG_PHYTimDly		0x0060
#define MIPI_REG_PHYSta			0x0062
#define MIPI_REG_CSIStatus		0x0064
#define MIPI_REG_CSIErrEn		0x0066
#define MIPI_REG_MDLSynErr		0x0068
#define MIPI_REG_FrmErrCnt		0x0080
#define MIPI_REG_MDLErrCnt		0x0090

void mipi_clear_error(void){
	MipiBridgeRegWrite(MIPI_REG_CSIStatus,0x01FF); // clear error
	MipiBridgeRegWrite(MIPI_REG_MDLSynErr,0x0000); // clear error
	MipiBridgeRegWrite(MIPI_REG_FrmErrCnt,0x0000); // clear error
	MipiBridgeRegWrite(MIPI_REG_MDLErrCnt, 0x0000); // clear error

  	MipiBridgeRegWrite(0x0082,0x00);
  	MipiBridgeRegWrite(0x0084,0x00);
  	MipiBridgeRegWrite(0x0086,0x00);
  	MipiBridgeRegWrite(0x0088,0x00);
  	MipiBridgeRegWrite(0x008A,0x00);
  	MipiBridgeRegWrite(0x008C,0x00);
  	MipiBridgeRegWrite(0x008E,0x00);
  	MipiBridgeRegWrite(0x0090,0x00);
}

void mipi_show_error_info(void){

	alt_u16 PHY_status, SCI_status, MDLSynErr, FrmErrCnt, MDLErrCnt;

	PHY_status = MipiBridgeRegRead(MIPI_REG_PHYSta);
	SCI_status = MipiBridgeRegRead(MIPI_REG_CSIStatus);
	MDLSynErr = MipiBridgeRegRead(MIPI_REG_MDLSynErr);
	FrmErrCnt = MipiBridgeRegRead(MIPI_REG_FrmErrCnt);
	MDLErrCnt = MipiBridgeRegRead(MIPI_REG_MDLErrCnt);
	printf("PHY_status=%xh, CSI_status=%xh, MDLSynErr=%xh, FrmErrCnt=%xh, MDLErrCnt=%xh\r\n", PHY_status, SCI_status, MDLSynErr,FrmErrCnt, MDLErrCnt);
}

void mipi_show_error_info_more(void){
    printf("FrmErrCnt = %d\n",MipiBridgeRegRead(0x0080));
    printf("CRCErrCnt = %d\n",MipiBridgeRegRead(0x0082));
    printf("CorErrCnt = %d\n",MipiBridgeRegRead(0x0084));
    printf("HdrErrCnt = %d\n",MipiBridgeRegRead(0x0086));
    printf("EIDErrCnt = %d\n",MipiBridgeRegRead(0x0088));
    printf("CtlErrCnt = %d\n",MipiBridgeRegRead(0x008A));
    printf("SoTErrCnt = %d\n",MipiBridgeRegRead(0x008C));
    printf("SynErrCnt = %d\n",MipiBridgeRegRead(0x008E));
    printf("MDLErrCnt = %d\n",MipiBridgeRegRead(0x0090));
    printf("FIFOSTATUS = %d\n",MipiBridgeRegRead(0x00F8));
    printf("DataType = 0x%04x\n",MipiBridgeRegRead(0x006A));
    printf("CSIPktLen = %d\n",MipiBridgeRegRead(0x006E));
}



bool MIPI_Init(void){
	bool bSuccess;


	bSuccess = oc_i2c_init_ex(I2C_OPENCORES_MIPI_BASE, 50*1000*1000,400*1000); //I2C: 400K
	if (!bSuccess)
		printf("failed to init MIPI- Bridge i2c\r\n");

    usleep(50*1000);
    MipiBridgeInit();

    usleep(500*1000);

//	bSuccess = oc_i2c_init_ex(I2C_OPENCORES_CAMERA_BASE, 50*1000*1000,400*1000); //I2C: 400K
//	if (!bSuccess)
//		printf("failed to init MIPI- Camera i2c\r\n");

    // test focus (motor control)
    /*
    OV8865_FOCUS_Move_to(0);
    usleep(20*1000);
    OV8865_FOCUS_Move_to(1023);
    usleep(20*1000);
    OV8865_FOCUS_Move_to(512);
*/
    // config camear
    MipiCameraInit();
//    MIPI_BIN_LEVEL(DEFAULT_LEVEL);
//    OV8865_FOCUS_Move_to(340);

//    oc_i2c_uninit(I2C_OPENCORES_CAMERA_BASE);  // Release I2C bus , due to two I2C master shared!




 	usleep(1000);


//    oc_i2c_uninit(I2C_OPENCORES_MIPI_BASE);

	return bSuccess;
}


#define D8M_DEFAULT_LEVEL 3

bool Handle_Touch(MTC2_INFO *pTouch){
	 bool bProcess = FALSE;
	 int X1, Y1, X2, Y2,X3,Y3, X4, Y4, X5, Y5 ;
	 alt_u8 Event, TouchNum;
	 static int nSingleTouchCnt = 0;

     static alt_u16 bin_level = D8M_DEFAULT_LEVEL;
     static alt_u16 pre_bin_level = D8M_DEFAULT_LEVEL;
     alt_u8 zoom_type = 1;

	 if (MTC2_GetStatus(pTouch,&Event, &TouchNum, &X1, &Y1, &X2, &Y2, &X3, &Y3, &X4, &Y4, &X5, &Y5)){
		 if (TouchNum == 2){ // process gesture first
			 nSingleTouchCnt = 0;
      		if((Event == MTC_ZOOM_IN && bin_level != CAMERA_BIN_LEVEL_MIN)
      		|| (Event == MTC_ZOOM_OUT && bin_level != CAMERA_BIN_LEVEL_MAX))
      		{

      			printf("ZOOM %s \n",(Event == MTC_ZOOM_IN)?"IN":"OUT");
      			if(1){//zoom_type == Event){ // double same zoom type



						printf("bin_level %d change to",bin_level);

						if(Event == MTC_ZOOM_IN) bin_level = bin_level-1;
						else                     bin_level = bin_level+1;

						printf(" %d \n",bin_level);

						if(pre_bin_level != bin_level)
						{
						  MIPI_BIN_LEVEL(bin_level);
//           		       BLC_LEVEL(bin_level);
						  pre_bin_level = bin_level;
						}
						usleep(500*1000);
						bProcess = TRUE;
      			}
      			zoom_type = Event;
      		}
		 }else if (TouchNum == 1){
			 nSingleTouchCnt++;
			 if (nSingleTouchCnt > 8){
				 printf("touch (x,y)=(%d,%d) %d\r\n", X1, Y1, nSingleTouchCnt);
			 	 if (!Focus_Processing()){
			 		 Focus_Window_immediately(X1,Y1);
			 		 bProcess = TRUE;
			 	 }
  	 		    usleep(200*1000);
			 	nSingleTouchCnt = 0;
		 	 }
		 }
	 }

	 if (bProcess){
		 MTC2_ClearEvent(pTouch); // clear touch evnet
	 }
	 return bProcess;

}


#define MODE_BIT_MASK 			0x03
#define MONITOR_GAMA_BIT_MASK 	0x04
#define HISTOGRAM_BIT_MASK 		0x08

// de10-standard led is high active
void welcome_led(){
	int i;
	for(i=0; i<3; i++){
		IOWR(LED_BASE, 0x00, 0x000);  // off
		usleep(200*1000);
		IOWR(LED_BASE, 0x00, 0x3FF); // on
		usleep(200*1000);
	}
}

int main(int argc, const char *argv[])
{


	MTC2_INFO *pTouch;


	welcome_led();

	printf("\n===== VIP Camera Demo =====\n");

	// touch
	oc_i2c_init_ex(I2C_OPENCORES_TOUCH_BASE, 50*1000*1000, 400*1000);
   //initial MULTI-touch
    pTouch = MTC2_Init(I2C_OPENCORES_TOUCH_BASE, TOUCH_INT_N_BASE, TOUCH_INT_N_IRQ);
	if (!pTouch){
	    printf("Failed to init multi-touch\r\n");
	}else{
	    printf("Init touch successfully\r\n");
	}

    //-------------------------------
    // D8M
    //-------------------------------

	  printf("MIPI Demo\n");
	  IOWR(CAMERA_PWDN_N_BASE, 0x00, 0x00);
	  IOWR(MIPI_RESET_N_BASE, 0x00, 0x00);

	  usleep(2000);
	  IOWR(CAMERA_PWDN_N_BASE, 0x00, 0xFF);

	  usleep(2000);


	  IOWR(MIPI_RESET_N_BASE, 0x00, 0xFF);


	  usleep(2000);


	  // MIPI Init
	   if (!MIPI_Init()){
		  printf("MIPI_Init Init failed!\r\n");
	  }else{
		  printf("MIPI_Init Init successfully!\r\n");
	  }

	//   while(1){
	 	    mipi_clear_error();
		 	usleep(50*1000);
	 	    mipi_clear_error();
		 	usleep(1000*1000);
		    mipi_show_error_info();
	//	    mipi_show_error_info_more();
		    printf("\n");
	//   }

   alt_u8  manual_focus_step = 10;
   alt_u16  current_focus = 300;



	Focus_Init();


	printf("Touch LCD screen for focus and zoom...\r\n");
    while(1){

    	Handle_Touch(pTouch);


       // touch KEY1 to trigger Manual focus  - step
       if((IORD(KEY_BASE,0)&0x0F) == 0x0D){

    	   if(current_focus > manual_focus_step)
    		   current_focus -= manual_focus_step;
    	   else
    		   current_focus = 0;
    	   OV8865_FOCUS_Move_to(current_focus);

       }

       // touch KEY2 to trigger Manual focus  + step
       if((IORD(KEY_BASE,0)&0x0F) == 0x0B){
    	   current_focus += manual_focus_step;
    	   if(current_focus >1023)
    		   current_focus = 1023;
    	   OV8865_FOCUS_Move_to(current_focus);
       }


   };

	return 0;
}
