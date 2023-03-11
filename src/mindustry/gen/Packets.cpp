#pragma once

#include "./Packets.hpp"
using namespace mindustry::net;
using namespace mindustry::gen;

void SendMessageCallPacket2::read(arc::util::io::Reads &read) {
  message = io::TypeIO::readString(read);
  unformatted = io::TypeIO::readString(read);
  playersender = read.i();
}