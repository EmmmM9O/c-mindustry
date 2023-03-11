#pragma once
#include <climits>
#include <netinet/in.h>
#include <string>
#include <vector>
typedef unsigned char byte;

namespace java {
namespace io {
class DataOutput {
public:
  DataOutput();
  DataOutput(int l);
  std::vector<byte> byteStream;
  template <typename T> void WriteValue(T &val);
  void WriteFloat(float val);
  void WriteInt(int val);
  void WriteByte(byte b);
  void WriteShort(short s);
  void Write(byte s[]);
  void writeUTF(std::string str);
  std::string _str();
};
} // namespace io
} // namespace java