#include <array>
#include <vector>
typedef unsigned char byte;
namespace java {
    namespace nio {
        class ByteBuffer{
            private:
            std::vector<byte> buf;
            int capacity,limit,position=0,mark=-1;
            ByteBuffer(int length){
                buf=std::vector<byte>(length);
                limit=length;
            }
            public:
            static auto allocate(int length){
                return ByteBuffer(length);
            }
            static auto  from(std::vector<byte> buffer){
                auto obj=ByteBuffer(buffer.size());
                
                return obj;
            }
            auto clear(){
                position=0;limit=buf.size();
                buf.clear();return this;
            }
            auto get(int length){
                auto o=position;
                position+=length;
                std::vector<byte> b;
                for(int i=o;i<position;i++){
                    b.push_back(buf[i]);
                }
                return b;
            }
            auto getInt(){
                
            }
        };
    }
}