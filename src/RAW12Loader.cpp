#include "RAW12Loader.hpp"


RAW12Loader::RAW12Loader( Image& image, const std::string& RAWIMG) : _RAWIMG(RAWIMG)
{
    //dimensions
    _width = image.getWidth();
    _height = image.getHeight();

    _pixelCount = image.getPixelCount();
    _byteCount = image.getByteCount();
    
    //get image data
    _imgData =  (image.getData());

    _redChannel =  (image.RedChannel());
    _gr1Channel =  (image.Gr1Channel());
    _gr2Channel =  (image.Gr2Channel());
    _bluChannel =  (image.BluChannel()); 
    
    //helper buffer
    _loadBuff = new uint8_t[_byteCount];

    _input.open(_RAWIMG,std::ios::binary);
    
    if(_input.fail()){
        std::cout << "Failed to open file....Exiting program" << std::endl;
        exit(1);
    }
    _input.read(reinterpret_cast< char*>(_loadBuff),_byteCount);
    //extract 12 bit per pixel and store
    
     unsigned int j=0;
    for(unsigned int i = 0; i < _byteCount; i++){

        if(j%2==0)
        {
            //first 8 bits of a complete element of _loadBuff
            _imgData[j] = _loadBuff[i];
            //next 4 bits from _loadBuff[i+1]
            _imgData[j] = _imgData[j]<<4;
            _imgData[j] = ((_imgData[j] | ((_loadBuff[i+1]>>4)&0x0F)));
            //tried swapping bytes ,doesn't work for this data
            //_imgData[j]=(_imgData[j] >> 8 | _imgData[j] <<8);

            j++;
        }else
        {
            //first 4 bits from current element of _loadBuff
            _imgData[j] = (_loadBuff[i] & 0x0F);
            //next 8 bits from next element of _loadBuff
            _imgData[j] = _imgData[j]<<8;
            _imgData[j] = _imgData[j]| _loadBuff[i+1];
            
            //tried swapping bytes ,doesn't work for this data
            //_imgData[j]=(_imgData[j] >> 8 | _imgData[j] <<8);

            i++;
            j++;
        }
       
    }
}

void RAW12Loader::SeperateChannels()
{
    unsigned int rgcount=0,gbcount=0;

    for(unsigned int  counter = 0; counter < _pixelCount-1; counter += 2)
    {
        if((counter/_width)%2==0){  // case for RGRGRGRGRG....
            
            _redChannel[rgcount] = _imgData[counter];
            _gr1Channel[rgcount] = _imgData[counter+1];
            
            rgcount++;

        }else{ //case for GBGBGBGBGB....
            
            _gr2Channel[gbcount] = _imgData[counter];
            _bluChannel[gbcount] = _imgData[counter+1];
            
            gbcount++;
        }
        
    }
    
}


void RAW12Loader::ConvertTo8Bit()
{
    unsigned int choice=1;//change this for user input
    switch (choice){
        case 1:
            //this case is for converting to 8 bits by clipping the last 4 bits
            
            Clipper(_redChannel,_pixelCount/4);
            Clipper(_gr1Channel,_pixelCount/4);
            Clipper(_gr2Channel,_pixelCount/4);
            Clipper(_bluChannel,_pixelCount/4);
            Clipper(_imgData,_pixelCount);
            break;

        case 2:
            //this case is for converting to 8 bits using non linear curve 
            /* for(unsigned int i = 0; i < pixelcount; i++)
            {
                
            } */
          
        default:
            break;
    }
}
void RAW12Loader::Clipper(uint16_t* data,unsigned int length)
{
    for(unsigned int index=0; index < length; index++)
    {
        data[index] = (data[index]>>4);
    }
}

void RAW12Loader::ExtractTileValues(int TileSize)
{
    for(unsigned int tile = 0; tile< _width*TileSize; tile+=_width)
    {
        for(unsigned int row = tile; row < tile+5; row++)
        {
            std::cout << (unsigned) _imgData[row] << " ";
        }
        std::cout << std::endl;
    }
}
RAW12Loader::~RAW12Loader()
{

}