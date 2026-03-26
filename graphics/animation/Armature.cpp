#include "Armature.h"

#include <iostream>
#include <cassert>

using namespace gt::doubovik::math;

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        Armature::Armature()
        {
          jointAmount = 0;
          rootJoint = NULL;
        }

        Armature::Armature(unsigned int jointAmount, Joint* rootJoint)
        {
          this->jointAmount = jointAmount;
          this->rootJoint = rootJoint;
        }

        Armature::Armature(const Armature& armature)
        {
          jointAmount = armature.jointAmount;
          if(armature.rootJoint != NULL)
          {
            rootJoint = new Joint(*armature.rootJoint);
          }
        }

        Armature& Armature::operator=(const Armature& armature)
        {
          deleteData();
          jointAmount = armature.jointAmount;
          if(armature.rootJoint != NULL)
          {
            rootJoint = new Joint(*armature.rootJoint);
          }
          return *this;
        }

        Armature::~Armature()
        {
          deleteData();
        }

        void Armature::deleteData()
        {
          delete rootJoint;
        }

        unsigned int Armature::getJointAmount() const
        {
          return jointAmount;
        }

        void Armature::applyPose(Joint* joint, const JointPose* pose, const gdm::Matrix4x4& parentTransformation)
        {
          int index = joint->getIndex();
          gdm::Matrix4x4 localTransformation;
          if((pose + index)->isDefaultPose())
          {
            localTransformation = joint->getLocalDefaultTransformation();
          }
          else
          {
            localTransformation = (pose + index)->getTransformation();
          }

          gdm::Matrix4x4 transformation = parentTransformation * localTransformation;
          for(unsigned int i=0;i<joint->children.size();i++)
          {
            applyPose(joint->children[i], pose, transformation);
          }
          joint->transformation = transformation;
        }

        void Armature::applyPose(const JointPose* pose, const gdm::Matrix4x4& rootTransformation)
        {
          applyPose(rootJoint, pose, rootTransformation);
        }

        void Armature::applyPose(const JointPose* pose)
        {
          applyPose(pose, gdm::Matrix4x4());
        }

        void Armature::getPose(Joint* joint, gdm::Matrix4x4* pose) const
        {
          *(pose + joint->getIndex()) = joint->getRelativeTransformation();
          for(unsigned int i=0;i<joint->children.size(); i++)
          {
            getPose(joint->children[i], pose);
          }
        }

        void Armature::getPose(gdm::Matrix4x4* pose) const
        {
          getPose(rootJoint, pose);
        }

        Joint* Armature::getRoot()
        {
          return rootJoint;
        }

        Joint* Armature::getJoint(unsigned int index, Joint& joint)
        {
          if(joint.getIndex() == index)
          {
            return &joint;
          }
          for(unsigned int i=0;i<joint.children.size();i++)
          {
            Joint* found = getJoint(index, joint.children[i]);
            if(found != NULL)
            {
              return found;
            }
          }
          return NULL;
        }

        Joint* Armature::getJoint(unsigned int index)
        {
          Joint* joint = getJoint(index, rootJoint);
          if(joint == NULL)
          {
            std::cerr << "ERROR JOINT NOT FOUND: " << index << std::endl;
            throw("joint not found!");
          }
          return joint;
        }

        Joint* Armature::getJoint(const gdu::String& name, Joint* joint)
        {
          if(joint->getName() == name)
          {
            return joint;
          }
          for(unsigned int i=0; i < joint->children.size();i++)
          {
            Joint* found = getJoint(name, joint->children[i]);
            if(found != NULL)
            {
              return found;
            }
          }
          return NULL;
        }

        Joint* Armature::getJoint(const gdu::String& name)
        {
          return getJoint(name, rootJoint);
        }

        int Armature::getJointId(const gdu::String& name)
        {
          Joint* joint = getJoint(name);
          assert(joint != NULL && "Error joint not found!");
          return joint->getIndex();
        }
      }
    }
  }
}
