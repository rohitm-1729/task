#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdint.h>

#define WIDTH 4096
#define HEIGHT 3072
using namespace std;
int main(int argc, char const *argv[])
{
    std::ifstream input;
    //3/8 because of 12/32
    unsigned int bitcount12=3;//WIDTH*HEIGHT;
    unsigned int count=WIDTH*HEIGHT*3/8;
    unsigned int bytecount=4;//WIDTH*HEIGHT*3/2;
    char *buffimg = new char[count];
    char32_t *chbuffimg =new char32_t[count];
    input.open("file.raw12",ifstream::binary);
    input.seekg(0, input.end);
    uint32_t length = input.tellg();
    input.seekg(0, input.beg);
    cout<<length<<endl;
    input.read((buffimg),count);
    uint16_t *newbuffimage = new uint16_t[bitcount12];
    uint16_t temp;
    for(auto k = 0; k < 3; k++)
    {
        cout<<buffimg[k]<<endl;
    }

    long long j=0;

    for(long long i = 0; i < bytecount; i++)
    {
        if(j%2==0)
        {
            newbuffimage[j]=buffimg[i];
            newbuffimage[j]=((newbuffimage[j]<<4) | buffimg[i+1]>>4);
            j++;
        }
        else
        {
            newbuffimage[j]=buffimg[i]>>4;
            newbuffimage[j]=newbuffimage[j]<<8 | buffimg[i+1];
            i++;
            j++;
        }
            
    }
    for(auto k = 0; k < 3; k++)
    {
        cout<<(unsigned)newbuffimage[k]<<endl;
    }
    
    
    /*input.read(buffer,12);
    input.close();
    for(int i = 0; i < count; i+=12)
    {
        
    }
    
    string newbuf(buffer);
    bitset <12> bits(newbuf);
        cout<<bits<<endl;
    */
    return 0;
}
