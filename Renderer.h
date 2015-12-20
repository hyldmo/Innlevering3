#ifndef _RENDERER_h
#define _RENDERER_h


#include <SD.h>

#include <avr/pgmspace.h>

#include <Adafruit_ST7735.h>


#define BUFFPIXEL 20

#define TFT_CS      8
#define TFT_RST     9  
#define TFT_DC      10

#define SD_CS 4



class Renderer
{
public:
	typedef struct
	{
		uint16_t source[1];
		uint8_t width;
		uint8_t height;
	} Image;

	static Adafruit_ST7735* Get();

	static void bmpDraw(char* filename, uint8_t x, uint8_t y);

	const static void drawBMP(uint8_t x, uint8_t y, Image img);
	static int loadBMP(char* filename, Image& emptyImage);

private:
	Renderer();
	~Renderer();

	Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
	static Renderer* instance;

	static uint16_t read16(File f);

	static uint32_t read32(File f);


	static void write16(File f, const uint16_t input);
};


#endif

