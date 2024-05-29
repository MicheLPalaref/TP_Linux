#ifndef DEINTERLACER_HPP_
#define DEINTERLACER_HPP_

#include "Vipcore.hpp"

class Deinterlacer : public Vipcore{
  public:
    static const int MIN_MOTION_VALUE = 0;
    static const int MAX_MOTION_VALUE = 65535;
    static const int MOTION_OVERRIDE_OFFSET = 2;
    static const int MOTION_VALUE_OFFSET = 3;

    
    Deinterlacer(long base_address) : Vipcore(base_address)
    {}
       
    void set_motion_override(bool override)
    {
        do_write(MOTION_OVERRIDE_OFFSET, (int) override);
    }
    
    void set_motion_value(int motion_value)
    {
        do_write(MOTION_VALUE_OFFSET,motion_value);
    }
    
    int get_max_motion_value() 
    {
        return MAX_MOTION_VALUE;
    }
    int get_min_motion_value() 
    {
        return MIN_MOTION_VALUE;
    }
};


#endif /*DEINTERLACER_HPP_*/
