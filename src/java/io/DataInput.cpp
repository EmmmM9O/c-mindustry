#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <stack>
#include <netinet/in.h>
typedef unsigned char byte;
namespace java{
    namespace io{
        class DataInput{
            public:
            DataInput(std::vector<byte> b){
                byteStream=b;
                streamIter=0;
            }
            DataInput(int l){
                streamIter=0;
                byteStream=std::vector<byte>(l);
            }
            int streamIter;
            std::vector<byte> byteStream;
	    DataInput(){
		    streamIter=0;
		    byteStream=std::vector<byte>();
	    }
            template<typename T>
            T ReadValue(){
                T val=*(reinterpret_cast<T*>(byteStream.data()+streamIter));
                streamIter+=sizeof(T);
                return val;
            }
            std::string Read2String(){
                auto o=streamIter;
                std::string str="";
                auto len=(int)ReadValue<char>();
                while(streamIter-o<=len){
                    str+=ReadValue<char>();
                }
                return str;
            }
            char Read2Char(){
                ReadValue<char>();
                return ReadValue<char>();
            }
            int ReadInt(){
                return ntohl(ReadValue<int>());
               // return ReadValue<int>();
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
