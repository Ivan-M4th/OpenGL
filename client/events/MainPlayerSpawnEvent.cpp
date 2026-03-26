#include "MainPlayerSpawnEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        unsigned int MainPlayerSpawnEvent::getStaticType()
        {
          return gde::CLIENT_MAIN_PLAYER_SPAWN_EVENT;
        }

        MainPlayerSpawnEvent::MainPlayerSpawnEvent(const Pointer<gdco::MainPlayer>& player)
        {
          this->player = player;
        }

        MainPlayerSpawnEvent::MainPlayerSpawnEvent(const MainPlayerSpawnEvent& event)
        {
          player = event.player;
        }

        MainPlayerSpawnEvent& MainPlayerSpawnEvent::operator=(const MainPlayerSpawnEvent& event)
        {
          player = event.player;
          return *this;
        }

        const Pointer<gdco::MainPlayer>& MainPlayerSpawnEvent::getPlayerPointer() const
        {
          return player;
        }

        gdco::MainPlayer* MainPlayerSpawnEvent::getPlayer() const
        {
          return player.value();
        }

        unsigned int MainPlayerSpawnEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
