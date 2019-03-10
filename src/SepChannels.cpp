#include "RAW2PGM.h"
using namespace std;

int RAW2PGM::SeperateChannels()
{
    Red = new uint16_t[PixelCount/4];
    Gr1 = new uint16_t[PixelCount/4];
    Gr2 = new uint16_t[PixelCount/4];
    Blu = new uint16_t[PixelCount/4];
    // to seperate 4 colour channels
    unsigned int rgcount=0,gbcount=0;

    for(unsigned int  counter = 0; counter < PixelCount-1; counter += 2){
        if((counter/_width)%2==0){  // case for RGRGRGRGRG....
            Red[rgcount]=Buff12Bit[counter];
            Gr1[rgcount]=Buff12Bit[counter+1];
            rgcount++;
        }else{ //case for GBGBGBGBGB....
            Gr2[gbcount]=Buff12Bit[counter];
            Blu[gbcount]=Buff12Bit[counter+1];
            gbcount++;
        }
        
    }
    return 0;
}