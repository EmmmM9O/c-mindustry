#include <boost/any.hpp>
#include <string>
#include <typeinfo>
#include <vector>
#include "./AssetDescriptor.cpp"
namespace arc{
    namespace assets{
        class Loadable{
            public:
            virtual void loadAsync(){
                
            }
            virtual void loadSync(){

            }
            virtual std::string getName(){
                return typeid(typeof this).name();
            }
            virtual std::vector<boost::any> getDependencies(){
                return std::vector<boost::any>();
            };

        };
    }
}