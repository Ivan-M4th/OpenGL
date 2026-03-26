#ifndef GD_CLIENT_EVENTS_MAINPLAYERSPAWNEVENT_H
#define GD_CLIENT_EVENTS_MAINPLAYERSPAWNEVENT_H

#include "../../gddef.h"

#include "../../events/Event.h"

#include "../../utils/Pointer.h"

#include "../objects/MainPlayer.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        class MainPlayerSpawnEvent : public gde::Event
        {
        private:
          Pointer<gdco::MainPlayer> player;

        public:
          static unsigned int getStaticType();

          MainPlayerSpawnEvent(const Pointer<gdco::MainPlayer>&);
          MainPlayerSpawnEvent(const MainPlayerSpawnEvent&);
          MainPlayerSpawnEvent& operator=(const MainPlayerSpawnEvent&);

          const Pointer<gdco::MainPlayer>& getPlayerPointer() const;
          gdco::MainPlayer* getPlayer() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
