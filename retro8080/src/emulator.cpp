#include "emulator.h"

#include <cstdlib>
#include <iostream>

#include "instructions.h"
#include "states.h"

size_t get_rom_from_file(const char *filename, void **data) {
    // Read ROM file into memory
    FILE *f = fopen(filename, "rb");
    if (f == nullptr) {
        std::cout << "error: Couldn't open " << filename << std::endl;
        exit(1);
    }

    // Get the file size and read it into a memory buffer
    fseek(f, 0L, SEEK_END);
    size_t size = ftell(f);
    (*data) = (void*) malloc(size);
    fseek(f, 0L, SEEK_SET);
    fread(*data, size, 1, f);
    fclose(f);
    return size;
}

State8080 load_game_from_rom(const void *data, size_t size) {
    State8080 state;

    state.LoadMemory(data, size);

    int pc = 0;
    while (pc < size) {
        pc += Disassemble8080Op(state.memory, pc);
    }

    return state;
}

void run_next_instruction(State8080 state) {
    Disassemble8080Op(state.memory, state.regs.get_pc());
    state.CycleInstruction();
    std::cout << state;
}

int main (int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Please specify a file as an argument" << std::endl;
    exit(1);
  }

  void* data;
  size_t size = get_rom_from_file(argv[1], &data);

  State8080 my_state;
  my_state = load_game_from_rom(data, size);
  std::cout << "This is a test message." << std::endl;

  #pragma clang diagnostic push
  #pragma ide diagnostic ignored "EndlessLoop"
  while (true) {
      run_next_instruction(my_state);
  }
  #pragma clang diagnostic pop
  return 0;
}
