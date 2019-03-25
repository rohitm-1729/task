#include "Image.h"
#include "DebayerAlgo.h"
#include "PPMImageWriter.h"
#include "RAW12Loader.h"

#define WIDTH 4096
#define HEIGHT 3072
#define TILE_SIZE 5

#define RAWIMG "../RAW_INPUT/input.raw12"
#define PGMIMG "../PGM_OUT/"

int main()
{
    std::cout << "Taking input from: " << RAWIMG << std::endl;
    Image image(WIDTH,HEIGHT);
    image.setRedChannel();
    image.setGr1Channel();
    image.setGr2Channel();
    image.setBluChannel();
    image.setImgData();
    
    std::cout << "Seperating Channels:...." << std::endl;
    RAW12Loader loader(image , RAWIMG);
    loader.SeperateChannels();
    loader.ConvertTo8Bit();
    std::cout << "Extracting a " << TILE_SIZE << "x" << TILE_SIZE << " square tile: "<<std::endl;
    loader.ExtractTileValues(TILE_SIZE);
    std::cout << "Creating colored image by debayering..." << std::endl;
    DebayerAlgo Container(image);
    Container.NearestNeighbour();

    PPMImageWriter Writer(image);
    std::cout << "Writing PGM images in : " << PGMIMG << std::endl;
    Writer.ImageWriter(PGMIMG);

    return 0;
}
