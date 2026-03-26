#include "Object.h"

#include "../math/Quaternion.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      Object::Object()
      {
        transformation.rotation = gdm::Quaternion(0, gdm::Vector3(1,0,0));
        transformation.position = gdm::Vector3(0.0,0.0,0.0);
        collider = NULL;
        calculateInformation();
      }

      Object::Object(const gdm::Vector3& position)
      {
        transformation.rotation = gdm::Quaternion(0, gdm::Vector3(1,0,0));
        transformation.position = position;
        collider = NULL;
        calculateInformation();
      }

      Object::Object(const Object& object)
      {
        transformation = object.transformation;
        speed = object.speed;
        rotationSpeed = object.rotationSpeed;
        collider = object.collider;
      }

      Object& Object::operator=(const Object& object)
      {
        transformation = object.transformation;
        speed = object.speed;
        rotationSpeed = object.rotationSpeed;
        collider = object.collider;
        return *this;
      }

      Object::~Object()
      {

      }

      void Object::update(float timePassed)
      {

      }

      void Object::calculateInformation()
      {
        transformation.calculate();
        physicalInformation.calculate(transformation);
      }

      gdm::Vector3 Object::getDirection(const gdm::Vector3& v) const
      {
        gdm::Vector3 direction = transformation.rotation.rotate(v);
        direction.normalize();
        return direction;
      }

      float Object::getRotationSpeedAngle() const
      {
        return rotationSpeed.getLength();
      }

      gdm::Vector3 Object::getRotationDirection() const
      {
        gdm::Vector3 direction = rotationSpeed;
        direction.normalize();
        return direction;
      }
    }
  }
}
