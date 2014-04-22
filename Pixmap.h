#ifndef PIXMAP_H
#define PIXMAP_H

#include "Color.h"

struct RGBApixel {
   unsigned char red, green, blue, alpha;
};

class Pixmap {
   private:
      const int columnSize, rowSize;
      RGBApixel *pixmap;
   public:
      Pixmap(const int columnSize, const int rowSize);
      ~Pixmap();
      RGBApixel *getPixles();
      const int getRowSize();
      const int getColumnSize();
      void setPixelAt(const int column, const int row, const Color color);
      const Color getPixelAt(const int column, const int row);
};

#endif
