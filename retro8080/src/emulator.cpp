#include "emulator.h"

#include <cstdlib>
#include <iostream>

#include "instructions.h"
#include "states.h"

void run_the_code(const void *data, size_t size) {
    State8080 state;

    state.LoadMemory(data, size);

    int pc = 0;

    while (pc < size) {
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
}

int main (int argc, char** argv) {
  // Initialize memory
  void* data;

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

  // Get the file size and read it into a memory buffer
  fseek(f, 0L, SEEK_END);
  size_t size = ftell(f);
  data = (void*) malloc(size);
  fseek(f, 0L, SEEK_SET);
  fread(data, size, 1, f);
  fclose(f);

  run_the_code(data, size);

  return 0;
}
