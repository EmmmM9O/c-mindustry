#pragma once
#include <string>
#include <vector>
typedef unsigned char byte;
namespace java{
    namespace io{
        class DataOutput{
            public:
            DataOutput(){
                byteStream=std::vector<byte>();
            }
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
            void WriteByte(byte b){
                WriteValue(b);
            }
            void WriteShort(short s){
                WriteValue(s);
            }
            void Write(byte s[]){
                WriteValue(s);
            }
            void writeUTF(std::string str){
                WriteValue(str);
            }
            std::string _str(){
                std::string k="";
                for(auto c:byteStream){
                    k+=c;
                }
                return k;
            }
        };
    }
}