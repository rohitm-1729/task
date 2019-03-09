#ifndef RAW2PGM_H
#define RAW2PGM_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>



#define PGM_FILENAME_RED "Red1.pgm"
#define PGM_FILENAME_GR1 "Green1.pgm"
#define PGM_FILENAME_GR2 "Green2.pgm"
#define PGM_FILENAME_BLU "Blue.pgm"
#define PPM_FILENAME_COLOR "Color.ppm"

using namespace std;


class RAW2PGM
{
private:
    std::ifstream input;
    uint8_t *LoadBuff;
    uint8_t *Buff8Bit;
    uint16_t *Buff12Bit;
    unsigned int _width,_height,Byte_Count,PixelCount;
    uint16_t *Red, *Gr1, *Gr2, *Blu, *Colored12Bit;
    uint8_t *Red8, *Gr18, *Gr28, *Blu8, *Colored8Bit;
    std::ofstream pgmfileRed,pgmfileGr1;
    std::ofstream pgmfileGr2,pgmfileBlu, ppmfileColor;
    
public:
    RAW2PGM(const char* rawfile,int width ,int _height);
    ~RAW2PGM();
    int SeperateChannels();
    int ExtractTileValues(int TILE_SIZE);
    int DebayerImage();
    int WriteChannelsPGM(const string directory);
};


#endif