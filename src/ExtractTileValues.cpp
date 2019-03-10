#include "RAW2PGM.h"
using namespace std;

int RAW2PGM::ExtractTileValues(int TileSize)
{
    for(unsigned int tile = 0; tile< _width*TileSize; tile+=_width)
    {
        for(unsigned int row = tile; row < tile+5; row++)
        {
            cout<<(unsigned) Buff8Bit[row]<<" ";
        }
        cout<<endl;
    }
    return 0;
}