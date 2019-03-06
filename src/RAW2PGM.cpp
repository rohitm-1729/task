#include "RAW2PGM.h"
using namespace std;

RAW2PGM::RAW2PGM(const char* rawfilename, int width, int height)
{
    this->width = width;
    this->height = height;
    
    // all required counters
    PixelCount= width * height;
    Byte_Count= width * height * 3 / 2;
    
    LoadBuff=new uint8_t[Byte_Count];
    Buff12Bit=new uint16_t[PixelCount];
    
    input.open(rawfilename,std::ios::binary);
    
    if(input.fail())
    {
        cout<<"Failed to open file....Exiting program"<<endl;
        EXIT_FAILURE;
    }
    input.read(reinterpret_cast< char*>(this->LoadBuff),Byte_Count);
    //extract 12 bit per pixel and store
    unsigned int j=0;
    
    for(unsigned int i = 0; i < Byte_Count; i++)
    {

        if(j%2==0)
        {
            Buff12Bit[j]=LoadBuff[i];
            Buff12Bit[j]=Buff12Bit[j]<<4;
            Buff12Bit[j]=((Buff12Bit[j] | (LoadBuff[i+1]>>4)&0x0F));
            j++;
        }
        else
        {
            Buff12Bit[j]=(LoadBuff[i] & 0x0F);
            Buff12Bit[j]=Buff12Bit[j]<<8;
            Buff12Bit[j]=Buff12Bit[j]| LoadBuff[i+1];
            i++;
            j++;
        }
       
    }
    int choice=1;//change this for user input
    Buff8Bit = new uint8_t[PixelCount];
    switch (choice)
    {
        case 1:
            //this case is for converting to 8 bits by clipping the last 4 bits
            for(unsigned int index = 0; index<PixelCount; index++)
            {
                Buff8Bit[index]=(Buff12Bit[index])>>4;
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
    
}
int RAW2PGM::SeperateChannels()
{
    Red = new uint8_t[PixelCount/4];
    Gr1 = new uint8_t[PixelCount/4];
    Gr2 = new uint8_t[PixelCount/4];
    Blu = new uint8_t[PixelCount/4]; 
    // to seperate 4 colour channels
    unsigned int rgcount=0,gbcount=0;
    for(unsigned int  counter = 0; counter <PixelCount-1; counter+=2)
    {
        if((counter/width)%2==0) // case for RGRGRGRGRG....
        {
            Red[rgcount]=Buff8Bit[counter];
            Gr1[rgcount]=Buff8Bit[counter+1];
            rgcount++;
        }
        else //case for GBGBGBGBGB....
        {
            Gr2[gbcount]=Buff8Bit[counter];
            Blu[gbcount]=Buff8Bit[counter+1];
            gbcount++;
        }
        
    }
}
int RAW2PGM::WriteChannelsPGM(const string directory)
{
    try
    {
        pgmfileRed.open((directory + PGM_FILENAME_RED).c_str(),std::ios::binary);
        pgmfileGr1.open((directory + PGM_FILENAME_GR1).c_str(),std::ios::binary);
        pgmfileGr2.open((directory + PGM_FILENAME_GR2).c_str(),std::ios::binary);
        pgmfileBlu.open((directory + PGM_FILENAME_BLU).c_str(),std::ios::binary);

        if (pgmfileRed.fail()) throw("Can't open pgmred file");
        if (pgmfileGr1.fail()) throw("Can't open pgmgr1 file");
        if (pgmfileGr2.fail()) throw("Can't open pgmgr2 file");
        if (pgmfileBlu.fail()) throw("Can't open pgmblu file");
        
        pgmfileRed<< "P2\n" << width/2 << " " << height/2 << "\n255\n";
        pgmfileGr1<< "P2\n" << width/2 << " " << height/2 << "\n255\n"; 
        pgmfileGr2<< "P2\n" << width/2 << " " << height/2 << "\n255\n";
        pgmfileBlu<< "P2\n" << width/2 << " " << height/2 << "\n255\n";
        
        for(unsigned int write_index = 0; write_index < PixelCount/4; write_index++)
        {
           pgmfileRed<<(unsigned)(Red[write_index])<<" ";
           pgmfileGr1<<(unsigned)(Gr1[write_index])<<" ";
           pgmfileGr2<<(unsigned)(Gr2[write_index])<<" ";
           pgmfileBlu<<(unsigned)(Blu[write_index])<<" ";
        }
        pgmfileRed.close();
        pgmfileGr1.close();
        pgmfileGr2.close();
        pgmfileBlu.close();
    }
    catch(const char *err)
    {
       fprintf(stderr, "%s\n", err); 
    }

}
    