#ifndef _BITMAP_FORMAT_H_
#define _BITMAP_FORMAT_H_

#include <inttypes.h>
#include <string>
#include <iostream>

namespace Bitmap{

  struct Identification{
    uint8_t magic[2];
    
    bool isCorrect(){
      return magic[0] == 'B' && magic[1] == 'M';
    }
  };

  struct Header{
    uint32_t file_size;
    uint16_t creator1;
    uint16_t creator2;
    uint32_t data_offset;
  };


  struct InfoHeader {
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t nplanes;
    uint16_t bitspp;
    uint32_t compression_type;
    uint32_t bmp_bytesize;
    int32_t horizontal_resolution;
    int32_t vertical_resolution;
    uint32_t ncolors;
    uint32_t nimpcolors;
  };


  enum CompressionMethod{
    BI_RGB = 0,
    BI_RLE8,
    BI_RLE4,
    BI_BITFIELDS, 
    BI_JPEG,      
    BI_PNG
  };

};


#endif
