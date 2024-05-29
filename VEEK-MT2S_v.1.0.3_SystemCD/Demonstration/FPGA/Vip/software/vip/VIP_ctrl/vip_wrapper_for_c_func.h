#ifndef VIP_WRAPPER_FOR_C_FUNC_H_
#define VIP_WRAPPER_FOR_C_FUNC_H_

#include "terasic_includes.h"

//#define NULL ((void *) 0)
#ifdef __cplusplus

extern "C" void Mixer_init(void);
extern "C" void Mixer_frame_on_off(int layer, int flg);
extern "C" void Mixer_set_layer_position(int layer, int x, int y);
extern "C" int Mixer_is_running();
extern "C" void Mixer_start();
extern "C" void Mixer_stop(bool is_blocking);
extern "C" void Scaler_init(void);
extern "C" void Scaler_set_output_size( int fw, int fh);
extern "C" int Scaler_is_running();
extern "C" void Scaler_start();
extern "C" void Scaler_stop(bool is_blocking);

extern "C" void Clipper_init(void) ;
extern "C" void Clipper_set_xywh(int x, int y, int w, int h);
extern "C" int Clipper_is_running(void);
extern "C" void Clipper_start(void);
extern "C" void Clipper_stop(bool is_blocking);

extern "C" void Clocked_Video_Input_init(void);
extern "C" int Clocked_Video_Input_get_f0_sample_count(void);
extern "C" int Clocked_Video_Input_get_f0_line_count(void);
extern "C" int Clocked_Video_Input_get_f1_sample_count(void);
extern "C" int Clocked_Video_Input_get_f1_line_count(void);
extern "C" int Clocked_Video_Input_is_fifo_overflowed();
extern "C" void Clocked_Video_Input_clear_fifo_overflow();


extern "C" void Clipper_set_top_offset(int ofst) ;


extern "C" void HSMC_Dual_DVI_init(void);
extern "C" void HSMC_Quad_Video_init(void);
extern "C" void Frame_Buffer_Reader_init(void);
extern "C" void Clocked_Video_Output_init(void);


extern "C" void Frame_Reader_init(void);
extern "C" void Frame_Reader_set_frame_0_properties(int base_address, int words, int samples, int width, int height, int interlaced);
extern "C" void Frame_Reader_switch_to_pb0(void);
extern "C" void Frame_Reader_start(void);

extern "C" void Control_Synchronizer_init(void);
extern "C" void Control_Synchronizer_set_number_of_writes(int writes);
extern "C" void Control_Synchronizer_setup_write(int write_number, int write_address, int write_data);
extern "C" bool Control_Synchronizer_event_is_empty(void);
extern "C" void Control_Synchronizer_event_clear(void);
extern "C" void Control_Synchronizer_enable_trigger(void);
extern "C" void Control_Synchronizer_clear_interrupt(void);

#else
//typedef int bool;
extern void Mixer_init(void);
extern void Mixer_frame_on_off(int layer, int flg);
extern void Mixer_set_layer_position(int layer, int x, int y);
extern int Mixer_is_running();
extern void Mixer_start();
extern void Mixer_stop(bool is_blocking);
extern void Scaler_init(void);
extern void Scaler_set_output_size( int fw, int fh);
extern int Scaler_is_running();
extern void Scaler_start();
extern void Scaler_stop(bool is_blocking);

extern void Clipper_init(void) ;
extern void Clipper_set_xywh(int x, int y, int w, int h);
extern int Clipper_is_running(void);
extern void Clipper_start(void);
extern void Clipper_stop(bool is_blocking);

extern void Clocked_Video_Input_init(void);
extern int Clocked_Video_Input_get_f0_sample_count(void);
extern int Clocked_Video_Input_get_f0_line_count(void);
extern int Clocked_Video_Input_get_f1_sample_count(void);
extern int Clocked_Video_Input_get_f1_line_count(void);
extern int Clocked_Video_Input_is_fifo_overflowed();
extern void Clocked_Video_Input_clear_fifo_overflow();

extern void Clipper_set_top_offset(int ofst) ;

extern void HSMC_Dual_DVI_init(void);
extern void HSMC_Quad_Video_init(void);
extern void Frame_Buffer_Reader_init(void);
extern void Clocked_Video_Input_init(void);
extern void Clocked_Video_Output_init(void);

extern void Frame_Reader_init(void);
extern void Frame_Reader_set_frame_0_properties(int base_address, int words, int samples, int width, int height, int interlaced);
extern void Frame_Reader_switch_to_pb0(void);
extern void Frame_Reader_start(void);

extern void Control_Synchronizer_init(void);
extern void Control_Synchronizer_set_number_of_writes(int writes);
extern void Control_Synchronizer_setup_write(int write_number, int write_address, int write_data);
extern bool Control_Synchronizer_event_is_empty(void);
extern void Control_Synchronizer_event_clear(void);
extern void Control_Synchronizer_enable_trigger(void);
extern void Control_Synchronizer_clear_interrupt(void);

#endif

#endif /*VIP_WRAPPER_FOR_C_FUNC_H_*/
