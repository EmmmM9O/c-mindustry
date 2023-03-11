#pragma once
#include "./PingHost.hpp"
using namespace Struct;
const char *tools::TimeOut::what() const throw() { return "TimeOut!"; }

tools::ServerInfo::ServerInfo(std::vector<char> data) { read(data); }
void tools::ServerInfo::read(java::io::DataInput data) {
  name = data.Read2String();
  mapName = data.Read2String();
  players = data.ReadInt();
  waves = data.ReadInt();
  version = data.ReadInt();
  versiontype = data.Read2String();
  gamemod = data.ReadValue<char>();
  limit = data.ReadInt();
  decs = data.Read2String();
  modeName = data.Read2String();
}
void tools::ServerInfo::read(std::vector<char> data) {
  java::io::DataInput in;
  for (auto i : data) {
    in.byteStream.push_back(static_cast<unsigned char>(i));
  }
  read(in);
}
std::string tools::ServerInfo::toString() {
  return name + "\n" + mapName + " mode:" + gamemod + " : " + modeName +
         "\n players:" + std::to_string(players) +
         " waves:" + std::to_string(waves) + "\n" + versiontype + " : " +
         std::to_string(version) + "\n";
}
tools::ServerInfo tools::pingHost(int port, std::string host) {
  std::unique_ptr<Socket> c(new Socket(domain::IPV4, type::UDP, 0));
  c->connect(port, host);
  unsigned char buf[2] = {static_cast<unsigned char>(-2), 1};
  c->send(buf, 2);
  auto data = c->data();
  if (data.wait_for(std::chrono::seconds(20)) == std::future_status::ready) {
    c->close();
    return ServerInfo(data.get());
  } else {
    c->close();
    throw TimeOut();
  }
}