#include "Players.h"

#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      Players::Players(unsigned int maxPlayers)
      {
        this->maxPlayers = maxPlayers;
        players = new Pointer<gdso::Player>[maxPlayers];
      }

      Players::Players(const Players& ps)
      {
        maxPlayers = ps.maxPlayers;
        players = new Pointer<gdso::Player>[maxPlayers];

        for(unsigned int i=0;i<maxPlayers;i++)
        {
          *(players + i) = *(ps.players + i);
        }
      }

      Players& Players::operator=(const Players& ps)
      {
        deleteData();
        maxPlayers = ps.maxPlayers;
        players = new Pointer<gdso::Player>[maxPlayers];

        for(unsigned int i=0;i<maxPlayers;i++)
        {
          *(players + i) = *(ps.players + i);
        }
        return *this;
      }

      Players::~Players()
      {
        deleteData();
      }

      void Players::deleteData()
      {
        delete[] players;
      }

      unsigned int Players::getMaxPlayers() const
      {
        return maxPlayers;
      }

      gdso::Player* Players::getPlayer(unsigned int index) const
      {
        assert(index < maxPlayers);
        return (players + index)->value();
      }

      void Players::setPlayer(unsigned int index, const Pointer<gdso::Player>& player)
      {
        assert(index < maxPlayers);
        *(players + index) = player;
      }

      void Players::removePlayer(unsigned int index)
      {
        assert(index < maxPlayers);
        (players + index)->deletePointer();
      }

      void Players::getPlayers(ArrayList<gdso::Player*>* playersList) const
      {
        for(unsigned int i=0;i<maxPlayers;i++)
        {
          gdso::Player* player = (players + i)->value();
          if(player != NULL)
          {
            playersList->add(player);
          }
        }
      }
    }
  }
}
