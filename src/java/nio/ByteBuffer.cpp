#pragma once

#include "../io/DataInput.cpp"
#include "../io/DataOutput.cpp"

#include <string>
#include <sys/syscall.h>
#include <vector>

typedef unsigned char byte;
namespace java {
    namespace nio {
        class ByteBuffer:virtual public io::DataInput,
        virtual public io::DataOutput{

            public:
            int remaining(){
                return byteStream.max_size()-streamIter;
            }
            std::vector<byte> byteStream;
            ByteBuffer():io::DataOutput(),io::DataInput(){

            }
            int size(){
                return byteStream.size();
            }
            void write(std::vector<unsigned char> v){
                for(auto i :v){
                    byteStream.push_back(i);
                }
            }
            ByteBuffer(int length):io::DataOutput(length),
            io::DataInput(length){
                
            }
            static auto allocate(int l){
                return ByteBuffer(l);
            }
            void put(std::vector<char> buf){
                for(auto i:buf){
                    byteStream.push_back(
                        static_cast<unsigned char>(i)
                    );
                }
            }
            void put(ByteBuffer byte){
                put(byte.byteStream);
            }
            void put(std::vector<byte> buf){
                for(auto i:buf){
                    byteStream.push_back(i);
                }
            }
            
            static auto from(std::vector<char> buf){
                auto b=ByteBuffer(buf.size());
                for(auto i:buf){
                    b.byteStream.push_back(
                            static_cast<unsigned char>(i)
                    );
                }
                return b;
            }
            auto flip(){
                streamIter=0;
                return this;
            }
            void clear(){
                byteStream.clear();
                streamIter=0;
            }
            int position(){
                return streamIter;
            }
            void position(int p){
                streamIter=p;
            }
            void limit(int length){
                if(length>byteStream.max_size()){
                    byteStream.resize(length);
                }
            }
        };
    }
}