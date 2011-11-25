#include <iostream>
#include <cstdlib>
#include "resizers.h"
#include "bitmap.h"

using namespace Bitmap;
using namespace Resizers;
using namespace std;

#define ARG_INFILE 1
#define ARG_X_PERCENT 3 
#define ARG_Y_PERCENT 4
#define ARG_METHOD 2 
#define ARG_DIFF_OUT 5
#define ARG_IMG_OUT 6



int main(int argc, char** argv){
  
  if(argc != 7){
    cout << "usage: infile method x y outfile_diff outfile_image\n";
    return -1;
  }

  // load desired image  
  Image* img;
  try{
    img = Image::load(argv[ARG_INFILE]);
  } catch(BitmapError e){
    cout << e;
    return -1;
  }

  double x_percent = atoi(argv[ARG_X_PERCENT]);
  double y_percent = atoi(argv[ARG_Y_PERCENT]);

  int old_width = img->getWidth();
  int old_height = img->getHeight();
  int new_width = double(old_width) * x_percent / 100.0;
  int new_height = double(old_height) * x_percent / 100.0;
  
  cout << "old dimensions : " << old_width << " " << old_height << "\n";
  cout << "new dimensions : " << new_width << " " << new_height << "\n";

  Resizer* resizer = get_by_name(argv[ARG_METHOD]);
  if(resizer == NULL){
    cout << "Unknown resize method\n";
    return -1;
  }

  ResizeStats r1, r2;
  r1 = img->resize_x_px(new_width, resizer);
  r2 = r1.img->resize_y_px(new_height, resizer);
  delete r1.img;
  r1 = r2.img->resize_x_px(old_width, resizer);
  delete r2.img;
  r2 = r1.img->resize_y_px(old_height, resizer);
  delete r1.img;

  Image *diff = r2.img->diff(img);

  try{
    diff->save(argv[ARG_DIFF_OUT]);
    r2.img->save(argv[ARG_IMG_OUT]);
  }
  catch(BitmapError ex){
    cout << ex;
    return -1;
  }
  
  delete diff;
  delete r2.img;
  delete resizer;  
  delete img;
  return 0;
}

