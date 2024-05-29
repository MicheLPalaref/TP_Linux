#ifndef FPGA_H
#define FPGA_H

#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include "MPU9250.h"
#include "adc9300.h"
#include "vm149c.h"

class FPGA
{
public:
    FPGA();
    ~FPGA();

    typedef enum{
        TONE_C=0,
        TONE_D,
        TONE_E,
        TONE_F,
        TONE_G,
        TONE_A,
        TONE_B
    }TONE_ID;

    typedef enum{
        VIDEO_IN_CAMERA=0,
        VIDEO_IN_COMPOSITIVE
    }VIDEO_IN_ID;

    bool LedSet(int mask);
    bool HexSet(int index, int value);
    bool KeyRead(uint32_t *mask);
    bool SwitchRead(uint32_t *mask);
    bool VideoEnable(bool bEnable);
    bool VideoMove(int x, int y);
    bool SwitchVideoIn(VIDEO_IN_ID VideoInID);
    bool IsVideoEnabled();
    bool IrDataRead(uint32_t *scan_code);
    bool IrIsDataReady(void);
    bool CameraFocus(int nFocusPos /* 0 ~ 1023 */);
    bool getMotion9(float *ax, float *ay, float *az, float *gx, float *gy, float *gz, float *mx, float *my, float *mz);
    bool getLight(uint16_t *light0, uint16_t *light1);



protected:
    bool m_bInitSuccess;
    int m_file_mem;
    bool m_bIsVideoEnabled;

    MPU9250 m_mpu9250;
    ADC9300 m_adc9300;
    VM149C  m_camera_vm149c;

    uint8_t *m_led_base;
    uint8_t *m_hex_base;
    uint8_t *m_key_base;
    uint8_t *m_sw_base;
    uint8_t *m_ir_rx_base;
    uint8_t *m_adc_spi_base;
    uint8_t *m_vip_cvi_base;
    uint8_t *m_vip_mix_base;
    uint8_t *m_switch_video_in_base;

    bool Init();

};

#endif // FPGA_H
