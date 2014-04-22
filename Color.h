#ifndef COLOR_H
#define COLOR_H

class Color {
   public:
      double red, green, blue;
      Color();
      Color(const double red, const double green, const double blue);
      void setRed(const double red);
      void setGreen(const double green);
      void setBlue(const double blue);
      Color operator+(const Color& color) const;
      Color &operator+=(const Color& color);
      Color operator*(const Color& color) const;
      Color operator*(const double& scalar) const;
      bool operator==(const Color& color) const;
      bool operator!=(const Color& color) const;
};

#endif
