#include "RAW2PGM.h"
using namespace std;

To8Bit::To8Bit()
{

}
To8Bit::To8Bit(Debayer& Debayerimage,PreProcessImage& image)
{
    this->_width=image._width;
    this->_height=image._height;

    this->PixelCount=Debayerimage.PixelCount;

    this->Buff12Bit=image.Buff12Bit;

    this->Red=Debayerimage.Red;
    this->Gr1=Debayerimage.Gr1;
    this->Gr2=Debayerimage.Gr2;
    this->Blu=Debayerimage.Blu;

    this->Colored12Bit=Debayerimage.Colored12Bit;

    Red8 = new uint8_t[PixelCount];
    Gr18 = new uint8_t[PixelCount];
    Gr28 = new uint8_t[PixelCount];
    Blu8 = new uint8_t[PixelCount];

    Colored8Bit = new uint8_t[PixelCount*3];
    Buff8Bit = new uint8_t[PixelCount];
}
int To8Bit::ConvertTo8()
{
    unsigned long int choice=1;//change this for user input
    switch (choice){
        case 1:
            //this case is for converting to 8 bits by clipping the last 4 bits
            
            for(unsigned long int index = 0; index<PixelCount*3; index++){
                
                if(index<PixelCount/4){
                    Red8[index] = (Red[index] >> 4);
                    Gr18[index] = (Gr1[index] >> 4);
                    Gr28[index] = (Gr2[index] >> 4);
                    Blu8[index] = (Blu[index] >> 4);
                }
                //to convert 12Bit buffer to 8Bit for Square tile values
                if (index < PixelCount){
                    Buff8Bit[index] = (Buff12Bit[index]>>4);
                }
                
                // conversion for debayered image 
                Colored8Bit[index] = (Colored12Bit[index]>>4);
            }
            break;
        case 2:
            //this case is for converting to 8 bits using non linear curve 
            /* for(unsigned long int i = 0; i < pixelcount; i++)
            {
                
            } */
          
        default:
            break;
    }
    return 0;
}
int To8Bit::PrintIntensityVals()
{
    
    for(unsigned long int tile = 0; tile< _width*TILE_SIZE; tile+=_width)
    {
        for(unsigned long int row = tile; row < tile+5; row++)
        {
            cout<<(unsigned)Buff8Bit[row]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
