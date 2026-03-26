#include "RandomGenerator.h"

#include <math.h>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      RandomGenerator::RandomGenerator(long seed)
      {
        m = 29989;
        a = 172;
        c = 0;
        this->seed = seed;
      }

      RandomGenerator::RandomGenerator(const RandomGenerator& generator)
      {
        m = generator.m;
        a = generator.a;
        c = generator.c;
        seed = generator.seed;
      }

      RandomGenerator& RandomGenerator::operator=(const RandomGenerator& generator)
      {
        m = generator.m;
        a = generator.a;
        c = generator.c;
        seed = generator.seed;
        return *this;
      }

      long RandomGenerator::getValue(long x) const
      {
        return (a * x + c)%m;
      }

      long RandomGenerator::getNext()
      {
        seed = getValue(seed);
        return seed;
      }

      float RandomGenerator::getNextFloat()
      {
        long r = getNext();
        return ((float)r)/((float)(m-1));
      }

      unsigned int RandomGenerator::getIndex(unsigned int x, unsigned int y) const
      {
        unsigned int a = (x + y + 1)*(x + y);
        return (a/2) + y;
      }

      unsigned int RandomGenerator::getIndex(int x) const
      {
        if(x >= 0)
        {
          return 2*x;
        }
        return -2*x + 1;
      }

      float RandomGenerator::getRandomFloat(int x, int y) const
      {
        int w = 9973;
        int k = getValue(seed + w*getIndex(x,y));
        int r = getValue(k);
        return ((float)r)/((float)(m-1));
      }

      float RandomGenerator::getNoise(int x, int y) const
      {
        unsigned int uix = getIndex(x);
        unsigned int uiy = getIndex(y);
        int index = getIndex(uix, uiy);
        int r = getValue(seed + 632*uix + 543*uiy + index);
        return ((float)r)/((float)(m-1));
      }

      float RandomGenerator::getSmoothNoise(int x, int y) const
      {
        float corners = (getNoise(x-1,y-1) + getNoise(x+1,y-1) + getNoise(x+1,y+1) + getNoise(x-1,y+1))/16.0;
        float sides = (getNoise(x-1,y) + getNoise(x,y-1) + getNoise(x+1,y) + getNoise(x,y+1))/8.0;
        float middle = getNoise(x,y)/4.0;
        return corners + sides + middle;
      }

      float RandomGenerator::interpolate(float t, float a, float b) const
      {
        t = (1.0 - t) * M_PI;
        t = (cos(t) + 1)*0.5;
        return a + (b-a)*t;
      }

      float RandomGenerator::getInterpolatedNoise(float x, float y) const
      {
        int iX = (int)x;
        int iY = (int)y;
        float tX = x - (float)iX;
        float tY = y - (float)iY;
        if(x < 0)
        {
          tX = 1 + tX;
          iX--;
        }
        if(y < 0)
        {
          tY = 1+tY;
          iY--;
        }

        float v1 = getSmoothNoise(iX, iY);
        float v2 = getSmoothNoise(iX + 1, iY);
        float v3 = getSmoothNoise(iX + 1, iY + 1);
        float v4 = getSmoothNoise(iX, iY + 1);

        float i1 = interpolate(tX, v1, v2);
        float i2 = interpolate(tX, v4, v3);
        return interpolate(tY, i1, i2);
      }
    }
  }
}
