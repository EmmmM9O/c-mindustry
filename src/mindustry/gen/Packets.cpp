#pragma once

#include "../net/Packet.cpp"
#include "../io/TypeIO.cpp"
#include <string>
using namespace mindustry::net;
namespace mindustry{
    namespace gen{
        class SendMessageCallPacket2: public ::Packet{
            public:
            std::string unformatted,message;
            int playersender;
            virtual void read(arc::util::io::Reads &read) override{
                message=io::TypeIO::readString(read);
                unformatted=io::TypeIO::readString(read);
                playersender=read.i();
            }
        };
    }
}