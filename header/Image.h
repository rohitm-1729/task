#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>

class Image
{
private:
    //image dimensions
    unsigned int _width;
    unsigned int _height;
    unsigned int _byteCount,_pixelCount;

    //pixel data
    void* _imgData;
    //channels
    void* _red;
    void* _gr1;
    void* _gr2;
    void* _blu;

public:
    Image():
    _width(0),
    _height(0),
    _red(nullptr),
    _gr1(nullptr),
    _gr2(nullptr),
    _blu(nullptr)
    {

    }
    Image(unsigned int _width, unsigned int _height):
    _width(_width),
    _height(_height),
    _red(nullptr),
    _gr1(nullptr),
    _gr2(nullptr),
    _blu(nullptr)
    {
        _pixelCount = _width * _height ;
        _byteCount = _width * _height * 3 / 2;
    }
    ~Image()
    {
        delete [] (uint16_t*)_imgData;
        delete [] (uint16_t*)_red;
        delete [] (uint16_t*)_gr1;
        delete [] (uint16_t*)_gr2;
        delete [] (uint16_t*)_blu;
    }
    

    void setRedChannel()
    {
        if(_red==nullptr)
        {
            _red = new uint16_t [_pixelCount/4];
        }
    }
    void setGr1Channel()
    {
        if(_gr1==nullptr)
        {
            _gr1 = new uint16_t [_pixelCount/4];
        }
    }
    void setGr2Channel()
    {
        if(_gr2==nullptr)
        {
            _gr2 = new uint16_t [_pixelCount/4];
        }
    }
    void setBluChannel()
    {
        if(_blu==nullptr)
        {
            _blu = new uint16_t [_pixelCount/4];
        }
    }
    void setImgData()
    {
        //for R,G,B combine
        _imgData = new uint16_t [_pixelCount * 3];
    }
    unsigned int getPixelCount()
    {
        
        return _pixelCount;
    }
    unsigned int getByteCount()
    {
        return _byteCount;
    }
    unsigned int getWidth()
    {
        return _width;
    }
    unsigned int getHeight()
    {
        return _height;
    }
    void* getData()
    {
        return _imgData;
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
};



// Image::~Image()
// {
// }




#endif