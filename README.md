# LumosLog

基于C++20开发，适合于集成的日志处理器。

## Introduction

**LumosLog** 是一个轻量级、纯头文件的日志 SDK，设计理念是简洁、灵活、无侵入。采用 **Service Locator（服务定位器）模式**，为 C++ 项目中的所有模块提供统一且极简的日志接口，同时避免对具体日志库的强依赖。

### ✨ 核心特性

- **Header-only，零依赖**  
  业务模块无需链接任何日志库，只需 `#include` LumosLog 头文件即可正常输出日志。

- **可插拔日志实现**  
  支持在运行时注册外部日志库（如 `spdlog`、`glog` 或文件日志），也可以自定义实现。

- **默认 Fallback 行为**  
  未注册日志实现时，自动回退到 `std::cout` 输出，保持最基础的日志能力。

- **线程安全设计**  
  内部使用 mutex 保护，配合 C++11 静态局部变量的线程安全初始化。

- **灵活可扩展**  
  支持扩展，如 TraceId、Context 信息、结构化日志等功能。

### 🧠 设计理念

> **“让业务模块与日志实现解耦。”**

LumosLog 尽可能将日志逻辑从业务模块中剥离出来，模块无需关心底层日志库是 `spdlog`、`glog`，还是简单终端输出，只需通过 LumosLog 提供的接口调用日志功能。  
这保证了业务代码的 **干净、稳定、一致**，而具体日志实现可以根据环境灵活切换，不侵入模块内部。

---

**LumosLog** is a lightweight, header-only logging SDK designed with simplicity, flexibility, and zero-coupling in mind. It follows the **Service Locator Pattern**, offering a unified and minimalistic logging interface for all modules in a C++ project, without binding them to any specific logging library.

### ✨ Key Features

- **Header-only, Zero Dependency**  
  Business modules can simply `#include` LumosLog headers. No need to link external logging libraries unless desired.

- **Pluggable Logging Backend**  
  Supports dynamic registration of external loggers like `spdlog`, `glog`, file loggers, or any custom implementation via a runtime callback.

- **Fallback Console Output**  
  If no logger is registered, LumosLog defaults to printing logs to `std::cout`, ensuring graceful behavior without dependency.

- **Thread-Safe by Design**  
  Internally protected by mutex and utilizing C++11 thread-safe static initialization.

- **Extensible & Future-Proof**  
  Easily extensible to support trace IDs, context information, or advanced structured logging in the future.

### 🧠 Design Philosophy

> **“Decouple business logic from logging implementation.”**

LumosLog aims to **abstract away logging concerns** from your core modules. By providing a globally accessible, pluggable service interface, modules can log important information without knowing—or caring—what backend is used. Whether you integrate a sophisticated logger in production, or leave it to simple console output during development, the module code stays clean, consistent, and free from intrusive macros or boilerplate.

## How to build

~~~
conan install . --build=missing -s build_type=Release -s compiler.cppstd=20 --output-folder=build
~~~

~~~
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=build/build/Release/generators/conan_toolchain.cmake

make
~~~

## example

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