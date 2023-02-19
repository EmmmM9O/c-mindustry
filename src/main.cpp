#include <iostream>
#include <variant>
#include "arc/Events.cpp"
using namespace std;
class testClass{
	public:
	string msg;
	testClass(string m){
		msg=m;
	}
	static testClass Class;
};
testClass testClass::Class=testClass("none");
std::map<std::string,std::forward_list<boost::any>> 
arc::Events::events=std::map<std::string,std::forward_list<boost::any>>();

int main(){
	cout<<"eventTest"<<endl;
	arc::Events::on(testClass::Class,
	[](auto event)->void{
		cout<<"Test:"<<event.msg<<endl;
	});
	arc::Events::fire(testClass::Class
	,testClass("this is a test"));
	return 0;
}
