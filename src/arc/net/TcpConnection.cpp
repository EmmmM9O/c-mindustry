#include "./NetSerializer.cpp"
#include "../../struct/Socket.cpp"
#include "../../java/nio/ByteBuffer.cpp"
namespace arc {
    namespace net {
        class TcpConnection{
            private:
            NetSerializer serialization;
            Struct::Socket socket;
            java::nio::ByteBuffer readBuffer, writeBuffer;
            public:
            short currentObjectLength;
            TcpConnection(
                NetSerializer serialization_, 
                int writeBufferSize, int objectBufferSize
            ):
                socket(Struct::domain::IPV4,
                Struct::type::TCP,0){
                    serialization=serialization_;
                    readBuffer=java::nio::ByteBuffer::allocate(
                        objectBufferSize
                    );
                    writeBuffer=java::nio::ByteBuffer::allocate(
                        writeBufferSize
                    );
                    readBuffer.flip();
                }
                void close(){
                    if(socket.connectd)socket.close();
                }
                void connect(int port,std::string ip){
                    if(socket.connectd) close();
                    currentObjectLength=0;
                    writeBuffer.clear();
                    readBuffer.clear();
                    readBuffer.flip();
                    socket.connect(port, ip);
                }
                auto readObject(){
                    if(socket.connectd){
                        if(currentObjectLength==0){
                            currentObjectLength=readBuffer.ReadShort();
                        }
                    }
                }
        };
    }
}