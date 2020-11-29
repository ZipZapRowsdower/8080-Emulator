#include "include/emulator.h"

#include <cstdlib>
#include <iostream>

#include "include/instructions.h"
#include "include/states.h"

int main (int argc, char** argv) {
  // Initialize memory
  State8080 state;

  // Read ROM file into memory
  if (argc < 2) {
    std::cout << "Please specify a file as an argument" << std::endl;
    exit(1);
  }
  FILE *f = fopen(argv[1], "rb");
  if (f == nullptr) {
    std::cout << "error: Couldn't open " << argv[1] << std::endl;
    exit(1);
  }
  long fsize = state.LoadMemory(f);
  fclose(f);

  int pc = 0;

  while (pc < fsize) {
    pc += Disassemble8080Op(state.memory, pc);
  }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
  while (true) {
    Disassemble8080Op(state.memory, state.regs.get_pc());
    state.CycleInstruction();
    std::cout << state;
  }
#pragma clang diagnostic pop
  return 0;
}
