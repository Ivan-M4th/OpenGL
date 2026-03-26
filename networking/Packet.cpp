#include "Packet.h"

namespace gt
{
  namespace doubovik
  {
    namespace networking
    {
      //INFORMATION TYPES

      //DATA TYPES
      const unsigned int REQUEST_DATA = 2;

      //connection info
      const unsigned int CONNECTION = 1;

      const unsigned int CLIENT_INFO = 1;
      const unsigned int SERVER_INFO = 2;

      //game info
      const unsigned int GAME_INFO = 2;

      const unsigned int REQUEST_SPAWN = 1;
      const unsigned int MAIN_PLAYER_SPAWN = 2;
      const unsigned int MAIN_PLAYER_UPDATE = 3;
      const unsigned int PLAYER_SPAWN = 4;
      const unsigned int PLAYER_UPDATE = 5;
      const unsigned int PLAYER_DESPAWN = 6;
      const unsigned int PLAYER_PLAY_ACTION = 7;

      //terrain
      const unsigned int TERRAIN_INFO = 3;

      const unsigned int DOWNLOAD_CHUNK = 1;
      const unsigned int SEND_CHUNK = 2;
      const unsigned int PLACE_BLOCK = 3;
      const unsigned int SET_BLOCK = 4;
      const unsigned int BREAK_BLOCK = 5;
      const unsigned int UPDATE_GRID_POSITION = 6;
      const unsigned int SEND_CHUNK_TREES = 7;

      //inventory
      const unsigned int INVENTORY_INFO = 4;

      const unsigned int SET_ITEM = 1;
      const unsigned int SWAP_ITEMS = 2;
      const unsigned int SELECTED_INVENTORY_SLOT = 3;
      const unsigned int PLAYER_EQUIPED_ITEM = 4;
    }
  }
}
