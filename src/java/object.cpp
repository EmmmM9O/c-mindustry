
#pragma once
#include "./object.hpp"
#include <boost/any.hpp>
#include <cstdio>
#include <ostream>
#include <type_traits>
std::string java::Object::toString() { return "[object][object]"; }
std::ostream &operator<<(std::ostream &out, java::Object &obj) {
  out << obj.toString();
  return out;
}
template <typename Father>
template <typename T>
T java::AnyObject<Father>::cast() noexcept(std::is_base_of<Father, T>::value) {
  try {
    return boost::any_cast<T>(DataAny);
  } catch (boost::bad_any_cast &e) {
    throw e;
  }
}
template <typename Father>
template <typename T>
bool java::AnyObject<Father>::is() {
  return DataAny->type().hash_code() == typeid(Father).hash_code();
}
template <typename Father> bool java::AnyObject<Father>::empty() {
  return DataObject == nullptr || DataAny->empty();
}
template <typename Father>
template <AnyType<Father> T>
java::AnyObject<Father>::AnyObject(T *t) {
  DataObject = t;
  DataAny = t;
}
template <typename Father> java::AnyObject<Father>::AnyObject() {
  DataObject = nullptr;
  DataAny = nullptr;
}