#pragma once

#include "./NetSerializer.hpp"
template <typename T>
void arc::net::NetSerializer<T>::write(
    java::nio::ByteBuffer &buffer,
    java::AnyTwo<java::AnyObject<T>,
                 java::AnyObject<FrameworkMessage::_FrameworkMessage_>>) {}
template <typename T>
java::AnyTwo<java::AnyObject<T>,
             java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>>
arc::net::NetSerializer<T>::read(java::nio::ByteBuffer &buffer) {
  return java::AnyTwo<java::AnyObject<T>,
                      java::AnyObject<FrameworkMessage::_FrameworkMessage_>>();
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