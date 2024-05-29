#ifndef SWITCH_HPP_
#define SWITCH_HPP_

#include "Vipcore.hpp"

class Switch : public Vipcore{
  public:

    static const int output_switch_offset = 2;
    static const int dout0_output_control = 3;
    static const int dout1_output_control = 4;
    static const int dout2_output_control = 5;
    static const int dout3_output_control = 6;
    static const int dout4_output_control = 7;
    static const int dout5_output_control = 8;
    static const int dout6_output_control = 9;
    static const int dout7_output_control = 10;
    static const int dout8_output_control = 11;
    static const int dout9_output_control = 12;
    static const int dout10_output_control = 13;
    static const int dout11_output_control = 14;
    static const int dout12_output_control = 15;


    Switch(long base_address) : Vipcore(base_address)
    {}

    /* DIAGNOSTIC/STATUS METHODS */
    /* todo: check ranges */
    void switch_channel(int output_channel_id, int onehot_channel_select)
    {
        do_write(dout0_output_control + output_channel_id, onehot_channel_select);
    }

    void set_output_switch()
    {
        do_write(output_switch_offset, 1);
    }

    /* END DIAGNOSTIC/STATUS METHODS */
};

#endif /*SWITCH_HPP_*/
