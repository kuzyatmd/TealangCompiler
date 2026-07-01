// trace/Trigger.cpp
#include "trace/Trigger.hpp"

#include <string>
// #include <format>

#include "trace/TriggerType.hpp"

namespace tea {

Trigger::Trigger(TriggerType type, const char* file, int line, int length)
    : type(type), file(file), line(line), length(length) {};

std::string Trigger::GetDescription() const {
  switch (type) {
    case None:
      return "No error";
    case MyError:
      return "My test error";
    default:
      return "Unknown error. Report behaviour";
  }
}

}  // namespace tea