# C-Mindustry

### 第三方服务器端

>[English](https://github.com/EmmmM9O/c-mindustry/blob/main/README.md)

> 还在制作

* ### build

   克隆`clone`然后编辑 `CMakeLists.txt`

   把 `CMAKE_CXX_COMPILER`

  改为你的clang的绝对路径

   环境:c++20 boost 和 cmake

* ### Demo

```c

//获取服务器信息

#include <iostream>

#include "./tools/PingHost.cpp"

#include "./arc/util/Log.cpp"

using namespace tools;

using namespace arc::util;

int main(){

	Log::info("Ping Host ${} : ${} ","n2.akiracloud.net",10404,pingHost(10404,"n2.akiracloud.net").toString());

	return 0;

}

```
