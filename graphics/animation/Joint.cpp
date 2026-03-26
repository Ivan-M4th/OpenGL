#include "Joint.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {

        Joint::Joint()
        {

        }

        Joint::Joint(unsigned int index, const gdu::String& name, const gdm::Matrix4x4& localDefaultTransformation)
        {
          this->index = index;
          this->name = name;
          this->localDefaultTransformation = localDefaultTransformation;
        }

        Joint::Joint(const Joint& joint)
        {
          index = joint.index;
          name = joint.name;
          copyChildren(joint.children);

          transformation = joint.transformation;
          localDefaultTransformation = joint.localDefaultTransformation;

          defaultTransformation = joint.defaultTransformation;
          inverseDefaultTransformation = joint.inverseDefaultTransformation;
        }

        Joint& Joint::operator=(const Joint& joint)
        {
          deleteData();
          index = joint.index;
          name = joint.name;
          copyChildren(joint.children);

          transformation = joint.transformation;
          localDefaultTransformation = joint.localDefaultTransformation;

          defaultTransformation = joint.defaultTransformation;
          inverseDefaultTransformation = joint.inverseDefaultTransformation;
          return *this;
        }

        Joint::~Joint()
        {
          deleteData();
        }

        void Joint::deleteData()
        {
          for(unsigned int i=0;i<children.size();i++)
          {
            delete children[i];
          }
          children.clear();
        }

        void Joint::copyChildren(const ArrayList<Joint*>& newChildren)
        {
          for(unsigned int i=0;i<newChildren.size();i++)
          {
            children.add(new Joint(*newChildren[i]));
          }
        }

        gdu::String Joint::getName() const
        {
          return name;
        }

        gdm::Matrix4x4 Joint::getRelativeTransformation()
        {
          return transformation*inverseDefaultTransformation;
        }

        const gdm::Matrix4x4& Joint::getDefaultTransformation() const
        {
          return defaultTransformation;
        }

        const gdm::Matrix4x4& Joint::getLocalDefaultTransformation() const
        {
          return localDefaultTransformation;
        }

        gdm::Matrix4x4& Joint::getInverseDefaultTransformation()
        {
          return inverseDefaultTransformation;
        }

        unsigned int Joint::getIndex() const
        {
          return index;
        }

        void Joint::getChildrenIds(ArrayList<unsigned int>* ids) const
        {
          ids->add(index);
          for(unsigned int i=0;i<children.size();i++)
          {
            children[i]->getChildrenIds(ids);
          }
        }

        void Joint::transform(const gdm::Matrix4x4& parentTransformation, const gdm::Matrix4x4& newTransformation)
        {
          transformation = parentTransformation * newTransformation;
        }

        void Joint::calculateInverseDefaultTransformation(const gdm::Matrix4x4& parentTransformation)
        {
          defaultTransformation = parentTransformation*localDefaultTransformation;
          inverseDefaultTransformation = defaultTransformation.invert();
          for(unsigned int i=0;i<children.size();i++)
          {
            children[i]->calculateInverseDefaultTransformation(defaultTransformation);
          }
          transformation = defaultTransformation;
        }
      }
    }
  }
}
