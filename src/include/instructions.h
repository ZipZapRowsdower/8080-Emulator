#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_
#include <cstdint>
#include <vector>

#include "states.h"

int Disassemble8080Op(std::vector<uint8_t>, int);
#endif // INSTRUCTIONS_H_
