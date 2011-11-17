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
#define ARG_OUTFILE 4

int main(int argc, char** argv){
  
  if(argc != 5){
    cout << "usage: start end step file\n";
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
  
  Image* xy, yx;

  ResizeStats a, b;

  delete img;
  return 0;
}

