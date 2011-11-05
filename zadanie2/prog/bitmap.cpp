#include "bitmap.h"
#include <cstdio>

using namespace Bitmap;

std::ostream& Bitmap::operator<< (std::ostream& out, const BitmapError& err){
  out << "File : " << err.filename << "\n";
  out << "Error : " << err.error << "\n";
  return out;
}
      
void Bitmap::load(const char* filename) throw(BitmapError){
  // try to open file
  FILE *file = fopen(filename, "rb");
  
  if(file == NULL){
    BitmapError err(filename, "Unable to open file") ; 
    throw err;
  }

  // check if magic numbers are correct
  Identification ident;
  size_t n_read = fread(&ident, sizeof(Identification), 1, file);
  if(n_read != 1 || !ident.isCorrect()){
    BitmapError err(filename, "Incorrect magic number");
    throw err;
  }

  // try to load header
  Header header;
  n_read = fread(&header, sizeof(Header), 1, file);
  if(n_read != 1){
    BitmapError err(filename, "Unable to parse header");
    throw err;
  }

  // try to load header
  InfoHeader info_header;
  n_read = fread(&info_header, sizeof(InfoHeader), 1, file);
  if(n_read != 1){
    BitmapError err(filename, "Unable to parse info header");
    throw err;
  }

  // check if compression type is supported
  if(info_header.compression_type != BI_RGB){
    BitmapError err(filename, "Unsupported compression type");
    throw err;
  }
  
  // check if bpp is supported
  if(info_header.bitspp != 24){
    BitmapError err(filename, "Unsupported bits per pixel value");
    throw err;
  }

  // load channels
  fseek(file, header.data_offset, SEEK_SET);
  
  Channel red(info_header.width, info_header.height);
  Channel green(info_header.width, info_header.height);
  Channel blue(info_header.width, info_header.height);
  
  int w = info_header.width + 4 - info_header.width % 4;
  int h = info_header.height;
  int hw = info_header.width;
  bool mono = true;
  uint8_t color[3];

  for(int y = 0 ; y < h ; y++){
    for(int x = 0 ; x < w ; x++){
      n_read = fread(&color, sizeof(uint8_t), 3, file);

      if(n_read != 3){
        BitmapError err(filename, "Problem while reading image data");
        throw err;
      }

      if(x < hw){
        red.data[x + y*hw] = color[2];
        green.data[x + y*hw] = color[1];
        blue.data[x + y*hw] = color[0];
        if(color[0] != color[1] || color[1] != color[2])
          mono = false;
      }
    }
  }

  std::cout << info_header.width << " " << info_header.height << "\n";
  std::cout << red;
  std::cout << green;
  std::cout << blue;

  fclose(file);
};



//--------------------------------------------------------------------------------
//                                  Channel
//--------------------------------------------------------------------------------

std::ostream& Bitmap::operator << (std::ostream& out, const Channel& channel){
  out << "\n";
  uint8_t* ptr = channel.data;
  for(int y = channel.height-1; y >=0 ; y--){
    for(int x = 0; x < channel.width; x++){
      out << " " << (int)*ptr++; 
    }
    out << "\n";
  }
  return out;
}

