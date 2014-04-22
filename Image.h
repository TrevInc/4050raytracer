#ifndef IMAGE_H
#define IMAGE_H

#include "Magick++.h"
#include "Pixmap.h"
#include "String.h"

class Image {
   private:
      Magick::Image image;
   public:
      Image();
      Pixmap *readImage(String filePath);
      void writeImage(String filePath, Pixmap *pixmap);
};

#endif
