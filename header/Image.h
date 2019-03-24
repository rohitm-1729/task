#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>

#define PGM_FILENAME_RED "Red1.pgm"
#define PGM_FILENAME_GR1 "Green1.pgm"
#define PGM_FILENAME_GR2 "Green2.pgm"
#define PGM_FILENAME_BLU "Blue.pgm"
#define PPM_FILENAME_COLOR "Color.ppm"

class ImageProcessor
{
private:
    const std::string _RAWIMG;
    std::ifstream _input;

    unsigned int _width,_height,_byteCount,_pixelCount;
    
    uint8_t *_loadBuff;

    uint8_t *_buff8Bit;
    uint16_t *_buff12Bit;

    uint16_t *_red,*_gr1,*_gr2,*_blu;
    uint8_t *_red8,*_gr18,*_gr28,*_blu8;

    uint16_t *_colored12Bit;
    uint8_t  *_colored8Bit;
    
public:
    ImageProcessor(int _width ,int _height, const std::string& _inputLoc);
    ~ImageProcessor();

    void SeperateChannels();

    void ExtractTileValues(int TILE_SIZE);

    void ConvertTo8Bit();
    void Clipper(uint16_t* data12Bit, uint8_t* data8Bit, unsigned int length);

    void ImageWriter(const std::string& location);
    void WriteChannel(bool grayscale,uint8_t* data, const std::string& fileName);
    

    unsigned int get_width()
    {
        return _width;
    }
    unsigned int get_height()
    {
        return _height;
    }
    unsigned int get_byteCount()
    {
        return _byteCount;
    }
    unsigned int get_pixelCount()
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