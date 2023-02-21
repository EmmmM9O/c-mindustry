#pragma once
#include <string>
#include <vector>
typedef unsigned char byte;
namespace java{
    namespace io{
        class DataInput{
            public:
            int streamIter;
            std::vector<byte> byteStream;
            template<typename T>
            T ReadValue(){
                T val=*(reinterpret_cast<T*>(byteStream.data()+streamIter));
                streamIter+=sizeof(T);
                return val;
            }
            int ReadInt(){
                return ReadValue<int>();
            }
            float ReadFloat(){
                return ReadValue<float>();
            }
            long ReadLong(){
                return ReadValue<long>();
            }
            byte ReadByte(){
                return ReadValue<byte>();
            }
            short ReadShort(){
                return ReadValue<short>();
            }
            void readFully(std::vector<byte> &d){
                while(streamIter<byteStream.size()){
                    d.push_back(ReadByte());
                }
            }
            std::string ReadString(){
                return ReadValue<std::string>();
            }
        };
    }
}