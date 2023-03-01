#include "./Connection.cpp"
#include "./NetSerializer.cpp"
#include <bits/types/time_t.h>
#include <chrono>
#include <set>
#include <string>
#include <thread>
#include <time.h>
#include <type_traits>
namespace arc {
    namespace net {
        class Client:Connection{
            private:
            std::thread thread;
            bool udpRegistered,tcpRegistered;
            NetSerializer serialization;
            public:
            time_t time;
            Client(int writeBufferSize,
             int objectBufferSize,
              NetSerializer serialization_)
              :Connection(serialization_,writeBufferSize
              ,objectBufferSize){
                serialization=serialization_;
                thread=std::thread([this]()->void{
                    if(!isConnected) return;
                    while(true){
                        try{
                          auto o=tcp.readObject();
                          if(o.empty()) break;
                          if(!tcpRegistered){
                            if(std::is_base_of<
                            FrameworkMessage::RegisterTCP
                            ,typeof o.type()>
                            ::value){
                                tcpRegistered=true;
                                auto p=FrameworkMessage::RegisterTCP();
                                sendUDP(p);
                            }
                          }
                          if(!udpRegistered){
                            if(std::is_base_of<FrameworkMessage::RegisterUDP, 
                            typeof o.type()>::value){
                                udpRegistered=true;
                            }
                          }
                          if(!std::is_base_of<FrameworkMessage::_FrameworkMessage_, 
                          typeof o.type()>::value){
                            notifyReceived(o);
                          }
                        }catch(Struct::TimeOut &e){
                            break;
                        }
                    }
                    keepAlive();
                });
            }
            void connect(int port,std::string host,int time){
                tcp.connect(port, host, time);
                udp.connect(port, host);
                thread.detach();
                isConnected=true;
            }
            void keepAlive(){
                if(!isConnected)return;
                time_t now(0);localtime(&now);
                if(difftime(now,time)<8) return;
                localtime(&time);
                sendTCP(FrameworkMessage::keepAlive);
                sendUDP(FrameworkMessage::keepAlive);
                //std::this_thread::sleep_for(std::chrono::seconds(8));
            }
            
        };
    }
}