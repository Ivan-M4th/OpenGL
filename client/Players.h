#ifndef GD_CLIENT_PLAYERS
#define GD_CLIENT_PLAYERS

#include "../gddef.h"

#include "../utils/Pointer.h"

#include "objects/Player.h"
#include "objects/MainPlayer.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      class Players
      {
      private:
        unsigned int maxPlayers;
        Pointer<gdco::Player>* players;
        Pointer<gdco::MainPlayer> mainPlayer;

        void deleteData();
        void clearPlayers();
      public:
        Players();
        Players(const Players&);
        Players& operator=(const Players&);
        ~Players();

        void setMaxPlayers(unsigned int);
        unsigned int getMaxPlayers() const;

        gdco::Player* getPlayer(unsigned int) const;
        void setPlayer(unsigned int, const Pointer<gdco::Player>&);
        void removePlayer(unsigned int);

        gdco::MainPlayer* getMainPlayer() const;
        void setMainPlayer(const Pointer<gdco::MainPlayer>&);
      };
    }
  }
}

#endif
