#ifndef GD_UTILS_OUTERSPIRALITERATOR_H
#define GD_UTILS_OUTERSPIRALITERATOR_H

namespace gt
{
  namespace doubovik
  {
    class OuterSpiralIterator
    {
    private:
      int sizex;
      int sizey;

      int currentMode;
      int w;
      int h;
      int x;
      int y;
    public:
      OuterSpiralIterator(int, int);
      OuterSpiralIterator(const OuterSpiralIterator&);
      OuterSpiralIterator& operator=(const OuterSpiralIterator&);

      void goRight();
      void goDown();
      void goLeft();
      void goUp();

      void next();
      bool isValid() const;
      int getX() const;
      int getY() const;
    };
  }
}

#endif
