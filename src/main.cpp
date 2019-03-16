#include "RAW2PGM.h"

#define WIDTH 4096
#define HEIGHT 3072
#define TILE_SIZE 5

using namespace std;

int main()
{
    PreProcessImage Image(WIDTH,HEIGHT);
    SepChannels Channels(Image);
    Channels.Seperate(Image);
    Debayer Debayered(Channels);
    Debayered.NearestNeighbour();
    To8Bit EightBitImage(Debayered,Image);
    EightBitImage.ConvertTo8();
    EightBitImage.PrintIntensityVals();
    WriteImage WriteFile(EightBitImage);
    WriteFile.WriteBoth();
    return 0;
}
