#include "DebayerAlgo.hpp"
#include "Image.hpp"
#include "PPMImageWriter.hpp"
#include "RAW12Loader.hpp"

#define WIDTH 4096
#define HEIGHT 3072
#define TILE_SIZE 5

#define RAWIMG "../RAW_INPUT/input.raw12"
#define PGMIMG "../PGM_OUT/"

int main()
{
    std::cout << "Taking input from: " << RAWIMG << std::endl;

    Image image(WIDTH, HEIGHT);

    image.setRedChannel();
    image.setGr1Channel();
    image.setGr2Channel();
    image.setBluChannel();
    image.setImgData();

    RAW12Loader loader(image, RAWIMG);

    std::cout << "Seperating Channels:...." << std::endl;

    // swapping isn't required for this data
    // loader.SwapEndianness();

    loader.LoadSensels();

    loader.SeperateChannels();

    loader.ConvertTo8Bit();

    std::cout << "Extracting a " << TILE_SIZE << "x" << TILE_SIZE << " square tile: " << std::endl;

    loader.IntensityValues(TILE_SIZE);

    std::cout << "Creating colored image by debayering..." << std::endl;

    DebayerAlgo container(image);

    container.NearestNeighbour();

    PPMImageWriter writer(image);

    std::cout << "Writing PGM/PPM images in : " << PGMIMG << std::endl;

    writer.ImageWriter(PGMIMG);

    return 0;
}
