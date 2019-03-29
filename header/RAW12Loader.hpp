#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include "Image.hpp"

class RAW12Loader
{
private:
    //input file for image
    const std::string _RAWIMG;
    std::ifstream _input;

    //image dimensions
    unsigned int _width,_height,_byteCount,_pixelCount;
    
    //pixel values in 12 bit format
    uint16_t *_imgData;

    //individual color channels
    uint16_t *_redChannel;
    uint16_t *_gr1Channel;
    uint16_t *_gr2Channel;
    uint16_t *_bluChannel;

    //buffer to helpload the image in imgData
    uint8_t *_loadBuff;

    
public:
    //construct the image object with all the required attributes

    RAW12Loader(Image& image, const std::string& _inputLoc);
    ~RAW12Loader();

    void LoadImage();
    //seperates individual channels (R,G1,G2,B) from the RAW12 input
    void SeperateChannels();

    //Prints the intensity values of the square tile of size =TILE_SIZE
    void ExtractTileValues(int TILE_SIZE);

    //Converts the 12Bit data to 8Bit data
    void ConvertTo8Bit();
    void Clipper(uint16_t* data12Bit, unsigned int length);

};

#endif