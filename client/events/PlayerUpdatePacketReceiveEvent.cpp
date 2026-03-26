#include "PlayerUpdatePacketReceiveEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        unsigned int PlayerUpdatePacketReceiveEvent::getStaticType()
        {
          return gde::CLIENT_PLAYER_UPDATE_RECEIVE_EVENT;
        }

        PlayerUpdatePacketReceiveEvent::PlayerUpdatePacketReceiveEvent(unsigned int clientId, const gdm::Vector3* position, const gdm::Vector3* speed, const gdm::Quaternion* rotation, const gdm::Vector3* rotationSpeed)
        {
          this->clientId = clientId;
          this->position = position;
          this->speed = speed;
          this->rotation = rotation;
          this->rotationSpeed = rotationSpeed;
        }

        PlayerUpdatePacketReceiveEvent::PlayerUpdatePacketReceiveEvent(const PlayerUpdatePacketReceiveEvent& event)
        {
          clientId = event.clientId;
          position = event.position;
          speed = event.speed;
          rotation = event.rotation;
          rotationSpeed = event.rotationSpeed;
        }

        PlayerUpdatePacketReceiveEvent& PlayerUpdatePacketReceiveEvent::operator=(const PlayerUpdatePacketReceiveEvent& event)
        {
          clientId = event.clientId;
          position = event.position;
          speed = event.speed;
          rotation = event.rotation;
          rotationSpeed = event.rotationSpeed;
          return *this;
        }

        unsigned int PlayerUpdatePacketReceiveEvent::getClientId() const
        {
          return clientId;
        }

        const gdm::Vector3& PlayerUpdatePacketReceiveEvent::getPosition() const
        {
          return *position;
        }

        const gdm::Vector3& PlayerUpdatePacketReceiveEvent::getSpeed() const
        {
          return *speed;
        }

        const gdm::Quaternion& PlayerUpdatePacketReceiveEvent::getRotation() const
        {
          return *rotation;
        }

        const gdm::Vector3& PlayerUpdatePacketReceiveEvent::getRotationSpeed() const
        {
          return *rotationSpeed;
        }

        unsigned int PlayerUpdatePacketReceiveEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
