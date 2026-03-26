#ifndef GD_MATH_RANDOMGENERATOR_H
#define GD_MATH_RANDOMGENERATOR_H

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class RandomGenerator
      {
      private:
        long seed;
        long a;
        long m;
        long c;
        long getValue(long) const;
        float interpolate(float, float, float) const;
        unsigned int getIndex(unsigned int, unsigned int) const;
        unsigned int getIndex(int) const;

      public:
        RandomGenerator(long);
        RandomGenerator(const RandomGenerator&);
        RandomGenerator& operator=(const RandomGenerator&);
        long getNext();
        float getNextFloat();
        float getRandomFloat(int, int) const;
        float getNoise(int, int) const;
        float getSmoothNoise(int, int) const;
        float getInterpolatedNoise(float, float) const;
      };
    }
  }
}

#endif
