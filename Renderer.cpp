#include "Renderer.h"

Renderer* Renderer::instance;

Renderer::Renderer()
{
	tft.initR(INITR_BLACKTAB);
	tft.setRotation(3);
	tft.fillScreen(ST7735_BLACK);

	//Serial.print("Initializing SD card...");
	if(!SD.begin(SD_CS)) {
		//Serial.println("failed!");
		return;
	}
	//Serial.println("OK!");
}

Renderer::~Renderer()
{
}

Adafruit_ST7735* Renderer::Get()
{
	if(!instance)
		instance = new Renderer;
	return &(instance->tft);
}

//int16_t test[240] = {};

const void Renderer::drawBMP(uint8_t x, uint8_t y, Image img)
{
	if(!instance)
		instance = new Renderer;

	
	instance->tft.setAddrWindow(x, y, x + img.width - 1, y + img.height - 1);

	for (int i = 0; i < img.width * img.height; i++) { // For each pixel...
								  // Time to read more pixel data?
		//instance->tft.pushColor(test[i]);
	}
}



int Renderer::loadBMP(char* filename, Image& emptyImage)
{
	if(!instance)
		instance = new Renderer;
	

	File     bmpFile;
	int      bmpWidth, bmpHeight;   // W+H in pixels
	uint8_t  bmpDepth;              // Bit depth (currently must be 24)
	uint32_t bmpImageoffset;        // Start of image data in file
	uint32_t rowSize;               // Not always = bmpWidth; may have padding
	uint8_t  sdbuffer[3 * BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
	uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
	boolean  goodBmp = false;       // Set to true on valid header parse
	boolean  flip = true;        // BMP is stored bottom-to-top
	int      w, h, row, col;
	uint8_t  r, g, b;
	uint32_t pos = 0, startTime = millis();

	// Open requested file on SD card
	if ((bmpFile = SD.open(filename)) == NULL) {
		bmpFile.close();
		return 0;
	}
	int i = 0;
	// Parse BMP header
	if (read16(bmpFile) == 0x4D42) { // BMP signature
		(void)read32(bmpFile); //File size
		(void)read32(bmpFile); // Read & ignore creator bytes
		bmpImageoffset = read32(bmpFile); // Start of image data
		(void)read32(bmpFile); // Read DIB header

		bmpWidth = read32(bmpFile);
		bmpHeight = read32(bmpFile);
		if (read16(bmpFile) == 1) { // # planes -- must be '1'
			bmpDepth = read16(bmpFile); // bits per pixel
			if ((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

				goodBmp = true; // Supported BMP format -- proceed!

				// BMP rows are padded (if needed) to 4-byte boundary
				rowSize = (bmpWidth * 3 + 3) & ~3;

				// If bmpHeight is negative, image is in top-down order.
				// This is not canon but has been observed in the wild.
				if (bmpHeight < 0) {
					bmpHeight = -bmpHeight;
					flip = false;
				}

				// Crop area to be loaded
				w = bmpWidth;
				h = bmpHeight;
				emptyImage.width = w;
				emptyImage.height = h;
				//emptyImage.source = (uint16_t*)malloc(sizeof(uint16_t) * w * h);
			
				
				for (row = 0; row<h; row++) { // For each scanline...

											  // Seek to start of scan line.  It might seem labor-
											  // intensive to be doing this on every line, but this
											  // method covers a lot of gritty details like cropping
											  // and scanline padding.  Also, the seek only takes
											  // place if the file position actually needs to change
											  // (avoids a lot of cluster math in SD library).
					pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;

					if (bmpFile.position() != pos) { // Need seek?
						bmpFile.seek(pos);
						buffidx = sizeof(sdbuffer); // Force buffer reload
					}

					for (col = 0; col<w; col++) { // For each pixel...
												  // Time to read more pixel data?
						if (buffidx >= sizeof(sdbuffer)) { // Indeed
							bmpFile.read(sdbuffer, sizeof(sdbuffer));
							buffidx = 0; // Set index to beginning
						}

						// Convert pixel from BMP to TFT format, push to display
						b = sdbuffer[buffidx++];
						g = sdbuffer[buffidx++];
						r = sdbuffer[buffidx++];
						
						//test[i] = instance->tft.Color565(r, g, b);
					} // end pixel
				} // end scanline
			} // end goodBmp
			
		}
	}
	bmpFile.close();
	
	// File f = SD.open("test.t", FILE_WRITE);

	//write16(f, )

	//if (!goodBmp) return 0;


	return 1;
}

void Renderer::write16(File f, const uint16_t input) {
	f.write(((uint8_t *)&input)[0]);  // LSB
	f.write(((uint8_t *)&input)[1]);  // MSB
}


//Code from Adafruit_ST7735 library example
void Renderer::bmpDraw(char* filename, uint8_t x, uint8_t y) {
	File     bmpFile;
	int      bmpWidth, bmpHeight;   // W+H in pixels
	uint8_t  bmpDepth;              // Bit depth (currently must be 24)
	uint32_t bmpImageoffset;        // Start of image data in file
	uint32_t rowSize;               // Not always = bmpWidth; may have padding
	uint8_t  sdbuffer[3 * BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
	uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
	boolean  goodBmp = false;       // Set to true on valid header parse
	boolean  flip = true;        // BMP is stored bottom-to-top
	int      w, h, row, col;
	uint8_t  r, g, b;
	uint32_t pos = 0;

	if ((x >= instance->tft.width()) || (y >= instance->tft.height())) return;


	// Open requested file on SD card
	if ((bmpFile = SD.open(filename)) == NULL) {
		Serial.print("File not found");
		return;
	}


	// Parse BMP header
	if (read16(bmpFile) == 0x4D42) { // BMP signature
		(void)read32(bmpFile); //File size
		(void)read32(bmpFile); // Read & ignore creator bytes
		bmpImageoffset = read32(bmpFile); // Start of image data
		(void)read32(bmpFile); // Read DIB header

		bmpWidth = read32(bmpFile);
		bmpHeight = read32(bmpFile);
		if (read16(bmpFile) == 1) { // # planes -- must be '1'
			bmpDepth = read16(bmpFile); // bits per pixel
			if ((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

				goodBmp = true; // Supported BMP format -- proceed!

				// BMP rows are padded (if needed) to 4-byte boundary
				rowSize = (bmpWidth * 3 + 3) & ~3;

				// If bmpHeight is negative, image is in top-down order.
				// This is not canon but has been observed in the wild.
				if (bmpHeight < 0) {
					bmpHeight = -bmpHeight;
					flip = false;
				}

				// Crop area to be loaded
				w = bmpWidth;
				h = bmpHeight;

				// Set TFT address window to clipped image bounds
				instance->tft.setAddrWindow(x, y, x + w - 1, y + h - 1);

				int i = 0;
				for (row = 0; row<h; row++) { // For each scanline...

											  // Seek to start of scan line.  It might seem labor-
											  // intensive to be doing this on every line, but this
											  // method covers a lot of gritty details like cropping
											  // and scanline padding.  Also, the seek only takes
											  // place if the file position actually needs to change
											  // (avoids a lot of cluster math in SD library).
					pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;

					if (bmpFile.position() != pos) { // Need seek?
						bmpFile.seek(pos);
						buffidx = sizeof(sdbuffer); // Force buffer reload
					}

					for (col = 0; col<w; col++) { // For each pixel...
												  // Time to read more pixel data?
						if (buffidx >= sizeof(sdbuffer)) { // Indeed
							bmpFile.read(sdbuffer, sizeof(sdbuffer));
							buffidx = 0; // Set index to beginning
						}

						// Convert pixel from BMP to TFT format, push to display
						b = sdbuffer[buffidx++];
						g = sdbuffer[buffidx++];
						r = sdbuffer[buffidx++];

						instance->tft.pushColor(instance->tft.Color565(r, g, b));
					} // end pixel
				} // end scanline
			} // end goodBmp
		}
	}

	bmpFile.close();
	if (!goodBmp) Serial.println("BMP format not recognized.");
	Serial.begin(9600);
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t Renderer::read16(File f) {
	uint16_t result;
	((uint8_t *)&result)[0] = f.read(); // LSB
	((uint8_t *)&result)[1] = f.read(); // MSB
	return result;
}

uint32_t Renderer::read32(File f) {
	uint32_t result;
	((uint8_t *)&result)[0] = f.read(); // LSB
	((uint8_t *)&result)[1] = f.read();
	((uint8_t *)&result)[2] = f.read();
	((uint8_t *)&result)[3] = f.read(); // MSB
	return result;
}