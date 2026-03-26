#ifndef GD_CLIENT_EVENTS_PLAYERUPDATEPACKETRECEIVEEVENT_H
#define GD_CLIENT_EVENTS_PLAYERUPDATEPACKETRECEIVEEVENT_H

#include "../../gddef.h"

#include "../../events/Event.h"

#include "../../math/Vector3.h"
#include "../../math/Quaternion.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        class PlayerUpdatePacketReceiveEvent : public gde::Event
        {
        private:
          unsigned int clientId;

          const gdm::Vector3* position;
          const gdm::Vector3* speed;
          const gdm::Quaternion* rotation;
          const gdm::Vector3* rotationSpeed;

        public:
          static unsigned int getStaticType();

          PlayerUpdatePacketReceiveEvent(unsigned int, const gdm::Vector3*, const gdm::Vector3*, const gdm::Quaternion*, const gdm::Vector3*);
          PlayerUpdatePacketReceiveEvent(const PlayerUpdatePacketReceiveEvent&);
          PlayerUpdatePacketReceiveEvent& operator=(const PlayerUpdatePacketReceiveEvent&);

          unsigned int getClientId() const;
          const gdm::Vector3& getPosition() const;
          const gdm::Vector3& getSpeed() const;
          const gdm::Quaternion& getRotation() const;
          const gdm::Vector3& getRotationSpeed() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
