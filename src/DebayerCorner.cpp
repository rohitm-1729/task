#include "RAW2PGM.h"
using namespace std;


int RAW2PGM::Debayer_corner(uint16_t *Colored12Bit)
{
       //Colored12Bit = new uint16_t[PixelCount*3];
    for(unsigned int index = 0;  index < _width; index++){

        //pixel at R and pixel at G
        for(unsigned int j=0; j < 6; j+=3){
            Colored12Bit[index*3 + j] = Buff12Bit[index];
            Colored12Bit[index*3 + j+1] = (Buff12Bit[index + 1] + Buff12Bit[index + _width])/2;
            Colored12Bit[index*3 + j+2] = Buff12Bit[index + _width + 1];
        }
    }
    for(unsigned int index = 0, index2=1; index < PixelCount; index+=_width, index2 += _width){
        if(index/_width % 2 ==0){
            //R pixel in column
            Colored12Bit[index*3] = Buff12Bit[index];
            Colored12Bit[index*3+1] = (Buff12Bit[index + 1] + Buff12Bit[index + _width])/2;
            Colored12Bit[index*3+2] = Buff12Bit[index + _width + 1];
            }
        else{
            // G pixel in column
            Colored12Bit[index*3] = Buff12Bit[index - _width];
            Colored12Bit[index*3+1] = (Buff12Bit[index]+Buff12Bit[(index - _width) + 1])/2;
            Colored12Bit[index*3+2] = Buff12Bit[index + 1];
        }
        }

return 0;
}    
