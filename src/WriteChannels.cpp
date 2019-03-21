#include "RAW2PGM.h"
using namespace std;


WriteImage::WriteImage (Debayer& Debayerimage,PreProcessImage& image)
{
    _width=image.get_width();
    _height=image.get_height();

    PixelCount=image.get_pixelCount();

    Buff12Bit=static_cast<uint16_t*> (image.getBuff12Bit());

    Red=static_cast<uint16_t*> (image.RedChannel());
    Gr1=static_cast<uint16_t*> (image.Gr1Channel());
    Gr2=static_cast<uint16_t*> (image.Gr2Channel());
    Blu=static_cast<uint16_t*> (image.BluChannel());

    Colored12Bit=static_cast<uint16_t*>(Debayerimage.getColored());

    Red8 = new uint8_t[PixelCount];
    Gr18 = new uint8_t[PixelCount];
    Gr28 = new uint8_t[PixelCount];
    Blu8 = new uint8_t[PixelCount];

    Colored8Bit = new uint8_t[PixelCount*3];
    Buff8Bit = new uint8_t[PixelCount];
}
int WriteImage::ConvertTo8()
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
int WriteImage::PrintIntensityVals()
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
int WriteImage::WriteBoth()
{
    WriteIndividual(pgmfile,Red8,PGMIMG,PGM_FILENAME_RED);
    WriteIndividual(pgmfile,Gr18,PGMIMG,PGM_FILENAME_GR1);
    WriteIndividual(pgmfile,Gr28,PGMIMG,PGM_FILENAME_GR2);
    WriteIndividual(pgmfile,Blu8,PGMIMG,PGM_FILENAME_BLU);
    WriteColor(ppmfile,Colored8Bit,PGMIMG,PPM_FILENAME_COL);

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
    
    for(unsigned long int write_index = 0; write_index < PixelCount/4; write_index++)
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
    for(unsigned long int write_index = 0; write_index < PixelCount*3; write_index++)
    {
        ppmfile << (unsigned) (Colored[write_index]) << " ";
    }
    ppmfile.close();
    
    return 0;
}