#include "./Packet.cpp"
#include <cstddef>
#include <string>
#include <sys/wait.h>
#include <vector>
#include "../../arc/util/io/Writes.cpp"
#include "../../arc/util/io/Reads.cpp"
#include "../../java/object.cpp"
#include <queue>
#include "../io/TypeIO.cpp"
namespace mindustry{
    namespace net{
        namespace Packets{
            class _KickReason_:java::Object{
                public:
                bool quiet;
                std::string name;
                _KickReason_(std::string n){
                    quiet=false;name=n;
                }
                _KickReason_(std::string n,bool q){
                    quiet=q;name=n;
                }
                virtual std::string toStirng(){
                    return "server.kicked"+name;
                }
            };
            namespace KickReason {
                _KickReason_ kick("kick"), clientOutdated("clientOutDated"), serverOutdated("serverOutdated"), 
                banned("banned"), gameover("gameover",true), recentKick("recentKick"),
                        nameInUse("nameInUse"), idInUse("idInUse"), nameEmpty("nameEmpty"),
                         customClient("customClinet"), serverClose("serverClose"), vote("vote"), typeMismatch("typeMismatch"),
                                whitelist("whitelist"), playerLimit("playerLimit"), serverRestarting("serverRestarting");
            }
            enum class AdminAction{
                kick, ban, trace, wave
            };
            class Connect:mindustry::net::Packet{
                public: 
                std::string addressTCP;
                virtual int getPriority() override{
                    return priorityHigh;
                }
            };
            class Disconnect:mindustry::net::Packet{
                public:
                std::string reason;
                virtual int getPriority() override{
                    return priorityHigh;
                }
            };
            class WorldStream:mindustry::net::Packet{

            };
            class StreamBegin:mindustry::net::Packet{
                private:
                static int lastid;
                public:
                int id;
                int total;
                byte type;
                virtual void write(arc::util::io::Writes &write) override{
                    write.i(id);
                    write.i(total);
                    write.b(type);
                }
                virtual void read(arc::util::io::Reads &reads) override{
                    id=reads.i();
                    total=reads.i();
                    type=reads.b();
                }
                StreamBegin(){
                    id=lastid++;
                }
            };
            class StreamChunk :mindustry::net::Packet{
                public:
                int id;
                std::vector<byte> data;
                virtual void write(arc::util::io::Writes &writes) override{
                    writes.i(id);
                    writes.s((short)data.size());
                    writes.b(data.data());
                }
                virtual void read(arc::util::io::Reads &reads) override{
                    id=reads.i();
                    data=reads.b(reads.s());
                }
            };
            class ConnectPacket:mindustry::net::Packet{
                public:
                int version;
                std::string versionType;
                std::queue<std::string> mods;
                std::string name, locale, uuid, usid;
                int color;
                bool mobile;
                virtual void write(arc::util::io::Writes &writes) override{
                    writes.i(version);
                    mindustry::io::TypeIO::writeString(writes, versionType);
                    mindustry::io::TypeIO::writeString(writes, name);
                    mindustry::io::TypeIO::writeString(writes, locale);
                    mindustry::io::TypeIO::writeString(writes, usid);
                    //TODD 
                    // base64
                }
                virtual void read(arc::util::io::Reads &buffer) override{
                    version=buffer.i();
                    versionType=mindustry::io::TypeIO::readString(buffer);
                    name=mindustry::io::TypeIO::readString(buffer);
                    locale=mindustry::io::TypeIO::readString(buffer);
                    usid=mindustry::io::TypeIO::readString(buffer);
                    //TODD
                }

            };

        }
    }
}