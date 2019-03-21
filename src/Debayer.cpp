//Function to Debayer Image using Nearest Neighbour Algorithm

#include "RAW2PGM.h"
using namespace std;

Debayer::Debayer()
{

}
Debayer::Debayer(PreProcessImage &Image)
{
    //get all values to the object of this class
    this->_width=Image.get_width();
    //this->_height=Image._height;
    this->_pixelCount=Image.get_pixelCount();
    
    this->red=static_cast<uint16_t*>(Image.RedChannel());
    this->gr1=static_cast<uint16_t*>(Image.Gr1Channel());
    this->gr2=static_cast<uint16_t*>(Image.Gr2Channel());
    this->blu=static_cast<uint16_t*>(Image.BluChannel());

    _colored12Bit = new uint16_t[_pixelCount*3];
}
int Debayer::NearestNeighbour()
{
    unsigned int indexrg=0,indexgb=0,clrindex = 0;
    
    for(unsigned int index = 0;  index < _pixelCount/2; index++,clrindex+=2){
        if ((index/_width)%2==0){
            //get values of missing pixels at R and G1
            for(unsigned int j=0; j < 6; j+=3){
            _colored12Bit[clrindex*3 + j] = red[indexrg];
            _colored12Bit[clrindex*3 + j+1] = (gr1[indexrg] + gr2[indexrg])/2;
            _colored12Bit[clrindex*3 + j+2] = blu[indexrg];
            }
            indexrg++;
        }else{
            //get values of missing pixels at G2 and B
            for(unsigned int k = 0; k < 6; k+=3){
                _colored12Bit[clrindex*3 + k] = red[indexgb];
                _colored12Bit[clrindex*3 + k+1] = (gr1[indexgb]+gr2[indexgb])/2;
                _colored12Bit[clrindex*3 + k+2] = blu[indexgb];
            }
            indexgb++;
        }
    }
    return 0;
}