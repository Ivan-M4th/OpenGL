#ifndef GD_GRAPHICS_CAMERA_H
#define GD_GRAPHICS_CAMERA_H

#include "../gddef.h"

#include "../math/Vector3.h"
#include "../math/Quaternion.h"
#include "../math/Matrix4x4.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      class Camera
      {
      private:
        gdm::Vector3 position;
        gdm::Vector3 rotation;
      public:
        Camera(const gdm::Vector3&);
        Camera(const Camera&);
        Camera& operator=(const Camera&);
        gdm::Vector3& getPosition();
        gdm::Vector3& getRotation();
        gdm::Matrix4x4 getTransformation() const;
        gdm::Vector3 getDirection() const;
      };
    }
  }
}

#endif
