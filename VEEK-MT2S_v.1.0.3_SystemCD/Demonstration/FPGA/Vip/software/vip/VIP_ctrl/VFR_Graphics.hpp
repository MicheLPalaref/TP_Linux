#ifndef VFR_GRAPHICS__
#define VFR_GRAPHICS__

class VFRScreen
{
  private:
	int xres;
	int yres;
	int base_address;

  public:

	// Default constructor :
	VFRScreen(long cpuscreen_address, int cpuscreen_xres, int cpuscreen_yres)
	{
		base_address = cpuscreen_address;
		xres = cpuscreen_xres;
		yres = cpuscreen_yres;
	}

	// Simple methods :
	int getXresolution() {
		return xres;
	}

	int getYresolution() {
		return yres;
	}

	int getBaseAddress() {
		return base_address;
	}

	// Prototype definitions for more complex methods :
	unsigned int  getPixelColor(int x, int y);
	void clearScreen ();
	void drawTestPattern ();
	void setPixel(int x, int y, int r, int g, int b);
	void drawLine (int x0, int y0, int x1, int y1, int r, int g, int b);
	void drawMandel ();
	void drawBorder ();
	void delay (unsigned int delay);
	void colorCycle ();

};

#endif /*VFR_GRAPHICS__*/
