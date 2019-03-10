#include "RAW2PGM.h"
using namespace std;

RAW2PGM::RAW2PGM( int _width, int _height) : _RAWIMG(RAWIMG)
{
    this->_width = _width;
    this->_height = _height;
    // all required counters
    PixelCount= _width * _height;
    Byte_Count= _width * _height * 3 / 2;
    
    LoadBuff = new uint8_t[Byte_Count];
    Buff12Bit= new uint16_t[PixelCount];

    input.open(_RAWIMG,std::ios::binary);
    
    if(input.fail()){
        cout<<"Failed to open file....Exiting program"<<endl;
        exit(1);
    }
    input.read(reinterpret_cast< char*>(LoadBuff),Byte_Count);
    //extract 12 bit per pixel and store
    
    unsigned int j=0;
    for(unsigned int i = 0; i < Byte_Count; i++){

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
RAW2PGM::~RAW2PGM()
{
    delete[] LoadBuff;
    delete[] Buff12Bit;
}

    