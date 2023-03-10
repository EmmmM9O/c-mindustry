
#pragma once
#include "./Packets.cpp"
#include "../net/ArcNetProvider.cpp"
using namespace arc::net;
namespace mindustry{
    namespace gen{
        namespace Call{
            void registerPackets(){
                net::Net::registerPacket<SendMessageCallPacket2>(71);
                net::Net::registerPacket<StreamBegin>(0);
                net::Net::registerPacket<StreamChunk>(1);
                

            }
        }
    }
}