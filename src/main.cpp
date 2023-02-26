
#include <future>
#include <iostream>
#include <netinet/in.h>
#include <vector>
#include <string>
#include <sys/socket.h>
#include "struct/Socket.cpp"
#include <netdb.h>
#include "java/io/DataInput.cpp"
#include "java/io/DataOutput.cpp"
using namespace java::io;
using namespace std;
using namespace Struct;
typedef unsigned char byte;

int main(){
	unique_ptr<Socket> c(new Socket(domain::IPV4,type::UDP,0));
	//c->connect(7678,"127.0.0.1");

	auto a=gethostbyname("n2.akiracloud.net");
	if(a==NULL){
		cout<<"no path";
		exit(1);
	}
	string ip="";
	for(int i=0;a->h_addr_list[i];i++){
		ip=inet_ntoa(*(struct in_addr*)a->h_addr_list[i]);
		cout<<ip<<endl;
	}
	c->connect(10404,ip);
	unsigned char buf[2] = {static_cast<unsigned char>(-2), 1};
	cout<<"send\n";
	c->send(buf,2);
	cout<<"wait...\n";
	auto data=c->dataSync();
	DataInput in;
	for(auto i:data){
		in.byteStream.push_back(
			static_cast<unsigned char>(i)		
		);
	}
	/*auto read=[](basic_string<char> d,DataInput &in)->void{
	for(int i=0;i<d.length();i++){
		auto c=d[i];
		in.byteStream.push_back(
			static_cast<unsigned char>(c)
		);cout<<static_cast<unsigned char>(c);
	}
	};*/

	/*
	cout<<"wait2...\n";
	f=c->data();f.wait();read(f.get(),in);
	*/
	cout<<"\nRead!\n";
	cout<<in.Read2String()
	<<std::endl<<in.Read2String()
	<<std::endl<<"Player:"<<in.ReadInt()<<" Wave:"
	<<in.ReadInt()<<"\nversion:"<<in.ReadInt()
	<<" versiontype:"<<in.Read2String()<<endl;
	//<<"\n"<<in.ReadInt()<<" and "<<in.ReadInt()<<"\n v:"
	//<<in.ReadInt()<<"//version//"<<in.ReadString();
	cout<<"close\n";
	c->close();
	return 0;
}
