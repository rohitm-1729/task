#include "RAW2PGM.h"
using namespace std;

int RAW2PGM::WriteChannelsPGM(const string directory)
{
    Red8 = new uint8_t[PixelCount];
    Gr18 = new uint8_t[PixelCount];
    Gr28 = new uint8_t[PixelCount];
    Blu8 = new uint8_t[PixelCount];
    Colored8Bit = new uint8_t[PixelCount*3];
    Buff8Bit = new uint8_t[PixelCount];
    unsigned int choice=1;//change this for user input
    switch (choice){
        case 1:
            //this case is for converting to 8 bits by clipping the last 4 bits
            
            for(unsigned int index = 0; index<PixelCount*3; index++){
                
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
            /* for(unsigned int i = 0; i < pixelcount; i++)
            {
                
            } */
          
        default:
            break;
    }
    try{
        pgmfileRed.open((directory + PGM_FILENAME_RED).c_str(),std::ios::binary);
        pgmfileGr1.open((directory + PGM_FILENAME_GR1).c_str(),std::ios::binary);
        pgmfileGr2.open((directory + PGM_FILENAME_GR2).c_str(),std::ios::binary);
        pgmfileBlu.open((directory + PGM_FILENAME_BLU).c_str(),std::ios::binary);
        ppmfileColor.open((directory + PPM_FILENAME_COLOR).c_str(),std::ios::binary);
        

        if (pgmfileRed.fail()) throw("Can't open pgmred file");
        if (pgmfileGr1.fail()) throw("Can't open pgmgr1 file");
        if (pgmfileGr2.fail()) throw("Can't open pgmgr2 file");
        if (pgmfileBlu.fail()) throw("Can't open pgmblu file");
        if (ppmfileColor.fail()) throw("Can't open ppmcolor file");
        
        pgmfileRed<< "P2\n" << _width/2 << " " << _height/2 << "\n255\n";
        pgmfileGr1<< "P2\n" << _width/2 << " " << _height/2 << "\n255\n"; 
        pgmfileGr2<< "P2\n" << _width/2 << " " << _height/2 << "\n255\n";
        pgmfileBlu<< "P2\n" << _width/2 << " " << _height/2 << "\n255\n";
        ppmfileColor<< "P3\n" << _width << " " << _height   << "\n255\n";

        for(unsigned int write_index = 0; write_index < PixelCount*3; write_index++){
           if (write_index < PixelCount/4){
               pgmfileRed<<(unsigned)(Red8[write_index])<<" ";
               pgmfileGr1<<(unsigned)(Gr18[write_index])<<" ";
               pgmfileGr2<<(unsigned)(Gr28[write_index])<<" ";
               pgmfileBlu<<(unsigned)(Blu8[write_index])<<" ";
           }
           ppmfileColor << (unsigned) (Colored8Bit[write_index]) << " ";
        }
        pgmfileRed.close();
        pgmfileGr1.close();
        pgmfileGr2.close();
        pgmfileBlu.close();
        ppmfileColor.close();
    }
    catch(const char *err){
       fprintf(stderr, "%s\n", err); 
    }
    return 0;
}