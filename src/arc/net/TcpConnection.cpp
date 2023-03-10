#include "../../struct/Socket.cpp"
#include "../../java/nio/ByteBuffer.cpp"
#include "./FrameworkMessage.cpp"
#include <boost/any.hpp>
#include <chrono>
#include "./NetSerializer.cpp"
#include <iostream>
namespace arc {
    namespace net {
        class TcpConnection{
            private:
		    bool debug=true;
            NetSerializer* serialization;
            Struct::Socket socket;
            java::nio::ByteBuffer readBuffer, writeBuffer;
            int timeout;
            public:
            std::string getIP(){
                return socket.Chost;
            }
            ~TcpConnection(){
                close();
            }
            short currentObjectLength=0;
            TcpConnection(
                NetSerializer *serialization_, 
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
                void connect(int port,std::string ip,int time){
                    timeout=time;
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
                            //currentObjectLength=readBuffer.ReadShort();
                            int lengthLength = serialization->getLengthLength();
                            currentObjectLength = serialization->readLength(readBuffer);
                            if(readBuffer.remaining()<lengthLength){
				    std::cout<<"Read new Buffer"<<std::endl;
                                try{
                                socket.read(readBuffer, timeout);                            
                                }catch(Struct::TimeOut &e){           
                                    throw e;
                                }
                            }
                        }
                    auto b=readBuffer.streamIter;
                    int length = currentObjectLength;
                    currentObjectLength = 0;
                    readBuffer.streamIter=b;
                    return serialization->read(readBuffer);
		    }
                }
                int send(boost::any obj){
                    int lengthLength = serialization->getLengthLength();
                    int start=writeBuffer.streamIter;
                    writeBuffer.streamIter+=lengthLength;
                    serialization->write(writeBuffer,obj);
                    int end=writeBuffer.streamIter;
                    writeBuffer.streamIter=start;
                    serialization->writeLength(writeBuffer, end - lengthLength - start);serialization->writeLength(writeBuffer, end - lengthLength - start);
                    writeBuffer.streamIter=end;
                    socket.send(writeBuffer.byteStream.data(),writeBuffer.byteStream.size());
                    return end-start;
                }

        };
    }
}
