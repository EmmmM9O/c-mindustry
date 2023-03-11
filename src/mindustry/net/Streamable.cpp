#pragma once
#include "./Streamable.hpp"
#include "Packets.hpp"
using namespace java::nio;
using namespace mindustry::net::Streamable;
int _Streamable_::getPriority() { return priorityHigh; }

StreamBuilder::StreamBuilder() {}
StreamBuilder::StreamBuilder(::mindustry::net::Packets::StreamBegin const &b) {
  id = b.id;
  type = b.type;
  total = b.total;
}
void StreamBuilder::add(std::vector<unsigned char> bytes) {
  stream.write(bytes);
}
bool StreamBuilder::isDone() { return stream.size() >= total; }
