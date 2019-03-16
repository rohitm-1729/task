#ifndef RAW2PGM_H
#define RAW2PGM_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>


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
public:
    ifstream input;
    const char* _RAWIMG;

    uint8_t *LoadBuff;
    uint16_t *Buff12Bit;

    unsigned int _width,_height,Byte_Count,PixelCount;

    PreProcessImage();
    PreProcessImage(int width ,int height);
    ~PreProcessImage();
};
class SepChannels
{ 
    //this class will seperate individual channels
    public:
    uint16_t *Red,*Gr1,*Gr2,*Blu;
    unsigned int _width,_height,Byte_Count,PixelCount;
    
    SepChannels();
    SepChannels(PreProcessImage &image);

    int Seperate(PreProcessImage &image);

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
class Debayer : public SepChannels
{
    public:
    // this class will debayer the raw12 img which is still 12-bit format
    uint16_t *Colored12Bit;
    Debayer();
    Debayer(SepChannels &Sepimage);
    int NearestNeighbour();
};
class To8Bit : public Debayer
{
    public:
    //this class is used to convert all data to 8bits
    //and print intensity values of tiles
    uint16_t *Buff12Bit;
    uint8_t *Buff8Bit;

    uint8_t *Colored8Bit;

    uint8_t *Red8,*Gr18,*Gr28,*Blu8;

    To8Bit();
    To8Bit(Debayer& Debayerimage,PreProcessImage& image);

    int ConvertTo8();
    int PrintIntensityVals();
};
class WriteImage :  public To8Bit 
{
    public:

    ofstream pgmfile;
    ofstream ppmfile;

    WriteImage();
    WriteImage(To8Bit& Image8Bit);

    int WriteIndividual(ofstream& pgmfile, uint8_t *channel,  const string& directory, const string&  PGM_FILENAME);
    int WriteColor(ofstream& ppmfile, uint8_t *channel,  const string& directory,const string& PPM_FILENAME);
    int WriteBoth();
};

#endif