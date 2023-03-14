#pragma once

#include "../io/DataInput.cpp"
#include "../io/DataOutput.cpp"
#include <string>
#include <sys/syscall.h>
#include <vector>
typedef unsigned char byte;
namespace java {
namespace nio {
class ByteBuffer : public io::DataInput, public io::DataOutput {

public:
  int remaining();
  std::vector<byte> byteStream;
  ByteBuffer();
  int size();
  void write(std::vector<unsigned char> v);
  ByteBuffer(int length);
  static ByteBuffer allocate(int l);
  void put(std::vector<char> buf);
  void put(ByteBuffer byte);
  void put(std::vector<byte> buf);
  static ByteBuffer from(std::vector<char> buf);
  ByteBuffer flip();
  void clear();
  int position();
  void position(int p);
  void limit(int length);
};
} // namespace nio
} // namespace java
