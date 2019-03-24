//Function to Debayer Image using Nearest Neighbour Algorithm

#include "Debayer.h"

Debayer::Debayer()
{

}
Debayer::Debayer(ImageProcessor &image)
{
    //get all values to the object of this class
    
    _width=image.get_width();

    _pixelCount=image.get_pixelCount();
    
    _red=static_cast<uint16_t*>(image.RedChannel());
    _gr1=static_cast<uint16_t*>(image.Gr1Channel());
    _gr2=static_cast<uint16_t*>(image.Gr2Channel());
    _blu=static_cast<uint16_t*>(image.BluChannel());

    _colored12Bit=static_cast<uint16_t*>(image.GetColored());
   
}
void Debayer::NearestNeighbour ()
{
    unsigned int indexrg=0, indexgb=0, clrindex = 0;
    
    for(unsigned int index = 0;  index < _pixelCount/2; index++,clrindex+=2){
        if ((index/_width)%2==0){
            //get values of missing pixels at R and G1
            for(unsigned int j=0; j < 6; j+=3){
            _colored12Bit[clrindex*3 + j] = _red[indexrg];
            _colored12Bit[clrindex*3 + j+1] = (_gr1[indexrg] + _gr2[indexrg])/2;
            _colored12Bit[clrindex*3 + j+2] = _blu[indexrg];
            }
            indexrg++;
        }else{
            //get values of missing pixels at G2 and B
            for(unsigned int k = 0; k < 6; k+=3){
                _colored12Bit[clrindex*3 + k] = _red[indexgb];
                _colored12Bit[clrindex*3 + k+1] = (_gr1[indexgb]+_gr2[indexgb])/2;
                _colored12Bit[clrindex*3 + k+2] = _blu[indexgb];
            }
            indexgb++;
        }
    
    }
}