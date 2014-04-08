#ifndef IMAGE_H
#define IMAGE_H

#include "Magick++.h"
#include "Pixmap.h"
#include "Object.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

class Image : public Object {
   private:
      Magick::Image *image;
   public:
      Image();
      ~Image();
      Pixmap *readImage(String filePath);
      void writeImage(String filePath, Pixmap *pixmap);
};

#endif
