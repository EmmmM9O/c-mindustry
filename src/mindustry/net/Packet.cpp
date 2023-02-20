#include <boost/any.hpp>
#include "./NetConnection.cpp"
namespace mindustry {
    namespace net {
        class Packet{
            public :
            static const int priorityLow =8;
            static const int priorityHigh=2;
            static const int priorityNormal=1;
            virtual void read(boost::any &read);
            virtual void write(boost::any &write);
            virtual void read(boost::any &readr,int length){
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