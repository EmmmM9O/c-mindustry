#pragma once

#include <boost/any.hpp>
#include <ostream>
#include <string>
#include <string_view>
#include <type_traits>
template <typename T, typename T1>
concept AnyType = std::is_base_of<T1, T>()
| std::is_same_v<T, T1>;
namespace java {
class Object {
public:
  virtual std::string toString();
  friend std::ostream &operator<<(std::ostream &out, Object &obj);
};
template <typename Father> class AnyObject : public Object {
public:
  Father *DataObject;
  boost::any *DataAny;
  template <typename T> T cast() noexcept(std::is_base_of<Father, T>::value);
  template <typename T> bool is();
  template <AnyType<Father> T> AnyObject(T *t);
  bool empty();
  AnyObject();
};
template <typename T1, typename T2> class AnyTwo : public Object {
public:
  T1 *first;
  T2 *second;
  short key = -1;
  AnyTwo(T1 *f) {
    first = f;
    key = 1;
  }
  AnyTwo(T2 *s) {
    second = s;
    key = 2;
  }
  AnyTwo() { key = -1; }
};
} // namespace java
