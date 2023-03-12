#pragma once

#include "../../java/nio/ByteBuffer.cpp"
#include "../../java/object.cpp"
#include "FrameworkMessage.cpp"
#include <boost/any.hpp>
namespace arc {
namespace net {
template <typename T> class NetSerializer {
public:
  virtual void
  write(java::nio::ByteBuffer &buffer,
        java::AnyTwo<java::AnyObject<T>,
                     java::AnyObject<FrameworkMessage::_FrameworkMessage_>>);
  virtual java::AnyTwo<java::AnyObject<T>,
                       java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
  read(java::nio::ByteBuffer &buffer);
  virtual int getLengthLength();
  virtual void writeLength(java::nio::ByteBuffer &buffer, int length);
  virtual int readLength(java::nio::ByteBuffer &buffer);
};
} // namespace net
} // namespace arc
