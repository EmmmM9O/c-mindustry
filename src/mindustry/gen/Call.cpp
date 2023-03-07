
#pragma once
#include "./Packets.cpp"
#include "../net/ArcNetProvider.cpp"
namespace mindustry{
    namespace gen{
        namespace Call{
            void registerPackets(){
                net::Net::registerPacket<SendMessageCallPacket2>
                ([]()->SendMessageCallPacket2{
                    return SendMessageCallPacket2();
                }, 71);
            }
        }
    }
}