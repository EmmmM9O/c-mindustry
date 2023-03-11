#pragma once
#include "./Reads.hpp"
arc::util::io::Reads::Reads(java::io::DataInput inp) { input = inp; }
arc::util::io::Reads arc::util::io::Reads::get(java::io::DataInput in) {
  instance.input = in;
  return instance;
}
long arc::util::io::Reads::l() { return input.ReadLong(); }
int arc::util::io::Reads::i() { return input.ReadInt(); }
byte arc::util::io::Reads::b() { return input.ReadByte(); }
std::string arc::util::io::Reads::str() { return input.ReadString(); }
short arc::util::io::Reads::s() { return input.ReadShort(); }
std::vector<byte> arc::util::io::Reads::b(short len) {
  std::vector<byte> d;
  input.readFully(d);
  return d;
}