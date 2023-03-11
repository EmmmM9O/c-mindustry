#pragma once

#include "./FrameworkMessage.hpp"
namespace arc {
namespace net {
namespace FrameworkMessage {

DiscoverHost discoverHost;
std::vector<size_t> maps;
} // namespace FrameworkMessage
} // namespace net
} // namespace arc
void arc::net::FrameworkMessage::init() {
  maps.push_back(typeid(_FrameworkMessage_).hash_code());
  maps.push_back(typeid(RegisterUDP).hash_code());
  maps.push_back(typeid(RegisterTCP).hash_code());
  maps.push_back(typeid(KeepAlive).hash_code());
}
bool arc::net::FrameworkMessage::isExtend(boost::any object) {
  if (maps.empty())
    init();
  auto t = object.type().hash_code();
  for (auto i : maps) {
    if (t == i) {
      return true;
    }
  }
  return false;
}
