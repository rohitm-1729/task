#ifndef DEBAYER_ALGO_H
#define DEBAYER_ALGO_H

#include "Image.h"

class DebayerAlgo
{
private:
    
    //variables for object construction
    unsigned int _width,_pixelCount;
    uint16_t *_redChannel;
    uint16_t *_gr1Channel;
    uint16_t *_gr2Channel;
    uint16_t *_bluChannel;
    uint16_t *_imgData;

public:
    
    DebayerAlgo();
    DebayerAlgo(Image& image);

    void NearestNeighbour();

};

#endif