#ifndef _BITMAP_H_
#define _BITMAP_H_

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

  
  class BitmapError{ 
    private:
      std::string filename;
      std::string error;

    public:
      BitmapError(const char* c_filename, const char* c_error):
        filename(c_filename), 
        error(c_error)
      {}
    
    friend std::ostream& operator << (std::ostream& out, const BitmapError& err);
  };
  
  std::ostream& operator << (std::ostream& out, const BitmapError& err);
 
  void load(const char* filename) throw(BitmapError); 


  //--------------------------------------------------------------------------------
  //                                  Channel
  //--------------------------------------------------------------------------------
  struct Channel{
    int width;
    int height;
    uint8_t *data;
  
    Channel(uint32_t w, uint32_t h){
      width = w;
      height = h;
      data = new uint8_t[w*h];
    }

    ~Channel(){
      delete[] data;
    }
  };

  std::ostream& operator << (std::ostream& out, const Channel& channel);

  //--------------------------------------------------------------------------------
  //                                  Image
  //--------------------------------------------------------------------------------


};


#endif
