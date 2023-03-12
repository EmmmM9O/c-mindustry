
#include <boost/any.hpp>
#include <ostream>
#include <string>
#include <string_view>
#include <type_traits>
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
};
} // namespace java
