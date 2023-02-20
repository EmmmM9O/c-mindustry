#include <vector>
typedef unsigned char byte;
namespace java{
    namespace io{
        class DataOutput{
            std::vector<byte> byteStream;
            template<typename T>
            void WriteValue(T &val){
                byteStream.insert(byteStream.end()
                ,reinterpret_cast<byte*>(&val),
                reinterpret_cast<byte*>(&val)+sizeof(T));
            }
            void WriteFloat(float val){
                WriteValue(val);
            }
            void WriteInt(int val){
                WriteValue(val);
            }
        };
    }
}