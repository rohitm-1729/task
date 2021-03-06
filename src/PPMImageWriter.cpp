/* Copyright (C) 2019 Rohit Mundada
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * 
 */

#include "PPMImageWriter.hpp"

PPMImageWriter::PPMImageWriter()
{
}

PPMImageWriter::PPMImageWriter(Image &img)
{
    // get image dimensions
    _width      = img.GetWidth();
    _height     = img.GetHeight();
    _pixelCount = img.GetPixelCount();

    // get data of channels
    _redChannel = img.RedChannel();
    _gr1Channel = img.Gr1Channel();
    _gr2Channel = img.Gr2Channel();
    _bluChannel = img.BluChannel();

    // get pixel data
    _imgData = img.GetData();
}

void PPMImageWriter::WriteChannel(bool grayscale, uint16_t *data, const std::string &fileName)
{
    std::ofstream pgmfile;

    pgmfile.open(fileName, std::ios::binary);

    if(pgmfile.fail())
    {
        throw("Can't open pgm file");
    }

    // choose format from grayscale and color
    pgmfile << (grayscale ? "P2" : "P3") << std::endl;
    pgmfile << (grayscale ? _width / 2 : _width);
    pgmfile << " ";
    pgmfile << (grayscale ? _height / 2 : _height) << std::endl;
    pgmfile << "255" << std::endl;

    unsigned int length = (grayscale ? _pixelCount / 4 : _pixelCount * 3);

    // write data to file
    for(unsigned int write_index = 0; write_index < length; write_index++)
    {
        pgmfile << (unsigned)(data[write_index]) << " ";
    }

    pgmfile.close();
}

void PPMImageWriter::WriteImage(const std::string &location)
{
    bool grayscale = true;

    WriteChannel(grayscale, _redChannel, location + PGM_FILENAME_RED);
    WriteChannel(grayscale, _gr1Channel, location + PGM_FILENAME_GR1);
    WriteChannel(grayscale, _gr2Channel, location + PGM_FILENAME_GR2);
    WriteChannel(grayscale, _bluChannel, location + PGM_FILENAME_BLU);
    WriteChannel(!grayscale, _imgData, location + PPM_FILENAME_COLOR);
}

PPMImageWriter::~PPMImageWriter()
{
}
