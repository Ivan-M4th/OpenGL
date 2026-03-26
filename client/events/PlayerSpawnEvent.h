#ifndef GD_CLIENT_EVENTS_PLAYERSPAWNEVENT_H
#define GD_CLIENT_EVENTS_PLAYERSPAWNEVENT_H

#include "../../gddef.h"

#include "../../events/Event.h"

#include "../../utils/Pointer.h"

#include "../objects/Player.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        class PlayerSpawnEvent : public gde::Event
        {
        private:
          unsigned int clientId;
          Pointer<gdco::Player> player;

        public:
          static unsigned int getStaticType();

          PlayerSpawnEvent(unsigned int, const Pointer<gdco::Player>&);
          PlayerSpawnEvent(const PlayerSpawnEvent&);
          PlayerSpawnEvent& operator=(const PlayerSpawnEvent&);

          unsigned int getClientId() const;
          const Pointer<gdco::Player>& getPlayerPointer() const;
          gdco::Player* getPlayer() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
