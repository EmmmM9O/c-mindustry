#pragma once
#include <boost/any.hpp>
#include "./NetConnection.cpp"
#include "../../arc/util/io/Writes.cpp"
#include "../../arc/util/io/Reads.cpp"
namespace mindustry {
    namespace net {
        class Packet{
            public :
            static const int priorityLow =8;
            static const int priorityHigh=2;
            static const int priorityNormal=1;
            virtual void read(arc::util::io::Reads &read);
            virtual void write(arc::util::io::Writes &write);
            virtual void read(arc::util::io::Reads &readr,int length){
                read(readr);
            }
            virtual void handled();
            virtual int getPriority(){
                return priorityNormal;
            }
            virtual void handleClient();
            virtual void handleServer(mindustry::net::NetConnection con);
        };
    }
}
template <typename T>
concept is_Packet=std::is_base_of<mindustry::net::Packet,T>::value;