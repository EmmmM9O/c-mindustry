
#pragma once
#include "./Call.hpp"
#include "../net/ArcNetProvider.cpp"
#include "./Packets.cpp"
using namespace arc::net;
using namespace mindustry::gen;
void Call::registerPackets() {
  net::Net::registerPacket<SendMessageCallPacket2>(71);
  net::Net::registerPacket<StreamBegin>(0);
  net::Net::registerPacket<StreamChunk>(1);
}