#include "../../java/nio/ByteBuffer.cpp"
#include "./NetSerializer.cpp"
#include <regex>
#include <string>
#include "../../struct/Socket.cpp"
#include "./FrameworkMessage.cpp"


using namespace java::nio;
namespace arc {
    namespace net {
        class UdpConnection{
            private:
            Struct::Socket socket;
            ByteBuffer readBuffer, writeBuffer;
            NetSerializer *serialization;
            public:
            UdpConnection(NetSerializer*serialization_, int bufferSize)
            :socket(Struct::domain::IPV4, Struct::type::UDP, 0){
                serialization=serialization_;
                readBuffer = ByteBuffer::allocate(bufferSize);
            writeBuffer = ByteBuffer::allocate(bufferSize);
            }
            ~UdpConnection(){
                close();
            }
            void close(){
                if(socket.connectd){
                    socket.close();
                }
            }
            void  connect(int port,std::string ip){
                close();readBuffer.clear();
                writeBuffer.clear();
                if(!socket.connectd){
                    socket.connect(port,ip);
                }
            }
            auto readObject(){
                readBuffer.flip();
                auto o=serialization->read(readBuffer);
                readBuffer.clear();
                return o;
            }
                
            template<typename T>
            void send(T obj){
                if(socket.connectd){
                    writeBuffer.clear();
                    serialization->write(writeBuffer, obj);
                    writeBuffer.flip();
                    socket.send(writeBuffer.byteStream.data(),
                    writeBuffer.byteStream.size());
                }
            }
        };
    }
}