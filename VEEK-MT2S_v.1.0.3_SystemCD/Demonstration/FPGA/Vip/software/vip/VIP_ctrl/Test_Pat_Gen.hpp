#ifndef TEST_PAT_GEN_HPP_
#define TEST_PAT_GEN_HPP_

#include "Vipcore.hpp"

class Test_Pat_Gen : public Vipcore
{
public:

    static const int OUT_WIDTH = 2;
    static const int OUT_HEIGHT = 3;


    Test_Pat_Gen(long base_address) : Vipcore(base_address)
    {}

    void set_output_size(int width, int height)
    {
        do_write(OUT_WIDTH, width);
        do_write(OUT_HEIGHT, height);
    }

};

#endif /*TEST_PAT_GEN_HPP_*/
