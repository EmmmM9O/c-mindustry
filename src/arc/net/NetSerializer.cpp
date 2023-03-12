#pragma once

#include "./NetSerializer.hpp"
template <typename T>
void arc::net::NetSerializer<T>::write(java::nio::ByteBuffer &buffer,
                                       java::AnyObject<T>) {}
template <typename T>
java::AnyObject<T>
arc::net::NetSerializer<T>::read(java::nio::ByteBuffer &buffer) {
  return java::AnyObject<T>();
}
template <typename T> int arc::net::NetSerializer<T>::getLengthLength() {
  return 2;
}
template <typename T>
void arc::net::NetSerializer<T>::writeLength(java::nio::ByteBuffer &buffer,
                                             int length) {}
template <typename T>
int arc::net::NetSerializer<T>::readLength(java::nio::ByteBuffer &buffer) {
  return buffer.ReadShort();
}