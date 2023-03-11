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
class Client : public Connection {
private:
  std::thread thread;
  bool udpRegistered, tcpRegistered;
  NetSerializer *serialization;

public:
  bool debug = true;
  time_t time;
  Client(int writeBufferSize, int objectBufferSize,
         NetSerializer *serialization_);
  void connect(int port, std::string host, int time);
  void keepAlive();
};
} // namespace net
} // namespace arc
