#ifndef _BITMAP_IMAGE_H_
#define _BITMAP_IMAGE_H_

#include <iostream>
#include <inttypes.h>
#include "bitmap_channel.h"

namespace Bitmap{
  
  
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



  class Image{
    private:
      // true if image is monochromatic
      bool isMono;

      int width;
      int height;

      Channel* red;
      Channel* green;
      Channel* blue;

      Channel* gray;

      void set(const Image& other);
      void decAllRefs();
      void incAllRefs();
    
    public:
      Image(const char* filename) throw(BitmapError);
      Image(Channel* r, Channel* g, Channel*b);
      Image(Channel* g);
      Image(const Image& other);
      void operator =(const Image& other);
      ~Image();

    friend std::ostream& operator << (std::ostream& out, const Image& image);
  };

  std::ostream& operator << (std::ostream& out, const Image& image);

}

#endif
