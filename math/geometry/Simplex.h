#ifndef GD_MATH_GEOMETRY_SIMPLEX_H
#define GD_MATH_GEOMETRY_SIMPLEX_H

#include "SupportVertex.h"
#include "../Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        class Simplex
        {
        private:
          const Vector3* location;
          SupportVertex* positions;
          unsigned int size;

          void processLine(const SupportVertex&);
          void processTriangle(const SupportVertex&);
          void processTetrahedron(const SupportVertex&);

          void calculateBC(float*, float*, bool*) const;
          void calculateBC(float*, float*, float*, bool*) const;
        public:
          Simplex(const Vector3*);
          Simplex(const Simplex&);
          Simplex& operator=(const Simplex&);
          ~Simplex();

          unsigned int getSize() const;
          const SupportVertex& operator[](unsigned int) const;
          void forceAdd(const SupportVertex&);
          bool contains(const SupportVertex&) const;
          void add(const SupportVertex&);
          void getClosestPosition(SupportVertex*, bool*) const;
        };
      }
    }
  }
}

#endif
