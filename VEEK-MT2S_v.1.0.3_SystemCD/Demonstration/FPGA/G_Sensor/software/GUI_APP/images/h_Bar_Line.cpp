#include "gimp_bmp.h"

#if 0

const struct {
    unsigned int width;
    unsigned int height;
    unsigned int bytes_per_pixel; /* 3:RGB, 4:RGBA */
    unsigned char	 pixel_data[4 * 36 * 3 + 1];
}h_Bar_Line = {
4, 36, 3, 
#endif



unsigned char h_Bar_Line_data[] = {
0x56, 0xA6, 0x05, 0x3C, 0x8C, 0x00, 0x3D, 0x99, 0x00, 0x58, 0xB4, 0x09, 0x68, 0xB8, 0x17, 0x4B, 0x9B, 0x00, 0x46, 0xA2, 
0x00, 0x65, 0xC1, 0x16, 0x7D, 0xBB, 0x0E, 0x5E, 0x9C, 0x00, 0x5E, 0xAA, 0x00, 0x7C, 0xC8, 0x0E, 0x7E, 0xBC, 0x0F, 0x65, 
0xA3, 0x00, 0x63, 0xAF, 0x00, 0x83, 0xCF, 0x15, 0x86, 0xBC, 0x0E, 0x6D, 0xA3, 0x00, 0x69, 0xAE, 0x00, 0x8A, 0xCF, 0x10, 
0x88, 0xBE, 0x10, 0x67, 0x9D, 0x00, 0x6A, 0xAF, 0x00, 0x8C, 0xD1, 0x12, 0x8F, 0xC0, 0x0F, 0x71, 0xA2, 0x00, 0x6D, 0xAE, 
0x00, 0x90, 0xD1, 0x11, 0x8F, 0xC0, 0x0F, 0x71, 0xA2, 0x00, 0x6E, 0xAF, 0x00, 0x94, 0xD5, 0x15, 0x92, 0xC3, 0x10, 0x6F, 
0xA0, 0x00, 0x6F, 0xAE, 0x00, 0x93, 0xD2, 0x12, 0x8E, 0xBF, 0x0C, 0x73, 0xA4, 0x00, 0x70, 0xAF, 0x00, 0x91, 0xD0, 0x10, 
0x92, 0xBE, 0x11, 0x73, 0x9F, 0x00, 0x76, 0xB2, 0x00, 0x96, 0xD2, 0x10, 0x8D, 0xB9, 0x0C, 0x72, 0x9E, 0x00, 0x76, 0xB2, 
0x00, 0x96, 0xD2, 0x10, 0x90, 0xBD, 0x0B, 0x72, 0x9F, 0x00, 0x76, 0xAF, 0x00, 0x98, 0xD1, 0x10, 0x96, 0xC3, 0x11, 0x76, 
0xA3, 0x00, 0x76, 0xAF, 0x00, 0x9B, 0xD4, 0x13, 0x92, 0xC2, 0x14, 0x73, 0xA3, 0x00, 0x72, 0xAE, 0x00, 0x97, 0xD3, 0x13, 
0x88, 0xB8, 0x0A, 0x6B, 0x9B, 0x00, 0x72, 0xAE, 0x00, 0x95, 0xD1, 0x11, 0x8B, 0xB7, 0x0C, 0x71, 0x9D, 0x00, 0x76, 0xAE, 
0x00, 0x9C, 0xD4, 0x13, 0x8D, 0xB9, 0x0E, 0x76, 0xA2, 0x00, 0x78, 0xB0, 0x00, 0x97, 0xCF, 0x0E, 0x99, 0xBF, 0x10, 0x79, 
0x9F, 0x00, 0x75, 0xAE, 0x00, 0x95, 0xCE, 0x0F, 0x96, 0xBC, 0x0D, 0x7B, 0xA1, 0x00, 0x76, 0xAF, 0x00, 0x99, 0xD2, 0x13, 
0x8F, 0xB9, 0x0F, 0x74, 0x9E, 0x00, 0x78, 0xAF, 0x00, 0x9A, 0xD1, 0x13, 0x8E, 0xB8, 0x0E, 0x71, 0x9B, 0x00, 0x78, 0xAF, 
0x00, 0x98, 0xCF, 0x11, 0x8F, 0xB6, 0x0B, 0x75, 0x9C, 0x00, 0x74, 0xB0, 0x00, 0x97, 0xD3, 0x11, 0x94, 0xBB, 0x10, 0x75, 
0x9C, 0x00, 0x75, 0xB1, 0x00, 0x99, 0xD5, 0x13, 0x95, 0xC2, 0x10, 0x76, 0xA3, 0x00, 0x78, 0xB1, 0x00, 0x99, 0xD2, 0x13, 
0x91, 0xBE, 0x0C, 0x75, 0xA2, 0x00, 0x74, 0xAD, 0x00, 0x97, 0xD0, 0x11, 0x8E, 0xBC, 0x11, 0x6E, 0x9C, 0x00, 0x73, 0xAF, 
0x00, 0x95, 0xD1, 0x11, 0x89, 0xB7, 0x0C, 0x70, 0x9E, 0x00, 0x76, 0xB2, 0x00, 0x95, 0xD1, 0x11, 0x8E, 0xB5, 0x0C, 0x74, 
0x9B, 0x00, 0x73, 0xB0, 0x00, 0x94, 0xD1, 0x11, 0x92, 0xB9, 0x10, 0x76, 0x9D, 0x00, 0x75, 0xB2, 0x00, 0x93, 0xD0, 0x10, 
0x91, 0xB8, 0x0F, 0x78, 0x9F, 0x00, 0x6E, 0xB1, 0x00, 0x8F, 0xD2, 0x13, 0x8B, 0xB2, 0x09, 0x72, 0x99, 0x00, 0x6C, 0xAF, 
0x00, 0x8A, 0xCD, 0x0E, 0x85, 0xB6, 0x0D, 0x6B, 0x9C, 0x00, 0x65, 0xAD, 0x00, 0x83, 0xCB, 0x0F, 0x87, 0xB8, 0x0F, 0x68, 
0x99, 0x00, 0x67, 0xAF, 0x00, 0x85, 0xCD, 0x11, 0x7C, 0xBA, 0x0D, 0x62, 0xA0, 0x00, 0x65, 0xB0, 0x00, 0x84, 0xCF, 0x12, 
0x7B, 0xB9, 0x0C, 0x5F, 0x9D, 0x00, 0x60, 0xAB, 0x00, 0x81, 0xCC, 0x0F, 0x00
};

gimp_image_struct h_Bar_Line = {4, 36, 3, h_Bar_Line_data};
