#ifndef PIXMAP
#define PIXMAP

#include "RGBApixel.h"
#include "Object.h"

class Pixmap : public Object {
   private:
      const int columnSize, rowSize;
      RGBApixel *pixmap;
   public:
      Pixmap(const int columnSize, const int rowSize);
      ~Pixmap();
      RGBApixel *getPixles();
      const int getRowSize();
      const int getColumnSize();
      void setPixelAt(const int column, const int row, RGBApixel pixel);
      RGBApixel *getPixelAt(const int column, const int row);
};

#endif
