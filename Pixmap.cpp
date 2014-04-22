#include "Pixmap.h"

Pixmap::Pixmap(const int columnSize, const int rowSize) : 
	columnSize(columnSize), 
	rowSize(rowSize), 
	pixmap(new RGBApixel[columnSize * rowSize]) {}

Pixmap::~Pixmap() {delete [] pixmap;}

RGBApixel *Pixmap::getPixles() {return pixmap;}

const int Pixmap::getRowSize() {return rowSize;}

const int Pixmap::getColumnSize() {return columnSize;}

void Pixmap::setPixelAt(const int column, const int row, const Color color) {
	unsigned int ndx(columnSize * row + column);
   pixmap[ndx].red = color.red * 255;
   pixmap[ndx].green = color.green * 255;
   pixmap[ndx].blue = color.blue * 255;
   pixmap[ndx].alpha = 255;
}

const Color Pixmap::getPixelAt(const int column, const int row) {
	unsigned int ndx(columnSize * row + column);
   return Color(pixmap[ndx].red, pixmap[ndx].green, pixmap[ndx].blue);
}
