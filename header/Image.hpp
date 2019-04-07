/* Copyright (C) 2019 Rohit Mundada
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * 
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string.h>

class Image
{
private:
    // image dimensions
    unsigned int _width;
    unsigned int _height;
    unsigned int _byteCount, _pixelCount;

    // pixel data
    uint16_t* _imgData;
    // channels
    uint16_t* _red;
    uint16_t* _gr1;
    uint16_t* _gr2;
    uint16_t* _blu;

public:
    Image() : _width(0), _height(0), _red(nullptr), _gr1(nullptr), _gr2(nullptr), _blu(nullptr)
    {
    }

    Image(unsigned int _width, unsigned int _height) :
        _width(_width),
        _height(_height),
        _red(nullptr),
        _gr1(nullptr),
        _gr2(nullptr),
        _blu(nullptr)
    {
        _pixelCount = _width * _height;
        _byteCount  = _width * _height * 3 / 2;
    }

    void SetRedChannel()
    {
        if(_red == nullptr)
        {
            _red = new uint16_t[_pixelCount / 4];
        }
    }
    void SetGr1Channel()
    {
        if(_gr1 == nullptr)
        {
            _gr1 = new uint16_t[_pixelCount / 4];
        }
    }
    void SetGr2Channel()
    {
        if(_gr2 == nullptr)
        {
            _gr2 = new uint16_t[_pixelCount / 4];
        }
    }
    void SetBluChannel()
    {
        if(_blu == nullptr)
        {
            _blu = new uint16_t[_pixelCount / 4];
        }
    }
    void SetImgData()
    {
        // for R,G,B combine
        _imgData = new uint16_t[_pixelCount * 3];
    }
    unsigned int GetPixelCount()
    {
        return _pixelCount;
    }
    unsigned int GetByteCount()
    {
        return _byteCount;
    }
    unsigned int GetWidth()
    {
        return _width;
    }
    unsigned int GetHeight()
    {
        return _height;
    }
    uint16_t* GetData()
    {
        return _imgData;
    }
    uint16_t* RedChannel()
    {
        return _red;
    }
    uint16_t* Gr1Channel()
    {
        return _gr1;
    }

    uint16_t* Gr2Channel()
    {
        return _gr2;
    }

    uint16_t* BluChannel()
    {
        return _blu;
    }

    ~Image()
    {
        delete[](uint16_t*) _imgData;
        delete[](uint16_t*) _red;
        delete[](uint16_t*) _gr1;
        delete[](uint16_t*) _gr2;
        delete[](uint16_t*) _blu;
    }
};

#endif