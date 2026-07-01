// Global.hpp
//  globally used namings and other stuff are placed here

#pragma once

#include <memory>
#pragma once

#include <chrono>
#include <format>
#include <iostream>
#include <source_location>
#include <string_view>

namespace tea {

// Shortcuts
template <typename T>
using uptr = std::unique_ptr<T>;

template <typename T>
using sptr = std::shared_ptr<T>;

template <typename T>
using wptr = std::weak_ptr<T>;

// Logging
static inline void Info(const char* msg) {
  std::cout << msg << std::endl;
}
static inline void InfoN(const char* msg) {
  std::cout << msg;
}
static inline void Info(std::string msg) {
  std::cout << msg << std::endl;
}
static inline void InfoN(std::string msg) {
  std::cout << msg;
}
template <typename... Args>
void Info(Args&&... args) {
  ((std::cout << std::forward<Args>(args)), ...);
}

// Debug
inline auto DEBUG_LAST = std::chrono::steady_clock::now();

inline void DebugLog(
    const std::string& msg, const char* func,
    const std::source_location& loc = std::source_location::current()) {
  auto now = std::chrono::steady_clock::now();
  auto delta =
      std::chrono::duration_cast<std::chrono::microseconds>(now - DEBUG_LAST);
  DEBUG_LAST = now;

  // crop to ./src/
  std::string_view file = loc.file_name();
  auto pos = file.find("src/");
  if (pos != std::string_view::npos) {
    file = file.substr(pos);
  }

  std::cout << std::format("[{:.3f}ms] ({}:{}::{})  {}\n",
                           delta.count() / 1000.0, file, loc.line(), func, msg);
}

}  // namespace tea

#ifdef NDEBUG
#define DEBUG(msg, ...) ((void)0)
#else
#define DEBUG(msg, ...) tea::DebugLog(std::format(msg, ##__VA_ARGS__), __func__)
#endif