/* Copyright (C) 2019 Rohit Mundada
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * 
 */

#include "DebayerAlgo.hpp"

DebayerAlgo::DebayerAlgo()
{
}

DebayerAlgo::DebayerAlgo(Image &img)
{
    // get dimensions
    _width = img.GetWidth();

    _pixelCount = img.GetPixelCount();

    // get channels
    _redChannel = img.RedChannel();
    _gr1Channel = img.Gr1Channel();
    _gr2Channel = img.Gr2Channel();
    _bluChannel = img.BluChannel();

    // get pixel data
    _imgData = img.GetData();
}

void DebayerAlgo::NearestNeighbour()
{    
    unsigned int indexrg = 0, indexgb = 0, clrindex = 0;

    for(unsigned int index = 0; index < _pixelCount / 2; index++, clrindex += 2)
    {
        if((index / _width) % 2 == 0)
        {
            // get values of missing pixels at R and G1
            for(unsigned int j = 0; j < 6; j += 3)
            {
                _imgData[clrindex * 3 + j]     = _redChannel[indexrg];
                _imgData[clrindex * 3 + j + 1] = (_gr1Channel[indexrg] + _gr2Channel[indexrg]) / 2;
                _imgData[clrindex * 3 + j + 2] = _bluChannel[indexrg];
            }

            indexrg++;
        }
        else
        {
            // get values of missing pixels at G2 and B

            for(unsigned int k = 0; k < 6; k += 3)
            {
                _imgData[clrindex * 3 + k]     = _redChannel[indexgb];
                _imgData[clrindex * 3 + k + 1] = (_gr1Channel[indexgb] + _gr2Channel[indexgb]) / 2;
                _imgData[clrindex * 3 + k + 2] = _bluChannel[indexgb];
            }

            indexgb++;
        }
    }
}

DebayerAlgo::~DebayerAlgo()
{
}