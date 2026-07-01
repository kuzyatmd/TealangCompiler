// src/main.cpp

#include "Global.hpp"
#include "compiler/Compiler.hpp"

int main(int argc, char* argv[]) {
  DEBUG("Main Entrypoint");
  tea::Compiler compiler;
  DEBUG("Compiler init");

  return compiler.Run(argc, argv);
}