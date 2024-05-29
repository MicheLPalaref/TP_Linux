#ifndef FRAME_BUFFER_HPP_
#define FRAME_BUFFER_HPP_

#include "Vipcore.hpp"

class Frame_Buffer_Reader : public Vipcore{
  public:
  
    static const int non_repeat_frames_output_addressoffset = 2;
    static const int repeat_frames_output_addressoffset = 3;
  
    Frame_Buffer_Reader(long base_address) : Vipcore(base_address)
    {}
    
    /* DIAGNOSTIC/STATUS METHODS */
    int get_number_of_non_repeat_frames_output()
    {
        return do_read(non_repeat_frames_output_addressoffset);
    }
    
    int get_number_of_repeat_frames_output()
    {
        return do_read(repeat_frames_output_addressoffset);
    }
    
    /* END DIAGNOSTIC/STATUS METHODS */  
};

class Frame_Buffer_Writer : public Vipcore{
  public:
  
    static const int non_dropped_frames_input_addressoffset = 2;
    static const int dropped_frames_addressoffset = 3;
  
    Frame_Buffer_Writer(long base_address) : Vipcore(base_address)
    {}
    
    /* DIAGNOSTIC/STATUS METHODS */
    int get_number_of_non_dropped_frames_input()
    {
        return do_read(non_dropped_frames_input_addressoffset);
    }
    
    int get_number_of_dropped_frames()
    {
        return do_read(dropped_frames_addressoffset);
    }    
    /* END DIAGNOSTIC/STATUS METHODS */  
};

#endif /*FRAME_BUFFER_HPP_*/



