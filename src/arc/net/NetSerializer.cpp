#pragma once

#include "./NetSerializer.hpp"
void arc::net::NetSerializer::write(java::nio::ByteBuffer &buffer, boost::any) {
}
boost::any arc::net::NetSerializer::read(java::nio::ByteBuffer &buffer) {
  return nullptr;
}
int arc::net::NetSerializer::getLengthLength() { return 2; }
void arc::net::NetSerializer::writeLength(java::nio::ByteBuffer &buffer,
                                          int length) {}

int arc::net::NetSerializer::readLength(java::nio::ByteBuffer &buffer) {
  return buffer.ReadShort();
}