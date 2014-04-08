#include "Image.h"

Image::Image() : Object(), image(new Magick::Image()) {}

Image::~Image() {delete image;}

void Image::writeImage(String filePath, Pixmap *pixmap) {
   glReadPixels(0, 0, pixmap->getColumnSize(), pixmap->getRowSize(), GL_RGBA, GL_UNSIGNED_BYTE, pixmap->getPixles());
   image->read(pixmap->getColumnSize(), pixmap->getRowSize(), "RGBA", Magick::CharPixel, (void *)pixmap->getPixles());
   image->flip();
   image->write(filePath.getString());
}

Pixmap *Image::readImage(String filePath) {
   image->read(filePath.getString());
   image->flip();
   Pixmap *pixmap = new Pixmap(image->columns(), image->rows());
   image->write(0, 0, image->columns(), image->rows(), "RGBA", Magick::CharPixel, (void *)pixmap->getPixles());
   return pixmap;
}
