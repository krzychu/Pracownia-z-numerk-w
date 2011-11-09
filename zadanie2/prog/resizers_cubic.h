#ifndef _RESIZERS_CUBIC_H_
#define _RESIZERS_CUBIC_H_

#include "resizers_base.h"
#include <vector>

namespace Resizers{
  
  class Cubic : public Resizer{
    protected:
      virtual void do_resize_x(const Bitmap::Channel* src, 
         Bitmap::Channel* dst) ;
      virtual void do_resize_y(const Bitmap::Channel* src, 
         Bitmap::Channel* dst) ;
  };

  struct CubicInterpolator{
   
    int n;
    static std::vector<double> c_prim;
    double *d_prim;
    double *ds;
    double *M;

    const uint8_t *data;
    int data_offset;

    CubicInterpolator(const uint8_t *data, int data_size, int offset);
    ~CubicInterpolator();

    double operator()(double x) const;
  };

};

#endif
