#include "../../arc/func/Func.cpp"
#include "./Packet.cpp"
#include "./Packets.cpp"
#include <boost/any.hpp>
#include <forward_list>
#include "./Streamable.cpp"
#include <map>
using namespace mindustry::net::Packets;
namespace mindustry{
    namespace net{
        class Net{
            public:
            std::map<int,Streamable::StreamBuilder> streams();
            std::map<std::string,boost::any> clientListeners;
            template<typename T,Cons<T> F>
            void handleClient(F listener){
                clientListeners[typeid(T).name()]=(void(*)(T))listener;
            }
            template<is_Packet T>
            void handleClientReceived(T object){
                object.handled();
                if(std::is_base_of<::StreamBegin,T>::value){

                }
            }
        };
    }
}
