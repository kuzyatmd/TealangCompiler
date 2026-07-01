// trace/StackTrace.cpp
#include "trace/StackTrace.hpp"

// #include <algorithm>
// #include <iostream>

namespace tea {

void StackTrace::AddError(Trigger trigger) {
  errors_.push_back(std::move(trigger));
}

void StackTrace::AddWarning(Trigger trigger) {
  warnings_.push_back(std::move(trigger));
}

void StackTrace::AddInfo(Trigger trigger) {
  infos_.push_back(std::move(trigger));
}

bool StackTrace::HasErrors() const {
  return !errors_.empty();
}

bool StackTrace::HasWarnings() const {
  return !warnings_.empty();
}

bool StackTrace::HasInfos() const {
  return !infos_.empty();
}

bool StackTrace::IsEmpty() const {
  return errors_.empty() && warnings_.empty() && infos_.empty();
}

int StackTrace::GetErrorCode() const {
  if (HasErrors()) {
    // TODO:
    // Combine all errors and warnings in single value with mask
    return -1;
  }
  return 0;
}

void StackTrace::Clear() {
  errors_.clear();
  warnings_.clear();
  infos_.clear();
}

const std::vector<Trigger>& StackTrace::GetErrors() const {
  return errors_;
}

const std::vector<Trigger>& StackTrace::GetWarnings() const {
  return warnings_;
}

const std::vector<Trigger>& StackTrace::GetInfos() const {
  return infos_;
}

std::string StackTrace::ToString() const {
  std::string result;

  if (HasErrors()) {
    result += "Errors:\n";
    for (const auto& error : errors_) {
      result += "  " + error.GetDescription() + "\n";
    }
  }
  if (HasWarnings()) {
    result += "Warnings:\n";
    for (const auto& warning : warnings_) {
      result += "  " + warning.GetDescription() + "\n";
    }
  }
  if (HasInfos()) {
    result += "Info:\n";
    for (const auto& info : infos_) {
      result += "  " + info.GetDescription() + "\n";
    }
  }

  return result.empty() ? "No triggers found." : result;
}

}  // namespace tea