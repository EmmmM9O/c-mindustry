#pragma once

#include "../../java/nio/ByteBuffer.cpp"
#include <boost/any.hpp>
namespace arc {
namespace net {
class NetSerializer {
public:
  virtual void write(java::nio::ByteBuffer &buffer, boost::any);
  virtual boost::any read(java::nio::ByteBuffer &buffer);
  virtual int getLengthLength();
  virtual void writeLength(java::nio::ByteBuffer &buffer, int length);
  virtual int readLength(java::nio::ByteBuffer &buffer);
};
} // namespace net
} // namespace arc
