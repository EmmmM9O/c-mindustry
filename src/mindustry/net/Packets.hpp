#pragma once

#include "../../arc/util/io/Reads.cpp"
#include "../../arc/util/io/Writes.cpp"
#include "../../java/object.cpp"
#include "../io/TypeIO.cpp"
#include "./Packet.cpp"
#include <cstddef>
#include <queue>
#include <string>
#include <sys/wait.h>
#include <vector>
namespace mindustry {
namespace net {
namespace Packets {
class _KickReason_ : public java::Object {
public:
  bool quiet;
  std::string name;
  _KickReason_(std::string n);
  _KickReason_(std::string n, bool q);
  virtual std::string toStirng();
};
namespace KickReason {}
enum class AdminAction { kick, ban, trace, wave };
class Connect : public mindustry::net::Packet {
public:
  std::string addressTCP;
  virtual int getPriority() override;
};
class Disconnect : public mindustry::net::Packet {
public:
  std::string reason;
  virtual int getPriority() override;
};
class WorldStream : public mindustry::net::Packet {};
class StreamBegin : public mindustry::net::Packet {
private:
  static int lastid;

public:
  int id;
  int total;
  byte type;
  virtual void write(arc::util::io::Writes &write) override;
  virtual void read(arc::util::io::Reads &reads) override;
  StreamBegin();
};
class StreamChunk : public mindustry::net::Packet {
public:
  int id;
  std::vector<byte> data;
  virtual void write(arc::util::io::Writes &writes) override;
  virtual void read(arc::util::io::Reads &reads) override;
};
class ConnectPacket : public mindustry::net::Packet {
public:
  int version;
  std::string versionType;
  std::queue<std::string> mods;
  std::string name, locale, uuid, usid;
  int color;
  bool mobile;
  virtual void write(arc::util::io::Writes &writes) override;
  virtual void read(arc::util::io::Reads &buffer) override;
};

} // namespace Packets
} // namespace net
} // namespace mindustry
