// compiler/Compiler.cpp
#include "Compiler.hpp"

#include "Global.hpp"
#include "lexer/Lexer.hpp"
#include "reader/Reader.hpp"

namespace tea {

Compiler::Compiler()
    : options_(nullptr), context_(nullptr), stacktrace_(nullptr) {
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
  context_ = std::make_unique<CompilerContext>();
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
  if (options_ == nullptr) {
    Info("Error: Options not initialized.\n");
    return false;
  }

  if (options_->show_version) {
    this->PrintVersion();
    return false;
  }

  if (options_->show_help) {
    this->PrintHelp();
    return false;
  }

  if (options_->input_files.empty()) {
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
  for (auto token : tokens_) {
    switch (token.type) {
      case TokenType::Space:
      case TokenType::Tab:
      case TokenType::NewLine:
      case TokenType::Unknown:
        break;

      case TokenType::Lexeme:
        // std::cout << std::format("\'{}:{}\'\n", token.offset, token.length);
        std::cout << std::format("\'{}\' ({}:{})\n", reader->ReadLexeme(token),
                                 token.offset, token.length);
        break;

      case TokenType::Number:
        std::cout << std::format("\'{}\'\n", reader->ReadLexeme(token));
        break;
      default:
        std::cout << std::format("\'{}\'\n", static_cast<char>(token.type));
        break;
    }
  }
}

int Compiler::Compile() {
  DEBUG("Compile Start");
  // TODO: place Reader, Lexer, Analyzer and etc. in CompilerContext ctx

  Reader reader;
  Lexer lexer;

  std::string_view buf;
  //
  for (auto file : options_->input_files) {
    reader.SetFile(file);
    reader.Open();

    // read until last
    while (!(buf = reader.Read()).empty()) {
      lexer.Process(buf);
    }
    auto tokens = lexer.GetTokens();
    reader.Reset();
    DebugLogTokens(tokens, &reader);
    reader.Close();
  }
  // TODO: Make reader not close but change file and manage 'ifs_'
  return 0;
}

void Compiler::InitOptions(int argc, char* argv[]) {
  options_ = std::make_unique<CompilerOptions>(argc, argv);
  options_->Init();
}

}  // namespace tea