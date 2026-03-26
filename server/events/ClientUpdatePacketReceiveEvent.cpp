#include "ClientUpdatePacketReceiveEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace events
      {
        unsigned int ClientUpdatePacketReceiveEvent::getStaticType()
        {
          return gde::SERVER_CLIENT_UPDATE_PACKET_RECEIVE_EVENT;
        }

        ClientUpdatePacketReceiveEvent::ClientUpdatePacketReceiveEvent(unsigned int clientId, const gdm::Vector3* position, const gdm::Vector3* speed, const gdm::Quaternion* rotation, const gdm::Vector3* rotationSpeed)
        {
          this->clientId = clientId;
          this->position = position;
          this->speed = speed;
          this->rotation = rotation;
          this->rotationSpeed = rotationSpeed;
        }

        ClientUpdatePacketReceiveEvent::ClientUpdatePacketReceiveEvent(const ClientUpdatePacketReceiveEvent& event)
        {
          clientId = event.clientId;
          position = event.position;
          speed = event.speed;
          rotation = event.rotation;
          rotationSpeed = event.rotationSpeed;
        }

        ClientUpdatePacketReceiveEvent& ClientUpdatePacketReceiveEvent::operator=(const ClientUpdatePacketReceiveEvent& event)
        {
          clientId = event.clientId;
          position = event.position;
          speed = event.speed;
          rotation = event.rotation;
          rotationSpeed = event.rotationSpeed;
          return *this;
        }

        unsigned int ClientUpdatePacketReceiveEvent::getClientId() const
        {
          return clientId;
        }

        const gdm::Vector3& ClientUpdatePacketReceiveEvent::getPosition() const
        {
          return *position;
        }

        const gdm::Vector3& ClientUpdatePacketReceiveEvent::getSpeed() const
        {
          return *speed;
        }

        const gdm::Quaternion& ClientUpdatePacketReceiveEvent::getRotation() const
        {
          return *rotation;
        }

        const gdm::Vector3& ClientUpdatePacketReceiveEvent::getRotationSpeed() const
        {
          return *rotationSpeed;
        }

        unsigned int ClientUpdatePacketReceiveEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
