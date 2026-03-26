#ifndef GD_GRAPHICS_ANIMATION_JOINT_H
#define GD_GRAPHICS_ANIMATION_JOINT_H

#include "../../gddef.h"

#include "../../utils/String.h"
#include "../../utils/ArrayList.h"
#include "../../math/Matrix4x4.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        class Joint
        {
        private:
          unsigned int index;
          gdu::String name;

          gdm::Matrix4x4 localDefaultTransformation;

          gdm::Matrix4x4 defaultTransformation;
          gdm::Matrix4x4 inverseDefaultTransformation;

          void deleteData();
          void copyChildren(const ArrayList<Joint*>&);
        public:
          gdm::Matrix4x4 transformation;
          ArrayList<Joint*> children;

          Joint();
          Joint(unsigned int, const gdu::String&, const gdm::Matrix4x4&);
          Joint(const Joint&);
          Joint& operator=(const Joint&);
          ~Joint();

          gdm::Matrix4x4 getRelativeTransformation();

          const gdm::Matrix4x4& getDefaultTransformation() const;
          const gdm::Matrix4x4& getLocalDefaultTransformation() const;
          gdm::Matrix4x4& getInverseDefaultTransformation();
          unsigned int getIndex() const;
          gdu::String getName() const;
          void getChildrenIds(ArrayList<unsigned int>*) const;

          void calculateInverseDefaultTransformation(const gdm::Matrix4x4&);
          void transform(const gdm::Matrix4x4&, const gdm::Matrix4x4&);
        };
      }
    }
  }
}

#endif
