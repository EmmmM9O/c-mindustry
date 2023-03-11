#pragma once
#include "./Writes.hpp"

arc::util::io::Writes::Writes(std::vector<byte> b) {
  output = java::io::DataOutput();
  output.byteStream = b;
}
arc::util::io::Writes::Writes(java::io::DataOutput out) { output = out; }
arc::util::io::Writes arc::util::io::Writes::get(java::io::DataOutput out) {
  instance.output = out;
  return instance;
}
void arc::util::io::Writes::i(int v) { output.WriteInt(v); }
void arc::util::io::Writes::b(byte b) { output.WriteByte(b); }
void arc::util::io::Writes::b(byte b[]) { output.Write(b); }
void arc::util::io::Writes::s(short s) { output.WriteShort(s); }
void arc::util::io::Writes::str(std::string str) { output.writeUTF(str); }