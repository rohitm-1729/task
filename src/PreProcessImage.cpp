#include "RAW2PGM.h"
using namespace std;

#define RAWIMG "../RAW_INPUT/input.raw12"

PreProcessImage::PreProcessImage( int _width, int _height) : _RAWIMG(RAWIMG)
{
    this->_width = _width;
    this->_height = _height;
    // all required counters
    _pixelCount= _width * _height;
    _byteCount= _width * _height * 3 / 2;

    _loadBuff = new uint8_t[_byteCount];
    _buff12Bit= new uint16_t[_pixelCount];

    red = new uint16_t[_pixelCount/4];
    gr1 = new uint16_t[_pixelCount/4];
    gr2 = new uint16_t[_pixelCount/4];
    blu = new uint16_t[_pixelCount/4];

    input.open(_RAWIMG,std::ios::binary);
    
    if(input.fail())
    {
        cout<<"Failed to open file....Exiting program"<<endl;
        exit(1);
    }
    input.read(reinterpret_cast< char*>(_loadBuff),_byteCount);
    //extract 12 bit per pixel and store
    
    unsigned long int j=0;
    for(unsigned long int i = 0; i < _byteCount; i++)
    {
        if(j%2==0){
            //first 8 bits of a complete element of _loadBuff
            _buff12Bit[j]=_loadBuff[i];
            //next 4 bits from _loadBuff[i+1]
            _buff12Bit[j]=_buff12Bit[j]<<4;
            _buff12Bit[j]=((_buff12Bit[j] | ((_loadBuff[i+1]>>4)&0x0F)));
            j++;
        }else{
            //first 4 bits from current element of _loadBuff
            _buff12Bit[j]=(_loadBuff[i] & 0x0F);
            //next 8 bits from next element of _loadBuff
            _buff12Bit[j]=_buff12Bit[j]<<8;
            _buff12Bit[j]=_buff12Bit[j]| _loadBuff[i+1];
            i++;
            j++;
        }
       
    }
    
    
}

int PreProcessImage::Seperate()
{
    // to seperate 4 colour channels
    unsigned long long int rgcount=0,gbcount=0;

    for(unsigned long long int  counter = 0; counter < _pixelCount-1; counter += 2){
        if((counter/_width)%2==0){  // case for RGRGRGRGRG....
            red[rgcount]=_buff12Bit[counter];
            gr1[rgcount]=_buff12Bit[counter+1];
            rgcount++;
        }else{ //case for GBGBGBGBGB....
            gr2[gbcount]=_buff12Bit[counter];
            blu[gbcount]=_buff12Bit[counter+1];
            gbcount++;
        }
    
    }
}

PreProcessImage::~PreProcessImage()
{
    delete[] _loadBuff;
    delete[] _buff12Bit;
    delete[] red,gr1,gr2,blu;
}

    