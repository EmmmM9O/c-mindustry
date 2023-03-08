#include "./Packet.cpp"
#include "./Packets.cpp"
#include <vector>
#include "../../java/nio/ByteBuffer.cpp"
using namespace java::nio;
namespace mindustry{
    namespace net{
        namespace Streamable{
            
            class _Streamable_:public ::mindustry::net::Packet{
                public:
                virtual int getPriority() override{
                    return priorityHigh;
                }
                ByteBuffer stream;
            };
            class StreamBuilder{
                public:
                int id;
                unsigned char type;
                int total;
                ByteBuffer stream;
                StreamBuilder(){
                    
                }
                StreamBuilder(::mindustry::net::Packets::StreamBegin const &b){
                    id=b.id;type=b.type;total=b.total;
                }
                void add(std::vector<unsigned char> bytes){
                    stream.write(bytes);
                }
                bool isDone(){
                    return stream.size() >= total;
                }
                _Streamable_ build();
            };
        }
    }
}