#pragma once
#include "./DataOutput.hpp"
#include "DataInput.hpp"
#include <string>

java::io::DataOutput::DataOutput() { byteStream = std::vector<byte>(); }
java::io::DataOutput::DataOutput(int l) { byteStream = std::vector<byte>(l); }
template <typename T> void java::io::DataOutput::WriteValue(T &val) {
  byteStream.insert(byteStream.end(), reinterpret_cast<byte *>(&val),
                    reinterpret_cast<byte *>(&val) + sizeof(T));
}
void java::io::DataOutput::WriteFloat(float val) { WriteValue(val); }
void java::io::DataOutput::WriteInt(int val) {
  auto i = htonl(val);
  WriteValue(i);
}
void java::io::DataOutput::WriteByte(byte b) { WriteValue(b); }
void java::io::DataOutput::WriteShort(short s) {
  auto i = htons(s);
  WriteValue(i);
}
void java::io::DataOutput::Write(byte s[]) { WriteValue(s); }
void java::io::DataOutput::writeUTF(std::string str) { WriteValue(str); }
std::string java::io::DataOutput::_str() {
  std::string k = "";
  for (int i = 0; i < byteStream.capacity(); i++) {
    auto c = byteStream[i];
    k += std::to_string((int)c);
    k += " ";
  }
  return k;
}
