#pragma once
#include "./Connection.cpp"
#include "./NetSerializer.cpp"
#include <bits/types/time_t.h>
#include <boost/any.hpp>
#include <chrono>
#include <iostream>
#include <set>
#include <string>
#include <thread>
#include <time.h>
#include <type_traits>
namespace arc {
namespace net {
template <typename T> class Client : public Connection<T> {
private:
  std::thread thread;
  bool udpRegistered, tcpRegistered;
  NetSerializer<T> *serialization;
public:
  bool debug = true;
  time_t time;
  Client(int writeBufferSize, int objectBufferSize,
         NetSerializer<T> *serialization_);
  void connect(int port, std::string host, int time);
  void keepAlive();
};
} // namespace net
} // namespace arc
