#include "Pixmap.h"

Pixmap::Pixmap(const int columnSize, const int rowSize) : columnSize(columnSize), rowSize(rowSize), pixmap(new RGBApixel[columnSize * rowSize]) {}

Pixmap::~Pixmap() {delete[] pixmap;}

RGBApixel *Pixmap::getPixles() {return pixmap;}

const int Pixmap::getRowSize() {return rowSize;}

const int Pixmap::getColumnSize() {return columnSize;}

void Pixmap::setPixelAt(const int column, const int row, RGBApixel pixel) {
    pixmap[columnSize * row + column] = pixel;
}

RGBApixel *Pixmap::getPixelAt(const int column, const int row) {
   return &pixmap[columnSize * row + column];
}
