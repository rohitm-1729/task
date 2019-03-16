#include "RAW2PGM.h"
using namespace std;

SepChannels::SepChannels()
{

}
SepChannels::SepChannels(PreProcessImage &image)
{
    this->_width=image._width;
    this->_height=image._height;

    this->PixelCount=image.PixelCount;
    this->Byte_Count=image.Byte_Count;

    Red = new uint16_t[PixelCount/4];
    Gr1 = new uint16_t[PixelCount/4];
    Gr2 = new uint16_t[PixelCount/4];
    Blu = new uint16_t[PixelCount/4];


}
int SepChannels::Seperate(PreProcessImage& image)
{
    // to seperate 4 colour channels
    unsigned long long int rgcount=0,gbcount=0;

    for(unsigned long long int  counter = 0; counter < PixelCount-1; counter += 2){
        if((counter/_width)%2==0){  // case for RGRGRGRGRG....
            Red[rgcount]=image.Buff12Bit[counter];
            Gr1[rgcount]=image.Buff12Bit[counter+1];
            rgcount++;
        }else{ //case for GBGBGBGBGB....
            Gr2[gbcount]=image.Buff12Bit[counter];
            Blu[gbcount]=image.Buff12Bit[counter+1];
            gbcount++;
        }
    
    }
}