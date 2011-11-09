#include "resizers_cubic.h"
#include <inttypes.h>

using namespace Bitmap;
using namespace Resizers;
using namespace std;

inline double p3(double x){
  return x*x*x;
}

vector<double> Resizers::CubicInterpolator::c_prim;

Resizers::CubicInterpolator::CubicInterpolator(const uint8_t* data, int data_size, int offset){
  this->data = data;
  data_offset = offset;
  n = data_size - 1;
  
  // calculate c_prim
  if(c_prim.empty()){
    c_prim.push_back(0); 
    c_prim.push_back(0.25);
  }
 
  for(int i = c_prim.size() ; i < n; i++){
    c_prim.push_back(1.0 / (4.0 - c_prim[i-1]));
  }
  
  // calculate divided diffrences
  ds = new double[n];
  const uint8_t *y = data;
  for(int i = 0; i < n-1; i++){
    ds[i] = 3.0 * (double(*y) + double(*(y + 2*offset))) - 6.0 * double(*(y+offset));
    y += offset;
  }
  

  d_prim = new double[n];
  d_prim[1] = 0.5 * ds[0];
  for(int i = 2; i < n ; i++){
    d_prim[i] = (2.0*ds[i-1] - d_prim[i-1]) / (4.0 - c_prim[i-1]);
  }

  M = new double[n+1];
  M[0] = 0;
  M[n] = 0;
  M[n-1] = d_prim[n-1];
  for(int i=n-2 ; i > 0 ; i--){
    M[i] = d_prim[i] - c_prim[i]*M[i+1];
  }
}

Resizers::CubicInterpolator::~CubicInterpolator(){
  delete[] ds;
  delete[] d_prim;
  delete[] M;
}

double Resizers::CubicInterpolator::operator()(double x) const{
  int k = int(x) + 1;
  if( k > n)
    k = n;
  if( k <= 0)
    k = 1;
  
  double j = 1.0 / 6.0;
  double A = j * M[k-1]; 
  double B = j * M[k]; 
  double C = double(data[data_offset*(k-1)]) - j * M[k-1] ;
  double D = double(data[data_offset*k]) - j * M[k] ;
  double h = double(k) - x;
  double val = A*p3(h) + B*p3(1.0 - h) + C*h + D*(1.0 - h);
  if(val < 0)
    val = 0;
  if(val > 255.0)
    val = 255.0;
  return val;
}


void Resizers::Cubic::do_resize_x(const Channel* src, Channel* dst){
  double x_pos;
  double step = double(src->width - 1) / double(dst->width - 1);
  
  uint8_t *dst_data = dst->data;
  
  for(int y = 0; y < dst->height; y++){
    CubicInterpolator inter(src->data + y*src->width, src->width, 1);
    x_pos = 0;
    for(int x = 0; x < dst->width ; x++){
      *dst_data++ = inter(x_pos);
      x_pos += step;
    }
  }
}

void Resizers::Cubic::do_resize_y(const Channel* src, Channel* dst){
  double y_pos = 0;
  double step = double(src->height - 1) / double(dst->height - 1);
  
  uint8_t *dst_data = dst->data;
  
  for(int x = 0; x < src->width; x++){
    CubicInterpolator inter(src->data + x, src->height, src->width);
    y_pos = 0;
    for(int y = 0; y < dst->height ; y++){
      dst->data[x + y*dst->width] = inter(y_pos);
      y_pos += step;
    }
  }
}
