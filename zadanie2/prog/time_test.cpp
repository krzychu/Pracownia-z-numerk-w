#include <iostream>
#include <cstdlib>
#include "resizers.h"
#include "bitmap.h"

using namespace Bitmap;
using namespace Resizers;
using namespace std;

#define ARG_START 1
#define ARG_END 2 
#define ARG_STEP 3
#define ARG_FILE 4

int main(int argc, char** argv){
  
  if(argc != 5){
    cout << "usage: start end step file\n";
    return -1;
  }

  // load desired image  
  Image* img;
  try{
    img = Image::load(argv[ARG_FILE]);
  } catch(BitmapError e){
    cout << e;
    return -1;
  }

  int start_resize = atoi(argv[ARG_START]);
  int end_resize = atoi(argv[ARG_END]);
  int step_resize = atoi(argv[ARG_STEP]);

  Closest   closest;
  Linear    linear;
  Cubic     cubic;
  Combined  combined;
 
  Resizer* resizers[4] = {&closest, &linear, &cubic, &combined};

  // data file header
  cout << "# test wydajnościowy\n";
  cout << "# obrazek: " << argv[ARG_FILE] << "\n";
  cout << "# szerokość: " << img->getWidth() << "\n";
  cout << "# wysokość: " << img->getHeight() << "\n";
  cout << "# \% closest linear cubic combined\n";

  for(int resize = start_resize; resize < end_resize; resize += step_resize){
    cout << resize  << " ";
  
    ResizeStats a,b;
    for(int method = 0 ; method < 4; method++){
      a = img->resize_x_percent(resize, resizers[method]);
      b = a.img->resize_y_percent(resize, resizers[method]);
      cout << a.time + b.time << " ";
      delete a.img;
      delete b.img;
    } 
    cout << "\n";
  }

  delete img;
  return 0;
}

