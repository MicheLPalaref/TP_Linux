/*************************************************************************
* Copyright (c) 2008 Altera Corporation, San Jose, California, USA.      *
* All rights reserved. All use of this software and documentation is     *
* subject to the License Agreement located at the end of this file below.*
*************************************************************************/
/******************************************************************************
 *
 * Description
 * ----------- 
 * This programs demonstrates how to configure and control the Altera Video and
 * Image Processing Suite MegaCore functions using a set of software API
 * classes.
 * 
 * In this example, the program uses these classes to access the register map of
 * the following MegaCore functions:
 * 
 * HSMC Bitec Quad Video daughtercard               (HSMC_Quad_Video.hpp)
 * HSMC Bitec DVI I/O daughtercard                  (HSMC_Dual_DVI.hpp)
 * Clocked Video Input                              (Clocked_Video_Input.hpp)
 * Clocked Video Output                             (Clocked_Video_Output.hpp)
 * Frame Buffer                                     (Frame_Buffer.hpp)
 * Mixer                                            (Mixer.hpp)
 * 
 * The software project also provides classes to access the following MegaCore functions:
 * 
 * Clipper                                          (Clipper.hpp)
 * Scaler                                           (Scaler.hpp)
 * Gamma Corrector                                  (Gamma_Corrector.hpp)
 * Base class to start/stop each video function     (Vipcore.hpp)
 * 
 * The VIP Suite functions are controllable at run-time via Avalon-MM Slave interfaces.
 *
 *
 * This program performs the following functions:
 *  - Initialises the HSMC Bitec Quad Video daughtercard     (HSMC_Quad_Video.hpp) 
 *  - Initialises the HSMC Bitec DVI I/O daughtercard        (HSMC_Dual_DVI.hpp)
 *  - Starts the Frame Buffer MegaCore function              (Frame_Buffer.hpp)
 *  - Initialised the Alpha Blending Mixer MegaCore function (Mixer.hpp)
 *  - Starts the Clocked Video Input MegaCore function       (Clock_Video_Input.hpp) 
 *  - Starts the Clocked Video Output MegaCore function      (Clock_Video_Output.hpp) 
 *  - Writes to the Mixer function to change the location of the Quad Video card video 
 *    stream input relative to the test pattern background image 
 */

#include <system.h>
//#include "HSMC_Dual_DVI.hpp"
//#include "HSMC_Quad_Video.hpp"
#include "Clocked_Video_Input.hpp"
#include "Clocked_Video_Output.hpp"
#include "Frame_Buffer.hpp"
#include "Mixer.hpp"
#include "Scaler.hpp"
#include "Clipper.hpp"
#include "Frame_Reader.hpp"
#include "Control_synchronizer.hpp"

#include "unistd.h"

#include "vip_wrapper_for_c_func.h"

#ifdef ALT_VIP_CLIP_1_BASE
Clipper_Rectangle_Type * the_clipper_ptr = (Clipper_Rectangle_Type *) NULL;

void Clipper_init(){

   the_clipper_ptr = new Clipper_Rectangle_Type(ALT_VIP_CLIP_1_BASE);

   the_clipper_ptr->set_left_offset(0);
   the_clipper_ptr->set_width(800);

   the_clipper_ptr->set_top_offset(60);
   the_clipper_ptr->set_height(480);

   the_clipper_ptr->start();
}

void Clipper_set_top_offset(int ofst){
   the_clipper_ptr->set_top_offset(ofst);
}

#endif



#ifdef ALT_VIP_MIX_0_BASE

//Mixer* the_mixer_ptr;
Mixer * the_mixer_ptr = (Mixer *) NULL;

void Mixer_init(){
   /* Initialise and start the Alpha Blending Mixer MegaCore function */
   the_mixer_ptr = new Mixer(ALT_VIP_MIX_0_BASE);
   /* Set position of layer 1 to (0,0) relative to background layer */

   //the_mixer_ptr->set_layer_position(0,0,0);
  // the_mixer_ptr->set_layer_position(1,(800-800/2)/2,(600-600/2)/2);

    the_mixer_ptr->set_layer_position(1,0,0);
    the_mixer_ptr->set_layer_position(2,0,0);
   the_mixer_ptr->set_layer_enabled(0, false);

   the_mixer_ptr->set_layer_enabled(1, true);
   the_mixer_ptr->set_layer_enabled(2, true);

 //  the_mixer_ptr->set_layer_enabled(1, false);
//   the_mixer_ptr->set_layer_enabled(2, false);

   the_mixer_ptr->start();
   //the_mixer_ptr->set_layer_enabled(0, false);
}

void Mixer_frame_on_off(int layer, int flg){
  if (the_mixer_ptr == NULL) return;
  if (flg)
    the_mixer_ptr->set_layer_enabled(layer, true);
  else
    the_mixer_ptr->set_layer_enabled(layer, false);
}

