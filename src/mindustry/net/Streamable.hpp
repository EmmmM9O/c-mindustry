#pragma once

#include "../../java/nio/ByteBuffer.cpp"
#include "./Packet.cpp"
#include "./Packets.cpp"
#include <vector>
using namespace java::nio;
namespace mindustry {
namespace net {
namespace Streamable {

class _Streamable_ : public ::mindustry::net::Packet {
public:
  virtual int getPriority() override;
  ByteBuffer stream;
};
class StreamBuilder {
public:
  int id;
  unsigned char type;
  int total;
  ByteBuffer stream;
  StreamBuilder();
  StreamBuilder(::mindustry::net::Packets::StreamBegin const &b);
  void add(std::vector<unsigned char> bytes);
  bool isDone();
  _Streamable_ build();
};
} // namespace Streamable
} // namespace net
} // namespace mindustry