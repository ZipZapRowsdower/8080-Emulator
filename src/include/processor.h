#ifndef PROCESSOR_H_
#define PROCESSOR_H_
#include <cstdint>

// The bits of the status register
typedef struct ConditionCodes {
  uint8_t z:1;
  uint8_t s:1;
  uint8_t p:1;
  uint8_t cy:1;
  uint8_t ac:1;
  uint8_t pad:3;
} ConditionCodes;

#endif // PROCESSOR_H_
