#include "resizers_cubic.h"
#include <inttypes.h>

using namespace Bitmap;
using namespace Resizers;


inline double p3(double x){
  return x*x*x;
}

void Resizers::Cubic::do_resize_x(const Channel* src, Channel* dst){
  double x_pos;
  double step = double(src->width - 1) / double(dst->width - 1);
  
  uint8_t *dst_data = dst->data;
  uint8_t *src_data = src->data;
  uint8_t *ys;

  double prev, next;

  // calculate c_prim
  int n = src->width - 1;
  double c_prim[n];
  c_prim[1] = 0.25;
  for(int i = 2 ; i < n; i++){
    c_prim[i] = 1.0 / (4.0 - c_prim[i-1]);
  }

  for(int y = 0; y < dst->height; y++){
    ys = src_data + y * src->width;

    // calculate divided diffrences for this row
    double ds[n];
    for(int i = 0; i < n-1; i++){
      ds[i] = 3.0 * (double(ys[i]) + double(ys[i+2])) - 6.0 * double(ys[i+1]);
    }

    double d_prim[n];
    d_prim[1] = 0.5 * ds[0];
    for(int i = 2; i < n ; i++){
      d_prim[i] = (2.0*ds[i-1] - d_prim[i-1]) / (4.0 - c_prim[i-1]);
    }

    double M[n+1];
    M[0] = 0;
    M[n] = 0;
    M[n-1] = d_prim[n-1];
    for(int i=n-2 ; i > 0 ; i--){
      M[i] = d_prim[i] - c_prim[i]*M[i+1];
    }

    x_pos = 0;
    for(int x = 0; x < dst->width ; x++){
      int k = int(x_pos) + 1;
      if( k > n)
        k = n;
      if( k <= 0)
        k = 1;
      
      double j = 1.0 / 6.0;
      double A = j * M[k-1]; 
      double B = j * M[k]; 
      double C = double(ys[k-1]) - j * M[k-1] ;
      double D = double(ys[k]) - j * M[k] ;
      double h = double(k) - double(x_pos);
      double val = A*p3(h) + B*p3(1.0 - h) + C*h + D*(1.0 - h);
      if(val < 0)
        val = 0;
      if(val > 255.0)
        val = 255.0;
      dst_data[x + y * dst->width] = val;
      x_pos += step;
    }
  }
}

void Resizers::Cubic::do_resize_y(const Channel* src, Channel* dst){
  double step = double(src->height - 1) / double(dst->height - 1);
  
  uint8_t *dst_data = dst->data;
  uint8_t *src_data = src->data;
  
  double prev, next;

  double y_pos = step;
  int y_pos_int;
  for(int y = 0; y < dst->height-1; y++){
    y_pos_int = src->width * int(y_pos);
    for(int x = 0; x < dst->width; x++){
      prev = src_data[x + y_pos_int];
      next = src_data[x + src->width + y_pos_int];
      *dst_data = next*(y_pos - int(y_pos)) + prev*(int(y_pos) + 1 - y_pos);
      dst_data++;
    }
    y_pos += step;
  }

  // lower border
  for(int x = 0 ; x < src->width ; x++){
    *dst_data = src_data[x + src->width*(src->height-1)];
    dst_data++;
  }
}