void Mixer_set_layer_position(int layer, int x, int y){
  if (the_mixer_ptr == NULL) return;

  the_mixer_ptr->set_layer_position(layer, x+(800-800)/2, y+ (600-600)/2); // NEEK LCD - VGA offset
//  the_mixer_ptr->set_layer_position(layer, x+(1024-800)/2, y+ (768-480)/2); // NEEK LCD - VGA offset
//  the_mixer_ptr->set_layer_position(layer, x, y);
}


int Mixer_is_running(){
  return the_mixer_ptr->is_running();
}
void Mixer_start(){
   the_mixer_ptr->start();
}
void Mixer_stop(bool is_blocking){
  the_mixer_ptr->stop(is_blocking);
}

#endif

#ifdef ALT_VIP_CL_MIXER_0_BASE

//Mixer* the_mixer_ptr;
Mixer * the_mixer_ptr = (Mixer *) NULL;

void Mixer_init(){
   /* Initialise and start the Alpha Blending Mixer MegaCore function */
   the_mixer_ptr = new Mixer(ALT_VIP_CL_MIXER_0_BASE);

   //background
   the_mixer_ptr->set_backgroud_size(800,480);
   the_mixer_ptr->set_backgroud_color(0,0,0);
   // layer 0,1
   the_mixer_ptr->set_layer_position(0,0,0);
   the_mixer_ptr->set_layer_position(1,0,0);

   the_mixer_ptr->set_layer_enabled(0, true);
   the_mixer_ptr->set_layer_enabled(1, true);

   the_mixer_ptr->start();
}

void Mixer_frame_on_off(int layer, int flg){
  if (the_mixer_ptr == NULL) return;
  // layer -1 to Mixer II same with Mixer
  if (flg)
    the_mixer_ptr->set_layer_enabled(layer-1, true);
  else
    the_mixer_ptr->set_layer_enabled(layer-1, false);
}

void Mixer_set_layer_position(int layer, int x, int y){
  if (the_mixer_ptr == NULL) return;
  // layer -1 to Mixer II same with Mixer
  the_mixer_ptr->set_layer_position(layer-1, x, y); // NEEK LCD - VGA offset
}


int Mixer_is_running(){
  return the_mixer_ptr->is_running();
}
void Mixer_start(){
   the_mixer_ptr->start();
}
void Mixer_stop(bool is_blocking){
  the_mixer_ptr->stop(is_blocking);
}

#endif

#ifdef ALT_VIP_SCL_0_BASE

Scaler<1,1> * the_scaler_ptr = (Scaler<1,1> *) NULL;
void Scaler_init(){

   the_scaler_ptr = new Scaler<1,1>(ALT_VIP_SCL_0_BASE,0,0);

//   the_scaler_ptr->set_output_size(640/2,480/2);
   the_scaler_ptr->set_output_size(800,600);
   the_scaler_ptr->start();
}


void Scaler_set_output_size( int fw, int fh){
  the_scaler_ptr->set_output_size( fw, fh);
}

int Scaler_is_running(){
  return the_scaler_ptr->is_running();
}
void Scaler_start(){
   the_scaler_ptr->start();
}
void Scaler_stop(bool is_blocking){
  the_scaler_ptr->stop(is_blocking);
}
#endif




#ifdef ALT_VIP_CLIP_0_BASE
Clipper_Rectangle_Type * the_clipper_ptr = (Clipper_Rectangle_Type *)NULL;
const int CLIPPER_TOP_OFFSET=0;
void Clipper_init(){
  the_clipper_ptr = new Clipper_Rectangle_Type(ALT_VIP_CLIP_0_BASE);
  the_clipper_ptr->set_left_offset(0);
  the_clipper_ptr->set_width(720);
  the_clipper_ptr->set_top_offset(CLIPPER_TOP_OFFSET);
  the_clipper_ptr->set_height(480);
  the_clipper_ptr->start();
}

void Clipper_set_xywh(int x, int y, int w, int h){
  the_clipper_ptr->set_left_offset(x);
  the_clipper_ptr->set_width(w);
  the_clipper_ptr->set_top_offset(y+CLIPPER_TOP_OFFSET);
  the_clipper_ptr->set_height(h);
}

int Clipper_is_running(){
  return the_clipper_ptr->is_running();
}
void Clipper_start(){
   the_clipper_ptr->start();
}
void Clipper_stop(bool is_blocking){
  the_clipper_ptr->stop(is_blocking);
}
#endif


#ifdef ALT_VIP_CTI_0_BASE
Clocked_Video_Input * the_clocked_video_input = ( Clocked_Video_Input *)NULL;
void Clocked_Video_Input_init(){

   /* Start the Clocked Video Input MegaCore function */
   the_clocked_video_input = new Clocked_Video_Input(ALT_VIP_CTI_0_BASE);
//   the_clocked_video_input.stop(true);
   while (!the_clocked_video_input->is_input_stable()) {} // wait stable video input
   the_clocked_video_input->clear_fifo_overflow();
   the_clocked_video_input->start();
}


