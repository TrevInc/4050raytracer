#include "Color.h"

Color::Color() : red(0), green(0), blue(0) {}

Color::Color(const double red, const double green, const double blue) : 
	red(red<1?red:1), 
	green(green<1?green:1), 
	blue(blue<1?blue:1) {}

void Color::setRed(const double red) {red<1?this->red=red:this->red=1;}

void Color::setGreen(const double green) {green<1?this->green=green:this->green=1;}

void Color::setBlue(const double blue) {blue<1?this->blue=blue:this->blue=1;}

Color &Color::operator+=(const Color& color) {
   red += color.red;
   if (red > 1) red = 1;
   green += color.green;
   if (green > 1) green = 1;
   blue += color.blue;
   if (blue > 1) blue = 1;
   return *this;
}

Color Color::operator+(const Color& color) const {
   return Color(red + color.red, green + color.green, blue + color.blue);
}
      
Color Color::operator*(const Color& color) const {
   return Color(red * color.red, green * color.green, blue * color.blue);
}

Color Color::operator*(const double& scalar) const {
   return Color(red * scalar, green * scalar, blue * scalar);
}

bool Color::operator==(const Color& color) const {
	if (red != color.red || green != color.green || blue != color.blue) return false;
   return true;
}

bool Color::operator!=(const Color& color) const {
	if (red != color.red || green != color.green || blue != color.blue) return true;
   return false;
}
