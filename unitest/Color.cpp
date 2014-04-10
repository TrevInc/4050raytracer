#include "Color.h"

Color::Color() : red(0), green(0), blue(0), alpha(1) {}

Color::Color(const double red, const double green, const double blue) : 
	red(red<1?red:1), 
	green(green<1?green:1), 
	blue(blue<1?blue:1),
	alpha(1) {}
	
Color::Color(const double red, const double green, const double blue, const double alpha) : 
	red(red<1?red:1), 
	green(green<1?green:1), 
	blue(blue<1?blue:1),
	alpha(alpha<1?alpha:1) {}

Color::Color(const enum Colors color) : red(0), green(0), blue(0), alpha(1) {
	switch (color) {
      case WHITE:
         red = 1; green = 1; blue = 1;
         break;
      case RED:
         red = 1;
         break;
      case GREEN:
         green = 1;
         break;
      case BLUE:
         blue = 1;
         break;
      case ORANGE:
         red = 1; green = 0.64705882;
         break;
      case PURPLE:
         red = 0.7841373; blue = 0.7841373;
         break;
      case DARK_PURPLE:
         red = 0.745098; green = 0.19607843; blue = 0.82352941;
         break;
      case MAGENTA:
         red = 1; blue = 1;
         break;
      case CYAN:
         green = 1; blue = 1;
         break;
      case YELLOW:
         red = 1; green = 1; 
         break;
      case BLACK:
      	break;
   }
}

const RGBApixel Color::toPixel() const {
    RGBApixel pixel;
    pixel.red = red * 255;
    pixel.green = green * 255;
    pixel.blue = blue * 255;
    pixel.alpha = 255;
    return pixel;
}

void Color::setRed(const double red) {red<1?this->red=red:this->red=1;}

void Color::setGreen(const double green) {green<1?this->green=green:this->green=1;}

void Color::setBlue(const double blue) {blue<1?this->blue=blue:this->blue=1;}

void Color::setAlpha(const double alpha) {alpha<1?this->alpha=blue:this->alpha=1;}

const double Color::getRed() const {return red;}

const double Color::getGreen() const {return green;}

const double Color::getBlue() const {return blue;}

const double Color::getAlpha() const {return blue;}

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