int Clocked_Video_Input_get_f0_sample_count(){
  return the_clocked_video_input->get_f0_sample_count();
}
int Clocked_Video_Input_get_f0_line_count(){
  return the_clocked_video_input->get_f0_line_count();
}
int Clocked_Video_Input_get_f1_sample_count(){
  return the_clocked_video_input->get_f1_sample_count();
}
int Clocked_Video_Input_get_f1_line_count(){
  return the_clocked_video_input->get_f1_line_count();
}

int Clocked_Video_Input_is_fifo_overflowed(){
  return the_clocked_video_input->is_fifo_overflowed();
}

void Clocked_Video_Input_clear_fifo_overflow(){
  the_clocked_video_input->clear_fifo_overflow();
}

#endif





#ifdef DVI_OUTPUT_I2C_MASTER_BASE
void HSMC_Dual_DVI_init(){
   /* Initialise the HSMC Bitec DVI I/O daughtercard */
   HSMC_Dual_DVI dual_dvi_board(DVI_OUTPUT_I2C_MASTER_BASE);
   dual_dvi_board.enable_output();
}
#endif

#ifdef QUAD_VIDEO_I2C_MASTER_BASE
void HSMC_Quad_Video_init(){
   /* Initialise the HSMC Bitec Quad Video daughtercard */
   HSMC_Quad_Video quad_analog_in_board(QUAD_VIDEO_I2C_MASTER_BASE);
   quad_analog_in_board.init();
}
#endif

#ifdef MY_ALT_VIP_VFB_BASE
void Frame_Buffer_Reader_init(){
   /* Start the Frame Buffer MegaCore function */
   Frame_Buffer_Reader the_frame_buffer(MY_ALT_VIP_VFB_BASE);
   the_frame_buffer.start();
}
#endif



#ifdef MY_ALT_VIP_CTI_1_BASE
void Clocked_Video_Input_init(){
   /* Start the Clocked Video Input MegaCore function */
   Clocked_Video_Input the_clocked_video_input(MY_ALT_VIP_CTI_1_BASE);
   the_clocked_video_input.stop(true);
   while (!the_clocked_video_input.is_input_stable()) {
   }
   the_clocked_video_input.start();
}
#endif

#ifdef MY_ALT_VIP_ITC_BASE
void Clocked_Video_Output_init(){
   /* Start the Clocked Video Output MegaCore function */
   Clocked_Video_Output the_clocked_video_output(MY_ALT_VIP_ITC_BASE); 
   /* Wait for data to appear in clocked video output FIFO before starting */  
   while (the_clocked_video_output.get_output_fifo_usedw() == 0) {
   }
   the_clocked_video_output.start();
}      
#endif


#ifdef ALT_VIP_VFR_0_BASE
Frame_Reader * the_frame_reader = ( Frame_Reader *)NULL;
void Frame_Reader_init(void){

   /* Start the Clocked Video Input MegaCore function */
   the_frame_reader = new Frame_Reader(ALT_VIP_VFR_0_BASE);
}
void Frame_Reader_set_frame_0_properties(int base_address, int words, int samples, int width, int height, int interlaced){
   the_frame_reader->set_frame_0_properties(base_address, words, samples, width, height, interlaced);
}
void Frame_Reader_switch_to_pb0(void){
   the_frame_reader->switch_to_pb0();
}

void Frame_Reader_start(void){
  the_frame_reader->start();
}

#endif  // ALT_VIP_VFR_0_BASE

#ifdef ALT_VIP_CTS_0_BASE
volatile EventQueue event_queue6;

Control_Synchronizer * the_control_synchronizer = (Control_Synchronizer *) NULL;
void Control_Synchronizer_init(void){
//  the_control_synchronizer = new Control_Synchronizer(ALT_VIP_CTS_0_BASE, ALT_VIP_CTS_0_IRQ, &event_queue6);
  the_control_synchronizer = new Control_Synchronizer(ALT_VIP_CTS_0_BASE);
  the_control_synchronizer->enable_interrupt(0);
  the_control_synchronizer->start();
}

void Control_Synchronizer_set_number_of_writes(int writes){
  the_control_synchronizer->set_number_of_writes(writes);
}

void Control_Synchronizer_setup_write(int write_number, int write_address, int write_data){
  the_control_synchronizer->setup_write( write_number, write_address, write_data);
}

bool Control_Synchronizer_event_is_empty(void){
  return event_queue6.is_empty();
}

void Control_Synchronizer_event_clear(void){
	  while(!event_queue6.is_empty()) {
	     volatile EventQueue::Event &event = event_queue6.pop();
	  }
}

void Control_Synchronizer_enable_trigger(void){
  the_control_synchronizer->enable_trigger();
}

void Control_Synchronizer_clear_interrupt(void){
  the_control_synchronizer->clear_interrupt();
}


#endif //ALT_VIP_CTS_0_BASE 
