#include "RAW2PGM.h"
using namespace std;

WriteImage::WriteImage()
{

}
WriteImage::WriteImage(To8Bit& Image8Bit)
{
    this->_width=Image8Bit._width;
    this->_height=Image8Bit._height;

    this->PixelCount=Image8Bit.PixelCount;
    this->Byte_Count=Image8Bit.Byte_Count;

    this->Red8=Image8Bit.Red8;
    this->Gr18=Image8Bit.Gr18;
    this->Gr28=Image8Bit.Gr28;
    this->Blu8=Image8Bit.Blu8;

    this->Colored8Bit=Image8Bit.Colored8Bit;

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