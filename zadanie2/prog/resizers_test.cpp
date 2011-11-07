#include <iostream>
#include <cstring>
#include <cstdlib>
#include "resizers.h"
#include "bitmap.h"

using namespace std;
using namespace Resizers;
using namespace Bitmap;



int main(int argc, char** argv){
  if(argc != 6){
    cout << "usage: resizers_test.run infile method \%x \%y outfile\n" ;
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
  Resizer* resizer;
  cout << "resize method : ";
  if(0 == strcmp(argv[2], "closest")){
    resizer = new Closest();
    cout << "closest point\n";
  }
  else if(0 == strcmp(argv[2], "linear")){
    resizer = new Linear();
    cout << "linear\n";
  }
  else{
    cout << "Unknown resize method\n"; 
    return -1;
  }
  
  // format other parameters
  int x_percent = atoi(argv[3]);
  int y_percent = atoi(argv[4]);
  cout << "x resize : " << x_percent << " \%\n";
  cout << "y resize : " << y_percent << " \%\n";


  // resize
  ResizeStats rs = img->resize_x_percent(x_percent, resizer);
  cout << "X resize time in us : " << rs.time << "\n";
  rs = rs.img->resize_y_percent(y_percent, resizer);
  cout << "Y resize time in us : " << rs.time << "\n";
  delete resizer;

  // save 
  try{
    rs.img->save(argv[5]);
  }
  catch(BitmapError ex){
    cout << ex;
    return -1;
  }

  cout << "file : " << argv[5] << " was saved successfuly\n";

  delete rs.img;
  delete img;
  return 0;
}
