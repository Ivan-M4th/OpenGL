#ifndef GD_NETWORKING_CLIENT_H
#define GD_NETWORKING_CLIENT_H

#include <SDL2/SDL_net.h>

#include "Packet.h"

#include "../gddef.h"

#include "../utils/Buffer.h"
#include "../utils/BufferWriter.h"
#include "../utils/BufferReader.h"

namespace gt
{
  namespace doubovik
  {
    namespace networking
    {
      class Client
      {
      private:
        TCPsocket socket;
        SDLNet_SocketSet socketSet;
        gdu::Buffer buffer;
        gdu::Buffer packetBuffer;

        bool connected;

        void sendBuffer();
        void preparePacket(const Packet&);

        void readIncomingPackets();
        void processIncomingPackets();
      public:
        Client(const char*, int);
        ~Client();

        void checkIncomingData();
        void update(float);

        void sendPacket(const Packet&);
        bool isConnected() const;
      };
    }
  }
}

#endif
