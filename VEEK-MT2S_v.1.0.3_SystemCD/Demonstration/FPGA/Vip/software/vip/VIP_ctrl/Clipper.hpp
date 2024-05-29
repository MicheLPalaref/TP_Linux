#ifndef CLIPPER_HPP_
#define CLIPPER_HPP_

#include "Vipcore.hpp"

class Clipper_Offset_Type : public Vipcore {
  public:
  
    static const int LEFT_OFFSET = 3;
    static const int RIGHT_OFFSET = 4;
    static const int TOP_OFFSET = 5;
    static const int BOTTOM_OFFSET = 6;
    
    Clipper_Offset_Type(long base_address) : Vipcore(base_address)
    {}
       
    void set_left_offset(int offset)
    {
        do_write(LEFT_OFFSET,offset);
    }
    
    void set_right_offset(int offset)
    {
        do_write(RIGHT_OFFSET,offset);
    }
    
    void set_top_offset(int offset)
    {
        do_write(TOP_OFFSET,offset);
    }
    
    void set_bottom_offset(int offset)
    {
        do_write(BOTTOM_OFFSET,offset);
    }
};

class Clipper_Rectangle_Type : public Vipcore{
  public:
  
    static const int LEFT_OFFSET = 3;
    static const int WIDTH = 4;
    static const int TOP_OFFSET = 5;
    static const int HEIGHT = 6;
    
    Clipper_Rectangle_Type(long base_address) : Vipcore(base_address)
    {}
       
    void set_left_offset(int offset)
    {
        do_write(LEFT_OFFSET,offset);
    }
    
    void set_width(int offset)
    {
        do_write(WIDTH,offset);
    }
    
    void set_top_offset(int offset)
    {
        do_write(TOP_OFFSET,offset);
    }
    
    void set_height(int offset)
    {
        do_write(HEIGHT,offset);
    }
};

#endif /*CLIPPER_HPP_*/
