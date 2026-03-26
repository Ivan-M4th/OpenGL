#ifndef GD_NETWORKING_SERVER_H
#define GD_NETWORKING_SERVER_H

#include <SDL2/SDL_net.h>

#include "ClientData.h"
#include "Packet.h"

#include "../utils/ArrayList.h"
#include "../utils/Pointer.h"
#include "../utils/Buffer.h"

namespace gt
{
  namespace doubovik
  {
    namespace networking
    {
      class Server
      {
      private:
        unsigned int maxClients;

        IPaddress ip;
        TCPsocket socket;
        Pointer<ClientData>* clients;
        SDLNet_SocketSet clientsSet;
        gdu::Buffer* buffer;

        bool isClientId(unsigned int) const;
        unsigned int genClientId() const;
        void removeClient(unsigned int);
        void checkNewConnection();
        void checkIncomingData();
        void checkTimeouts(float);
        void readIncomingPackets(unsigned int, ClientData*);
        void processIncomingPackets(unsigned int, ClientData*);
      public:
        Server(unsigned int, int, gdu::Buffer*);
        ~Server();

        ClientData* getClient(unsigned int) const;
        void sendBuffer(const TCPsocket&) const;
        void sendBufferTo(int) const;
        void sendBuffer() const;
        void sendBufferToOthers(int) const;

        void preparePacket(const Packet&);
        void sendPacket(const TCPsocket&, const Packet&);
        void sendPacketTo(unsigned int, const Packet&);
        void sendPacket(const Packet&);
        void sendPacketToOtherClients(unsigned int, const Packet&);

        void update(float);

        bool isOnline(int) const;
      };
    }
  }
}

#endif
