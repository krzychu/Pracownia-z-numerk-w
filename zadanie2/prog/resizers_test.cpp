#include <iostream>
#include <cstring>
#include <cstdlib>
#include "resizers.h"
#include "bitmap.h"

using namespace std;
using namespace Resizers;
using namespace Bitmap;


int main(int argc, char** argv){
  if(argc != 7){
    cout << "usage: resizers_test.run infile method order \%x \%y outfile\n" ;
    return -1;
  }
  
  // load
  Image* img;
  try{
    img = Image::load(argv[1]);
  }
  catch(BitmapError e){
    cout << e;
    return -1;
  }
  cout << "file : " << argv[1] << " was loaded successfuly\n";


  // guess resizer type
  Resizer* resizer = get_by_name(argv[2]);
  if(resizer == NULL){
    cout << "Unknown resize method\n"; 
    return -1;
  }

  // guess resize order
  #define X_FIRST 1
  #define Y_FIRST 2
  int order;
  if( 0 == strcmp(argv[3], "xy")){
    order = X_FIRST;
  }
  else{
    order = Y_FIRST;
  }

  // format other parameters
  int x_percent = atoi(argv[4]);
  int y_percent = atoi(argv[5]);
  cout << "x resize : " << x_percent << " \%\n";
  cout << "y resize : " << y_percent << " \%\n";


  // resize
  ResizeStats rs;
  if(order == X_FIRST){
    rs = resize_xy_percent(img, x_percent, y_percent, resizer);
  }
  else{
    rs = resize_yx_percent(img, x_percent, y_percent, resizer);
  }
  cout << "resize time : " << rs.time << "\n";


  delete resizer;

  // save 
  try{
    rs.img->save(argv[6]);
  }
  catch(BitmapError ex){
    cout << ex;
    return -1;
  }

  cout << "file : " << argv[6] << " was saved successfuly\n";

  delete rs.img;
  delete img;
  return 0;
}
