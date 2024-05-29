#include <math.h>
#include <io.h>
#include "VFR_Graphics.hpp"


void VFRScreen::delay(unsigned int delay)
{
    for(unsigned int i=0; i < delay ; i++) {};
}


void VFRScreen::setPixel(int x, int y, int r, int g, int b)
{

	//Pixel address is found by the following formula :
	//getBaseAddress() +
	//my 'screen' is getXresolution() wide by getYresolution() high

	//so every row is getXresolution() pixels. After 2 pixels we 'waste' two bytes, so that gives getXresolution() x 4 pixel bytes 
	//which is 640 bytes per row
	

//	unsigned int y_offset = y * (getXresolution() * 3 + (int) ((float) getXresolution() / 5));
	unsigned int y_offset = y * getXresolution() * 4 ;
//	unsigned int x_offset = x*3 + ((int) ((float) x/2)) * 2;
	unsigned int x_offset = x*4;

	unsigned int address_offset = y_offset+x_offset;
	unsigned int word_aligned_address;
	unsigned int old_val;
	unsigned int new_val;

	unsigned int blue  = b & 0x000000FF;
	unsigned int green = g & 0x000000FF;
	unsigned int red   = r & 0x000000FF;
	unsigned int byte_address = address_offset %4;

	// Need to do writes on 32bit word boundaries.
	if (byte_address == 0 ) {

		// This is 32bit aligned, so straightforward :
		old_val = IORD(getBaseAddress() + address_offset, 0 );
		new_val = (old_val & 0xFF000000) | blue | green << 8 | red << 16;
		IOWR(getBaseAddress() + address_offset, 0, new_val );

	} else {

		// Get lower word address :
		word_aligned_address = address_offset & 0xFFFFFFFC;
		old_val = IORD(getBaseAddress() + word_aligned_address, 0 );

		// Need to mask off the lower bytes :
		if (byte_address == 1) {
			new_val = (old_val & 0x000000FF) | blue << 8 | green << 16 | red << 24;
		} else if (byte_address == 2) {
			new_val = (old_val & 0x0000FFFF) | blue << 16 | green << 24; // blue needed at next address
		} else if (byte_address == 3) {
			new_val = (old_val & 0x00FFFFFF) | blue << 24; // green & blue needed at next address
		}

		// Now write it :
		IOWR(getBaseAddress() + word_aligned_address, 0, new_val );


		// Now do the higher word if byte address is 2 or 3:

		// Get higher word address :
		word_aligned_address = (address_offset & 0xFFFFFFFC) + 4;
		old_val = IORD(getBaseAddress() + word_aligned_address, 0 );

		// Need to mask off the higher bytes :
		if (byte_address == 2) {
			new_val = (old_val & 0xFFFFFF00) | red ; // RG already written in last word
			IOWR(getBaseAddress() + word_aligned_address, 0, new_val );
		} else if (byte_address == 3) {
			new_val = (old_val & 0xFFFF0000) | red << 8 | green ; // R already written in last word
			IOWR(getBaseAddress() + word_aligned_address, 0, new_val );
		}
	}
}

void VFRScreen::drawLine (int x0, int y0, int x1, int y1, int r, int g, int b)
{
	int x_delta = x1-x0;
	int y_delta = y1-y0;

	int pixels = 0;
	int i;

	pixels = (int) sqrt( pow (float(y_delta), 2) + pow (float(x_delta),2));

	float x_inc = (float) x_delta / (float) pixels ;
	float y_inc = (float) y_delta / (float) pixels ;

	float current_x = x0;
	float current_y = y0;

	for (i=0; i< pixels; i++) {
		setPixel ((int) current_x, (int) current_y, r,g,b);
        current_x = current_x + x_inc;
        current_y = current_y + y_inc;
	}

}

// Define the ClearScreen method
void VFRScreen::clearScreen ()
{

	for (int y=0; y< getYresolution(); y++) {
		drawLine (0, y, getXresolution(), y, 0, 0, 0);
	}

}


// Define the DrawBorder method
void VFRScreen::drawBorder ()
{

	unsigned int brightness = 0;
	// Top/bottom border :
	for (int y=0; y< 10; y++) {
		brightness = 255 - (255 * y/10);
		drawLine (y, y, getXresolution()-y, y, brightness, brightness, brightness);
		drawLine (y, getYresolution()-y-1, getXresolution()-y, getYresolution()-y-1, brightness, brightness, brightness);
	}

	// Left/right border :
	for (int x=0; x< 10; x++) {
		brightness = 255 - (255 * x/10);
		drawLine (x, x, x, getYresolution()-x, brightness, brightness, brightness);
		drawLine (getXresolution()-x-1, x, getXresolution()-x-1, getYresolution()-x-1, brightness, brightness, brightness);
	}

}


void VFRScreen::drawTestPattern ()
{

	int y;
	int color_scale;

	int one_third  =     getYresolution()/3;
	int two_thirds = 2 * getYresolution()/3;

	for (y=0; y< one_third ; y++) {
		color_scale = 200 * y / one_third ;
		drawLine (0, y , getXresolution(), y,          0xff, color_scale, color_scale); //RGB
	}

	for (y= one_third; y < two_thirds; y++) {
		color_scale = 200 * (y - one_third) / one_third;
		drawLine (0, y , getXresolution(), y,   color_scale,        0xff, color_scale); //RGB
	}

	for (y=two_thirds; y< getYresolution(); y++) {
		color_scale =  200 * (y - two_thirds) / one_third;
		drawLine (0, y , getXresolution(), y,   color_scale, color_scale,        0xff); //RGB
	}

}


