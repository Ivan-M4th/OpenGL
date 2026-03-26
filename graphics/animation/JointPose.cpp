#include "JointPose.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      namespace animation
      {
        JointPose::JointPose()
        {
          defaultPose = true;
        }

        JointPose::JointPose(const gdm::Vector3& position, const gdm::Vector3& scale, const gdm::Quaternion& rotation)
        {
          defaultPose = false;
          this->position = position;
          this->scale = scale;
          this->rotation = rotation;
        }

        JointPose::JointPose(const gdm::Matrix4x4& matrix)
        {
          defaultPose = false;
          gdm::Matrix4x4 m = matrix;
          position = gdm::Vector3(m.get(0,3), m.get(1,3), m.get(2,3));
          scale = m.getScale();
          m.unScale();
          rotation = gdm::Quaternion(m);
        }

        JointPose::JointPose(const JointPose& pose)
        {
          defaultPose = pose.defaultPose;
          position = pose.position;
          scale = pose.scale;
          rotation = pose.rotation;
        }

        JointPose& JointPose::operator=(const JointPose& pose)
        {
          defaultPose = pose.defaultPose;
          position = pose.position;
          scale = pose.scale;
          rotation = pose.rotation;
          return *this;
        }

        gdm::Matrix4x4 JointPose::getTransformation() const
        {
          gdm::Matrix4x4 scalem;
          scalem.get(0,0) = scale.getX();
          scalem.get(1,1) = scale.getY();
          scalem.get(2,2) = scale.getZ();
          gdm::Matrix4x4 transformation = rotation.toMatrix4x4()*scalem;
          transformation.get(0,3) = position.getX();
          transformation.get(1,3) = position.getY();
          transformation.get(2,3) = position.getZ();
          return transformation;
        }

        JointPose JointPose::interpolate(float t, const JointPose& pose) const
        {
          gdm::Vector3 tposition = position + t*(pose.position - position);
          gdm::Vector3 tscale = scale + t*(pose.scale - scale);
          gdm::Quaternion troation = rotation.slerp(t, pose.rotation);
          return JointPose(tposition, tscale, troation);
        }

        bool JointPose::isDefaultPose() const
        {
          return defaultPose;
        }
      }
    }
  }
}
