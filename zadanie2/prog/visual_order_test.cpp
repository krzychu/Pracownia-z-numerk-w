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
#define ARG_OUTFILE 5

int main(int argc, char** argv){
  
  if(argc != 6){
    cout << "usage: infile method x y outfile\n";
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

  int x_percent = atoi(argv[ARG_X_PERCENT]);
  int y_percent = atoi(argv[ARG_Y_PERCENT]);

  Resizer* resizer = get_by_name(argv[ARG_METHOD]);
  if(resizer == NULL){
    cout << "Unknown resize method\n";
    return -1;
  }
  
  ResizeStats xy, yx;
  xy = resize_xy_percent(img, x_percent, y_percent, resizer);
  yx = resize_yx_percent(img, x_percent, y_percent, resizer);

  Image* diff = xy.img->diff(yx.img);

  try{
    diff->save(argv[ARG_OUTFILE]);
  }
  catch(BitmapError ex){
    cout << ex;
    return -1;
  }

  
  delete diff;
  delete xy.img;
  delete yx.img;
  delete img;
  return 0;
}

