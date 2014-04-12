#include "Image.h"

Image::Image() : image(Magick::Image()) {}

void Image::writeImage(String filePath, Pixmap *pixmap) {
   image.read(pixmap->getColumnSize(), pixmap->getRowSize(), "RGBA", Magick::CharPixel, (void *)pixmap->getPixles());
   image.flip();
   image.write(filePath.getString());
}

Pixmap *Image::readImage(String filePath) {
   image.read(filePath.getString());
   image.flip();
   Pixmap *pixmap = new Pixmap(image.columns(), image.rows());
   image.write(0, 0, image.columns(), image.rows(), "RGBA", Magick::CharPixel, (void *)pixmap->getPixles());
   return pixmap;
}
