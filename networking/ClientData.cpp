#include "ClientData.h"

namespace gt
{
  namespace doubovik
  {
    namespace networking
    {
      ClientData::ClientData() : buffer(100000000)
      {
      }

      ClientData::ClientData(const TCPsocket& socket) : buffer(100000000)
      {
        this->socket = socket;
      }

      ClientData::ClientData(ClientData& clientData) : buffer(clientData.buffer)
      {
        socket = clientData.socket;
        clientData.socket = NULL;
      }

      ClientData& ClientData::operator=(ClientData& clientData)
      {
        TCPsocket tempSockset = socket;
        socket = clientData.socket;
        clientData.socket = tempSockset;
        buffer = clientData.buffer;
        return *this;
      }

      ClientData::~ClientData()
      {
        if(socket != NULL)
        {
          SDLNet_TCP_Close(socket);
        }
      }

      TCPsocket* ClientData::getSocket()
      {
        return &socket;
      }
    }
  }
}
