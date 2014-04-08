#ifndef COLOR_H
#define COLOR_H

#include "RGBApixel.h"
#include "EnumColors.h"

class Color {
   private:
      double red, green, blue, alpha;
   public:
      Color();
      Color(const RGBApixel *pixel);
      Color(const enum Colors color);
      Color(const double red, const double green, const double blue);
      Color(const double red, const double green, const double blue, const double alpha);
      const RGBApixel toPixel() const;
      const double getRed() const;
      const double getGreen() const;
      const double getBlue() const;
      const double getAlpha() const;
      void setRed(const double red);
      void setGreen(const double green);
      void setBlue(const double blue);
      void setAlpha(const double alpha);
      Color operator+(const Color& color) const;
      Color &operator+=(const Color& color);
      Color operator*(const Color& color) const;
      Color operator*(const double& scalar) const;
      bool operator==(const Color& color) const;
      bool operator!=(const Color& color) const;
};

#endif
