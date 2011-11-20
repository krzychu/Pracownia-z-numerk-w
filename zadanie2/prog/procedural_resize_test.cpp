#include <iostream>
#include "resizers.h"
#include "bitmap.h"
#include <cstring>

using namespace std;
using namespace Bitmap;
using namespace Resizers;

#define START 10
#define END 511
#define STEP 20

#define SIZE 200

typedef BWImage* (*ImageCreator)(int, int);

int main(int argc, char** argv){
  
  if(argc != 3){
    cout << "usage: method image\n";
  }

  Resizer * resizer = get_by_name(argv[1]);
  if(resizer == NULL){
    cout << "unknown resizer";
    return -1;
  }


  ImageCreator fun;
  if(0 == strcmp(argv[2], "sin"))
     fun = sinImage;
  else if(0 == strcmp(argv[2], "saw"))
     fun = sawImage;
  else if(0 == strcmp(argv[2], "runge"))
     fun = rungeImage;
  else{
    cout << "unknown image type\n";
    return -1;
  }
  
  
  // image to be resized
  Image* img = fun(SIZE, SIZE);
  
  for(int x_percent = START; x_percent < END; x_percent += STEP){   
    for(int y_percent = START; y_percent < END; y_percent += STEP){
      
      ResizeStats rs = resize_xy_percent(img, x_percent, y_percent, resizer);
      Image* reference = fun(rs.img->getWidth(), rs.img->getHeight());
      Image* diff = rs.img->diff(reference);

      cout << x_percent << " " << y_percent << " " << diff->norm() << "\n";

      delete diff;
      delete rs.img;
      delete reference;
    }
    cout << "\n";
  }
 
  delete img;
  delete resizer;

  return 0;
}
