// trace/Error.hpp
//  Compiler-sent Errors/Warnings/Info

#pragma once

#include <string>

#include "trace/TriggerType.hpp"

namespace tea {

class Trigger {
 public:
  TriggerType type;
  const char* file;
  int line;
  int length;

  Trigger(TriggerType type, const char* file, int line, int length);
  std::string GetDescription() const;
};

}  // namespace tea