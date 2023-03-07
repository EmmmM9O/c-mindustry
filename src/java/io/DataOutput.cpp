#pragma once
#include <climits>
#include <netinet/in.h>
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
            DataOutput(int l){
                byteStream=std::vector<byte>(l);
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
                auto i=htonl(val);
                WriteValue(i);
            }
            void WriteByte(byte b){
                WriteValue(b);
            }
            void WriteShort(short s){
                auto i=htons(s);
                WriteValue(i);
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