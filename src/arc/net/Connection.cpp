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
            virtual void received(Connection *con,boost::any obj){
                
            }
            virtual void connected(Connection *connection){

            }


        };
        class Connection{
            public:
            std::string name;
            TcpConnection tcp;
            UdpConnection udp;
            std::list<NetListener*> listeners;
            volatile bool isConnected;
            int id=-1;
            Connection(NetSerializer* serialization, int writeBufferSize, int objectBufferSize)
            :tcp(serialization,writeBufferSize,objectBufferSize),
            udp(serialization,writeBufferSize)
            {

            }
            public:
            std::string getIP(){
                return tcp.getIP();
            }
            int getID(){
                return id;
            }
            bool getIsConnected(){
                return isConnected;
            }
            void sendTCP(boost::any o){
                tcp.send(o);
            }
            
            void sendUDP(boost::any o){
                udp.send(o);
            }

            void close(){
                isConnected=false;
                tcp.close();udp.close();
            }
            void notifyReceived(boost::any obj){
                for(auto i:listeners){
                    i->received(this, obj);
                }
            }
            void addListener(NetListener*listener){
                listeners.push_front(listener);
            }
        };
    }
}
