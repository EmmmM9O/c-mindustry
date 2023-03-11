#include "./files/Fi.cpp"
namespace arc {
class ApplicationListener {
public:
  virtual void init(), exit(), fileDropped(files::Fi file), dispose(), pause(),
      update(), resize(int w, int h), resume();
};
} // namespace arc
