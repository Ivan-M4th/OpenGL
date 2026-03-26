#include "ConnectionPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace packets
      {
        void ConnectionPacket::loadToBuffer(const gdu::BufferWriter& writer) const
        {
          writer.addData(gdn::CONNECTION);
          writer.addSpace();
          writer.addData(gdn::CLIENT_INFO);
        }
      }
    }
  }
}
