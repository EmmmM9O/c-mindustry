#pragma once
#include "./Net.cpp"
#include "../../arc/net/Client.cpp"
#include "../../arc/net/ArcNet.cpp"
#include "../../arc/net/NetSerializer.cpp"
#include "../../arc/util/Log.cpp"
#include "../Vars.cpp"
#include <exception>
#include "./Packets.cpp"
using namespace arc::net;
using namespace arc::util;
namespace mindustry{
    
    namespace net{
        class _NetListener_:public NetListener{
            public:
            virtual void connected(Connection *connection) override;
        };
        class PacketSerializer:virtual public NetSerializer{

        };
        class ArcNetProvider:virtual public NetProvider{
            public:
            Client client;
            ArcNetProvider();
        };
    }
    namespace Vars{
        mindustry::net::Net net=mindustry::net::Net(ArcNetProvider());
    }
}
mindustry::net::ArcNetProvider::
ArcNetProvider():client(8192,8192,PacketSerializer()){
    ArcNet::errorHandler=[](std::exception err)->void{Log::debug(err.what());};
    client.addListener(_NetListener_());
}
void mindustry::net::_NetListener_::connected(Connection *connection){
    Connect c;c.addressTCP=connection->getIP();
    Vars::net.handleClientReceived(c);
}