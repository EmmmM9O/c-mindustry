#include "./Packet.cpp"
namespace mindustry{
    namespace net{
        namespace Streamable{
            class _Streamable_:public ::mindustry::net::Packet{
                public:
                virtual int getPriority() override{
                    return priorityHigh;
                }
            };
            class StreamBuilder{
                public:
                int id;
                unsigned char type;
                int total;
                StreamBuilder(StreamBuilder const &b){
                    id=b.id;type=b.type;total=b.total;
                }
                
            };
        }
    }
}