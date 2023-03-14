
#include "./arc/util/Log.cpp"
#include "mindustry/core/NetClient.cpp"
#include "mindustry/gen/Call.cpp"
#include "mindustry/gen/Call.hpp"
#include "mindustry/gen/Packets.hpp"
#include "mindustry/net/ArcNetProvider.hpp"
#include <cstdio>
using namespace mindustry::gen;
using namespace arc::util;
int main() {
  Call::registerPackets();
  Log::info("Net Test! look forword -2:${}",(int)(unsigned char)-2);
  mindustry::Vars::net.connect("n2.akiracloud.net", 10404,
                               []() -> void { Log::info("Connect success"); });

  mindustry::Vars::net.handleClient<mindustry::gen::SendMessageCallPacket2>(
      [](SendMessageCallPacket2 packet) -> void {
        Log::info("A Message! ${}", packet.message);
      });
  Log::debug("Wait");
  std::getchar();
  Log::debug("Close");
  mindustry::Vars::net.disconnect();
  return 0;
}
