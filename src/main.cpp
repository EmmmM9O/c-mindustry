#include <iostream>
#include <string>
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
enum class Test2 {
	f=30001
};
int main(){
	cout<<"eventTest"<<endl;
	arc::Events::on(testClass::Class,
	[](auto event)->void{
		cout<<"Test:"<<event.msg<<endl;
	});
	arc::Events::fire(testClass::Class
	,testClass("this is a test"));
	arc::Events::on(Test2::f,[]()->void{
		cout<<"Test for enum"<<endl;
	});
	arc::Events::fire(Test2::f);
	return 0;
}
