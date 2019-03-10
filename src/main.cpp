#include "RAW2PGM.h"

#define WIDTH 4096
#define HEIGHT 3072
#define TILE_SIZE 5

using namespace std;

int main()
{
    cout << "Taking input from: "<< RAWIMG << endl;
    RAW2PGM Image(WIDTH,HEIGHT);
    cout << "Seperating Channels:...." << endl;
    Image.SeperateChannels();
    cout<< "Creating colored image by debayering..." << endl;
    Image.DebayerNearest();
    cout<<"Writing PGM images in : "<< PGMIMG <<endl;
    Image.WriteChannelsPGM(PGMIMG);
    cout<< "Extracting a " << TILE_SIZE <<"x" <<TILE_SIZE << " square tile: "<<endl;
    Image.ExtractTileValues(TILE_SIZE);
    return 0;
}
