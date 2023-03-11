#pragma once
#include "./Packet.hpp"

void mindustry::net::Packet::read(arc::util::io::Reads &read) {}
void mindustry::net::Packet::write(arc::util::io::Writes &write) {}
void mindustry::net::Packet::read(arc::util::io::Reads &readr, int length) {
  read(readr);
}
void mindustry::net::Packet::handled() {}
int mindustry::net::Packet::getPriority() { return priorityNormal; }
void mindustry::net::Packet::handleClient() {}
void mindustry::net::Packet::handleServer(mindustry::net::NetConnection con) {}
