#ifndef GD_NETWORKING_PACKET_H
#define GD_NETWORKING_PACKET_H

#include "../gddef.h"

#include "../utils/BufferWriter.h"

namespace gt
{
  namespace doubovik
  {
    namespace networking
    {


      //-----------------------------



      extern const unsigned int REQUEST_DATA;

      //connection info
      extern const unsigned int CONNECTION;

      extern const unsigned int CLIENT_INFO;
      extern const unsigned int SERVER_INFO;

      //game info
      extern const unsigned int GAME_INFO;

      extern const unsigned int REQUEST_SPAWN;
      extern const unsigned int MAIN_PLAYER_SPAWN;
      extern const unsigned int MAIN_PLAYER_UPDATE;
      extern const unsigned int PLAYER_SPAWN;
      extern const unsigned int PLAYER_UPDATE;
      extern const unsigned int PLAYER_DESPAWN;
      extern const unsigned int PLAYER_PLAY_ACTION;
      const unsigned int UPDATE_BOAR = 8;

      //terrain
      extern const unsigned int TERRAIN_INFO;

      extern const unsigned int DOWNLOAD_CHUNK;
      extern const unsigned int SEND_CHUNK;
      extern const unsigned int PLACE_BLOCK;
      extern const unsigned int SET_BLOCK;
      extern const unsigned int BREAK_BLOCK;
      extern const unsigned int UPDATE_GRID_POSITION;
      extern const unsigned int SEND_CHUNK_TREES; //server sending trees
      const unsigned int SEND_CHUNK_BOARS = 8; //Server sending boars

      //inventory
      extern const unsigned int INVENTORY_INFO;

      extern const unsigned int SET_ITEM;
      extern const unsigned int SWAP_ITEMS;
      extern const unsigned int SELECTED_INVENTORY_SLOT;
      extern const unsigned int PLAYER_EQUIPED_ITEM;

      class Packet
      {
      public:
        virtual void loadToBuffer(const gdu::BufferWriter&) const = 0;
      };
    }
  }
}

#endif
