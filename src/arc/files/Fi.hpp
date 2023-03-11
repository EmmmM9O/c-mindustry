#pragma once
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <string>
using namespace boost;
namespace arc {
namespace files {
enum class FileType { absolute };
class File {
public:
  filesystem::path path;
  File(std::string pa);
  std::string getPath();
  std::string getName();
};
class Fi {
protected:
  File file;
  FileType type;
  Fi(std::string p, FileType t);

public:
  Fi(std::string p);
  std::string path();
  std::string name();
};
} // namespace files
} // namespace arc