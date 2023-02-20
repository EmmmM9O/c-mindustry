#include "./Packet.cpp"
#include <cstddef>

namespace mindustry{
    namespace net{
        namespace Packets{
            enum class AdminAction{
                kick, ban, trace, wave
            };
            class Connect:mindustry::net::Packet{
                public: 
                std::string addressTCP;
                virtual int getPriority() override{
                    return priorityHigh;
                }
            };
            class Disconnect:mindustry::net::Packet{
                public:
                std::string reason;
                virtual int getPriority() override{
                    return priorityHigh;
                }
            };
            class WorldStream:mindustry::net::Packet{

            };
            class StreamBegin:mindustry::net::Packet{
                private:
                static int lastid;
                public:
                int id;
                int total;
                std::byte type;
                virtual void write(boost::any &write) override{
                    
                }
                StreamBegin(){
                    id=lastid++;
                }
            };
        }
    }
}