#ifndef _BITMAP_CHANNEL_H_
#define _BITMAP_CHANNEL_H_

#include <iostream>
#include <inttypes.h>

namespace Bitmap{
  
  struct Channel{
    int n_refs;
    int width;
    int height;
    uint8_t *data;

    Channel(uint32_t w, uint32_t h);
    ~Channel();
    void incRefs();
    void decRefs();
  };

  std::ostream& operator << (std::ostream& out, const Channel& channel);


}

#endif
