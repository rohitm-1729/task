#ifndef RAW2PGM_H
#define RAW2PGM_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>

using namespace std;

const int TILE_SIZE=5;

class PreProcessImage
{
private:
    ifstream input;
    const char* _RAWIMG;

    uint8_t *_loadBuff;
    uint16_t *_buff12Bit;
    uint16_t *red,*gr1,*gr2,*blu;

    unsigned int _width,_height,_byteCount,_pixelCount;
public:
    PreProcessImage();
    PreProcessImage(int width ,int height);
    ~PreProcessImage();

    int Seperate();


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
    void* getBuff12Bit()
    {
        return _buff12Bit;
    }
    void* RedChannel()
    {
        return red;
    }

    void* Gr1Channel()
    {
        return gr1;
    }

    void* Gr2Channel()
    {
        return gr2;
    }

    void* BluChannel()
    {
        return blu;
    }
    
};
class Debayer
{
private:
    // this class will debayer the raw12 img which is still 12-bit format
    unsigned int _width,_pixelCount;
    uint16_t *red,*gr1,*gr2,*blu;
    uint16_t *_colored12Bit;

public:
    Debayer();
    Debayer(PreProcessImage &Image);
    int NearestNeighbour();

    void* getColored()
    {
        return _colored12Bit;
    }
};
class WriteImage 
{
private:

    unsigned int _width,_height,_byteCount,_pixelCount;

    uint16_t *_buff12Bit;
    uint8_t *_buff8Bit;

    uint8_t *_colored8Bit;
    uint16_t *_colored12Bit;

    uint16_t *red,*gr1,*gr2,*blu;
    uint8_t *red8,*gr18,*gr28,*blu8;

    ofstream pgmfile;
    ofstream ppmfile;

    const string PGM_FILENAME_RED = "Red1.pgm";
    const string PGM_FILENAME_GR1 = "Green1.pgm";
    const string PGM_FILENAME_GR2 = "Green2.pgm";
    const string PGM_FILENAME_BLU = "Blue.pgm";
    const string PPM_FILENAME_COL = "Color.ppm";
    

public:
    WriteImage();
    WriteImage(Debayer& Debayerimage,PreProcessImage& image);

    int ConvertTo8();
    int PrintIntensityVals();

    int WriteIndividual(ofstream& pgmfile, uint8_t *channel,  const string& directory, const string&  PGM_FILENAME);
    int WriteColor(ofstream& ppmfile, uint8_t *channel,  const string& directory,const string& PPM_FILENAME);
    int WriteBoth();
};

#endif