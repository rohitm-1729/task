#include "RAW12Loader.hpp"

RAW12Loader::RAW12Loader(Image& img, const std::string& RAWIMG) : _RAWIMG(RAWIMG)
{
    // dimensions
    _width  = img.getWidth();
    _height = img.getHeight();

    _pixelCount = img.getPixelCount();
    _byteCount  = img.getByteCount();

    // get image data
    _imgData = img.getData();

    _redChannel = img.RedChannel();
    _gr1Channel = img.Gr1Channel();
    _gr2Channel = img.Gr2Channel();
    _bluChannel = img.BluChannel();

    // helper buffer
    _loadBuff = new uint8_t[_byteCount];

    _input.open(_RAWIMG, std::ios::binary);

    if(_input.fail())
    {
        std::cout << "Failed to open file....Exiting program" << std::endl;
        exit(1);
    }

    _input.read(reinterpret_cast<char*>(_loadBuff), _byteCount);
}

void RAW12Loader::LoadSensels()
{
    // extracting 12 bit per pixel for general usage
    for(unsigned int i = 0, j = 0; i < _byteCount; i++)
    {
        if(j % 2 == 0)
        {
            // first 8 bits of a complete element of _loadBuff
            _imgData[j] = _loadBuff[i];

            // next 4 bits from _loadBuff[i+1]
            _imgData[j] = _imgData[j] << 4;
            _imgData[j] = ((_imgData[j] |
                          ((_loadBuff[i + 1] >> 4) & 0x0F)));

            j++;
        }
        else
        {
            // first 4 bits from current element of _loadBuff
            _imgData[j] = (_loadBuff[i] & 0x0F);

            // next 8 bits from next element of _loadBuff
            _imgData[j] = _imgData[j] << 8;
            _imgData[j] = _imgData[j] | _loadBuff[i + 1];

            i++;
            j++;
        }
    }
}

void RAW12Loader::SwapEndianness()
{
    for(unsigned int i = 0; i < _byteCount - 3; i += 3)
    {
        // swap every two bytes of input data
        std::swap(_loadBuff[i], _loadBuff[i + 2]);
        std::swap(_loadBuff[i + 1], _loadBuff[i + 3]);

        // swap 12Bit sensel data
        //_imgData[i] = (_imgData[i] >> 8 | _imgData[i] <<8);
    }
}

void RAW12Loader::SeperateChannels()
{
    unsigned int rgcount = 0, gbcount = 0;

    for(unsigned int counter = 0; counter < _pixelCount - 1; counter += 2)
    {
        if((counter / _width) % 2 == 0)
        { // case for RGRGRGRGRG....

            _redChannel[rgcount] = _imgData[counter];
            _gr1Channel[rgcount] = _imgData[counter + 1];

            rgcount++;
        }
        else
        { // case for GBGBGBGBGB....

            _gr2Channel[gbcount] = _imgData[counter];
            _bluChannel[gbcount] = _imgData[counter + 1];

            gbcount++;
        }
    }
}

void RAW12Loader::ConvertTo8Bit()
{
    unsigned int choice = 1; // change this for user input
    switch(choice)
    {
    case 1:

        // this case is for converting to 8 bits by clipping the last 4 bits
        Clipper(_redChannel, _pixelCount / 4);
        Clipper(_gr1Channel, _pixelCount / 4);
        Clipper(_gr2Channel, _pixelCount / 4);
        Clipper(_bluChannel, _pixelCount / 4);

        Clipper(_imgData, _pixelCount);

        break;
    case 2:
        // this case is for converting to 8 bits using non linear curve
    
    default:
        break;
    }
}

void RAW12Loader::Clipper(uint16_t* data, unsigned int length)
{
    for(unsigned int index = 0; index < length; index++)
    {
        data[index] = (data[index] >> 4);
    }
}

void RAW12Loader::IntensityValues(unsigned int TileSize)
{

    PrintTileValues(_redChannel, TileSize, "Red");
    PrintTileValues(_gr1Channel, TileSize, "Green");
    PrintTileValues(_gr2Channel, TileSize, "Green2");
    PrintTileValues(_bluChannel, TileSize, "Blue");

}

void RAW12Loader::PrintTileValues(uint16_t* _data, unsigned int TileSize, std::string _channelName)
{
    std::cout << "Intensity values of " << _channelName << " Channel" << std::endl;

    for(unsigned int row = 0; row < TileSize * TileSize; row += TileSize)
    {
        for(unsigned int i = 0; i < TileSize; i++)
        {
            std::cout << (unsigned)_data[row + i] << " ";
        }
        std::cout << std::endl;
    }
}

RAW12Loader::~RAW12Loader()
{
}