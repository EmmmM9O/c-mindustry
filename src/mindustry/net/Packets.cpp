#pragma once

#include "./Packets.hpp"
using namespace mindustry::net::Packets;
_KickReason_::_KickReason_(std::string n) {
  quiet = false;
  name = n;
}
_KickReason_::_KickReason_(std::string n, bool q) {
  quiet = q;
  name = n;
}
std::string _KickReason_::toStirng() { return "server.kicked" + name; }
namespace mindustry {
namespace net {
namespace Packets {
namespace KickReason {
_KickReason_ kick("kick"), clientOutdated("clientOutDated"),
    serverOutdated("serverOutdated"), banned("banned"),
    gameover("gameover", true), recentKick("recentKick"),
    nameInUse("nameInUse"), idInUse("idInUse"), nameEmpty("nameEmpty"),
    customClient("customClinet"), serverClose("serverClose"), vote("vote"),
    typeMismatch("typeMismatch"), whitelist("whitelist"),
    playerLimit("playerLimit"), serverRestarting("serverRestarting");
}
} // namespace Packets
} // namespace net
} // namespace mindustry
int Connect::getPriority() { return priorityHigh; }
int Disconnect::getPriority() { return priorityHigh; }

void StreamBegin::write(arc::util::io::Writes &write) {
  write.i(id);
  write.i(total);
  write.b(type);
}
void StreamBegin::read(arc::util::io::Reads &reads) {
  id = reads.i();
  total = reads.i();
  type = reads.b();
}
StreamBegin::StreamBegin() { id = lastid++; }

void StreamChunk::write(arc::util::io::Writes &writes) {
  writes.i(id);
  writes.s((short)data.size());
  writes.b(data.data());
}
void StreamChunk::read(arc::util::io::Reads &reads) {
  id = reads.i();
  data = reads.b(reads.s());
}

void ConnectPacket::write(arc::util::io::Writes &writes) {
  writes.i(version);
  mindustry::io::TypeIO::writeString(writes, versionType);
  mindustry::io::TypeIO::writeString(writes, name);
  mindustry::io::TypeIO::writeString(writes, locale);
  mindustry::io::TypeIO::writeString(writes, usid);
  // TODD
  //  base64
}
void ConnectPacket::read(arc::util::io::Reads &buffer) {
  version = buffer.i();
  versionType = mindustry::io::TypeIO::readString(buffer);
  name = mindustry::io::TypeIO::readString(buffer);
  locale = mindustry::io::TypeIO::readString(buffer);
  usid = mindustry::io::TypeIO::readString(buffer);
  // TODD
}
int mindustry::net::Packets::StreamBegin::lastid = 0;