#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>

//modify filenames by changing the values of the following
#define PGM_FILENAME_RED "Red.pgm"
#define PGM_FILENAME_GR1 "Green1.pgm"
#define PGM_FILENAME_GR2 "Green2.pgm"
#define PGM_FILENAME_BLU "Blue.pgm"
#define PPM_FILENAME_COLOR "Color.ppm"

class ImageProcessor
{
private:
    //input file for image
    const std::string _RAWIMG;
    std::ifstream _input;

    //image dimensions
    unsigned int _width,_height,_byteCount,_pixelCount;
    
    //buffer to load the image
    uint8_t *_loadBuff;

    //buffers of 8 & 12 bit for processing
    uint8_t *_buff8Bit;
    uint16_t *_buff12Bit;

    //individual color channels
    uint16_t *_red,*_gr1,*_gr2,*_blu;
    uint8_t *_red8,*_gr18,*_gr28,*_blu8;

    //containers to load the debayered color data
    uint16_t *_colored12Bit;
    uint8_t  *_colored8Bit;
    
public:
    //construct the image object with all the required attributes

    ImageProcessor(int _width ,int _height, const std::string& _inputLoc);
    ~ImageProcessor();

    //seperates individual channels (R,G1,G2,B) from the RAW12 input
    void SeperateChannels();

    //Prints the intensity values of the square tile of size =TILE_SIZE
    void ExtractTileValues(int TILE_SIZE);

    //Converts the 12Bit data to 8Bit data
    void ConvertTo8Bit();
    void Clipper(uint16_t* data12Bit, uint8_t* data8Bit, unsigned int length);

    //Writing the data in pgm format for channels and ppm for debayered image
    void ImageWriter(const std::string& location);
    void WriteChannel(bool grayscale,uint8_t* data, const std::string& fileName);
    
    //access functions
    unsigned int get_width() const
    {
        return _width;
    }
    unsigned int get_height() const 
    {
        return _height;
    }
    unsigned int get_byteCount() const
    {
        return _byteCount;
    }
    unsigned int get_pixelCount() const
    {
        return _pixelCount;
    }

    void* RedChannel()
    {
        return _red;
    }
    void* Gr1Channel()
    {
        return _gr1;
    }

    void* Gr2Channel()
    {
        return _gr2;
    }

    void* BluChannel()
    {
        return _blu;
    }

    void* GetColored()
    {
        return _colored12Bit;
    }

};

#endif