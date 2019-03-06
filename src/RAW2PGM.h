#ifndef RAW2PGM_H
#define RAW2PGM_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string.h>


#define TILE_SIZE 5
#define PGM_FILENAME_RED "Red1.pgm"
#define PGM_FILENAME_GR1 "Green1.pgm"
#define PGM_FILENAME_GR2 "Green2.pgm"
#define PGM_FILENAME_BLU "Blue.pgm"

using namespace std;


class RAW2PGM
{
private:
    std::ifstream input;
    uint8_t *LoadBuff;
    uint8_t *Buff8Bit;
    uint16_t *Buff12Bit;
    unsigned int width,height,Byte_Count,PixelCount;
    uint8_t *Red;
    uint8_t *Gr1;
    uint8_t *Gr2;
    uint8_t *Blu;
    std::ofstream pgmfileRed,pgmfileGr1;
    std::ofstream pgmfileGr2,pgmfileBlu;
    
public:
    RAW2PGM(const char* rawfile,int width ,int height);
    //~RAW2PGM();
    int SeperateChannels();
    int WriteChannelsPGM(const string directory);
};


#endif