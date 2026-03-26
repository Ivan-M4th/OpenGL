#ifndef GD_MATH_EPA_POLYTOPE_H
#define GD_MATH_EPA_POLYTOPE_H

#include "../../gddef.h"

#include "Face.h"

#include "../Vector3.h"
#include "../Vector2ui.h"

#include "../../utils/ArrayList.h"
#include "../../utils/LinkedList.h"

#include "../geometry/SupportVertex.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace epa
      {
        class Polytope
        {
        private:
          ArrayList<gdmg::SupportVertex> vertices;
          ArrayList<Face> faces;

          gdu::LinkedList<unsigned int> freeFaces;

          Vector3 getNormal(unsigned int) const;
          unsigned int getNextEdge(unsigned int) const;
          unsigned int getPreviousEdge(unsigned int) const;
          unsigned int getFirstUsedFaceId() const;
          bool isVisibleFrom(unsigned int, const Vector3&) const;
          void removeFace(unsigned int);
          unsigned int getNewFaceIndex();
          gdu::LinkedList<Vector2ui> getSilhouette(const Vector3&, unsigned int, unsigned int);
          unsigned int addFace(const Face&);
          void linkEdges(unsigned int, unsigned int, unsigned int, unsigned int);
          unsigned int createConeFace(unsigned int, unsigned int, unsigned int);
          void createCone(unsigned int, gdu::LinkedList<Vector2ui>&);
        public:
          Polytope(const gdmg::SupportVertex&, const gdmg::SupportVertex&, const gdmg::SupportVertex&, const gdmg::SupportVertex&);

          void getClosestFaceId(unsigned int*, float*, Vector3*) const;
          Vector3 getFacePoint(unsigned int) const;
          gdmg::SupportVertex getFaceOriginProjection(unsigned int) const;

          void addVertex(const gdmg::SupportVertex&, unsigned int);
        };
      }
    }
  }
}

#endif
