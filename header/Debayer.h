#ifndef DEBAYER_H
#define DEBAYER_H


#include "Image.h"
class Debayer
{
private:
    
    unsigned int _width,_pixelCount;
    uint16_t *_red,*_gr1,*_gr2,*_blu;
    uint16_t *_colored12Bit;

public:
    
    Debayer();
    Debayer(ImageProcessor& image);
    void NearestNeighbour();

};

#endif