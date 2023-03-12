#pragma once
#include <array>
#include <boost/any.hpp>
#include <map>
namespace arc {
namespace net {
namespace FrameworkMessage {
class _FrameworkMessage_ {};
class KeepAlive : public _FrameworkMessage_ {};
const extern KeepAlive keepAlive;
class RegisterTCP : public _FrameworkMessage_ {
public:
  int connectionID;
};
class RegisterUDP : public _FrameworkMessage_ {
public:
  int connectionID;
};
class DiscoverHost : public _FrameworkMessage_ {};
const extern DiscoverHost discoverHost;
extern std::vector<size_t> maps;
class Ping : public _FrameworkMessage_ {
public:
  int id;
  bool isReply;
};
void init();
bool isExtend(boost::any object);
}; // namespace FrameworkMessage
} // namespace net
} // namespace arc