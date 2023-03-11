#pragma once
#include <cstdint>
#include <netinet/in.h>
#include <stack>
#include <string>
#include <vector>
typedef unsigned char byte;
namespace java {
namespace io {
class DataInput {
public:
  DataInput(std::vector<byte> b);
  DataInput(int l);
  int streamIter;
  std::vector<byte> byteStream;
  DataInput();
  template <typename T> T ReadValue();
  std::string Read2String();
  char Read2Char();
  int ReadInt();
  float ReadFloat();
  long ReadLong();
  byte ReadByte();
  short ReadShort();
  void readFully(std::vector<byte> &d);
  std::string ReadString();
};
} // namespace io
} // namespace java
