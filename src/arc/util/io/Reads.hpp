#pragma once
#include "../../../java/io/DataInput.cpp"
#include <string>
#include <vector>

namespace arc {
namespace util {
namespace io {
class Reads {
public:
  static Reads instance;
  java::io::DataInput input;
  Reads(java::io::DataInput input);
  static Reads get(java::io::DataInput in);
  long l();
  int i();
  byte b();
  std::string str();
  short s();
  std::vector<byte> b(short len);
};
} // namespace io
} // namespace util
} // namespace arc