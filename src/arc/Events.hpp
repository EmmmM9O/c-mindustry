#pragma once

#include "func/Func.hpp"
#include <boost/any.hpp>
#include <forward_list>
#include <functional>
#include <iostream>
#include <string>
#include <type_traits>
#define EventType typename
template <typename T>
concept EnumType = std::is_enum<T>();
namespace arc {
class _Events_ {
private:
  static std::map<std::string, std::forward_list<boost::any>> events;

public:
  template <EnumType T, T V> static std::string getHash();
  template <EnumType T, Runnable R> static void on(T t, R func);
  template <EventType T, Cons<T> R> static void on(R func);
  template <EventType T, Runnable R> static void run(R func);
  template <typename T> static void fire(T packet) noexcept;
  template <EnumType T> static void fire(T t) noexcept;
  _Events_();
  ~_Events_();
};
} // namespace arc
