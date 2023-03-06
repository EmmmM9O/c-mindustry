#pragma once
#include "../../../java/io/DataOutput.cpp"
#include <iterator>
#include <string>
#include <vector>

namespace arc{
    namespace util{
        namespace io{
            class Writes{
                public:
                java::io::DataOutput output;
                static Writes instance;
                Writes(std::vector<byte> b){
                    output=java::io::DataOutput();
                    output.byteStream=b;
                }
                Writes(java::io::DataOutput out){
                    output=out;
                }
                static Writes get(java::io::DataOutput out){
                    instance.output=out;
                    return instance;
                }
                void i(int v){
                    output.WriteInt(v);
                }
                void b(byte b){
                    output.WriteByte(b);
                }
                void b(byte b[]){
                    output.Write(b);
                }
                void s(short s){
                    output.WriteShort(s);
                }
                void str(std::string str){
                    output.writeUTF(str);
                }
            };
        }
    }
}