#include "RAW2PGM.h"
using namespace std;

RAW2PGM::RAW2PGM(const char* rawfilename, int width, int height)
{
    this->width = width;
    this->height = height;
    // all required counters
    PixelCount= width * height;
    Byte_Count= width * height * 3 / 2;
    
    LoadBuff = new uint8_t[Byte_Count];
    Buff12Bit= new uint16_t[PixelCount];
    
    input.open(rawfilename,std::ios::binary);
    
    if(input.fail()){
        cout<<"Failed to open file....Exiting program"<<endl;
        exit(1);
    }
    input.read(reinterpret_cast< char*>(this->LoadBuff),Byte_Count);
    //extract 12 bit per pixel and store
    unsigned int j=0;
    
    for(unsigned int i = 0; i < Byte_Count; i++){

        if(j%2==0){
            Buff12Bit[j]=LoadBuff[i];
            Buff12Bit[j]=Buff12Bit[j]<<4;
            Buff12Bit[j]=((Buff12Bit[j] | ((LoadBuff[i+1]>>4)&0x0F)));
            j++;
        }else{
            Buff12Bit[j]=(LoadBuff[i] & 0x0F);
            Buff12Bit[j]=Buff12Bit[j]<<8;
            Buff12Bit[j]=Buff12Bit[j]| LoadBuff[i+1];
            i++;
            j++;
        }
       
    }
    
    
}
int RAW2PGM::SeperateChannels()
{
    Red = new uint16_t[PixelCount/4];
    Gr1 = new uint16_t[PixelCount/4];
    Gr2 = new uint16_t[PixelCount/4];
    Blu = new uint16_t[PixelCount/4];
    // to seperate 4 colour channels
    unsigned int rgcount=0,gbcount=0;

    for(unsigned int  counter = 0; counter < PixelCount-1; counter += 2){
        if((counter/width)%2==0){  // case for RGRGRGRGRG....
            Red[rgcount]=Buff12Bit[counter];
            Gr1[rgcount]=Buff12Bit[counter+1];
            rgcount++;
        }else{ //case for GBGBGBGBGB....
            Gr2[gbcount]=Buff12Bit[counter];
            Blu[gbcount]=Buff12Bit[counter+1];
            gbcount++;
        }
        
    }
    return 0;
}

int RAW2PGM::DebayerImage()
{
    Colored12Bit = new uint16_t[PixelCount*3];
    for(unsigned int index = 0;  index < PixelCount; index+=2){
        if ((index/width)%2==0){
            //pixel at R and pixel at G
            for(unsigned int j=0; j < 6; j+=3){
            Colored12Bit[index*3 + j] = Buff12Bit[index];
            Colored12Bit[index*3 + j+1] = (Buff12Bit[index + 1] + Buff12Bit[index + width])/2;
            Colored12Bit[index*3 + j+2] = Buff12Bit[index + width + 1];
            }
        }else{
            for(unsigned int k = 0; k < 6; k+=3){
                Colored12Bit[index*3 + k] = Buff12Bit[index - width];
                Colored12Bit[index*3 + k+1] = (Buff12Bit[index]+Buff12Bit[(index - width) + 1])/2;
                Colored12Bit[index*3 + k+2] = Buff12Bit[index + 1];
            }
            
        }
        
        
    }
    return 0;
}

int RAW2PGM::WriteChannelsPGM(const string directory)
{
    Red8 = new uint8_t[PixelCount];
    Gr18 = new uint8_t[PixelCount];
    Gr28 = new uint8_t[PixelCount];
    Blu8 = new uint8_t[PixelCount];
    Colored8Bit = new uint8_t[PixelCount*3];
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
                // conversion for debayered image 
                Colored8Bit[index] = (Colored12Bit[index]>>4);
            }
            break;
        case 2:
            //this case is for converting to 8 bits using non linear curve 
            /* for(int i = 0; i < pixelcount; i++)
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
        
        pgmfileRed<< "P2\n" << width/2 << " " << height/2 << "\n255\n";
        pgmfileGr1<< "P2\n" << width/2 << " " << height/2 << "\n255\n"; 
        pgmfileGr2<< "P2\n" << width/2 << " " << height/2 << "\n255\n";
        pgmfileBlu<< "P2\n" << width/2 << " " << height/2 << "\n255\n";
        ppmfileColor<< "P3\n" << width << " " << height   << "\n255\n";

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
RAW2PGM::~RAW2PGM()
{
    delete[] LoadBuff;
    delete[] Buff12Bit;
}
    