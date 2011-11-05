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
  
  isMono = true;
  uint8_t color[3];

  for(int y = 0 ; y < height ; y++){
    for(int x = 0 ; x < width ; x++){
      n_read = fread(&color, sizeof(uint8_t), 3, file);

      if(n_read != 3){
        BitmapError err(filename, "Problem while reading image data");
        throw err;
      }

      red->data[x + y*width] = color[2];
      green->data[x + y*width] = color[1];
      blue->data[x + y*width] = color[0];
      if(color[0] != color[1] || color[1] != color[2])
        isMono = false;
    }
    fseek(file, getRowLen() - 3*width, SEEK_CUR);
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


int Bitmap::Image::getRowLen(){
  if(width % 4 == 0){
    return 3*width;
  }
  else{
    return 3*width + 4 - (3*width)%4;
  }
}


void Bitmap::Image::save(const char* filename) throw(BitmapError){
  // try to open destination file
  FILE * file = fopen(filename, "wb");
  if(file == NULL){
    BitmapError ex(filename, "Unable to open file for writing");
    throw ex;
  }


  int row_len = getRowLen();

  Identification id;
  id.magic[0] = 'B';
  id.magic[1] = 'M';

  Header header;
  header.creator1 = 0;
  header.creator2 = 0;
  header.data_offset = sizeof(Identification) + sizeof(Header) + sizeof(InfoHeader);
  header.file_size = header.data_offset + row_len*height;
  
  InfoHeader info;
  info.header_size = sizeof(InfoHeader);
  info.width = width;
  info.height = height;
  info.nplanes = 1;
  info.bitspp = 24;
  info.compression_type = BI_RGB;
  info.bmp_bytesize = 0;
  info.horizontal_resolution = 0;
  info.vertical_resolution = 0;
  info.ncolors = 0;
  info.nimpcolors = 0;

  // write header to file
  size_t written = fwrite(&id, sizeof(Identification), 1, file);
  written += fwrite(&header, sizeof(Header), 1, file);
  written += fwrite(&info, sizeof(InfoHeader), 1, file);

  if(written != 3){
    BitmapError err(filename, "Unable to write file header");
    throw err;
  }

  // write contents to file
  uint8_t color[3];
  uint8_t zeros[3] = {0,0,0};
  for(int y=0 ; y < height; y++){
    for(int x=0 ; x < width; x++){

      if(!isMono){
        color[2] = red->data[x + y*width];
        color[1] = green->data[x + y*width];
        color[0] = blue->data[x + y*width];
      }
      else{
        color[0] = gray->data[x + y*width];
        color[1] = color[0];
        color[2] = color[0];
      }
     
      written = fwrite(color, sizeof(uint8_t), 3, file);
      if(written != 3){
        BitmapError err(filename, "Unable to write bitmap contents to file");
        throw err;
      }
    }
    fwrite(zeros, sizeof(uint8_t), getRowLen() - 3*width, file);
  }

  fclose(file);
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

