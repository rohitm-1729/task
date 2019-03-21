#ifndef RAW2PGM_H
#define RAW2PGM_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>

//used global variables for modification from a single place
#define RAWIMG "../RAW_INPUT/input.raw12"
#define PGMIMG "../PGM_OUT/"
#define PGM_FILENAME_RED "Red1.pgm"
#define PGM_FILENAME_GR1 "Green1.pgm"
#define PGM_FILENAME_GR2 "Green2.pgm"
#define PGM_FILENAME_BLU "Blue.pgm"
#define PPM_FILENAME_COL "Color.ppm"

using namespace std;

const int TILE_SIZE=5;

class PreProcessImage
{
private:
    ifstream input;
    const char* _RAWIMG;

    uint8_t *LoadBuff;
    uint16_t *Buff12Bit;
    uint16_t *Red,*Gr1,*Gr2,*Blu;

    unsigned int _width,_height,Byte_Count,PixelCount;
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
        return Byte_Count;
    }
    unsigned int get_pixelCount()
    {
        return PixelCount;
    }
    void* getBuff12Bit()
    {
        return Buff12Bit;
    }
    void* RedChannel()
    {
        return Red;
    }

    void* Gr1Channel()
    {
        return Gr1;
    }

    void* Gr2Channel()
    {
        return Gr2;
    }

    void* BluChannel()
    {
        return Blu;
    }
    
};
class Debayer
{
    private:
    // this class will debayer the raw12 img which is still 12-bit format
    unsigned int _width,PixelCount;
    uint16_t *Red,*Gr1,*Gr2,*Blu;
    uint16_t *Colored12Bit;

    public:
    Debayer();
    Debayer(PreProcessImage &Image);
    int NearestNeighbour();

    void* getColored()
    {
        return Colored12Bit;
    }
};
class WriteImage 
{
    private:

    unsigned int _width,_height,Byte_Count,PixelCount;

    uint16_t *Buff12Bit;
    uint8_t *Buff8Bit;

    uint8_t *Colored8Bit;
    uint16_t *Colored12Bit;

    uint16_t *Red,*Gr1,*Gr2,*Blu;
    uint8_t *Red8,*Gr18,*Gr28,*Blu8;

    ofstream pgmfile;
    ofstream ppmfile;

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