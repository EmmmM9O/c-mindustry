#include "../../arc/ApplicationListener.cpp"
#include "../../arc/util/Log.cpp"
#include "../Vars.cpp"
#include "../net/Packets.cpp"
using namespace mindustry::Vars;
using namespace mindustry::net::Packets;
using namespace arc::util;
namespace mindustry{
    namespace core{
        class NetClient:public arc::ApplicationListener{
            public:
            NetClient(){
                ::net.handleClient<::Connect>
                ([](auto packet)->void{
                    Log::info("Connecting to server: ${}", packet.addressTCP);
                });
                
            }
        };
    }
}