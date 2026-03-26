#include "Client.h"

#include <iostream>
#include <cstring>
#include <cassert>

#include "../events/Events.h"

#include "../client/events/PacketReceiveEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace networking
    {
      Client::Client(const char* address, int port) : buffer(100000000), packetBuffer(100000000)
      {
        connected = false;

        SDLNet_Init();
        IPaddress ip;
        if(SDLNet_ResolveHost(&ip, address, port) == -1)
        {
          std::cout << "Client connection error!" << std::endl;
        }
        socket = SDLNet_TCP_Open(&ip);
        if(socket == NULL)
        {
          std::cout << "Client connection error! (wrong ip address?)" << std::endl;
        }
        else
        {
          connected = true;
        }
        socketSet = SDLNet_AllocSocketSet(1);
        SDLNet_TCP_AddSocket(socketSet, socket);
      }

      Client::~Client()
      {
        SDLNet_TCP_Close(socket);
        SDLNet_FreeSocketSet(socketSet);
        SDLNet_Quit();
      }

      void Client::sendBuffer()
      {
        int size = buffer.size;
        int sentSize = 0;
        while(sentSize < size)
        {
          int sent = SDLNet_TCP_Send(socket, buffer.getData() + sentSize, size - sentSize);
          if(sent < 1)
          {
            connected = false;
            break;
          }
          sentSize+=size;
        }
      }

      void Client::preparePacket(const Packet& packet)
      {
        buffer.clear();
        gdu::BufferWriter writer(&buffer);
        packet.loadToBuffer(writer);
        writer.addEndOfLine();
      }

      void Client::sendPacket(const Packet& packet)
      {
        preparePacket(packet);
        sendBuffer();
      }

      void Client::readIncomingPackets()
      {
        assert(packetBuffer.size + 1400 < packetBuffer.getMemorySize());
        int loaded = SDLNet_TCP_Recv(socket, packetBuffer.getData() + packetBuffer.size, 1400);
        if(loaded < 1)
        {
          connected = false;
        }
        else
        {
          packetBuffer.size+=loaded;
        }
      }

      void Client::processIncomingPackets()
      {
        if(!connected)
        {
          return;
        }
        bool process = true;
        while(process)
        {
          buffer.clear();
          gdu::BufferReader reader(&packetBuffer);
          reader.readPacket(&buffer);
          if(buffer.size > 0)
          {
            gdu::BufferReader reader(&buffer);
            gdce::PacketReceiveEvent event(&reader);
            gde::onEvent(event);
          }
          else
          {
            process = false;
          }
        }
      }

      void Client::checkIncomingData()
      {
        while(connected && SDLNet_CheckSockets(socketSet,0) > 0)
        {
          if(SDLNet_SocketReady(socket))
          {
            readIncomingPackets();
            processIncomingPackets();
          }
        }
      }

      void Client::update(float timePassed)
      {
        if(connected)
        {
          checkIncomingData();
        }
      }

      bool Client::isConnected() const
      {
        return connected;
      }
    }
  }
}
