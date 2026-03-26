#include "Camera.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      Camera::Camera(const gdm::Vector3& position)
      {
        this->position = position;
      }

      Camera::Camera(const Camera& camera)
      {
        position = camera.position;
        rotation = camera.rotation;
      }

      Camera& Camera::operator=(const Camera& camera)
      {
        position = camera.position;
        rotation = camera.rotation;
        return *this;
      }

      gdm::Vector3& Camera::getPosition()
      {
        return position;
      }

      gdm::Vector3& Camera::getRotation()
      {
        return rotation;
      }

      gdm::Matrix4x4 Camera::getTransformation() const
      {
        gdm::Quaternion qx(-rotation.getX(), gdm::Vector3(1,0,0));
        gdm::Quaternion qy(-rotation.getY(), gdm::Vector3(0,1,0));
        gdm::Quaternion qz(-rotation.getZ(), gdm::Vector3(0,0,1));
        gdm::Matrix4x4 rotationm = (qz*qx*qy).toMatrix4x4();
        gdm::Matrix4x4 translation;
        translation.get(0,3) = -position.getX();
        translation.get(1,3) = -position.getY();
        translation.get(2,3) = -position.getZ();
        return rotationm*translation;
      }

      gdm::Vector3 Camera::getDirection() const
      {
        gdm::Quaternion qx(rotation.getX(), gdm::Vector3(1,0,0));
        gdm::Quaternion qy(rotation.getY(), gdm::Vector3(0,1,0));
        gdm::Quaternion qz(rotation.getZ(), gdm::Vector3(0,0,1));
        return (qy*qx*qz).toMatrix4x4()*gdm::Vector3(0,0,-1);
      }
    }
  }
}
