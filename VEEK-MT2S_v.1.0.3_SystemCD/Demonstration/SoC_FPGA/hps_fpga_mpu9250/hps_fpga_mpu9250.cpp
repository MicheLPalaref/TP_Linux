/*
To run this example navigate to the directory containing it and run following commands in SoCEDS command shell:
make
./hps_fpga_mpu9250
*/

#include "MPU9250.h"
#include <stdlib.h>
//=============================================================================

int main()
{
	unsigned char value;
	//-------------------------------------------------------------------------
	MPU9250 imu;
	value=imu.whoami();
	printf("id=0x%x\n",value);
	imu.initialize();
	imu.calib_acc();
	float ax, ay, az, gx, gy, gz, mx, my, mz;
    //-------------------------------------------------------------------------

    while(1) {
    imu.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
	printf("Acc: %+7.3f %+7.3f %+7.3f  \n", ax, ay, az);
	printf("Gyr: %+8.3f %+8.3f %+8.3f  \n", gx, gy, gz);
	printf("Mag: %+7.3f %+7.3f %+7.3f  \n", mx, my, mz);
	
	usleep(50000);
    }
}
