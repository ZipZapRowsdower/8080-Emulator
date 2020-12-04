#ifndef EMULATOR_H_
#define EMULATOR_H_
#include <cstdlib>

#include "states.h"

State8080 load_game_from_rom(const void*, size_t);
void run_next_instruction(State8080);
#endif // EMULATOR_H_
