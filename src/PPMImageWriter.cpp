#include "PPMImageWriter.hpp"

PPMImageWriter::PPMImageWriter()
{

}
PPMImageWriter::PPMImageWriter(Image& image)
{
    _width=image.getWidth();
    _height=image.getHeight();
    _pixelCount=image.getPixelCount();

    _redChannel = static_cast<uint16_t*>(image.RedChannel());
    _gr1Channel = static_cast<uint16_t*>(image.Gr1Channel());
    _gr2Channel = static_cast<uint16_t*>(image.Gr2Channel());
    _bluChannel = static_cast<uint16_t*>(image.BluChannel());
    
    _imgData = static_cast<uint16_t*>(image.getData());
}

void PPMImageWriter::ImageWriter(const std::string& location)
{
    bool grayscale=true;
    
    WriteChannel(grayscale,_redChannel,location + PGM_FILENAME_RED);
    WriteChannel(grayscale,_gr1Channel,location + PGM_FILENAME_GR1);
    WriteChannel(grayscale,_gr2Channel,location + PGM_FILENAME_GR2);
    WriteChannel(grayscale,_bluChannel,location + PGM_FILENAME_BLU);

    WriteChannel(!grayscale,_imgData,location + PPM_FILENAME_COLOR);
}

void PPMImageWriter::WriteChannel(bool grayscale,uint16_t* data,const std::string& fileName)
{
    
        std::ofstream pgmfile;

        pgmfile.open(fileName,std::ios::binary);
        if (pgmfile.fail()) 
        {
            throw("Can't open pgm file");
        }

        pgmfile << (grayscale ? "P2\n":"P3\n");
        pgmfile << (grayscale ? _width/2 :_width);
        pgmfile << " ";
        pgmfile << (grayscale ? _height/2 :_height);
        pgmfile << "\n255\n";

        unsigned int length= (grayscale ? _pixelCount/4 : _pixelCount*3);

        for(unsigned int write_index = 0; write_index < length; write_index++)
        {
            pgmfile << (unsigned)(data[write_index]) << " ";
        }
        
        pgmfile.close();
    
}