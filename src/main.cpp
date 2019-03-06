#include "RAW2PGM.h"

#define RAWIMG "RAW_INPUT/input.raw12"
#define PGMIMG "PGM_OUT/"
#define WIDTH 4096
#define HEIGHT 3072

using namespace std;

int main()
{
    cout << "Taking input from: "<< RAWIMG << endl;
    RAW2PGM Image(RAWIMG,WIDTH,HEIGHT);
    cout << "Seperating Channels:...." << endl;
    Image.SeperateChannels();
    cout<<"Writing PGM images in : "<< PGMIMG <<endl;
    Image.WriteChannelsPGM(PGMIMG);
    return 0;
}
