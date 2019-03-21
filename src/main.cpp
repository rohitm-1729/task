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
    Image.Seperate();

    cout<<"Debayering the image to a colored one.."<<endl;
    Debayer Debayered(Image);
    Debayered.NearestNeighbour();
    
    WriteImage Write(Debayered,Image);
    cout<<"Converting data to 8 bit format :"<<endl;
    Write.ConvertTo8();

    cout<<"Intensity Values of 5x5 tile:"<<endl;
    Write.PrintIntensityVals();
    
    cout<<"Writing Image to PPM format"<<endl;
    
    Write.WriteBoth();

    return 0;
}
