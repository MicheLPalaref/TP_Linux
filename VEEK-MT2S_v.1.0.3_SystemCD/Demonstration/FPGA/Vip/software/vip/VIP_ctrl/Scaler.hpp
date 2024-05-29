#ifndef SCALER_HPP_
#define SCALER_HPP_

#include "Vipcore.hpp"

template<int H_TAPS, int V_TAPS>
class Scaler : public Vipcore
{
public:

	    static const int OUT_WIDTH = 3;
	    static const int OUT_HEIGHT = 4;
	    static const int H_COEFF_BANK_WRITE_ADDRESS = 8;
	    static const int H_COEFF_BANK_READ_ADDRESS = 9;
	    static const int V_COEFF_BANK_WRITE_ADDRESS = 10;
	    static const int V_COEFF_BANK_READ_ADDRESS = 11;
	    static const int H_TAP_DATA_BEGIN = 12;
	    static const int H_PHASE = H_TAP_DATA_BEGIN + H_TAPS;
	    static const int V_TAP_DATA_BEGIN = H_PHASE + 1;
	    static const int V_PHASE = V_TAP_DATA_BEGIN + V_TAPS;



    Scaler(long base_address, int h_phases, int v_phases)
            : Vipcore(base_address), h_phases(h_phases), v_phases(v_phases) 
    {}

    void set_output_size(int width, int height)
    {
        the_width = width;
        the_height = height;
        do_write(OUT_WIDTH, width);
        do_write(OUT_HEIGHT, height);
    }

    int get_output_width()
    {
        return the_width;
    }
    int get_output_height()
    {
        return the_height;
    }

    void set_h_write_bank(int n)
    {
        do_write(H_COEFF_BANK_WRITE_ADDRESS, n);
    }
    void set_h_read_bank(int n)
    {
        do_write(H_COEFF_BANK_READ_ADDRESS, n);
    }
    void set_v_write_bank(int n)
    {
        do_write(V_COEFF_BANK_WRITE_ADDRESS, n);
    }
    void set_v_read_bank(int n)
    {
        do_write(V_COEFF_BANK_READ_ADDRESS, n);
    }

    void write_h_coeffs(const int coeffs[][H_TAPS])
    {
        for(int i=0; i < h_phases; i++)
        {
            for(int j=0; j < H_TAPS; j++)
            {
                do_write(H_TAP_DATA_BEGIN + j, coeffs[i][j]);
            }
            do_write(H_PHASE, i);
        }
    }

private:
    int h_phases;
    int v_phases;
    int the_width;
    int the_height;
    
};

#endif /*SCALER_HPP_*/
