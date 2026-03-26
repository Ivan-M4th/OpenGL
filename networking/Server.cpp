#include "Server.h"

#include <iostream>
#include <cstring>
#include <cassert>

#include "../utils/BufferWriter.h"
#include "../utils/BufferReader.h"

#include "../events/Events.h"

#include "../server/events/PacketReceiveEvent.h"
#include "../server/events/ClientDisconnectEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace networking
    {
      Server::Server(unsigned int maxClients, int port, gdu::Buffer* buffer)
      {
        this->maxClients = maxClients;
        this->buffer = buffer;

        clientsSet = SDLNet_AllocSocketSet(maxClients);

        SDLNet_ResolveHost(&ip, NULL, port);
        socket = SDLNet_TCP_Open(&ip);

        clients = new Pointer<ClientData>[maxClients];
      }

      Server::~Server()
      {
        SDLNet_FreeSocketSet(clientsSet);
        SDLNet_TCP_Close(socket);
        delete[] clients;
      }

      bool Server::isClientId(unsigned int id) const
      {
        return (clients + id)->value() != NULL;
      }

      unsigned int Server::genClientId() const
      {
        for(unsigned int i=0;i<maxClients;i++)
        {
          if(!isClientId(i))
          {
            return i;
          }
        }
        assert(true && "Error generating client id!");
        return -1;
      }

      ClientData* Server::getClient(unsigned int index) const
      {
        return (clients + index)->value();
      }

      void Server::removeClient(unsigned int index)
      {
        gdse::ClientDisconnectEvent event(index);
        gde::onEvent(event);

        ClientData* clientData = getClient(index);
        if(clientData != NULL)
        {
          SDLNet_TCP_DelSocket(clientsSet, *clientData->getSocket());
          (clients + index)->deletePointer();
        }
      }

      void Server::sendBuffer(const TCPsocket& clientSocket) const
      {
        int size = buffer->size;
        int sentSize = 0;
        while(sentSize < size)
        {
          int sent = SDLNet_TCP_Send(clientSocket, buffer->getData() + sentSize, size - sentSize);
          if(sent < 1)
          {
            std::cout << "Data Sending error: client disconected? sent: " << sent << std::endl;
            break;
          }
          sentSize+=sent;
        }
      }

      void Server::sendBufferTo(int clientId) const
      {
        ClientData* clientData = getClient(clientId);
        if(clientData != NULL)
        {
          sendBuffer(*clientData->getSocket());
        }
      }

      void Server::sendBuffer() const
      {
        for(int i=0;i<maxClients;i++)
        {
          sendBufferTo(i);
        }
      }

      void Server::sendBufferToOthers(int clientId) const
      {
        for(int i=0;i<maxClients;i++)
        {
          if(i != clientId)
          {
            sendBufferTo(i);
          }
        }
      }

      void Server::preparePacket(const Packet& packet)
      {
        buffer->clear();
        gdu::BufferWriter writer(buffer);
        packet.loadToBuffer(writer);
        writer.addEndOfLine();
      }

      void Server::sendPacket(const TCPsocket& socket, const Packet& packet)
      {
        preparePacket(packet);
        sendBuffer(socket);
      }

      void Server::sendPacketTo(unsigned int clientId, const Packet& packet)
      {
        ClientData* clientData = getClient(clientId);
        if(clientData != NULL)
        {
          sendPacket(*clientData->getSocket(), packet);
        }
      }

      void Server::sendPacket(const Packet& packet)
      {
        preparePacket(packet);
        for(unsigned int i=0;i<maxClients;i++)
        {
          ClientData* clientData = getClient(i);
          if(clientData != NULL)
          {
            sendBuffer(*clientData->getSocket());
          }
        }
      }

      void Server::sendPacketToOtherClients(unsigned int clientId, const Packet& packet)
      {
        preparePacket(packet);
        for(unsigned int i=0;i<maxClients;i++)
        {
          if(i != clientId)
          {
            ClientData* clientData = getClient(i);
            if(clientData != NULL)
            {
              sendBuffer(*clientData->getSocket());
            }
          }
        }
      }

      void Server::checkNewConnection()
      {
        TCPsocket clientSocket = SDLNet_TCP_Accept(socket);
        if(clientSocket)
        {
          unsigned int id = genClientId();
          if(id < maxClients)
          {
            SDLNet_TCP_AddSocket(clientsSet, clientSocket);
            *(clients + id) = Pointer<ClientData>(new ClientData(clientSocket), false);

            std::cout << "new connection id: " << id << std::endl;
          }
          else
          {
            //no more space!
            SDLNet_TCP_Close(clientSocket);
          }
        }
      }

      //ok

      void Server::processIncomingPackets(unsigned int clientId, ClientData* clientData)
      {
        bool process = true;
        while(process)
        {
          buffer->clear();
          gdu::BufferReader reader(&clientData->buffer);
          reader.readPacket(buffer);
          if(buffer->size > 0)
          {
            gdu::BufferReader reader(buffer);
            gdse::PacketReceiveEvent event(clientId, &reader);
            gde::onEvent(event);
          }
          else
          {
            process = false;
          }
        }
      }

      void Server::checkIncomingData()
      {
        while(SDLNet_CheckSockets(clientsSet, 0) > 0)
        {
          for(unsigned int i=0;i<maxClients;i++)
          {
            ClientData* clientData = getClient(i);
            if(clientData != NULL)
            {
              if(SDLNet_SocketReady(*clientData->getSocket()))
              {
                readIncomingPackets(i, clientData);
                clientData = getClient(i);
                if(clientData != NULL)
                {
                  processIncomingPackets(i, clientData);
                }
              }
            }
          }
        }
      }

      void Server::checkTimeouts(float timePassed)
      {
        for(unsigned int i=0;i<maxClients;i++)
        {
          ClientData* clientData = getClient(i);
          if(clientData != NULL)
          {
            clientData->timer.update(timePassed);
            if(clientData->timer.getTime() > 5.0)
            {
              removeClient(i);
            }
          }
        }
      }

      void Server::update(float timePassed)
      {
        checkNewConnection();
        checkIncomingData();
        checkTimeouts(timePassed);
      }

      void Server::readIncomingPackets(unsigned int clientId, ClientData* clientData)
      {
        assert(clientData->buffer.getFreeSpace() >= 1400);
        int loaded = SDLNet_TCP_Recv(*clientData->getSocket(), clientData->buffer.getData() + clientData->buffer.size, 1400);
        if(loaded < 1)
        {
          removeClient(clientId);
        }
        else
        {
          clientData->timer.reset();
          clientData->buffer.size+=loaded;
        }
      }

      bool Server::isOnline(int index) const
      {
        assert(0 <= index && index < maxClients);
        return (clients + index)->value() != NULL;
      }
    }
  }
}
