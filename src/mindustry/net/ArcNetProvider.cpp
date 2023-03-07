#pragma once
#include "./Net.cpp"
#include "../../arc/net/Client.cpp"
#include "../../arc/net/ArcNet.cpp"
#include "../../arc/net/NetSerializer.cpp"
#include "../../arc/net/FrameworkMessage.cpp"
#include "../../arc/util/Log.cpp"
#include "../../arc/util/io/Reads.cpp"
#include "../../arc/util/io/Writes.cpp"

#include "../Vars.cpp"
#include <boost/any.hpp>
#include <exception>
#include <unistd.h>
#include "./Packets.cpp"
#include "Packet.cpp"
using namespace arc::net;
using namespace arc::util;
using namespace arc::util::io;
using namespace java::io;
namespace mindustry{
    
    namespace net{
        class _NetListener_:public NetListener{
            public:
            virtual void connected(Connection *connection) override;
            virtual void received(Connection *con, boost::any obj) override;
        };
        class PacketSerializer:public NetSerializer{
            private:
            java::nio::ByteBuffer temp;
            bool debug=false;
            public:
            virtual boost::any read(java::nio::ByteBuffer &buffer) override;
            arc::net::FrameworkMessage::_FrameworkMessage_ 
            readFramework(java::nio::ByteBuffer &buffer) ;
            virtual void write(java::nio::ByteBuffer &buffer, boost::any obj) override;
            void writeFramework(ByteBuffer &buffer,boost::any obj);
        };
        
        class ArcNetProvider:public NetProvider{
            public:
            Client client;
            ArcNetProvider();
            virtual void connectClient(std::string ip, int port, void (*success)()) override{
                client.close();
                client.connect(port, ip, 5);
                success();
            }
            virtual void disconnectClient() override{
                client.close();
            }
            virtual void sendClient(boost::any object, bool reliable) override{
                if(reliable){
                    client.sendTCP(object);
                }else{
                    client.sendUDP(object);
                }
            } 
        };
    }
    namespace Vars{
        mindustry::net::Net net=mindustry::net::Net(ArcNetProvider());
    }
}
mindustry::net::ArcNetProvider::
ArcNetProvider():client(8192,8192,PacketSerializer()){
    ArcNet::errorHandler=[](std::exception err)->void{Log::debug(err.what());};
    client.addListener(_NetListener_());
}
void mindustry::net::_NetListener_::connected(Connection *connection){
    Connect c;c.addressTCP=connection->getIP();
    Vars::net.handleClientReceived(c);
}
void mindustry::net::_NetListener_
::received(Connection *con, boost::any obj){
    try{
        auto p=boost::any_cast<Packet>(obj);
        Vars::net.handleClientReceived(p);
    }catch(...){}
}
boost::any mindustry::net::PacketSerializer
::read(java::nio::ByteBuffer &buffer){
    if(debug){
        Log::debug(buffer._str());
    }
    byte id=buffer.ReadByte();
    if(id==static_cast<byte>(-2))
    return readFramework(buffer);
    else{
        auto packet=Net::newPacket<Packet>(id);
        int length=buffer.ReadShort()&0xffff;
        byte compression=buffer.ReadByte();
        temp.clear();
        if((int)compression==0){
            temp.position(0);
            temp.limit(length);
            temp.put(buffer.byteStream);
            temp.position(0);
            auto r=Reads(DataInput(buffer.byteStream));
            packet.read(r,length);
            temp.byteStream=r.input.byteStream;
            buffer.position(buffer.position()+temp.position());
        }else{
            int read=buffer.remaining();
            //LE wait
            throw "No Le4";
            temp.position(0);temp.limit(length);
            auto r=Reads(DataInput(buffer.byteStream));
            packet.read(r,length);
            buffer.position(read+buffer.position());
            
        }
        return packet;
    }
}

void mindustry::net::PacketSerializer
::write(ByteBuffer &byteBuffer, boost::any object){
    if(debug){
        int lastPos = byteBuffer.position();
    }
    if(object.type()==typeid(ByteBuffer)){
        byteBuffer.put(boost::any_cast<ByteBuffer>(object));
    }
    if(FrameworkMessage::isExtend(object)){
        byteBuffer.put(static_cast<byte>(-2));
        writeFramework(byteBuffer,object);
    }else{
    auto id=Net::getPacketId(object);
    if((int)id==-1) throw "Not Packet";
    byteBuffer.put(id);
    temp.position(0);
    auto pack= boost::any_cast<Packet>(object);
    auto w=Writes(temp.byteStream);pack.write(w);
    temp.byteStream=w.output.byteStream;
    auto length=(short)temp.position();
    byteBuffer.WriteShort(length);
    if(length<36||object.type().hash_code()
    ==typeid(StreamChunk).hash_code()){
        byteBuffer.put((byte)0);
        byteBuffer.put(temp.byteStream);
    }else{
        byteBuffer.put((byte)1);
        //LE4
        throw "No LE4";
    }
    }
}
void mindustry::net::PacketSerializer::writeFramework
(ByteBuffer &buffer, boost::any obj){
    if(obj.type().hash_code()==typeid(FrameworkMessage::Ping).hash_code()){
        auto p=boost::any_cast<FrameworkMessage::Ping>(obj);
        buffer.put((byte)0);
        buffer.WriteInt(p.id);
        buffer.put(p.isReply ? (byte)1 : (byte)0);
    }
    else if(obj.type().hash_code()
    ==typeid(FrameworkMessage::DiscoverHost).hash_code()){
        buffer.put((byte)1);
    }else if(obj.type().hash_code()==
    typeid(FrameworkMessage::KeepAlive).hash_code()){
        buffer.put((byte)2);
    }else if(obj.type().hash_code()==
    typeid(FrameworkMessage::RegisterUDP).hash_code()){
        auto p=boost::any_cast<FrameworkMessage::RegisterUDP>(obj);
        buffer.put((byte)3);
        buffer.WriteInt(p.connectionID);
    }else if(obj.type().hash_code()==
    typeid(FrameworkMessage::RegisterTCP).hash_code()){
        auto p=boost::any_cast<FrameworkMessage::RegisterTCP>(obj);
        buffer.put((byte)4);
        buffer.WriteInt(p.connectionID);
    }
}
FrameworkMessage::_FrameworkMessage_ mindustry::net::PacketSerializer::readFramework(java::nio::ByteBuffer &buffer){
    byte id=buffer.ReadByte();
    if(id==0){
        FrameworkMessage::Ping p;
        p.id=buffer.ReadInt();
        p.isReply = (int)buffer.ReadByte() == 1;
        return p;
    }if(id==1){
        return FrameworkMessage::discoverHost;
    }if(id==2){
        return FrameworkMessage::keepAlive;
    }if(id==3){
        FrameworkMessage::RegisterUDP p;
        p.connectionID=buffer.ReadInt();
        return p;
    }if(id==4){
        FrameworkMessage::RegisterTCP p;
        p.connectionID=buffer.ReadInt();
        return p;
    }
    throw "Unknown framework message!";
}