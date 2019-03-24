#include "Image.h"


ImageProcessor::ImageProcessor( int _width, int _height, const std::string& RAWIMG) : _RAWIMG(RAWIMG)
{
    this->_width = _width;
    this->_height = _height;
    // all required counters
    _pixelCount= _width * _height;
    _byteCount= _width * _height * 3 / 2;
    
    _loadBuff = new uint8_t[_byteCount];
    _buff12Bit= new uint16_t[_pixelCount];
    _colored12Bit = new uint16_t[_pixelCount*3];
    input.open(_RAWIMG,std::ios::binary);
    
    if(input.fail()){
        std::cout<<"Failed to open file....Exiting program"<<std::endl;
        exit(1);
    }
    input.read(reinterpret_cast< char*>(_loadBuff),_byteCount);
    //extract 12 bit per pixel and store
    
    unsigned int j=0;
    for(unsigned int i = 0; i < _byteCount; i++){

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
ImageProcessor::~ImageProcessor()
{
    delete[] _loadBuff;
    delete[] _buff12Bit;
    delete[] _red,_gr1,_gr2,_blu;
    delete[] _red8,_gr18,_gr28,_blu8;
    delete[] _colored12Bit;
    delete[] _colored8Bit;
}

void ImageProcessor::SeperateChannels()
{
    _red = new uint16_t[_pixelCount/4];
    _gr1 = new uint16_t[_pixelCount/4];
    _gr2 = new uint16_t[_pixelCount/4];
    _blu = new uint16_t[_pixelCount/4];
    // to seperate 4 colour channels
    unsigned int rgcount=0,gbcount=0;

    for(unsigned int  counter = 0; counter < _pixelCount-1; counter += 2){
        if((counter/_width)%2==0){  // case for RGRGRGRGRG....
            
            _red[rgcount]=_buff12Bit[counter];
            _gr1[rgcount]=_buff12Bit[counter+1];
            
            rgcount++;

        }else{ //case for GBGBGBGBGB....
            
            _gr2[gbcount]=_buff12Bit[counter];
            _blu[gbcount]=_buff12Bit[counter+1];
            
            gbcount++;
        }
        
    }
    
}
void ImageProcessor::ExtractTileValues(int TileSize)
{
    for(unsigned int tile = 0; tile< _width*TileSize; tile+=_width)
    {
        for(unsigned int row = tile; row < tile+5; row++)
        {
            std::cout << (unsigned) _buff8Bit[row] << " ";
        }
        std::cout << std::endl;
    }
}
void ImageProcessor::ImageWriter(const std::string& location)
{
    bool grayscale=true;
    
    WriteChannel(grayscale,_red8,location + PGM_FILENAME_RED);
    WriteChannel(grayscale,_gr18,location + PGM_FILENAME_GR1);
    WriteChannel(grayscale,_gr28,location + PGM_FILENAME_GR2);
    WriteChannel(grayscale,_blu8,location + PGM_FILENAME_BLU);

    WriteChannel(!grayscale,_colored8Bit,location + PPM_FILENAME_COLOR);
}
void ImageProcessor::WriteChannel(bool grayscale,uint8_t* data,const std::string& fileName)
{
    
        std::ofstream pgmfile;

        pgmfile.open(fileName,std::ios::binary);
        if (pgmfile.fail()) 
        {
            throw("Can't open pgm file");
        }

        pgmfile << (grayscale ? "P2\n":"P3\n");
        pgmfile << (grayscale ? _width/2 :_width);
        pgmfile << " ";
        pgmfile << (grayscale ? _height/2 :_height);
        pgmfile << "\n255\n";

        unsigned long int length= (grayscale ? _pixelCount/4 : _pixelCount*3);

        for(unsigned long int write_index = 0; write_index < length; write_index++)
        {
            pgmfile<<(unsigned)(data[write_index])<<" ";
        }
        
        pgmfile.close();
    
}

void ImageProcessor::ConvertTo8Bit()
{
    _red8 = new uint8_t[_pixelCount];
    _gr18 = new uint8_t[_pixelCount];
    _gr28 = new uint8_t[_pixelCount];
    _blu8 = new uint8_t[_pixelCount];

    _colored8Bit = new uint8_t[_pixelCount*3];
    _buff8Bit = new uint8_t[_pixelCount];
    
    unsigned int choice=1;//change this for user input
    switch (choice){
        case 1:
            //this case is for converting to 8 bits by clipping the last 4 bits
            
            Clipper(_red,_red8,_pixelCount/4);
            Clipper(_gr1,_gr18,_pixelCount/4);
            Clipper(_gr2,_gr28,_pixelCount/4);
            Clipper(_blu,_blu8,_pixelCount/4);
            Clipper(_buff12Bit,_buff8Bit,_pixelCount);
            Clipper(_colored12Bit,_colored8Bit,_pixelCount*3);

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
void ImageProcessor::Clipper(uint16_t* data12Bit, uint8_t* data8Bit, unsigned int length)
{
    for(unsigned int index=0; index < length; index++)
    {
        data8Bit[index] = (data12Bit[index]>>4);
    }
}

