#include <type_traits>
template<typename T,typename T1>
concept Func= requires(T t,T1 t1){
    t(t1);
};
template<typename T>
concept Runnable=requires(T t){
    t();
};