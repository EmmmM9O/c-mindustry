#pragma once
#include "./DataInput.hpp"

java::io::DataInput::DataInput(std::vector<byte> b) {
  byteStream = b;
  streamIter = 0;
}
java::io::DataInput::DataInput(int l) {
  streamIter = 0;
  byteStream = std::vector<byte>(l);
}
java::io::DataInput::DataInput() {
  streamIter = 0;
  byteStream = std::vector<byte>();
}
template <typename T> T java::io::DataInput::ReadValue() {
  T val = *(reinterpret_cast<T *>(byteStream.data() + streamIter));
  streamIter += sizeof(T);
  return val;
}
std::string java::io::DataInput::Read2String() {
  auto o = streamIter;
  std::string str = "";
  auto len = (int)ReadValue<char>();
  while (streamIter - o <= len) {
    str += ReadValue<char>();
  }
  return str;
}
char java::io::DataInput::Read2Char() {
  ReadValue<char>();
  return ReadValue<char>();
}
int java::io::DataInput::ReadInt() { return ntohl(ReadValue<int>()); }
float java::io::DataInput::ReadFloat() { return ReadValue<float>(); }
long java::io::DataInput::ReadLong() { return ntohl(ReadValue<long>()); }
byte java::io::DataInput::ReadByte() { return ReadValue<byte>(); }

short java::io::DataInput::ReadShort() { return ntohs(ReadValue<short>()); }
void java::io::DataInput::readFully(std::vector<byte> &d) {
  while (streamIter < byteStream.size()) {
    d.push_back(ReadByte());
  }
}
std::string java::io::DataInput::ReadString() {
  return ReadValue<std::string>();
}
