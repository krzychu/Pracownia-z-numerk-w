#include "bitmap_image.h"
#include "bitmap_channel.h"
#include "bitmap_format.h"

#include <cstdio>

using namespace Bitmap;

Bitmap::Image::Image(const char* filename) throw(BitmapError){
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
  
  red = new Channel(info_header.width, info_header.height);
  green = new Channel(info_header.width, info_header.height);
  blue = new Channel(info_header.width, info_header.height);

  width = info_header.width;
  height = info_header.height;
  
  int w = info_header.width + 4 - info_header.width % 4;
  isMono = true;
  uint8_t color[3];

  for(int y = 0 ; y < height ; y++){
    for(int x = 0 ; x < w ; x++){
      n_read = fread(&color, sizeof(uint8_t), 3, file);

      if(n_read != 3){
        BitmapError err(filename, "Problem while reading image data");
        throw err;
      }

      if(x < width){
        red->data[x + y*height] = color[2];
        green->data[x + y*height] = color[1];
        blue->data[x + y*height] = color[0];
        if(color[0] != color[1] || color[1] != color[2])
          isMono = false;
      }
    }
  }
  fclose(file);

  if(isMono){
    gray = red;
    delete blue;
    delete green;
    red = NULL;
    green = NULL;
    blue = NULL;
  }
  else{
    gray = NULL;
  }
}


Bitmap::Image::Image(const Image& other){
  set(other);
}

void Bitmap::Image::operator = (const Image& other){
  set(other);
}  

Bitmap::Image::Image(Channel* r, Channel* g, Channel*b){
  isMono = false;
  
  red = r;
  r->incRefs();

  green = g;
  g->incRefs();

  blue = b;
  b->incRefs();

  gray = NULL;

  width = r->width;
  height = r->height;
}


Bitmap::Image::Image(Channel* g){
  isMono = true;
  gray = g;
  g->incRefs();
  
  red = NULL;
  green = NULL;
  blue = NULL;
}

Bitmap::Image::~Image(){
  decAllRefs();
}

void Bitmap::Image::decAllRefs(){
  if(red)
    red->decRefs();
  if(green)
    green->decRefs();
  if(blue)
    blue->decRefs();
  if(gray)
    gray->decRefs();
}


void Bitmap::Image::incAllRefs(){
  if(red)
    red->incRefs();
  if(green)
    green->incRefs();
  if(blue)
    blue->incRefs();
  if(gray)
    gray->incRefs();
}

void Bitmap::Image::set(const Image& other){
  decAllRefs();

  isMono = other.isMono;
  width = other.width;
  height = other.height;
  
  gray = other.gray;
  red = other.red;
  green = other.green;
  blue = other.blue;
  
  incAllRefs();
}



std::ostream& Bitmap::operator << (std::ostream& out, const Image& bitmap){
  out << "Width : " << bitmap.width << "\n";
  out << "Height : " << bitmap.height << "\n";
  out << "isMono : " << bitmap.isMono << "\n";
  
  if(bitmap.isMono){
    out << "Gray : " << *bitmap.gray;
  }
  else{
    out << "Red : " << *bitmap.red;
    out << "Green : " << *bitmap.green;
    out << "Blue : " << *bitmap.blue;
  }

  return out;
}


std::ostream& Bitmap::operator<< (std::ostream& out, const BitmapError& err){
  out << "File : " << err.filename << "\n";
  out << "Error : " << err.error << "\n";
  return out;
}

