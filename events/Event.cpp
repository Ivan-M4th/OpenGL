#include "Event.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      const unsigned int NULL_EVENT = 0;

      const unsigned int KEY_PRESSED_EVENT = 1;
      const unsigned int LEFT_CLICK_EVENT = 2;
      const unsigned int BLOCK_SET_EVENT = 3;

      const unsigned int SERVER_PACKET_RECEIVE = 4;
      const unsigned int SERVER_CONNECTION_PACKET_RECEIVE = 5;
      const unsigned int CLIENT_PACKET_RECEIVE = 6;
      const unsigned int CLIENT_CONNECTION_PACKET_RECEIVE_EVENT = 7;
      const unsigned int SERVER_REQUEST_SPAWN_PACKET_RECEIVE_EVENT = 8;
      const unsigned int CLIENT_MAIN_PLAYER_SPAWN_EVENT = 9;
      const unsigned int SERVER_CHUNK_REQUEST_EVENT = 10;
      const unsigned int CHUNK_GENERATED_EVENT = 11;
      const unsigned int SERVER_PLAYER_DISCONNECT_EVENT = 12;
      const unsigned int SERVER_CLIENT_UPDATE_PACKET_RECEIVE_EVENT = 13;
      const unsigned int CLIENT_PLAYER_SPAWN_EVENT = 14;
      const unsigned int CLIENT_PLAYER_UPDATE_RECEIVE_EVENT = 15;
      const unsigned int CLIENT_PLAYER_DESPAWN_PACKET_RECEIVE_EVENT = 16;
      const unsigned int CLIENT_MAINPLAYER_SET_ITEMSTACK_EVENT = 17;
      const unsigned int MOUSE_SCROLL_EVENT = 18;
      const unsigned int MOUSE_GRAB_EVENT = 19;
      const unsigned int GUI_TOGGLE_EVENT = 20;

      const unsigned int EVENT_AMOUNT = 300;
    }
  }
}
