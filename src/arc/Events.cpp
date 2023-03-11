#include "./Events.hpp"

template <EnumType T, T V> std::string arc::_Events_::getHash() {
  return __PRETTY_FUNCTION__;
}
template <EnumType T, Runnable R> void arc::_Events_::on(T t, R func) {
  events[getHash<T, t>()].push_front((void (*)())func);
}
template <EventType T, Cons<T> R> void arc::_Events_::on(R func) {
  events[typeid(T).name()].push_front((void (*)(T))func);
}
template <EventType T, Runnable R> void arc::_Events_::run(R func) {
  events[typeid(T).name()].push_front(
      (void (*)(T))[&func](T _)->void { func(); });
}
template <typename T> void arc::_Events_::fire(T packet) noexcept {
  auto list = events[typeid(T).name()];
  for (auto i = list.begin(); i != list.end(); i++) {
    try {
      boost::any_cast<void (*)(T)> (*i)(packet);
    } catch (boost::bad_any_cast &e) {
      std::cerr << e.what() << '\n';
    }
  }
}
template <EnumType T> void arc::_Events_::fire(T t) noexcept {
  auto list = events[getHash<T, t>()];
  for (auto i = list.begin(); i != list.end(); i++) {
    try {
      boost::any_cast<void (*)()> (*i)();
    } catch (boost::bad_any_cast &e) {
      std::cerr << e.what() << '\n';
    }
  }
}
arc::_Events_::_Events_() {
  events = std::map<std::string, std::forward_list<boost::any>>();
}
arc::_Events_::~_Events_() { events.clear(); }
std::map<std::string, std::forward_list<boost::any>> arc::_Events_::events;
