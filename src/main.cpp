
#include <iostream>
#include "./tools/PingHost.cpp"
using namespace tools;
using namespace std;
typedef unsigned char byte;

int main(){
	cout<<"ping\n";
	cout<<pingHost(10404,"n2.akiracloud.net").toString();
	
	cout<<"close\n";
	return 0;
}
