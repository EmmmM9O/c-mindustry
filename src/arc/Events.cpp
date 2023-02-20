#include <functional>
#include <iostream>
#include <forward_list>
#include <boost/any.hpp>
#include <string>
#include <system_error>
#include <type_traits>
#include "func/Func.cpp"
template<typename T>
concept EventType= requires(T t){
    t.Class;
};

template<typename T>
concept EnumType=std::is_enum<T>();

namespace arc{
    class _EventType_{

    };
    class Events{
        public:
        static std::map<std::string,std::forward_list<boost::any>> events;
        template<EnumType T,Runnable R>
        static void on(T t,R func){
            events[std::to_string((int)t)].push_front((void(*)())func);
        }
        template<EventType T,Func<T> R>
        static void on(T _,R func){
            events[typeid(T).name()].push_front((void(*)(T))func);
        }
        template<EventType T,Runnable R>
        static void run(T _,R func){
            events[typeid(T).name()].push_front((void(*)(T))[&func](T _)->void{
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
        template<EnumType T>
        static void fire(T t){
            auto list=events[std::to_string((int)t)];
            for(auto i=list.begin();i!=list.end();i++){
                try{
                    boost::any_cast<void(*)()>(*i)();
                }catch(boost::bad_any_cast &e){
                    std::cerr<<e.what()<<'\n';
                }
            }
        }
        ~Events(){
            events.clear();
        }
    };
}
/*
extern std::map<std::string,std::forward_list<boost::any>> arc::Events::events
=std::map<std::string,std::forward_list<boost::any>>();*/
