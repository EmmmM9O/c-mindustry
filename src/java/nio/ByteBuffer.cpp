#pragma once

#include "../io/DataInput.cpp"
#include "../io/DataOutput.cpp"

#include <vector>

typedef unsigned char byte;
namespace java {
    namespace nio {
        class ByteBuffer:virtual public io::DataInput,
        virtual public io::DataOutput{

            public:
            std::vector<byte> byteStream;
            ByteBuffer():io::DataOutput(),io::DataInput(){

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
        };
    }
}