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
    this->PixelCount=Image.get_pixelCount();
    
    this->Red=static_cast<uint16_t*>(Image.RedChannel());
    this->Gr1=static_cast<uint16_t*>(Image.Gr1Channel());
    this->Gr2=static_cast<uint16_t*>(Image.Gr2Channel());
    this->Blu=static_cast<uint16_t*>(Image.BluChannel());

    Colored12Bit = new uint16_t[PixelCount*3];
}
int Debayer::NearestNeighbour()
{
    unsigned int indexrg=0,indexgb=0,clrindex = 0;
    
    for(unsigned int index = 0;  index < PixelCount/2; index++,clrindex+=2){
        if ((index/_width)%2==0){
            //get values of missing pixels at R and G1
            for(unsigned int j=0; j < 6; j+=3){
            Colored12Bit[clrindex*3 + j] = Red[indexrg];
            Colored12Bit[clrindex*3 + j+1] = (Gr1[indexrg] + Gr2[indexrg])/2;
            Colored12Bit[clrindex*3 + j+2] = Blu[indexrg];
            }
            indexrg++;
        }else{
            //get values of missing pixels at G2 and B
            for(unsigned int k = 0; k < 6; k+=3){
                Colored12Bit[clrindex*3 + k] = Red[indexgb];
                Colored12Bit[clrindex*3 + k+1] = (Gr1[indexgb]+Gr2[indexgb])/2;
                Colored12Bit[clrindex*3 + k+2] = Blu[indexgb];
            }
            indexgb++;
        }
    }
    return 0;
}