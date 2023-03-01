#pragma once

#include "./TcpConnection.cpp"
#include "./UdpConnection.cpp"
#include <boost/any.hpp>
#include <string>
#include <sys/socket.h>

namespace arc {
    namespace net {
        class Connection;
        class NetListener{
            public:
            void received(Connection *con,boost::any obj);

        };
        class Connection{
            protected:
            std::string name;
            TcpConnection tcp;
            UdpConnection udp;
            std::vector<NetListener> listeners;
            volatile bool isConnected;
            int id=-1;
            protected:
            Connection(NetSerializer serialization, int writeBufferSize, int objectBufferSize)
            :tcp(serialization,writeBufferSize,objectBufferSize),
            udp(serialization,writeBufferSize)
            {

            }
            public:
            int getID(){
                return id;
            }
            bool getIsConnected(){
                return isConnected;
            }
            template<typename T>
            void sendTCP(T o){
                tcp.send(o);
            }
            template<typename T>
            void sendUDP(T o){
                udp.send(o);
            }

            void close(){
                isConnected=false;
                tcp.close();udp.close();
            }
            void notifyReceived(boost::any obj){
                for(auto i:listeners){
                    i.received(this, obj);
                }
            }
            
        };
    }
}