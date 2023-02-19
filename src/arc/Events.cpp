#include <iostream>
#include <forward_list>
#include <boost/any.hpp>
#include <string>
#include <system_error>
#include "func/Func.cpp"
template<typename T>
concept EventType= requires(T t){
    t.Class;
};
namespace arc{
    class _EventType_{

    };
    class Events{
        public:
        static std::map<std::string,std::forward_list<boost::any>> events;
        template<typename T,Func<T> F>
        static void on(T _,F func){
            events[typeid(T).name()].push_front(func);
        }
        template<typename T,Runnable R>
        static void run(T _,R func){
            events[typeid(T).name()].push_front([&func]()->void{
                func();
            });
        }
        template<typename T>
        static void fire(T _,T packet){
            auto list=events[typeid(T).name()];
            for(auto i=list.begin();i!=list.end();i++){
                try{
                    boost::any_cast<void(*)(T)>(*i)(packet);
                }catch(boost::bad_any_cast &e){
                    std::cerr<<e.what()<<'\n';
                }
            }
        }
        template<EventType T>
        static void fire(T packet){
            fire(packet.Class,packet);
        }
    };
}
/*
extern std::map<std::string,std::forward_list<boost::any>> arc::Events::events
=std::map<std::string,std::forward_list<boost::any>>();*/
