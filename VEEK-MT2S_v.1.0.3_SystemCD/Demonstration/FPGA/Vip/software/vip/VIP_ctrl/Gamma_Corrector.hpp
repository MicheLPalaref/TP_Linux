#ifndef GAMMA_CORRECTOR_HPP_
#define GAMMA_CORRECTOR_HPP_

#include "Vipcore.hpp"

class Gamma_Corrector : public Vipcore{
  public:
  
    static int get_input_value_addressoffset(int input_value){
        return input_value+2;
    }
    
    Gamma_Corrector(long base_address) : Vipcore(base_address)
    {}
       
    void set_gamma_value(int input_value, int output_value){
        do_write(get_input_value_addressoffset(input_value),output_value);
    }
    
    int get_gamma_value(int input_value){
        return do_read(get_input_value_addressoffset(input_value));
    }  
};

#endif /*GAMMA_CORRECTOR_HPP_*/
