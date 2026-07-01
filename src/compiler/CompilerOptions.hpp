// compiler/CompilerOptions.hpp
#pragma once

#include <string_view>
#include <vector>

namespace tea {

class CompilerOptions {
 private:
  int argc;
  char** raw_args;

 public:
  char* workpath;
  bool show_help = false;
  bool show_version = false;
  std::vector<std::string_view> input_files;

 public:
  CompilerOptions(int argc, char** raw_args);

  ~CompilerOptions();

  void PrintAllRaw() const;
  void PrintAll() const;

  void PrintHelp() const;
  void PrintVersion();

  void Init();
};

}  // namespace tea