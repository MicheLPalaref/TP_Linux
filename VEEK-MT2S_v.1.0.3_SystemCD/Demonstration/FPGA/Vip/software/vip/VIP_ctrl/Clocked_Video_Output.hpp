#ifndef CLOCKED_VIDEO_OUTPUT_HPP_
#define CLOCKED_VIDEO_OUTPUT_HPP_

#include "Vipcore.hpp"

template<int NO_OF_MODES>
class Clocked_Video_Output : public Vipcore{
  public:

    /* ADDRESS OFFSETS */
    static const int fifo_usedw_addressoffset = 3; // updated for 9.1
    static const int video_matched_addressoffset = 4; // updated for 9.1
    static const int offsets_per_mode = 19;

    static const int interlaced_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 4;
    }

    static const int active_picture_width_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 5;
    }

    static const int active_picture_height_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 6;
    }

    static const int active_picture_width_f1_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 7;
    }

    static const int active_picture_height_f1_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 8;
    }

    static const int horizontal_front_porch_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 9;
    }

    static const int horizontal_sync_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 10;
    }

    static const int horizontal_blanking_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 11;
    }

    static const int vertical_front_porch_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 12;
    }

    static const int vertical_sync_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 13;
    }

    static const int vertical_blanking_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 14;
    }

    static const int vertical_front_porch_f0_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 15;
    }

    static const int veritcal_sync_f0_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 16;
    }

    static const int vertical_blanking_f0_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 17;
    }

    static const int active_picture_line_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 18;
    }

    static const int vertical_blank_rising_edge_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 19;
    }

    static const int field_rising_edge_line_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 20;
    }

    static const int field_falling_edge_line_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 21;
    }

    static const int valid_addressoffset(int mode)
    {
        return (offsets_per_mode * mode) + 22;
    }

    /* END OF ADDRESS OFFSETS */


    //CONSTRCUTOR
    Clocked_Video_Output(long base_address) : Vipcore(base_address)
    {}

    //TODO: Add object oriented interrupt support

    /* DIAGNOSTIC/STATUS METHODS */
    int get_output_fifo_usedw()
    {
        return do_read(fifo_usedw_addressoffset);
    }

    int get_video_matched()
    {
        return do_read(video_matched_addressoffset);
    }

    bool is_fifo_underflowed()
    {
        return (bool)(do_read(STATUS) & 0x04);
    }

    void clear_fifo_underflow()
    {
        return do_write(STATUS, 0x04);
    }

    /* END OF DIAGNOSTIC/STATUS METHODS */




    /* VIDEO MODE SETTING METHODS */

    void configure_modes(int no_of_modes, int (&mode_definition)[19][NO_OF_MODES]) {
        int output_mode;
        int offset;

        for(output_mode = 0; output_mode < no_of_modes; output_mode++)
        {
            int mode_base = (output_mode * offsets_per_mode) + 4;
            for(offset = 0; offset < offsets_per_mode; offset++)
            {
                do_write(mode_base + offset, mode_definition[offset][output_mode]);
            }
        }
    }

    //TODO: make this a bit easier for users perhaps some data structures this could be configured with
    // whatever this needs more abstraction from the register map than simple setters provide.

    void set_interlaced(int mode, bool interlaced)
    {
        do_write(interlaced_addressoffset(mode), (int)interlaced);
    }

    void set_active_picture_width(int mode, int width)
    {
        do_write(active_picture_width_addressoffset(mode), width);
    }

    void set_active_picture_height(int mode, int height)
    {
        do_write(active_picture_height_addressoffset(mode), height);
    }

    void set_active_picture_width_f1(int mode, int width)
    {
        do_write(active_picture_width_f1_addressoffset(mode), width);
    }

    void set_active_picture_height_f1(int mode, int height)
    {
        do_write(active_picture_width_f1_addressoffset(mode), height);
    }

    void set_horizontal_front_porch(int mode, int length)
    {
        do_write(horizontal_front_porch_addressoffset(mode), length);
    }

    void set_horizontal_sync(int mode, int length)
    {
        do_write(horizontal_sync_addressoffset(mode), length);
    }

    void set_horizontal_blanking(int mode, int length)
    {
        do_write(horizontal_blanking_addressoffset(mode), length);
    }

    void set_vertical_front_porch(int mode, int lines)
    {
        do_write(vertical_front_porch_addressoffset(mode), lines);
    }

    void set_vertical_sync(int mode, int lines)
    {
        do_write(vertical_sync_addressoffset(mode), lines);
    }

    void set_vertical_blanking(int mode, int lines)
    {
        do_write(vertical_blanking_addressoffset(mode), lines);
    }

    void set_vertical_front_porch_f0(int mode, int lines)
    {
        do_write(vertical_front_porch_f0_addressoffset(mode), lines);
    }

    void set_veritcal_sync_f0(int mode, int length)
    {
        do_write(veritcal_sync_f0_addressoffset(mode), length);
    }

    void set_vertical_blanking_f0(int mode, int lines)
    {
        do_write(vertical_blanking_f0_addressoffset(mode), lines);
    }

    void set_active_picture_line(int mode, int line)
    {
        do_write(active_picture_line_addressoffset(mode), line);
    }

    void set_vertical_blank_rising_edge(int mode, int line)
    {
        do_write(vertical_blank_rising_edge_addressoffset(mode), line);
    }

    void set_field_rising_edge_line(int mode, int line)
    {
        do_write(field_rising_edge_line_addressoffset(mode), line);
    }

    void set_valid(int mode, bool valid)
    {
        do_write(valid_addressoffset(mode), (int) valid);
    }

    /* END OF VIDEO MODE SETTING METHODS */


};

#endif /*CLOCKED_VIDEO_OUTPUT_HPP_*/
