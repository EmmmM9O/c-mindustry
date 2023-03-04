
#include <iostream>
#include "./tools/PingHost.cpp"
#include "./arc/util/Log.cpp"
using namespace tools;
using namespace std;
using namespace arc::util;

int main(){
	Log::info("Log Test ${} ${} ",1,"test");
	cout<<pingHost(10404,"n2.akiracloud.net").toString();
	
	cout<<"close\n";
	return 0;
}
