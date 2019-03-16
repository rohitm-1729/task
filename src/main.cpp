#include "RAW2PGM.h"

#define WIDTH 4096
#define HEIGHT 3072
#define TILE_SIZE 5

using namespace std;

int main()
{
    //create an Image object
    cout<<"Loading RAW12 Image into memory.."<<endl;
    PreProcessImage Image(WIDTH,HEIGHT);
    //Seperate channels of the Image 
    cout<<"Seperating R,G,G,B channels"<<endl;
    SepChannels Channels(Image);
    Channels.Seperate(Image);

    cout<<"Debayering the image to a colored one.."<<endl;
    Debayer Debayered(Channels);
    Debayered.NearestNeighbour();
    
    cout<<"Converting data to 8 bit format :"<<endl;
    To8Bit EightBitImage(Debayered,Image);
    EightBitImage.ConvertTo8();
    cout<<"Intensity Values of 5x5 tile:"<<endl;
    EightBitImage.PrintIntensityVals();
    
    cout<<"Writing Image to PPM format"<<endl;
    WriteImage WriteFile(EightBitImage);
    WriteFile.WriteBoth();
    
    cout<<"Check Images in "<<PGMIMG<<endl;
    return 0;
}
