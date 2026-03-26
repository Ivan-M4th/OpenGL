#ifndef GD_SERVER_PLAYERS_H
#define GD_SERVER_PLAYERS_H

#include "../gddef.h"

#include "../utils/Pointer.h"

#include "objects/Player.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      class Players
      {
      private:
        unsigned int maxPlayers;
        Pointer<gdso::Player>* players;

        void deleteData();
      public:
        Players(unsigned int);
        Players(const Players&);
        Players& operator=(const Players&);
        ~Players();

        unsigned int getMaxPlayers() const;

        gdso::Player* getPlayer(unsigned int) const;
        void setPlayer(unsigned int, const Pointer<gdso::Player>&);
        void removePlayer(unsigned int);

        void getPlayers(ArrayList<gdso::Player*>*) const;
      };
    }
  }
}

#endif
