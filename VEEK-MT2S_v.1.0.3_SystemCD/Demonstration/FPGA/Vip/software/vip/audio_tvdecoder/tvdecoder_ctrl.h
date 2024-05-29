/*****************************************************************************
 * File: tvdecoder_ctrl.h
 *
 * TV decoder ÇÃêßå‰
 *
 *  Author : H.S.Hagiwara    Nov.29,2008
 *  
 ****************************************************************************/

#ifndef __TVDECODER_CTRL_H__
#define __TVDECODER_CTRL_H__

#include "i2c.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
	
void tv_decoder_write(int ad, int dt);
int tv_decoder_read(int ad);

void tv_decoder_init();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TVDECODER_CTRL_H__ */
