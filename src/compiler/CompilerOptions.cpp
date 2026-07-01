// compiler/CompilerOptions.cpp
#include "compiler/CompilerOptions.hpp"

#include <cstring>

#include "Global.hpp"

namespace tea {

CompilerOptions::CompilerOptions(int argc, char** raw_args)
    : argc(argc), raw_args(raw_args) {
}

CompilerOptions::~CompilerOptions() = default;

void CompilerOptions::PrintAllRaw() const {
  Info("Args: [");
  for (int i = 0; i < argc; i++) {
    Info(" ", i, " ", raw_args[i], '\n');
  }
  Info("]\n");
}
void CompilerOptions::PrintAll() const {
  Info("argc = ", argc, '\n');
  Info("workpath = ", workpath, '\n');
  Info("help = ", show_help, '\n');
  Info("version = ", show_version, '\n');
  InfoN("input_files = [ ");
  for (auto file : input_files) {
    Info(file, " ");
  }
  Info("]");
}

void CompilerOptions::Init() {
  DEBUG("Init");

  workpath = raw_args[0];

  std::vector<std::string_view> tokens;
  int i = 1;
  // 1) Get Tokens
  {
    tokens.reserve(this->argc * 2);

    for (; i < this->argc; i++) {
      const char* str = this->raw_args[i];
      const char* start = str;

      // Check ' '
      bool has_space = false;
      const char* p = str;
      while (*p) {
        if (*p == ' ') {
          has_space = true;
          break;
        }
        p++;
      }

      if (has_space) {
        const char* token_start = str;
        const char* token_end = str;

        while (*token_end) {
          if (*token_end == ' ') {
            if (token_end != token_start) {
              tokens.emplace_back(token_start, token_end - token_start);
            }
            token_start = token_end + 1;
          }
          token_end++;
        }

        if (token_end != token_start) {
          tokens.emplace_back(token_start, token_end - token_start);
        }
      } else {
        tokens.emplace_back(str, strlen(str));
      }
    }
  }

  // 2) Analyze Tokens
  {
#define opts(ARG) if (token == ARG)
#define opt(ARG) else if (token == ARG)
    for (i = 0; i < tokens.size(); i++) {
      auto token = tokens[i];

      if (token[0] == '-') {
        // Long name
        if (token.length() > 1 && token[1] == '-') {
          opts("--help") {
            this->show_help = true;
          }
          opt("--version") {
            this->show_version = true;
          }
          opt("--input") {
            if (i + 1 >= tokens.size()) {
              Info("Error: --input requires at least one file\n");
              break;
            }

            // Subcycle to collect all file names
            while (i + 1 < tokens.size()) {
              const auto& next = tokens[i + 1];

              if (next[0] == '-') {
                break;
              }

              this->input_files.push_back(next);
              i++;
            }
          }
          else {
            // Error, unknown long named parameter
            Info("Error: Unknown argument -> \'", token, "\'\n");
          }
        }
        // Short name
        else {
          opts("-h") {
            this->show_help = true;
          }
          opt("-v") {
            this->show_version = true;
          }
          opt("-i") {
            if (i + 1 >= tokens.size()) {
              Info("Error: -i requires at least one file\n");
              break;
            }

            // Subcycle to collect all file names
            while (i + 1 < tokens.size()) {
              const auto& next = tokens[i + 1];

              if (next[0] == '-') {
                break;
              }

              this->input_files.push_back(next);
              i++;
            }
          }
          else {
            // Error, unknown parameter
            Info("Error: Unknown argument -> \'", token, "\'\n");
          }
        }
      }
    }
#undef opts
#undef opt
  }
}

}  // namespace tea