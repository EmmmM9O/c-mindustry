#pragma once

#include "../../arc/util/io/Writes.cpp"
#include "../../arc/util/io/Reads.cpp"
#include <cstddef>
#include <string>
namespace mindustry {
    namespace io {
        class TypeIO{
            public:
            static void writeString(arc::util::io::Writes &buffer
            ,std::string str){
                if(str.length()>0){
                    buffer.b(1);
                    buffer.str(str);
                }else{
                    buffer.b((short)0);
                }
            }
            static std::string readString(
                arc::util::io::Reads &read
            ){
                byte exists = read.b();
                if(exists!=0){
                    return read.str();
                }
                return nullptr;
            }
        };
    }
}