#pragma once

#include "./ByteBuffer.hpp"

int java::nio::ByteBuffer::remaining() {
  return byteStream.max_size() - streamIter;
}

java::nio::ByteBuffer::ByteBuffer() : io::DataOutput(), io::DataInput() {}
int java::nio::ByteBuffer::size() { return byteStream.capacity(); }
void java::nio::ByteBuffer::write(std::vector<unsigned char> v) {
  for (auto i : v) {
    byteStream.push_back(i);
  }
}
java::nio::ByteBuffer::ByteBuffer(int length)
    : io::DataOutput(length), io::DataInput(length) {}
java::nio::ByteBuffer java::nio::ByteBuffer::allocate(int l) {
  return ByteBuffer(l);
}
void java::nio::ByteBuffer::put(std::vector<char> buf) {
  for (auto i : buf) {
    byteStream.push_back(static_cast<unsigned char>(i));
  }
}
void java::nio::ByteBuffer::put(ByteBuffer byte) { put(byte.byteStream); }
void java::nio::ByteBuffer::put(std::vector<byte> buf) {
  for (auto i : buf) {
    byteStream.push_back(i);
  }
}

java::nio::ByteBuffer java::nio::ByteBuffer::from(std::vector<char> buf) {
  auto b = ByteBuffer(buf.size());
  for (auto i : buf) {
    b.byteStream.push_back(static_cast<unsigned char>(i));
  }
  return b;
}
java::nio::ByteBuffer java::nio::ByteBuffer::flip() {
  streamIter = 0;
  return *this;
}
void java::nio::ByteBuffer::clear() {
  byteStream.clear();
  streamIter = 0;
}
int java::nio::ByteBuffer::position() { return streamIter; }
void java::nio::ByteBuffer::position(int p) { streamIter = p; }
void java::nio::ByteBuffer::limit(int length) {
  if (length > byteStream.max_size()) {
    byteStream.resize(length);
  }
}
