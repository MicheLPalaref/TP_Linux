#ifndef CLOCKED_VIDEO_INPUT_HPP_
#define CLOCKED_VIDEO_INPUT_HPP_

#include "Vipcore.hpp"

class Clocked_Video_Input : public Vipcore{
  public:

	static const int status_update_interrupt_bit = 1;
	static const int stable_video_interrupt_bit = 2;
	static const int fifo_usedw_addressoffset = 3; /* updated for 9.1 */
    static const int f0_sample_count_addressoffset = 4; /* updated for 9.1 */
    static const int f0_line_count_addressoffset = 5; /* updated for 9.1 */
    static const int f1_sample_count_addressoffset = 4; /* updated for 9.1  */
    static const int f1_line_count_addressoffset = 6; /* unchanged in 9.1 */

    Clocked_Video_Input(long base_address) : Vipcore(base_address)
    {}

    /* DIAGNOSTIC/STATUS METHODS */
    bool is_f0_sample_count_valid()
    {
        return (bool)(do_read(STATUS) & (1<<3));
    }

    bool is_f0_line_count_valid()
    {
        return (bool)(do_read(STATUS) & (1<<4));
    }

    bool is_f1_sample_count_valid()
    {
        return (bool)(do_read(STATUS) & (1<<5));
    }

    bool is_f1_line_count_valid()
    {
        return (bool)(do_read(STATUS) & (1<<6));
    }

    bool is_input_interlaced()
    {
        return (bool)(do_read(STATUS) & (1<<7));
    }

    bool is_input_stable()
    {
        return (bool)(do_read(STATUS) & (1<<8));
    }

    bool is_resolution_valid()
        {
            return (bool)(do_read(STATUS) & (1<<10));
        }

    bool is_fifo_overflowed()
    {
        return (bool)(do_read(STATUS) & (1<<9));
    }

    int get_input_fifo_usedw()
    {
        return do_read(fifo_usedw_addressoffset);
    }

    int get_f0_sample_count()
    {
        return do_read(f0_sample_count_addressoffset);
    }

    int get_f0_line_count()
    {
        return do_read(f0_line_count_addressoffset);
    }

    int get_f1_sample_count()
    {
        return do_read(f1_sample_count_addressoffset);
    }

    int get_f1_line_count()
    {
        return do_read(f1_line_count_addressoffset);
    }

    void clear_fifo_overflow()
    {
        return do_write(STATUS, 0x200);
    }

    /* END DIAGNOSTIC/STATUS METHODS */
};

#endif /*CLOCKED_VIDEO_INPUT_HPP_*/
