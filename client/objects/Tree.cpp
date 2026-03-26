#include "Tree.h"

#include "../../data/Assets.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace objects
      {
        Tree::Tree() : gdp::Structure()
        {
          collider = gdd::getConvexShape(gdd::BIRCH2_COLLIDER_SHAPE);
        }

        Tree::Tree(const Tree& tree) : gdp::Structure(tree)
        {

        }

        Tree& Tree::operator=(const Tree& tree)
        {
          gdp::Structure::operator=(tree);
          return *this;
        }

        Tree::~Tree()
        {

        }
      }
    }
  }
}
