#pragma once

#include "./Log.hpp"
template <OutString... T>
void arc::util::Log::info(std::string str, T... args) {
  log(LogLevel::info, str, args...);
}
template <OutString... T>
void arc::util::Log::debug(std::string str, T... args) {
  log(LogLevel::debug, str, args...);
}
void arc::util::Log::out(std::string str, std::smatch s) {
  std::cout << str << std::endl;
}
template <OutString U>
void arc::util::Log::out(std::string str, std::smatch s, U arg) {
  bool flag = false;
  while (std::regex_search(str, s, Reg)) {
    auto a = s[0];
    auto p = s.position();
    auto key = a.str().substr(2, a.length());
    std::cout << str.substr(0, p);
    if (datas.count(key) > 0) {
      std::cout << datas[key];
    } else {
      if (!flag)
        std::cout << arg;
      else
        std::cout << "[none]";
    }
    str = s.suffix().str();
  }
  std::cout << str.substr(0) << std::endl;
  return;
}
template <OutString U, OutString... T>
void arc::util::Log::out(std::string str, std::smatch s, U arg, T... args) {
  if (!std::regex_search(str, s, Reg)) {
    std::cout << str << std::endl;
    return;
  }
  auto a = s[0];
  auto p = s.position();
  std::cout << str.substr(0, p);
  auto key = a.str().substr(2, a.length());
  if (datas.count(key) > 0) {
    std::cout << datas[key];
  } else {
    std::cout << arg;
  }
  str = s.suffix().str();
  out(str, s, args...);
}
template <OutString... T>
void arc::util::Log::log(LogLevel level, std::string str, T... args) {
  std::string f = "[none]";
  switch (level) {
  case LogLevel::info:
    f = "[info]";
    break;
  case LogLevel::warn:
    f = "[warn]";
    break;
  case LogLevel::err:
    f = "[err]";
    break;
  case LogLevel::none:
    f = "[none]";
    break;
  case LogLevel::debug:
    f = "[debug]";
    break;
  }
  std::cout << f;
  std::smatch match;

  out(str, match, args...);
}

std::regex arc::util::Log::Reg("\\$\\{[^\\$\\{\\}]*\\}");
std::map<std::string, std::string> arc::util::Log::datas;
