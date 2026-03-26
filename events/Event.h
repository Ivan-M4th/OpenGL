#ifndef GD_EVENTS_EVENT_H
#define GD_EVENTS_EVENT_H

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      extern const unsigned int NULL_EVENT;

      extern const unsigned int KEY_PRESSED_EVENT;
      extern const unsigned int LEFT_CLICK_EVENT;
      extern const unsigned int BLOCK_SET_EVENT;

      extern const unsigned int SERVER_PACKET_RECEIVE;
      extern const unsigned int SERVER_CONNECTION_PACKET_RECEIVE;
      extern const unsigned int CLIENT_PACKET_RECEIVE;
      extern const unsigned int CLIENT_CONNECTION_PACKET_RECEIVE_EVENT;
      extern const unsigned int SERVER_REQUEST_SPAWN_PACKET_RECEIVE_EVENT;
      extern const unsigned int CLIENT_MAIN_PLAYER_SPAWN_EVENT;
      extern const unsigned int SERVER_CHUNK_REQUEST_EVENT;
      extern const unsigned int CHUNK_GENERATED_EVENT;
      extern const unsigned int SERVER_PLAYER_DISCONNECT_EVENT;
      extern const unsigned int SERVER_CLIENT_UPDATE_PACKET_RECEIVE_EVENT;
      extern const unsigned int CLIENT_PLAYER_SPAWN_EVENT;
      extern const unsigned int CLIENT_PLAYER_UPDATE_RECEIVE_EVENT;
      extern const unsigned int CLIENT_PLAYER_DESPAWN_PACKET_RECEIVE_EVENT;
      extern const unsigned int CLIENT_MAINPLAYER_SET_ITEMSTACK_EVENT;
      extern const unsigned int MOUSE_SCROLL_EVENT;
      extern const unsigned int MOUSE_GRAB_EVENT;
      extern const unsigned int GUI_TOGGLE_EVENT;

      extern const unsigned int EVENT_AMOUNT;

      class Event
      {
      public:
        virtual unsigned int getType() const = 0;
      };
    }
  }
}

#endif
