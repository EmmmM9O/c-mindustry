#pragma once

#include "../../arc/util/io/Reads.cpp"
#include "../../arc/util/io/Writes.cpp"
#include <cstddef>
#include <string>
namespace mindustry {
namespace io {
class TypeIO {
public:
  static void writeString(arc::util::io::Writes &buffer, std::string str);
  static std::string readString(arc::util::io::Reads &read);
};
} // namespace io
} // namespace mindustry