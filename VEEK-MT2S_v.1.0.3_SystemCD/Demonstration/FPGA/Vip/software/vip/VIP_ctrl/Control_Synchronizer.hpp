#ifndef CONTROL_SYNCHRONIZER_HPP_
#define CONTROL_SYNCHRONIZER_HPP_

#include "Vipcore.hpp"

class Control_Synchronizer : public Vipcore{
  public:

    static const int interrupt_addressoffset = 2;
    static const int disable_trigger_addressoffset = 3;
    static const int number_of_writes_addressoffset = 4;

    static const int address0 = 5;
    static const int word0 = 6;

    static const int address1 = 7;
    static const int word1 = 8;

    static const int address2 = 9;
    static const int word2 = 10;

    static const int address3 = 11;
    static const int word3 = 12;

    static const int address4 = 13;
    static const int word4 = 14;

    static const int address5 = 15;
    static const int word5 = 16;

    static const int address6 = 17;
    static const int word6 = 18;

    static const int address7 = 19;
    static const int word7 = 20;

    static const int address8 = 21;
    static const int word8 = 22;

    static const int address9 = 23;
    static const int word9 = 24;

    Control_Synchronizer(long base_address, long irq_number=-1, volatile EventQueue* event_queue=NULL)
                : Vipcore(base_address, irq_number, event_queue)
        {
        }

    /* DIAGNOSTIC/STATUS METHODS */

    void set_number_of_writes(int writes)
    {
        do_write(number_of_writes_addressoffset, writes);

    }

    // Set up a write of "write_data" to "write_address" for write number "write_number" :
    void setup_write(int write_number, int write_address, int write_data)
    {
        do_write(address0 + write_number*2, write_address);
        do_write(word0    + write_number*2, write_data);
    }

    void enable_trigger()
    {
        do_write(disable_trigger_addressoffset, 0);
    }

    void disable_trigger()
    {
        do_write(disable_trigger_addressoffset, 1);
    }

    int interrupt_triggered()
    {
    	 return do_read(interrupt_addressoffset);
    }

    void clear_interrupt()
    {
//        do_write(interrupt_addressoffset, 0);
//        do_write(interrupt_addressoffset, -1);
        do_write(interrupt_addressoffset, 1<<1);
    }

//    void set_interrupt()
//    {
//        do_write(interrupt_addressoffset, 1);
//    }


    /* END DIAGNOSTIC/STATUS METHODS */
};

#endif /*FRAME_READER_HPP_*/
