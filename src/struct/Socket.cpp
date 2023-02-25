#include <algorithm>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <future>
#include <unistd.h>
#include <vector>
#include "../arc/Events.cpp"
namespace Struct{
    
    enum class domain{
        IPV6=AF_INET6,IPV4=AF_INET
    };
    enum class type {
        TCP=SOCK_STREAM,UDP=SOCK_DGRAM
    };
    class Socket{
        public:
        static const int BUFFER_SIZE=1024;
        int id;
        bool connectd=false;
        struct sockaddr_in servaddr;
        Socket(domain dom,type t,int protocol){
            id=socket((int)dom,(int)t,protocol);
            servaddr.sin_family=(int)dom;
        }
        void send(char arr[],int length){
            if(connectd){
                if(::send(id,arr,length,0)<0){
			std::cout<<"error send";
			exit(1);
		}
            }else{
                std::cout<<"还未连接";perror("no connect");exit(1);
            }
        }
        void send(std::string str){
            if(connectd){
                ::send(id,str.data(),str.length(),0);
            }else{
                std::cout<<"还未连接";
                perror("no connect");
                exit(1);
            }
        }
        void connect(int port,std::string host){
            if(!connectd){
                servaddr.sin_port = htons(port);
                inet_pton(servaddr.sin_family,host.data(),&servaddr.sin_addr);
                if(::connect(id, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
			std::cout<<"连接中出错";
                    perror("connect");
                    exit(1);
                }
                connectd=true;
            }else {
		    std::cout<<"连接过了";
                perror("connectd");
                exit(1);
            }
        }
        void close(){
            if(connectd){
                ::close(id);
            }else{
		    std::cout<<"还没连接";
                perror("no ocnnect");
                exit(1);
            }
        }
        std::future<std::string> data(){
            if(connectd){
                return std::async(std::launch::async
                ,[this]()->std::string{
                    char recvbuf[BUFFER_SIZE];
                    int len;
                    len = recv(this->id, recvbuf, sizeof(recvbuf),0);
                    if(len<0){
                        return "Error";
                    }
                    return recvbuf;
                });
            }else{
		    std::cout<<"还没连接";
                perror("no connect");
                exit(1);
            }
        }
    };
}
