#include "OuterSpiralIterator.h"

namespace gt
{
  namespace doubovik
  {
    OuterSpiralIterator::OuterSpiralIterator(int sizex, int sizey)
    {
      this->sizex = sizex;
      this->sizey = sizey;

      currentMode = 0;
      w = 1;
      h = 1;
      x = 0;
      y = 0;
    }

    OuterSpiralIterator::OuterSpiralIterator(const OuterSpiralIterator& itt)
    {
      sizex = itt.sizex;
      sizey = itt.sizey;

      currentMode = itt.currentMode;
      w = itt.w;
      h = itt.h;
      x = itt.x;
      y = itt.y;
    }

    OuterSpiralIterator& OuterSpiralIterator::operator=(const OuterSpiralIterator& itt)
    {
      sizex = itt.sizex;
      sizey = itt.sizey;

      currentMode = itt.currentMode;
      w = itt.w;
      h = itt.h;
      x = itt.x;
      y = itt.y;
      return *this;
    }

    void OuterSpiralIterator::goRight()
    {
      x++;
      if(x >= w)
      {
        currentMode = 1;
      }
    }

    void OuterSpiralIterator::goDown()
    {
      y--;
      if(y <= -h)
      {
        currentMode = 2;
      }
    }

    void OuterSpiralIterator::goLeft()
    {
      x--;
      if(x <= -w)
      {
        w++;
        currentMode = 3;
      }
    }

    void OuterSpiralIterator::goUp()
    {
      y++;
      if(y >= h)
      {
        h++;
        currentMode = 0;
      }
    }

    void OuterSpiralIterator::next()
    {
      if(currentMode == 0)
      {
        goRight();
      }
      else if(currentMode == 1)
      {
        goDown();
      }
      else if(currentMode == 2)
      {
        goLeft();
      }
      else if(currentMode == 3)
      {
        goUp();
      }
    }

    bool OuterSpiralIterator::isValid() const
    {
      return x >= -sizex && x <= sizex && y >= -sizey && y <= sizey;
    }

    int OuterSpiralIterator::getX() const
    {
      return sizex + x;
    }

    int OuterSpiralIterator::getY() const
    {
      return sizey + y;
    }
  }
}
