#pragma once
#include <cstdarg>
#include <format>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>

namespace LumosLog {

// 日志等级
enum class LogLevel {
  TRACE,
  DEBUG,
  INFO,
  WARN,
  ERROR,
  FATAL
};

// 日志回调
using LogCallback = std::function<void(LogLevel, const std::string& module_name, const std::string& message)>;

static LogCallback logger = nullptr;
static std::mutex logger_mutex;

void setLogger(LogCallback cb) {
  std::lock_guard<std::mutex> lock(logger_mutex);
  logger = cb;
}

LogCallback getLogger() {
  std::lock_guard<std::mutex> lock(logger_mutex);
  return logger;
}

template <typename... Args>
inline void log(LogLevel level, const std::string& module_name, const std::string& fmt, Args&&... args) {
  auto logger = getLogger();
  std::string message = std::vformat(fmt, std::make_format_args(args...));
  if (logger) {
    logger(level, module_name, message);
  } else {
    std::cout << "[" << module_name << "] " << message << std::endl;
  }
}

}  // namespace LumosLog
