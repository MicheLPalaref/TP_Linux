#ifndef MIXER_HPP_
#define MIXER_HPP_

#include "Vipcore.hpp"




 /*Mixer II*/
#ifdef ALT_VIP_CL_MIXER_0_BASE

class Mixer : public Vipcore{
  public:

    static int get_layer_x_offset_offset(int layer)
    {
        return 8 + layer * 5;
    }

    static int get_layer_y_offset_offset(int layer)
    {
       return get_layer_x_offset_offset(layer) + 1;
    }

    static int get_layer_enabled_offset(int layer)
    {
        return get_layer_x_offset_offset(layer) + 2;
    }


    Mixer(long base_address) : Vipcore(base_address)
    {}

    void set_backgroud_size(int Width, int Height)
    {
        do_write(3,Width);
        do_write(4,Height);

    }

    void set_backgroud_color(alt_u16 R,alt_u16 G,alt_u16 B)
    {
        do_write(5,R);
        do_write(6,G);
        do_write(6,B);
    }


    void set_layer_enabled(int layer, bool enabled)
    {
        do_write(get_layer_enabled_offset(layer),(int)enabled);
    }


    void set_layer_position(int layer, int x, int y)
    {
        do_write(get_layer_x_offset_offset(layer),x);
        do_write(get_layer_y_offset_offset(layer),y);
    }
};
#endif /*Mixer II*/



/*Mixer*/
#ifdef ALT_VIP_MIX_0_BASE

class Mixer : public Vipcore{
 public:

   static int get_layer_x_offset_offset(int layer)
   {
       return 2 + ((layer-1) * 3);
   }

   static int get_layer_y_offset_offset(int layer)
   {
      return get_layer_x_offset_offset(layer) + 1;
   }

   static int get_layer_enabled_offset(int layer)
   {
       return get_layer_x_offset_offset(layer) + 2;
   }


   Mixer(long base_address) : Vipcore(base_address)
   {}

   void set_layer_enabled(int layer, bool enabled)
   {
       do_write(get_layer_enabled_offset(layer),(int)enabled);
   }

   void set_layer_enabled(int layer, int enabled)
   {
       do_write(get_layer_enabled_offset(layer),(int)enabled);
   }

   void set_layer_position(int layer, int x, int y)
   {
       do_write(get_layer_x_offset_offset(layer),x);
       do_write(get_layer_y_offset_offset(layer),y);
   }
};
#endif /*Mixer*/

#endif /*MIXER_HPP_*/

