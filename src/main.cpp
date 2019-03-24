#include "Image.h"
#include "Debayer.h"

#define WIDTH 4096
#define HEIGHT 3072
#define TILE_SIZE 5

#define RAWIMG "../RAW_INPUT/input.raw12"
#define PGMIMG "../PGM_OUT/"

int main()
{
    std::cout << "Taking input from: " << RAWIMG << std::endl;
    ImageProcessor Image(WIDTH,HEIGHT,RAWIMG);

    std::cout << "Seperating Channels:...." << std::endl;
    Image.SeperateChannels();

    std::cout << "Creating colored image by debayering..." << std::endl;
    DebayerAlgo Container(Image);
    Container.NearestNeighbour();

    Image.ConvertTo8Bit();
    std::cout << "Writing PGM images in : " << PGMIMG << std::endl;
    Image.ImageWriter(PGMIMG);

    std::cout << "Extracting a " << TILE_SIZE << "x" << TILE_SIZE << " square tile: "<<std::endl;
    Image.ExtractTileValues(TILE_SIZE);
    return 0;
}
