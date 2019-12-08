/* Copyright (C) 2019 Rohit Mundada
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * 
 */

//change 1

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

    Image img(WIDTH, HEIGHT);

    img.SetRedChannel();
    img.SetGr1Channel();
    img.SetGr2Channel();
    img.SetBluChannel();
    img.SetImgData();

    RAW12Loader loader(img, RAWIMG);

    // swapping isn't required for this data
    // loader.SwapEndianness();

    loader.LoadSensels();

    std::cout << "Seperating Channels:...." << std::endl;

    loader.SeperateChannels();
    loader.ConvertTo8Bit();

    std::cout << "Extracting a " << TILE_SIZE << "x" << TILE_SIZE << " square tile: " << std::endl;

    loader.IntensityValues(TILE_SIZE);

    std::cout << "Creating colored img by debayering..." << std::endl;

    DebayerAlgo container(img);
    container.NearestNeighbour();

    std::cout << "Writing PGM/PPM images in : " << PGMIMG << std::endl;

    PPMImageWriter writer(img);
    writer.WriteImage(PGMIMG);

    std::cout << "Check Images in " << PGMIMG << std::endl;

    return 0;
}
