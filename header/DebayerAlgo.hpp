/* Copyright (C) 2019 Rohit Mundada
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * 
 */
#ifndef DEBAYER_ALGO_H
#define DEBAYER_ALGO_H

#include "Image.hpp"

class DebayerAlgo
{
private:
    // dimensions of image
    unsigned int _width, _pixelCount;

    // color channel data
    uint16_t *_redChannel;
    uint16_t *_gr1Channel;
    uint16_t *_gr2Channel;
    uint16_t *_bluChannel;

    // pixel data
    uint16_t *_imgData;

public:
    DebayerAlgo();

    DebayerAlgo(Image &image);

    ~DebayerAlgo();

    // Debayering Algorithm
    void NearestNeighbour();
};

#endif
