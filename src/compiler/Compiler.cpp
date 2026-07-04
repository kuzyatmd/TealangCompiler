// compiler/Compiler.cpp
#include "Compiler.hpp"

#include "Global.hpp"
#include "lexer/Lexer.hpp"
#include "reader/Reader.hpp"

namespace tea {

Compiler::Compiler() : opts_(nullptr), ctx_(nullptr), stacktrace_(nullptr) {
  DEBUG("Init");
}

Compiler::~Compiler() {
  // unique pointers automatically are cleared there
  // no need to call anything
  DEBUG("Delete");
}

void Compiler::InitStackTrace() {
  stacktrace_ = std::make_unique<StackTrace>();
}

void Compiler::InitContext() {
  ctx_ = std::make_unique<CompilerContext>();
}

int Compiler::Run(int argc, char* argv[]) {
  InitStackTrace();
  InitOptions(argc, argv);
  // this->options_->PrintAll();
  InitContext();

  Info(stacktrace_->ToString());
  if (!Validate()) {
    return stacktrace_->GetErrorCode();
  }

  stacktrace_->Clear();
  return Compile();
}

// Validate things and print help/version options
bool Compiler::Validate() {
  if (opts_ == nullptr) {
    Info("Error: Options not initialized.\n");
    return false;
  }

  if (opts_->show_version) {
    this->PrintVersion();
    return false;
  }

  if (opts_->show_help) {
    this->PrintHelp();
    return false;
  }

  if (opts_->input_files.empty()) {
    Info("Error: No input files.\n");
  }

  return true;
}

void Compiler::PrintHelp() {
  Info("HELP NOT IMPLEMENTED");
}
void Compiler::PrintVersion() {
  Info("VERSION NOT IMPLEMENTED");
}

static void DebugLogTokens(std::vector<Token> tokens_, Reader* reader) {
  // DEBUG ONLY
  std::string msg;
  for (auto token : tokens_) {
    switch (token.type) {
      case TokenType::Space:
        msg = "\' \'";
        break;
      case TokenType::Tab:
        msg = "\'\\t\'";
        break;
      case TokenType::NewLine:
        msg = "\'\\n\'";
        break;
      case TokenType::Unknown:
        break;

      case TokenType::Lexeme:
        // std::cout << std::format("\'{}:{}\'\n", token.offset, token.length);
        msg = std::format("\'{}\' ({}:{})\n", reader->ReadLexeme(token),
                          token.offset, token.length);
        break;

      case TokenType::Number:
        msg = std::format("\'{}\'\n", reader->ReadLexeme(token));
        break;
      default:
        msg = std::format("\'{}\'\n", static_cast<char>(token.type));
        break;
    }

    std::cout << msg;
  }
}

int Compiler::Compile() {
  DEBUG("Compile Start");

  std::string_view buffer;
  //
  for (auto file : opts_->input_files) {
    ctx_->reader.SetFile(file);
    ctx_->reader.Open();

    // read until empty buffer
    while (!(buffer = ctx_->reader.Read()).empty()) {
      ctx_->lexer.Process(buffer);
    }
    auto tokens = ctx_->lexer.GetTokens();
    ctx_->reader.Reset();
    DebugLogTokens(tokens, &(ctx_->reader));
    ctx_->reader.Close();
  }

  // TODO: Make reader not close but change file and manage 'ifs_'
  return 0;
}

void Compiler::InitOptions(int argc, char* argv[]) {
  opts_ = std::make_unique<CompilerOptions>(argc, argv);
  opts_->Init();
}

}  // namespace tea