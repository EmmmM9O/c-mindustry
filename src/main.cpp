
#include <iostream>
#include <vector>
#include <string>
#include <sys/socket.h>
#include "struct/Socket.cpp"

using namespace std;
using namespace Struct;

int main(){
	unique_ptr<Socket> c(new Socket(domain::IPV4,type::UDP,0));
	c->connect(10404,"n2.akiracloud.net");
	short s[]={-2,1};
	send(c->id,s,sizeof(s),0);
	while(true){
		auto f=c->data();
		cout<<"wait...\n";
		f.wait();
		auto s=f.get();
		if(s=="Error"){
			cout<<"Error\n";
			break;
		}
		cout<<s<<"\n";
	}
	cout<<"close\n";
	c->close();
	return 0;
}
