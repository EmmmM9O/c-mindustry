#include "./files/Fi.cpp"
namespace arc{
    class ApplicationListener{
        public:
        virtual void init(),exit(),
        fileDropped(files::Fi file),dispose(),
        pause(),update(),
        resize(int w,int h),resume();
    };
}
using namespace arc;
void ApplicationListener::dispose(){}
void ApplicationListener::init(){}
void ApplicationListener::exit(){}
void ApplicationListener::fileDropped(files::Fi fi){}
void ApplicationListener::pause(){}
void ApplicationListener::update(){}
void ApplicationListener::resume(){}
void ApplicationListener::resize(int w, int h){}



