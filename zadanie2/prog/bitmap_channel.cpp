#include "bitmap_channel.h"

Bitmap::Channel::Channel(uint32_t w, uint32_t h){
  width = w;
  height = h;
  data = new uint8_t[w*h];
}

Bitmap::Channel::~Channel(){
  delete[] data;
}


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


