#pragma once

#include "../../arc/func/Func.cpp"
#include "./Packet.cpp"
#include "./Packets.cpp"
#include <boost/any.hpp>
#include <cstdio>
#include <forward_list>
#include "./Streamable.cpp"
#include <map>
#include <math.h>
#include <type_traits>
#include "../../arc/util/Log.cpp"
using namespace mindustry::net::Packets;
using namespace arc::util;
template <typename T,typename T1>
concept IsExtend=std::is_base_of<T1, T>::value;
namespace mindustry{
    namespace net{
        class NetProvider{
            public:
            virtual void connectClient(std::string ip, int port, void(*success)());
            virtual void sendClient(boost::any object,bool reliable);
            virtual void disconnectClient();
        };
        class Net{
            public:
            
            Net(NetProvider provide){
                provider=provide;
            }
            NetProvider provider;
            bool active=false;
            bool server=false;
            bool clientLoaded=true;
            static std::map<unsigned char, boost::any> packetProvs;
            template<IsExtend<Packet> T>
            static T newPacket(unsigned char id){
                auto t=packetProvs[id & 0xff];
                try{
                    return boost::any_cast<T(*)()>(t)();
                }catch(boost::bad_any_cast &e){
                    perror(e.what());
                    exit(1);
                }
            }
            static byte getPacketId(boost::any obj){
                for(auto i:packetProvs){
                    if(i.second.type().hash_code()==obj.type().hash_code()){
                        return i.first;
                    }
                }
                return -1;
            }
            std::map<int,Streamable::StreamBuilder> streams;
            std::map<std::string,boost::any> clientListeners;
            template<typename T,Cons<T> F>
            void handleClient(F listener){
                clientListeners[typeid(T).name()]=(void(*)(T))listener;
            }
            template<is_Packet T>
            void handleClientReceived(T object){
                object.handled();
                if(std::is_base_of<::StreamBegin,T>::value){
                    auto c=(::StreamBegin)object;
                    streams[c.id]=Streamable::StreamBuilder(c);
                }else if(std::is_base_of<::StreamChunk,T>::value){
                    auto c=(::StreamChunk)object;
                    if(streams.count(c.id)<=0) return;
                    auto builder=streams[c.id];
                    builder.add(c.data);
                    if(builder.isDone()){
                        streams.erase(builder.id);
                        handleClientReceived(builder.build());
                    }
                }else{
                    int p = object.getPriority();
                    if(clientLoaded||p==Packet::priorityHigh){
                        auto key=typeid(T).name();
                        if(clientListeners.count(key)>0){
                            auto t= clientListeners[key];
                            try{
                                boost::any_cast<void(*)(T)>(t)(object);
                            }catch(boost::bad_any_cast &e){
                                perror(e.what());
                                exit(1);
                            }
                        }else{
                            object.handleClient();
                        }
                    }
                }
            }
            template<Runnable Run>
            void connect(std::string ip, int port, Run success){
                try{
                    provider.connectClient(ip, port, (void(*)())success);
                    active=true;
                    server=false;
                }catch(...){}
            }
            void disconnect(){
                if(active&&!server){
                    Log::info("Disconnecting.");
                }
                provider.disconnectClient();
                server = false;
                active = false;
            }
            
        };
        
    }
}
using namespace mindustry::net;
std::map<unsigned char, boost::any> Net::packetProvs;
Streamable::_Streamable_
 Streamable::StreamBuilder::build(){
    auto s=
    Net::newPacket<Streamable::_Streamable_>(type);
    s.stream=stream;
    return s;
}