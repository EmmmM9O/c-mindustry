#pragma once
#include "./ArcNetProvider.hpp"
using namespace arc::net;
using namespace arc::util;
using namespace arc::util::io;
using namespace java::io;
using namespace mindustry::net;
void ArcNetProvider::connectClient(std::string ip, int port,
                                   void (*success)()) {
  if (debug)
    Log::debug("Connect!");
  client.close();
  client.connect(port, ip, 5);
  success();
}
void ArcNetProvider::disconnectClient() { client.close(); }
void ArcNetProvider::sendClient(
    java::AnyTwo<java::AnyObject<Packet>,
                 java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
        object,
    bool reliable) {
  if (reliable) {
    client.sendTCP(object);
  } else {
    client.sendUDP(object);
  }
}

namespace mindustry {
namespace Vars {
PacketSerializer _pcs = PacketSerializer();
_NetListener_ _lis = _NetListener_();
ArcNetProvider _pro = ArcNetProvider();
} // namespace Vars
} // namespace mindustry
mindustry::net::Net mindustry::Vars::net = mindustry::net::Net(_pro);
mindustry::net::ArcNetProvider::ArcNetProvider()
    : client(8192, 8192, &Vars::_pcs) {
  ArcNet::errorHandler = [](std::exception err) -> void {
    Log::debug(err.what());
  };
  client.addListener(&Vars::_lis);
}
void mindustry::net::_NetListener_::connected(Connection<Packet> *connection) {
  Connect c;
  c.addressTCP = connection->getIP();
  Vars::net.handleClientReceived(c, c);
}
void mindustry::net::_NetListener_ ::received(
    Connection<Packet> *con,
    java::AnyTwo<java::AnyObject<Packet>,
                 java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
        obj) {
  try {
    // Vars::net.handleClientReceived(obj.DataObje
  } catch (...) {
  }
}
java::AnyTwo<java::AnyObject<Packet>,
             java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
mindustry::net::PacketSerializer ::read(java::nio::ByteBuffer &buffer) {
  try {
    byte id = buffer.ReadByte();
    if (id == static_cast<byte>(-2)) {
      auto fp = readFramework(buffer);
      auto p = java::AnyObject<FrameworkMessage::_FrameworkMessage_>();
      p.DataObject = &fp;
      *p.DataAny = fp;
      return java::AnyTwo<
          java::AnyObject<Packet>,
          java::AnyObject<FrameworkMessage::_FrameworkMessage_>>(&p);
    } else {
      auto packet = Net::newPacketI(id);
      if (packet.key == -1) {
        Log::debug("空指针");
        return java::AnyTwo<
            java::AnyObject<Packet>,
            java::AnyObject<FrameworkMessage::_FrameworkMessage_>>();
      }
      if (packet.key == 2)
        return packet;
      auto o = packet.first->DataObject;
      Log::debug("New Packet ${} size: ${} postion:${}", (int)id,
                 buffer.byteStream.size(), buffer.position());
      int length = buffer.ReadShort() & 0xffff;
      byte compression = buffer.ReadByte();
      temp.clear();
      if ((int)compression == 0) {
        temp.position(0);
        temp.limit(length);
        temp.put(buffer.byteStream);
        temp.position(0);
        auto r = Reads(DataInput(buffer.byteStream));
        o->read(r, length);

        temp.byteStream = r.input.byteStream;
        buffer.position(buffer.position() + temp.position());
      } else {
        // Log::debug("Packet Test");
        int read = buffer.remaining();
        // LE wait
        Log::debug("No Le4");
        throw "No Le4";
        temp.position(0);
        temp.limit(length);
        auto r = Reads(DataInput(buffer.byteStream));
        o->read(r, length);
        buffer.position(read + buffer.position());
      }
      return packet;
    }
  } catch (char *&e) {
    Log::debug("${}", e);
    return java::AnyTwo<
        java::AnyObject<Packet>,
        java::AnyObject<FrameworkMessage::_FrameworkMessage_>>();
  }
}

void mindustry::net::PacketSerializer ::write(
    ByteBuffer &byteBuffer,
    java::AnyTwo<java::AnyObject<Packet>,
                 java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
        object) {
  try {
    if (debug) {
      int lastPos = byteBuffer.position();
    }
    if (object.key == 2) {
      byteBuffer.put(static_cast<byte>(-2));
      writeFramework(byteBuffer, object);
    } else {
      auto id = Net::getPacketId(object);
      if ((int)id == -1)
        throw "Not Packet";
      byteBuffer.put(id);
      temp.position(0);
      auto pack = boost::any_cast<Packet>(object);
      auto w = Writes(temp.byteStream);
      pack.write(w);
      temp.byteStream = w.output.byteStream;
      auto length = (short)temp.position();
      byteBuffer.WriteShort(length);
      if (length < 36 || object.first->DataAny->type().hash_code() ==
                             typeid(StreamChunk).hash_code()) {
        byteBuffer.put((byte)0);
        byteBuffer.put(temp.byteStream);
      } else {
        byteBuffer.put((byte)1);
        // LE4
        throw "No LE4";
      }
    }
  } catch (boost::bad_any_cast &e) {
    std::cout << "Bug from PacketSerializer " << e.what();
  }
}
void mindustry::net::PacketSerializer::writeFramework(
    ByteBuffer &buffer,
    java::AnyTwo<java::AnyObject<Packet>,
                 java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
        obj) {
  if (obj.second->is<FrameworkMessage::Ping>()) {
    auto p = boost::any_cast<FrameworkMessage::Ping>(obj);
    buffer.put((byte)0);
    buffer.WriteInt(p.id);
    buffer.put(p.isReply ? (byte)1 : (byte)0);
  } else if (obj.second->is<FrameworkMessage::DiscoverHost>()) {
    buffer.put((byte)1);
  } else if (obj.second->is<FrameworkMessage::KeepAlive>()) {
    buffer.put((byte)2);
  } else if (obj.second->is<FrameworkMessage::RegisterUDP>()) {
    auto p =
        boost::any_cast<FrameworkMessage::RegisterUDP>(*obj.second->DataAny);
    buffer.put((byte)3);
    buffer.WriteInt(p.connectionID);
  } else if (obj.second->is<FrameworkMessage::RegisterTCP>()) {
    auto p =
        boost::any_cast<FrameworkMessage::RegisterTCP>(*obj.second->DataAny);
    buffer.put((byte)4);
    buffer.WriteInt(p.connectionID);
  }
}
FrameworkMessage::_FrameworkMessage_
mindustry::net::PacketSerializer::readFramework(java::nio::ByteBuffer &buffer) {
  byte id = buffer.ReadByte();
  if (id == 0) {
    FrameworkMessage::Ping p;
    p.id = buffer.ReadInt();
    p.isReply = (int)buffer.ReadByte() == 1;
    return p;
  }
  if (id == 1) {
    return FrameworkMessage::discoverHost;
  }
  if (id == 2) {
    return FrameworkMessage::keepAlive;
  }
  if (id == 3) {
    FrameworkMessage::RegisterUDP p;
    p.connectionID = buffer.ReadInt();
    return p;
  }
  if (id == 4) {
    FrameworkMessage::RegisterTCP p;
    p.connectionID = buffer.ReadInt();
    return p;
  }
  throw "Unknown framework message!";
}