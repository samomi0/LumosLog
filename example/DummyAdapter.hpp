#pragma once
#include "LumosLog.hpp"
#include <spdlog/spdlog.h>

void spdlogAdapter(LumosLog::LogLevel level, const std::string& module, const std::string& msg) {
  std::string logMsg = "[" + module + "] " + msg;
  switch (level) {
    case LumosLog::LogLevel::TRACE:
      spdlog::trace(logMsg);
      break;
    case LumosLog::LogLevel::DEBUG:
      spdlog::debug(logMsg);
      break;
    case LumosLog::LogLevel::INFO:
      spdlog::info(logMsg);
      break;
    case LumosLog::LogLevel::WARN:
      spdlog::warn(logMsg);
      break;
    case LumosLog::LogLevel::ERROR:
      spdlog::error(logMsg);
      break;
    case LumosLog::LogLevel::FATAL:
      spdlog::critical(logMsg);
      break;
  }
}

void initLumosLog() {
  spdlog::set_level(spdlog::level::trace);
  LumosLog::setLogger(spdlogAdapter);
}