#pragma once

#include "./TypeIO.hpp"

void mindustry::io::TypeIO::writeString(arc::util::io::Writes &buffer,
                                        std::string str) {
  if (str.length() > 0) {
    buffer.b(1);
    buffer.str(str);
  } else {
    buffer.b((short)0);
  }
}
std::string mindustry::io::TypeIO::readString(arc::util::io::Reads &read) {
  byte exists = read.b();
  if (exists != 0) {
    return read.str();
  }
  return nullptr;
}