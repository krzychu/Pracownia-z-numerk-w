#ifndef _BITMAP_IMAGE_H_
#define _BITMAP_IMAGE_H_

#include <iostream>
#include <inttypes.h>
#include "bitmap_channel.h"
#include "resizers_base.h"

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

  class Image;  
  struct ResizeStats{
    long time;
    Image* img;
  };


  class Image{
    protected:
      int width;
      int height;
      static int getRowLen(int w);    
      
      void save_to_file(const char* filename, Channel* r, Channel* g, 
          Channel* b, Channel* gray) throw(BitmapError);
    public:
      virtual ~Image(){};
      
      // loading
      static Image* load(const char* filename) throw(BitmapError);

      // saving
      virtual void save(const char* filename) throw(BitmapError) = 0;
  
      // resizing
      virtual ResizeStats resize_x_px(int newsize, Resizers::Resizer* resizer) = 0;
      virtual ResizeStats resize_y_px(int newsize, Resizers::Resizer* resizer) = 0;
    
      // diffrence
      virtual Image* diff(const Image* other) const = 0;

      // size
      int getWidth() const;
      int getHeight() const;

      // norm
      virtual double norm() const = 0;

      ResizeStats resize_x_percent(int percent, Resizers::Resizer* resizer);
      ResizeStats resize_y_percent(int percent, Resizers::Resizer* resizer);
  };




  class RGBImage : public Image{
    private:
      Channel* red;
      Channel* green;
      Channel* blue;
      
    public:
      RGBImage(Channel* r, Channel* g, Channel* b);
   
      virtual void save(const char* filename) throw(BitmapError);
      virtual ~RGBImage();
      
      virtual ResizeStats resize_x_px(int newsize, Resizers::Resizer* resizer);
      virtual ResizeStats resize_y_px(int newsize, Resizers::Resizer* resizer);
      virtual Image* diff(const Image* other) const;
      virtual double norm() const;


    friend std::ostream& operator << (std::ostream& out, const RGBImage& image);
  };

  std::ostream& operator << (std::ostream& out, const RGBImage& image);




  class BWImage : public Image{
    private:
      Channel* gray;
 
    public:
      BWImage(Channel* g);
      virtual ~BWImage();

      virtual void save(const char* filename) throw(BitmapError);
      
      virtual ResizeStats resize_x_px(int newsize, Resizers::Resizer* resizer);
      virtual ResizeStats resize_y_px(int newsize, Resizers::Resizer* resizer);
      virtual Image* diff(const Image* other) const;
      virtual double norm() const;

    friend std::ostream& operator << (std::ostream& out, const BWImage& image);
  };
  
  std::ostream& operator << (std::ostream& out, const BWImage& image);

};

#endif
