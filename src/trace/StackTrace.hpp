// trace/StackTrace.hpp
#pragma once

#include <string>
#include <vector>

#include "trace/Trigger.hpp"

namespace tea {

class StackTrace {
 private:
  std::vector<Trigger> errors_;
  std::vector<Trigger> warnings_;
  std::vector<Trigger> infos_;

 public:
  StackTrace() = default;

  void AddError(Trigger trigger);
  void AddWarning(Trigger trigger);
  void AddInfo(Trigger trigger);

  bool HasErrors() const;
  bool HasWarnings() const;
  bool HasInfos() const;

  bool IsEmpty() const;

  int GetErrorCode() const;

  void Clear();

  const std::vector<Trigger>& GetErrors() const;
  const std::vector<Trigger>& GetWarnings() const;
  const std::vector<Trigger>& GetInfos() const;

  std::string ToString() const;
};

}  // namespace tea