#pragma once
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <future>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <regex>
#include "../arc/Events.cpp"
#include <netdb.h>


namespace Struct{
    class HostErr:public std::exception{
        const char * what() const throw(){
            return "Cann't get ip by the host:";
        }
    };
    /*
    class TimeOut :public std::exception{
        const char * what() const throw(){
            return "Socket Time Out!";
        }
    };*/
    enum class domain{
        IPV6=AF_INET6,IPV4=AF_INET
    };
    enum class type {
        TCP=SOCK_STREAM,UDP=SOCK_DGRAM
    };
    class Socket{
        public:
        static const std::regex IPV4R;
        static const int BUFFER_SIZE=1024;
        int id;
        bool connectd=false;
        struct sockaddr_in servaddr;
        std::string getIpByHost(std::string str){
            auto a=gethostbyname(str.data());
            if(a==NULL){
                throw HostErr();
            }else{
                std::string ip="";
                for(int i=0;a->h_addr_list[i];i++){
                    ip=inet_ntoa(*(struct in_addr*)a->h_addr_list[i]);
                }
                return ip;
            }
        }
        Socket(domain dom,type t,int protocol){
            id=socket((int)dom,(int)t,protocol);
            servaddr.sin_family=(int)dom;
        }
        template<typename T>
        void send(T arr,int length){
            if(connectd){
                int len;
                len=sendto(id, arr, length
                , 0,(struct sockaddr*)&servaddr,sizeof(struct sockaddr));
                if(len<0){
                    std::cout<<"发送出错";
                    perror("sendto");
                    exit(1);
                }
            }else{
                std::cout<<"还未连接";perror("no connect");exit(1);
            }
        }
        void send(std::string str){
            if(connectd){
                int len;
                len=sendto(id, str.data(), str.length()
                , 0,(struct sockaddr*)&servaddr,sizeof(struct sockaddr));
                if(len<0){
                    std::cout<<"发送出错";
                    perror("sendto");
                    exit(1);
                }
            }else{
                std::cout<<"还未连接";
                perror("no connect");
                exit(1);
            }
        }
        void connect(int port,std::string host){
            if(!connectd){
                std::smatch s;
                if(!std::regex_match(host,s,IPV4R)){
                    try{
                        host=getIpByHost(host);
                    }catch(HostErr &e){
                        throw e;
                    }
                }
                servaddr.sin_port = htons(port);
                inet_pton(servaddr.sin_family,host.data(),&servaddr.sin_addr);
		bzero(&(servaddr.sin_zero),8);
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
        
        std::vector<char> dataSync(){
            if(connectd){
                char recvbuf[BUFFER_SIZE];
                    socklen_t len = sizeof(struct sockaddr);int lent;
                    lent=recvfrom(id,recvbuf,BUFFER_SIZE,0
                    ,(struct sockaddr*)&servaddr,&len);
		    
                    if(lent<0){
                        perror("recvto");
                        exit(1);
                    }
                    return std::vector<char>(recvbuf,recvbuf+lent);
            }else{
                std::cout<<"还未连接";perror("no connect");exit(1);
            }
        }
        std::future<std::vector<char>> data(){
            if(connectd){
                return std::async(std::launch::async
                ,[this]()->std::vector<char>{
                    char recvbuf[BUFFER_SIZE];
                    socklen_t len = sizeof(struct sockaddr);int lent;
                   // recvfrom(int fd, void *__restrict buf, size_t n, int flags, struct sockaddr *__restrict addr, socklen_t *__restrict addr_len)
                    lent=recvfrom(this->id,recvbuf,BUFFER_SIZE,0
                    ,(struct sockaddr*)&this->servaddr,&len);
                    //len = recv(this->id, recvbuf, sizeof(recvbuf),0);
                    if(lent<0){
                        perror("recv");
                        exit(1);
                        
                    }
                    return std::vector<char>(recvbuf,recvbuf+lent);
                });
            }else{
		    std::cout<<"还没连接";
                perror("no connect");
                exit(1);
            }
        }
    };
}
const std::regex Struct::Socket::IPV4R = 
std::regex("((25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\\.){3}(25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))");
