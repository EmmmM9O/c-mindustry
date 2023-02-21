#include "../../java/nio/ByteBuffer.cpp"
#include <boost/any.hpp>
namespace arc {
    namespace net {
        class NetSerializer{
            public:
            virtual void write(java::nio::ByteBuffer buffer, 
            boost::any object);
            virtual boost::any read(java::nio::ByteBuffer);
            int getLengthLength(){
                return 2;
            }
            void writeLength(java::nio::ByteBuffer buffer, int length){

            }
            /*
            int readLength(java::nio::ByteBuffer buffer){
                return buffer.getShort();
            }*/
        };
    }
}