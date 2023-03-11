#include "./NetClient.hpp"
using namespace mindustry::Vars;
using namespace mindustry::net::Packets;
using namespace arc::util;
using namespace mindustry::core;
NetClient::NetClient() {
  Vars::net.handleClient<::Connect>([](auto packet) -> void {
    Log::info("Connecting to server: ${}", packet.addressTCP);
  });
}
namespace mindustry {
namespace core {
namespace Vars {
core::NetClient netClient;
}
} // namespace core
} // namespace mindustry