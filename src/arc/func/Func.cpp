#include <type_traits>
#include <iostream>
template<typename T,typename T1>
concept Func= requires(T t,T1 t1){
    {t(t1)} -> std::same_as<void>;
};
template<typename T>
concept Runnable=requires(T t){
    {t()} -> std::same_as<void>;
};