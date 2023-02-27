#include "../../java/nio/ByteBuffer.cpp"
#include "./NetSerializer.cpp"
#include <string>
#include "../../struct/Socket.cpp"
#include "./FrameworkMessage.cpp"
#include <thread>
#include <chrono>

using namespace java::nio;
namespace arc {
    namespace net {
        class UdpConnection{
            private:
            Struct::Socket socket;
            ByteBuffer readBuffer, writeBuffer;
            NetSerializer serialization;
            std::thread socketThread;
            public:
            UdpConnection(NetSerializer serialization_, int bufferSize)
            :socket(Struct::domain::IPV4, Struct::type::UDP, 0){
                serialization=serialization_;
                readBuffer = ByteBuffer::allocate(bufferSize);
            writeBuffer = ByteBuffer::allocate(bufferSize);
            socketThread=std::thread([this]()->void{
                if(!this->socket.connectd){
                    return;
                }
                std::this_thread::sleep_for(std::chrono::seconds(8));
            });
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
                    socketThread.detach();
                }
            }
        };
    }
}