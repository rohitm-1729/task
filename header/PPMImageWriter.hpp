#ifndef PPM_IMAGE_WRITER_H
#define PPM_IMAGE_WRITER_H

#include "Image.hpp"

#define PGM_FILENAME_RED "Red.pgm"
#define PGM_FILENAME_GR1 "Green1.pgm"
#define PGM_FILENAME_GR2 "Green2.pgm"
#define PGM_FILENAME_BLU "Blue.pgm"
#define PPM_FILENAME_COLOR "Color.ppm"

class PPMImageWriter
{
  private:
    uint16_t *_redChannel;
    uint16_t *_gr1Channel;
    uint16_t *_gr2Channel;
    uint16_t *_bluChannel;

    uint16_t *_imgData;

    unsigned int _width, _height, _pixelCount;

  public:
    PPMImageWriter();
    PPMImageWriter(Image &image);

    //Writing the data in pgm format for channels and ppm for debayered image
    void ImageWriter(const std::string &location);
    void WriteChannel(bool grayscale, uint16_t *data, const std::string &fileName);
};

#endif