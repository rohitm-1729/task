#include "RAW2PGM.h"
using namespace std;

PreProcessImage::PreProcessImage( int _width, int _height) : _RAWIMG(RAWIMG)
{
    this->_width = _width;
    this->_height = _height;
    // all required counters
    PixelCount= _width * _height;
    Byte_Count= _width * _height * 3 / 2;

    LoadBuff = new uint8_t[Byte_Count];
    Buff12Bit= new uint16_t[PixelCount];

    Red = new uint16_t[PixelCount/4];
    Gr1 = new uint16_t[PixelCount/4];
    Gr2 = new uint16_t[PixelCount/4];
    Blu = new uint16_t[PixelCount/4];

    input.open(_RAWIMG,std::ios::binary);
    
    if(input.fail())
    {
        cout<<"Failed to open file....Exiting program"<<endl;
        exit(1);
    }
    input.read(reinterpret_cast< char*>(LoadBuff),Byte_Count);
    //extract 12 bit per pixel and store
    
    unsigned long int j=0;
    for(unsigned long int i = 0; i < Byte_Count; i++)
    {
        if(j%2==0){
            //first 8 bits of a complete element of LoadBuff
            Buff12Bit[j]=LoadBuff[i];
            //next 4 bits from LoadBuff[i+1]
            Buff12Bit[j]=Buff12Bit[j]<<4;
            Buff12Bit[j]=((Buff12Bit[j] | ((LoadBuff[i+1]>>4)&0x0F)));
            j++;
        }else{
            //first 4 bits from current element of LoadBuff
            Buff12Bit[j]=(LoadBuff[i] & 0x0F);
            //next 8 bits from next element of LoadBuff
            Buff12Bit[j]=Buff12Bit[j]<<8;
            Buff12Bit[j]=Buff12Bit[j]| LoadBuff[i+1];
            i++;
            j++;
        }
       
    }
    
    
}
PreProcessImage::~PreProcessImage()
{
    delete[] LoadBuff;
    delete[] Buff12Bit;
}
//Functions of the class SepChannels: 

// SepChannels::SepChannels()
// {

// }
// SepChannels::SepChannels(PreProcessImage &image)
// {
//     this->_width=image.get_width();
//     this->_height=image.get_height();

//     this->PixelCount=image.get_pixelCount();
//     this->Byte_Count=image.get_byteCount();

//     Red = new uint16_t[PixelCount/4];
//     Gr1 = new uint16_t[PixelCount/4];
//     Gr2 = new uint16_t[PixelCount/4];
//     Blu = new uint16_t[PixelCount/4];


// }
int PreProcessImage::Seperate()
{
    // to seperate 4 colour channels
    unsigned long long int rgcount=0,gbcount=0;

    for(unsigned long long int  counter = 0; counter < PixelCount-1; counter += 2){
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
}

    