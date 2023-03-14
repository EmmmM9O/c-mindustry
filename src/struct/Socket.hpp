#pragma once
#include "../arc/Events.cpp"
#include "../java/nio/ByteBuffer.cpp"
#include <algorithm>
#include <arpa/inet.h>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <future>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <regex>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

namespace Struct {
class TimeOut : public std::exception {
  const char *what() const throw();
};
class HostErr : public std::exception {
  const char *what() const throw();
};
class ConnectEd : public std::exception {
  const char *what() const throw();
};
class UnConnect : public std::exception {
  const char *what() const throw();
};
class ConnectErr : public std::exception {
  const char *what() const throw();
};
enum class domain { IPV6 = AF_INET6, IPV4 = AF_INET };
enum class type { TCP = SOCK_STREAM, UDP = SOCK_DGRAM };
class Socket {
public:
  static const std::regex IPV4R;
  static const int BUFFER_SIZE = 1024;
  int id;
  bool connectd = false;
  struct sockaddr_in servaddr;
  void read(java::nio::ByteBuffer *buf, int time);
  std::string getIpByHost(std::string str);
  Socket(domain dom, type t, int protocol);
  template <typename T> void send(T arr, int length);
  void send(std::string str);
  std::string Chost;
  void connect(int port, std::string host);
  void close();
  std::vector<char> dataSync();
  std::future<std::vector<char>> data();
};
} // namespace Struct
