
#pragma once
#include "./Call.hpp"
#include "../net/ArcNetProvider.cpp"
#include "./Packets.cpp"
using namespace arc::net;
using namespace mindustry::gen;
void Call::registerPackets() {
  net::Net::registerPacket1<SendMessageCallPacket2>(71);
  net::Net::registerPacket1<StreamBegin>(0);
  net::Net::registerPacket1<StreamChunk>(1);
}
