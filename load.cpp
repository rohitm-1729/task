#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdint.h>

#define WIDTH 4096
#define HEIGHT 3072
#define TILE_SIZE 5
#define PPM_FILENAME_RED "red1.pgm"
#define PPM_FILENAME_GR1 "gr1.pgm"
#define PPM_FILENAME_GR2 "gr2.pgm"
#define PPM_FILENAME_BLU "blu.pgm"

using namespace std;
int main(int argc, char const *argv[])
{
    std::ifstream input;
    unsigned int pixelcount=WIDTH*HEIGHT;
    unsigned int bytecount=WIDTH*HEIGHT*3/2;
    uint8_t *loadbuff = new uint8_t[bytecount];
    
    input.open("input.raw12",std::ios::binary);
    if(input.fail()) cout<<"failed to open file"<<endl; //debug
    input.read(reinterpret_cast< char*>(loadbuff),bytecount);
    //newbuffimage array is used to store all the 12 bits of pixel by pixel.
    uint16_t *newbuffimage = new uint16_t[pixelcount];
    
    //for getting the data into array of 32 bit integers
   /*  for(unsigned int  i = 0; i < bytecount; i++)
    {
        temp=loadbuff[i];
        newbuffimage[j]=(newbuffimage[i] <<8) | temp;
        if ((i+1)%4==0) 
        {
            j++;
        }
        
    } */
    // below code is for converting to 12 bits
    unsigned int j=0;
    
    for(unsigned int i = 0; i < bytecount; i++)
    {
        //cout<<"hey"<<i<<endl; //debug
        if(j%2==0)
        {
            newbuffimage[j]=loadbuff[i];
            newbuffimage[j]=newbuffimage[j]<<4;
            newbuffimage[j]=((newbuffimage[j] | (loadbuff[i+1]>>4)&0x0F));
            j++;
        }
        else
        {
            newbuffimage[j]=(loadbuff[i] & 0x0F);
            newbuffimage[j]=newbuffimage[j]<<8;
            newbuffimage[j]=newbuffimage[j]| loadbuff[i+1];
            i++;
            j++;
        }
       
    }
    cout<<"j: "<<j<<endl; // debug
    //debug 
    ofstream ofs;
    ofs.open("outputlog.txt"); //debug
    delete[] loadbuff;
    int choice=1;//change this for user input
    uint8_t * finalimage = new uint8_t[WIDTH*HEIGHT];
    switch (choice)
    {
        case 1:
            //this case is for converting to 8 bits by clipping the last 4 bits
            for(unsigned int index = 0; index<pixelcount; index++)
            {
                finalimage[index]=newbuffimage[index]>>4;
                ofs<<(unsigned)finalimage[index]<<" ";
            }
            ofs<<endl;
            break;
        case 2:
            //this case is for converting to 8 bits using non linear curve 
            /* for(int i = 0; i < pixelcount; i++)
            {
                
            } */
          
        default:
            break;
    }

    // seperating the channels for 5 * 5 square tile
     
    /* int redIndex=0,gr1Index=0,gr2Index=0,bluIndex=0;  
    for(unsigned int row = 0; row <WIDTH*TILE_SIZE; row+=WIDTH)
    {
        for(unsigned int ctr = 0; ctr < TILE_SIZE; ctr++)
        {
            cout<<(unsigned)finalimage[row+ctr]<<" ";
        }
        cout<<endl;  
    } */
    uint8_t *red = new uint8_t [(WIDTH*HEIGHT)/4];
    uint8_t *gr1 = new uint8_t [(WIDTH*HEIGHT)/4];
    uint8_t *gr2 = new uint8_t [(WIDTH*HEIGHT)/4];
    uint8_t *blu = new uint8_t [(WIDTH*HEIGHT)/4]; 
    // to seperate 4 colour channels
    unsigned int rgcount=0,gbcount=0;
    for(unsigned int  counter = 0; counter <pixelcount-1; counter+=2)
    {
        if((counter/WIDTH)%2==0) // case for RGRGRGRGRG....
        {
            red[rgcount]=finalimage[counter];
            gr1[rgcount]=finalimage[counter+1];
            rgcount++;
        }
        else //case for GBGBGBGBGB....
        {
            gr2[gbcount]=finalimage[counter];
            blu[gbcount]=finalimage[counter+1];
            gbcount++;
        }
        
    }
    //debug
    cout<<"rgcount: "<<rgcount<<endl;
    cout<<"gbcount: "<<gbcount<<endl;

    ofstream ppmfileRed;
    ofstream ppmfileGr1;
    ofstream ppmfileGr2;
    ofstream ppmfileBlu;
    try
    {
        ppmfileRed.open(PPM_FILENAME_RED,std::ios::binary);
        ppmfileGr1.open(PPM_FILENAME_GR1,std::ios::binary);
        ppmfileGr2.open(PPM_FILENAME_GR2,std::ios::binary);
        ppmfileBlu.open(PPM_FILENAME_BLU,std::ios::binary);
        if (ppmfileRed.fail()) throw("Can't open ppmred file");
        if (ppmfileGr1.fail()) throw("Can't open ppmgr1 file");
        if (ppmfileGr2.fail()) throw("Can't open ppmgr2 file");
        if (ppmfileBlu.fail()) throw("Can't open ppmblu file");
        ppmfileRed<< "P2\n" << WIDTH/2 << " " << HEIGHT/2 << "\n255\n";
        ppmfileGr1<< "P2\n" << WIDTH/2 << " " << HEIGHT/2 << "\n255\n"; 
        ppmfileGr2<< "P2\n" << WIDTH/2 << " " << HEIGHT/2 << "\n255\n";
        ppmfileBlu<< "P2\n" << WIDTH/2 << " " << HEIGHT/2 << "\n255\n";
        for(unsigned int write_index = 0; write_index < (WIDTH*HEIGHT)/4; write_index++)
        {
           ppmfileRed<<(unsigned)red[write_index]<<" ";
           ppmfileGr1<<(unsigned)gr1[write_index]<<" ";
           ppmfileGr2<<(unsigned)gr2[write_index]<<" ";
           ppmfileBlu<<(unsigned)blu[write_index]<<" ";
        }
        ppmfileRed.close();
        ppmfileGr1.close();
        ppmfileGr2.close();
        ppmfileBlu.close();

        
    }
    catch(const char *err)
    {
       fprintf(stderr, "%s\n", err); 
    }
    

    return 0;
}
