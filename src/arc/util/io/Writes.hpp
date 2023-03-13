#pragma once
#include "../../../java/io/DataOutput.cpp"
#include <iterator>
#include <string>
#include <vector>

namespace arc {
namespace util {
namespace io {
class Writes {
public:
  java::io::DataOutput output;
  static Writes instance;
  Writes(std::vector<byte> b);
  Writes(java::io::DataOutput out);
  static Writes get(java::io::DataOutput out);
  void i(int v);
  void b(byte b);
  void b(byte b[]);
  void s(short s);
  void str(std::string str);
  Writes();
};
} // namespace io
} // namespace util
} // namespace arc