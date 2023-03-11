#pragma once

#include <boost/any.hpp>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <type_traits>
#include <utility>
template <typename T>
concept OutString = requires(T t) {
  std::cout << t;
};

namespace arc {
namespace util {
class Log {
public:
  int now;
  static std::regex Reg;
  static std::map<std::string, std::string> datas;
  enum class LogLevel { debug, info, warn, err, none };
  template <OutString... T> static void info(std::string str, T... args);
  template <OutString... T> static void debug(std::string str, T... args);
  static void out(std::string str, std::smatch s);
  template <OutString U> static void out(std::string str, std::smatch s, U arg);
  template <OutString U, OutString... T>
  static void out(std::string str, std::smatch s, U arg, T... args);
  template <OutString... T>
  static void log(LogLevel level, std::string str, T... args);
};
} // namespace util
} // namespace arc
