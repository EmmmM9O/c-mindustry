# C-Mindustry
### Third party Server Side
>[中文版](https://github.com/EmmmM9O/c-mindustry/cn-README.md)
> Still in production
* ### build
   clone and edit `CMakeLists.txt`
   change `CMAKE_CXX_COMPILER`
   into where your clang is.

   build with c++20 cmake and boost
* ### Demo
```c
//Ping Host
#include <iostream>
#include "./tools/PingHost.cpp"
#include "./arc/util/Log.cpp"
using namespace tools;
using namespace arc::util;
int main(){
	Log::info("Ping Host ${} : ${} ","n2.akiracloud.net"
,10404,pingHost(10404,"n2.akiracloud.net").toString());
	return 0;
}
```
