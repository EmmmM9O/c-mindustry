#pragma once
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <string>
using namespace boost;
namespace arc{
    namespace files{
        enum class FileType{
            absolute
        };
        class File{
            public:
            filesystem::path path;
            File(std::string pa){
                path=filesystem::path(pa);
            }
            std::string getPath(){
                return path.string();
            }
            std::string getName(){
                return path.filename().string();
            }

        };
        class Fi{
            protected:
            File file;
            FileType type;
            
            Fi(std::string p,FileType t):file(p){
                type=t;
            }
            public:
            Fi(std::string p):file(p){
                type=FileType::absolute;
            }
            std::string path(){
                return file.getPath();
            }
            std::string name(){
                return file.getName();
            }

        };
    }
}