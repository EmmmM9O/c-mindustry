
#include <iostream>
#include "mindustry/core/NetClient.cpp"
#include "./arc/util/Log.cpp"
#include "mindustry/gen/Packets.cpp"
#include "mindustry/gen/Call.cpp"

using namespace std;
using namespace arc::util;
using namespace mindustry::core;
using namespace mindustry;
using namespace mindustry::gen;
int main(){
	Log::info("Net Test!");
	Vars::net.connect("n2.akiracloud.net",10404,[]()->void{
		Log::info("Connect Succeed");
	});
	Call::registerPackets();
	Vars::net.handleClient<SendMessageCallPacket2>(
		[](SendMessageCallPacket2 p)->void{
			Log::info("Get A Message!\n${}",p.message);
		});
	Log::info("Wait");getchar();
	Vars::net.disconnect();
	Log::info("Close!");
	return 0;
}
