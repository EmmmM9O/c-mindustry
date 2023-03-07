#pragma once

#include <array>
#include <boost/any.hpp>
#include <map>
namespace arc {
    namespace net {
        namespace FrameworkMessage{
            class _FrameworkMessage_{

            };
            class KeepAlive:public _FrameworkMessage_{

            };
            const KeepAlive keepAlive;
            class RegisterTCP:public _FrameworkMessage_{
                public:
                int connectionID;
            };
            class RegisterUDP:public _FrameworkMessage_{
                public:
                int connectionID;
            };
            class DiscoverHost:public _FrameworkMessage_{

            };
            class Ping:public _FrameworkMessage_{
                public:
                int id;
                bool isReply;
            };
            DiscoverHost discoverHost;
            std::vector<size_t> maps;
            void init(){
                maps.push_back(typeid(_FrameworkMessage_).hash_code());
                maps.push_back(typeid(RegisterUDP).hash_code());
                maps.push_back(typeid(RegisterTCP).hash_code());
                maps.push_back(typeid(KeepAlive).hash_code());

            }
            bool isExtend(boost::any object){
                if(maps.empty()) init();
                auto t=object.type().hash_code();
                for(auto i:maps){
                    if(t==i){
                        return true;
                    }
                }
                return false;
            }
        };
    }
}