#ifndef GD_NETWORKING_CLIENTDATA_H
#define GD_NETWORKING_CLIENTDATA_H

#include <SDL2/SDL_net.h>

#include "../gddef.h"

#include "../utils/Timer.h"
#include "../utils/Buffer.h"

namespace gt
{
  namespace doubovik
  {
    namespace networking
    {
      class ClientData
      {
      private:
        TCPsocket socket;

      public:
        Timer timer;
        gdu::Buffer buffer;

        ClientData();
        ClientData(const TCPsocket&);
        ClientData(ClientData&);
        ClientData& operator=(ClientData&);
        ~ClientData();

        TCPsocket* getSocket();
      };
    }
  }
}

#endif
