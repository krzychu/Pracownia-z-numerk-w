#include "bitmap_image.h"
#include "bitmap_channel.h"
#include "bitmap_format.h"

#include <cstdio>

using namespace Bitmap;

Image* Bitmap::Image::load(const char* filename) throw(BitmapError){
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
  
  Channel* red = new Channel(info_header.width, info_header.height);
  Channel* green = new Channel(info_header.width, info_header.height);
  Channel* blue = new Channel(info_header.width, info_header.height);

  int width = info_header.width;
  int height = info_header.height;
  
  bool isMono = true;
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
    fseek(file, getRowLen(width) - 3*width, SEEK_CUR);
  }
  fclose(file);

  if(isMono){
    BWImage* img = new BWImage(red);
    delete green;
    delete blue;
    return img;
  }
  else{
    RGBImage* img = new RGBImage(red, green, blue);
    return img;
  }
}

int Bitmap::Image::getWidth() const{
  return width;
}

int Bitmap::Image::getHeight() const{
  return height;
}


//------------------------------------------------------------------RGB
Bitmap::RGBImage::RGBImage(Channel* r, Channel* g, Channel* b){
  red = r;
  green = g;
  blue = b;

  width = r->width;
  height = r->height;
}

void Bitmap::RGBImage::save(const char* filename) throw(BitmapError){
  save_to_file(filename, red, green, blue, NULL);
}

Bitmap::RGBImage::~RGBImage(){
  if(red)
    delete red;
  if(green)
    delete green;
  if(blue)
    delete blue;
}

std::ostream& Bitmap::operator << (std::ostream& out, const RGBImage& bitmap){
  out << "Width : " << bitmap.width << "\n";
  out << "Height : " << bitmap.height << "\n";
  
  out << "Red : " << *bitmap.red;
  out << "Green : " << *bitmap.green;
  out << "Blue : " << *bitmap.blue;

  return out;
}

ResizeStats Bitmap::RGBImage::resize_x_px(int newsize, Resizers::Resizer* resizer){
  Resizers::Result res_red, res_green, res_blue;

  res_red = resizer->resize_x(red, newsize);
  res_green = resizer->resize_x(green, newsize);
  res_blue = resizer->resize_x(blue, newsize);
  
  ResizeStats res;
  res.time = res_red.time + res_green.time + res_blue.time;
  res.img = new RGBImage(res_red.channel, res_green.channel, res_blue.channel);

  return res;
}

ResizeStats Bitmap::RGBImage::resize_y_px(int newsize, Resizers::Resizer* resizer){
  Resizers::Result res_red, res_green, res_blue;

  res_red = resizer->resize_y(red, newsize);
  res_green = resizer->resize_y(green, newsize);
  res_blue = resizer->resize_y(blue, newsize);
  
  ResizeStats res;
  res.time = res_red.time + res_green.time + res_blue.time;
  res.img = new RGBImage(res_red.channel, res_green.channel, res_blue.channel);

  return res;
}

Image* Bitmap::RGBImage::diff(const Image* img) const{
  RGBImage* rgb = (RGBImage*) img;
  return new RGBImage(rgb->red->diff(red), 
  rgb->green->diff(green), rgb->blue->diff(blue));
}

double Bitmap::RGBImage::norm() const{
  return red->norm() + green->norm() + blue->norm();
}


//------------------------------------------------------------------BW
Bitmap::BWImage::BWImage(Channel* g){
  gray = g;

  width = g->width;
  height = g->height;
}

void Bitmap::BWImage::save(const char* filename) throw(BitmapError){
  save_to_file(filename, NULL, NULL, NULL, gray);
}

Bitmap::BWImage::~BWImage(){
  if(gray)
    delete gray;
}

std::ostream& Bitmap::operator << (std::ostream& out, const BWImage& bitmap){
  out << "Width : " << bitmap.width << "\n";
  out << "Height : " << bitmap.height << "\n";
  
  out << "Gray : " << *bitmap.gray;

  return out;
}


ResizeStats Bitmap::BWImage::resize_x_px(int newsize, Resizers::Resizer* resizer){
  Resizers::Result res_gray;

  res_gray = resizer->resize_x(gray, newsize);
  
  ResizeStats res;
  res.time = res_gray.time;
  res.img = new BWImage(res_gray.channel);

  return res;
}

ResizeStats Bitmap::BWImage::resize_y_px(int newsize, Resizers::Resizer* resizer){
  Resizers::Result res_gray;

  res_gray = resizer->resize_y(gray, newsize);
  
  ResizeStats res;
  res.time = res_gray.time;
  res.img = new BWImage(res_gray.channel);

  return res;
}

Image* Bitmap::BWImage::diff(const Image* img) const {
  BWImage* bw = (BWImage*) img;
  return new BWImage(bw->gray->diff(gray));
}

double Bitmap::BWImage::norm() const{
  return gray->norm();
}

//--------------------------------------------------------------------------image

ResizeStats Bitmap::Image::resize_x_percent(int percent, Resizers::Resizer* resizer){
  double new_size = double(percent) / 100.0 * double(width);
  if(new_size < 2)
    new_size = 2;
  return resize_x_px((int) new_size, resizer);
}

ResizeStats Bitmap::Image::resize_y_percent(int percent, Resizers::Resizer* resizer){
  double new_size = double(percent) / 100.0 * double(height);
  if(new_size < 2)
    new_size = 2;
  return resize_y_px((int) new_size, resizer);
}


int Bitmap::Image::getRowLen(int width){
  if(width % 4 == 0){
    return 3*width;
  }
  else{
    return 3*width + 4 - (3*width)%4;
  }
}


void Bitmap::Image::save_to_file(const char* filename, Channel* red, Channel* green, 
    Channel* blue, Channel* gray) throw(BitmapError)
{
  // try to open destination file
  FILE * file = fopen(filename, "wb");
  if(file == NULL){
    BitmapError ex(filename, "Unable to open file for writing");
    throw ex;
  }


  int row_len = getRowLen(width);

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
  bool isMono = gray != NULL;
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
    fwrite(zeros, sizeof(uint8_t), getRowLen(width) - 3*width, file);
  }

  fclose(file);
}




std::ostream& Bitmap::operator<< (std::ostream& out, const BitmapError& err){
  out << "File : " << err.filename << "\n";
  out << "Error : " << err.error << "\n";
  return out;
}