// Get the RGB value for a given pixel
unsigned int VFRScreen::getPixelColor(int x, int y)
{

	//Pixel address is found by the following formula :
	//getBaseAddress() +
	//my 'screen' is getXresolution() wide by getYresolution() high
	//so every row is getXresolution() pixels. After 5 pixels we 'waste' a byte, so that gives getXresolution() x 3 pixel bytes +getXresolution()/5 'waste' bytes
	//which is 640 bytes per row

//	unsigned int y_offset = y * (getXresolution() * 3 + (int) ((float) getXresolution() / 5));
//	unsigned int x_offset = x*3 + (int) ((float) x/5);
	unsigned int y_offset = y * getXresolution() * 4 ;
//	unsigned int x_offset = x*3 + ((int) ((float) x/2)) * 2;
	unsigned int x_offset = x*4;



	unsigned int address_offset = y_offset+x_offset;
	unsigned int word_aligned_address;
	unsigned int old_val;

	unsigned int r = 0;
	unsigned int g = 0;
	unsigned int b = 0;

	unsigned int byte_address = address_offset %4;

	// Need to do writes on 32bit word boundaries.
	if (byte_address == 0 ) {

		// This is 32bit aligned, so straightforward :
		old_val = IORD(getBaseAddress() + address_offset, 0 );
		r = ((old_val & 0x00FF0000) >> 16);
		g = ((old_val & 0x0000FF00) >> 8);
		b = ((old_val & 0x000000FF));

	} else {

		// Get lower word address :
		word_aligned_address = address_offset & 0xFFFFFFFC;
		old_val = IORD(getBaseAddress() + word_aligned_address, 0 );

		// Need to mask off the lower bytes :
		if (byte_address == 1) {
			r = ((old_val & 0xFF000000) >> 24);
			g = ((old_val & 0x00FF0000) >> 16);
			b = ((old_val & 0x0000FF00) >> 8);

		} else if (byte_address == 2) {
			g = ((old_val & 0xFF000000) >> 24);
			b = ((old_val & 0x00FF0000) >> 16);

		} else if (byte_address == 3) {
			b = ((old_val & 0xFF000000) >> 24);
		}

		// Now do the higher word if byte address is 2 or 3:

		// Get higher word address :
		word_aligned_address = (address_offset & 0xFFFFFFFC) + 4;
		old_val = IORD(getBaseAddress() + word_aligned_address, 0 );

		// Need to mask off the higher bytes :
		if (byte_address == 2) {
			r = (old_val & 0x000000FF);
		} else if (byte_address == 3) {
			r = ((old_val & 0x0000FF00) >> 8);
			g =  (old_val & 0x000000FF);
		}

	}

	return b | (g << 8) | (r << 16);

}



void VFRScreen::drawMandel ()
{

	float MinRe = -2.0;
	float MaxRe = 1.0;

	float MinIm = -1.2;
	float MaxIm = 1.2;
	float Re_factor = (MaxRe-MinRe)/(getXresolution()-1);
	float Im_factor = (MaxIm-MinIm)/(getYresolution()-1);
	unsigned MaxIterations = 100;
	unsigned n;
	unsigned final_n;
	unsigned int r;
	unsigned int g;
	unsigned int b;

	drawBorder();

	for(unsigned y = (unsigned) getYresolution()/2; y> 10; --y)
	{
	    float c_im = MaxIm - y*Im_factor;
	    for(unsigned x=10; x< (unsigned) getXresolution()-10; ++x)
	    {
	        float c_re = MinRe + x*Re_factor;
	        float Z_re = c_re, Z_im = c_im;

	        bool isInside = true;
	        for(n=0; n<MaxIterations; ++n)
			{
				float Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
				if(Z_re2 + Z_im2 > 4)
				{
					isInside = false;
					final_n = n;
				    break;
				}
				Z_im = 2*Z_re*Z_im + c_im;
				Z_re = Z_re2 - Z_im2 + c_re;
			}

	        if (isInside) {
				r = 0; g = 0; b = 0;
	        } else {

				if (final_n <11) {
					b = final_n*25; g = 0; r = 0;
				} else if (final_n <21) {
					b = 255; g = 25*(final_n-10); r = 0;
				} else if (final_n <40) {
					b = 255; g = 255; r = 50;
				} else if (final_n <60) {
					b = 255; g = 255; r = 150;
				} else if (final_n <100) {
					b = 255; g = 255; r = 255;
				}

	        }

			// For these co-ordinates the set is symmetrical about the Y axis :
	        setPixel (x, y, r, g, b);
	        setPixel (x, getYresolution() - y, r, g, b);

	    }
	}
}


void VFRScreen::colorCycle ()
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int rgb = 0;

	for (int y=0; y< getYresolution(); y++) {
		for (int x=0; x< getXresolution(); x++) {

			rgb = getPixelColor(x, y);
			r = (rgb & 0x00FF0000) >> 16;
			g = (rgb & 0x0000FF00) >> 8;
			b =  rgb & 0x000000FF;

			// Colour swap :
			setPixel (x, y, b, r, g);

		}
	}

	delay(5000000);
}




