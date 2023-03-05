#pragma once

#include <exception>
#include <functional>
namespace arc{
    namespace net{
        class ArcNet{
            public:
            static std::function<void (std::exception)> errorHandler;
            static void handleError(std::exception err){
                errorHandler(err);
            }
        };
    }
}
std::function<void (std::exception)> 
arc::net::ArcNet::errorHandler
=[](std::exception err)->void{

};