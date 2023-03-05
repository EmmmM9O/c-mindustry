#pragma once
#include "./Net.cpp"
#include "../../arc/net/Client.cpp"
#include "../../arc/net/ArcNet.cpp"
#include "../../arc/net/NetSerializer.cpp"
#include "../../arc/util/Log.cpp"
#include "../Vars.cpp"
#include <boost/any.hpp>
#include <exception>
#include <unistd.h>
#include "./Packets.cpp"
#include "Packet.cpp"
using namespace arc::net;
using namespace arc::util;
namespace mindustry{
    
    namespace net{
        class _NetListener_:public NetListener{
            public:
            virtual void connected(Connection *connection) override;
            virtual void received(Connection *con, boost::any obj) override;
        };
        class PacketSerializer:public NetSerializer{
            private:
            bool debug=false;
            public:
            virtual boost::any read(java::nio::ByteBuffer buffer) override:
            arc::net::FrameworkMessage::_FrameworkMessage_ readFramework(java::nio::ByteBuffer buffer);
            
        };
        class ArcNetProvider:public NetProvider{
            public:
            Client client;
            ArcNetProvider();
            virtual void connectClient(std::string ip, int port, void (*success)()) override{
                client.close();
                client.connect(port, ip, 5);
                success();
            }
            virtual void disconnectClient() override{
                client.close();
            }
            virtual void sendClient(boost::any object, bool reliable) override{
                if(reliable){
                    client.sendTCP(object);
                }else{
                    client.sendUDP(object);
                }
            } 
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
void mindustry::net::_NetListener_
::received(Connection *con, boost::any obj){
    try{
        auto p=boost::any_cast<Packet>(obj);
        Vars::net.handleClientReceived(p);
    }catch(...){}
}
boost::any mindustry::net::PacketSerializer
::read(java::nio::ByteBuffer buffer){
                if(debug){
                    Log::debug(buffer._str());
                }
                byte id=buffer.ReadByte();
                if(id==static_cast<byte>(-2))
                return readFramework(buffer);
                else{
                
                }
}