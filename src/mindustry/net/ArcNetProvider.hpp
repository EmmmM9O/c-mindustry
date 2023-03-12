#pragma once
#include "../../arc/net/ArcNet.cpp"
#include "../../arc/net/Client.cpp"
#include "../../arc/net/FrameworkMessage.cpp"
#include "../../arc/net/NetSerializer.cpp"
#include "../../arc/util/Log.cpp"
#include "../../arc/util/io/Reads.cpp"
#include "../../arc/util/io/Writes.cpp"

#include "../Vars.cpp"
#include "./Packets.cpp"
#include "Packet.cpp"
#include "Packet.hpp"
#include <boost/any.hpp>
#include <cstddef>
#include <exception>
#include <unistd.h>
using namespace arc::net;
using namespace arc::util;
using namespace arc::util::io;
using namespace java::io;
namespace mindustry {
namespace net {
class _NetListener_ : public NetListener<Packet> {
public:
  virtual void connected(Connection<Packet> *connection) override;
  virtual void
  received(Connection<Packet> *con,
           java::AnyTwo<java::AnyObject<Packet>,
                        java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
               obj) override;
};
class PacketSerializer : public NetSerializer<Packet> {
private:
  java::nio::ByteBuffer temp;
  bool debug = false;

public:
  virtual java::AnyTwo<java::AnyObject<Packet>,
                       java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
  read(java::nio::ByteBuffer &buffer) override;
  arc::net::FrameworkMessage::_FrameworkMessage_
  readFramework(java::nio::ByteBuffer &buffer);
  virtual void
  write(java::nio::ByteBuffer &buffer,
        java::AnyTwo<java::AnyObject<Packet>,
                     java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
            obj) override;
  void writeFramework(
      ByteBuffer &buffer,
      java::AnyTwo<java::AnyObject<Packet>,
                   java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
          obj);
};
class ArcNetProvider : public NetProvider<Packet> {
public:
  bool debug = true;
  Client<Packet> client;
  ArcNetProvider();
  void connectClient(std::string ip, int port, void (*success)()) override;
  void disconnectClient() override;
  void
  sendClient(java::AnyTwo<java::AnyObject<Packet>,
                          java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
                 object,
             bool reliable) override;
};
} // namespace net
namespace Vars {
extern mindustry::net::Net net;
}
} // namespace mindustry
