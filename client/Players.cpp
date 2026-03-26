#include "Players.h"

#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      Players::Players()
      {
        maxPlayers = 0;
        players = NULL;
      }

      Players::Players(const Players& ps)
      {
        maxPlayers = ps.maxPlayers;
        if(maxPlayers == 0)
        {
          players = NULL;
        }
        else
        {
          players = new Pointer<gdco::Player>[maxPlayers];
          for(unsigned int i=0;i<maxPlayers;i++)
          {
            *(players + i) = *(ps.players + i);
          }
        }
        mainPlayer = ps.mainPlayer;
      }

      Players& Players::operator=(const Players& ps)
      {
        deleteData();
        maxPlayers = ps.maxPlayers;
        if(maxPlayers == 0)
        {
          players = NULL;
        }
        else
        {
          players = new Pointer<gdco::Player>[maxPlayers];
          for(unsigned int i=0;i<maxPlayers;i++)
          {
            *(players + i) = *(ps.players + i);
          }
        }
        mainPlayer = ps.mainPlayer;
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

      void Players::clearPlayers()
      {
        deleteData();
        players = NULL;
        maxPlayers = 0;
      }

      void Players::setMaxPlayers(unsigned int maxPlayers)
      {
        clearPlayers();
        this->maxPlayers = maxPlayers;
        if(maxPlayers > 0)
        {
          players = new Pointer<gdco::Player>[maxPlayers];
        }
      }

      unsigned int Players::getMaxPlayers() const
      {
        return maxPlayers;
      }

      gdco::Player* Players::getPlayer(unsigned int index) const
      {
        assert(index < maxPlayers);
        return (players + index)->value();
      }

      void Players::setPlayer(unsigned int index, const Pointer<gdco::Player>& player)
      {
        assert(index < maxPlayers);
        *(players + index) = player;
      }

      void Players::removePlayer(unsigned int index)
      {
        assert(index < maxPlayers);
        (players + index)->deletePointer();
      }

      gdco::MainPlayer* Players::getMainPlayer() const
      {
        return mainPlayer.value();
      }

      void Players::setMainPlayer(const Pointer<gdco::MainPlayer>& mainPlayer)
      {
        this->mainPlayer = mainPlayer;
      }
    }
  }
}
