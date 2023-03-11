#pragma once
#include "../java/io/DataInput.cpp"
#include "../struct/Socket.cpp"
#include <asm-generic/errno.h>
#include <chrono>
#include <exception>
#include <memory>
#include <string>
#include <vector>
using namespace Struct;
namespace tools {
class TimeOut : public std::exception {
  const char *what() const throw();
};
class ServerInfo {
public:
  std::string name, mapName, decs, modeName, versiontype;
  int players, waves, version, limit;
  char gamemod;
  ServerInfo(std::vector<char> data);
  void read(java::io::DataInput data);
  void read(std::vector<char> data);
  std::string toString();
};
ServerInfo pingHost(int port, std::string host);
} // namespace tools
