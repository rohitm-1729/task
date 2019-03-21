#include "RAW2PGM.h"
using namespace std;

#define PGMIMG "../PGM_OUT/"

WriteImage::WriteImage (Debayer& Debayerimage,PreProcessImage& image)
{
    _width=image.get_width();
    _height=image.get_height();

    _pixelCount=image.get_pixelCount();

    _buff12Bit=static_cast<uint16_t*> (image.getBuff12Bit());

    red=static_cast<uint16_t*> (image.RedChannel());
    gr1=static_cast<uint16_t*> (image.Gr1Channel());
    gr2=static_cast<uint16_t*> (image.Gr2Channel());
    blu=static_cast<uint16_t*> (image.BluChannel());

    _colored12Bit=static_cast<uint16_t*>(Debayerimage.getColored());

    red8 = new uint8_t[_pixelCount];
    gr18 = new uint8_t[_pixelCount];
    gr28 = new uint8_t[_pixelCount];
    blu8 = new uint8_t[_pixelCount];

    _colored8Bit = new uint8_t[_pixelCount*3];
    _buff8Bit = new uint8_t[_pixelCount];


}
int WriteImage::ConvertTo8()
{
    unsigned long int choice=1;//change this for user input
    switch (choice){
        case 1:
            //this case is for converting to 8 bits by clipping the last 4 bits
            
            for(unsigned long int index = 0; index<_pixelCount*3; index++){
                
                if(index<_pixelCount/4){
                    red8[index] = (red[index] >> 4);
                    gr18[index] = (gr1[index] >> 4);
                    gr28[index] = (gr2[index] >> 4);
                    blu8[index] = (blu[index] >> 4);
                }
                //to convert 12Bit buffer to 8Bit for Square tile values
                if (index < _pixelCount){
                    _buff8Bit[index] = (_buff12Bit[index]>>4);
                }
                
                // conversion for debayered image 
                _colored8Bit[index] = (_colored12Bit[index]>>4);
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
int WriteImage::PrintIntensityVals()
{
    
    for(unsigned long int tile = 0; tile< _width*TILE_SIZE; tile+=_width)
    {
        for(unsigned long int row = tile; row < tile+5; row++)
        {
            cout<<(unsigned)_buff8Bit[row]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
int WriteImage::WriteBoth()
{
    WriteIndividual(pgmfile,red8,PGMIMG,PGM_FILENAME_RED);
    WriteIndividual(pgmfile,gr18,PGMIMG,PGM_FILENAME_GR1);
    WriteIndividual(pgmfile,gr28,PGMIMG,PGM_FILENAME_GR2);
    WriteIndividual(pgmfile,blu8,PGMIMG,PGM_FILENAME_BLU);
    WriteColor(ppmfile,_colored8Bit,PGMIMG,PPM_FILENAME_COL);

    return 0;
}

int WriteImage::WriteIndividual(ofstream& pgmfile, uint8_t *channel,  const string& directory,  const string& PGM_FILENAME)
{
    pgmfile.open((directory + PGM_FILENAME).c_str(),std::ios::binary);

    if (pgmfile.fail()) 
    {
        throw("Can't open pgm file");
    }
    pgmfile<< "P2\n" << _width/2 << " " << _height/2 << "\n255\n";
    
    for(unsigned long int write_index = 0; write_index < _pixelCount/4; write_index++)
    {
        pgmfile<<(unsigned)(channel[write_index])<<" ";
    }

    pgmfile.close();

    return 0;
}
int WriteImage::WriteColor(ofstream& ppmfile, uint8_t *Colored,  const string& directory,  const string& PPM_FILENAME_COLOR)
{
    ppmfile.open((directory + PPM_FILENAME_COLOR).c_str(),std::ios::binary);
    if (ppmfile.fail()) 
    {
        throw("Can't open ppmcolor file");
    }

    ppmfile<< "P3\n" << _width << " " << _height   << "\n255\n";
    for(unsigned long int write_index = 0; write_index < _pixelCount*3; write_index++)
    {
        ppmfile << (unsigned) (Colored[write_index]) << " ";
    }
    ppmfile.close();
    
    return 0;
}