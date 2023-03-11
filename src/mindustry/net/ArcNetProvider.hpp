#pragma once
#include "../../arc/net/ArcNet.cpp"
#include "../../arc/net/Client.cpp"
#include "../../arc/net/FrameworkMessage.cpp"
#include "../../arc/net/NetSerializer.cpp"
#include "../../arc/util/Log.cpp"
#include "../../arc/util/io/Reads.cpp"
#include "../../arc/util/io/Writes.cpp"
#include "./Net.cpp"

#include "../Vars.cpp"
#include "./Packets.cpp"
#include "Packet.cpp"
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
class _NetListener_ : public NetListener {
public:
  virtual void connected(Connection *connection) override;
  virtual void received(Connection *con, boost::any obj) override;
};
class PacketSerializer : public NetSerializer {
private:
  java::nio::ByteBuffer temp;
  bool debug = false;

public:
  virtual boost::any read(java::nio::ByteBuffer &buffer) override;
  arc::net::FrameworkMessage::_FrameworkMessage_
  readFramework(java::nio::ByteBuffer &buffer);
  virtual void write(java::nio::ByteBuffer &buffer, boost::any obj) override;
  void writeFramework(ByteBuffer &buffer, boost::any obj);
};
class ArcNetProvider : public NetProvider {
public:
  bool debug = true;
  Client client;
  ArcNetProvider();
  void connectClient(std::string ip, int port, void (*success)()) override;
  void disconnectClient() override;
  void sendClient(boost::any object, bool reliable) override;
};
} // namespace net

} // namespace mindustry
