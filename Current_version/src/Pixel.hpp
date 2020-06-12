#ifndef PIXEL_HPP
#define PIXEL_HPP

class Pixel {
public:
  // Constructors
  Pixel();
  Pixel(int a, int b, int c);
  // Affectation
  void assign(int a, int b, int c);
  Pixel& operator=(const Pixel& p);
  // Getters
  int getX() const;
  int getY() const;
  int getZ() const;
private:
  int x, y, z;
};

#endif
