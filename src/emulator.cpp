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
  int fsize = 0;
  if (f==NULL) {
    std::cout << "error: Couldn't open " << argv[1] << std::endl;
    exit(1);
  }
  fsize = state.LoadMemory(f);
  fclose(f);

  int pc = 0;

  while (pc < fsize) {
    pc += Disassemble8080Op(state.memory, pc);
  }

  while (1) {
    Disassemble8080Op(state.memory, state.regs.get_pc());
    state.CycleInstruction();
    std::cout << state;
  }
  return 0;
}
