# LumosLog

基于C++20开发，适合集成的日志处理。

方便本地调用和集成统一，本地调试可以用默认的标准输出，也可以用适配器模块接入自己喜欢的日志库。

业务模块不需要考虑日志层面，通过引入库来接入日志系统，集成时方便换成工程更统一的日志库。

- [x] 仅头文件，轻松引入，不会给项目增加额外依赖。
- [x] 不依赖具体的日志库，你可以选择你正在用的来接入，方便从集成侧统一日志库。
- [x] 默认采用cout输出，适合本地调试。
- [x] 线程安全
- [x] 灵活扩展，你可以改成自己想要的日志输出结构。

## how to build

~~~
conan install . --build=missing -s build_type=Release -s compiler.cppstd=20 --output-folder=build
~~~

~~~
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=build/build/Release/generators/conan_toolchain.cmake

make
~~~

## how to use

~~~c++
// example/demo.cpp

#include "DummyAdapter.hpp"

class DummyModule {
 public:
  void process(int value) {
    LumosLog::log(LumosLog::LogLevel::INFO, "DummyModule", "Processing value: {}", value);
  }
};

int main() {
  DummyModule bm;

  // default
  bm.process(114514);

  /* NOT NECESSARY 
   * it could be used in your example.
   * initLumosLog() will be defined in the module to be integrated. */
  initLumosLog();
  
  // use spdlog instead
  bm.process(1919810);

  return 0;
}
~~~