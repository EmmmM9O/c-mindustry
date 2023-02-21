#pragma once
#include "../../../java/io/DataInput.cpp"
#include <string>
#include <vector>

namespace arc{
    namespace util{
        namespace io{
            class Reads{
                public:
                static Reads instance;
                java::io::DataInput input;
                Reads(java::io::DataInput inp){
                    input=inp;
                }
                static Reads get(java::io::DataInput in){
                    instance.input=in;
                    return instance;
                }
                long l(){
                    return input.ReadLong();
                }
                int i(){
                    return input.ReadInt();
                }
                byte b(){
                    return input.ReadByte();
                }
                std::string str(){
                    return input.ReadString();
                }
                short s(){
                    return input.ReadShort();
                }
                std::vector<byte> b(short len){
                    std::vector<byte> d;
                    input.readFully(d);
                    return d;
                }
            };
        }
    }
}