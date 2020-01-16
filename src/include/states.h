#ifndef STATES_H_
#define STATES_H_
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

// The bits of the status register
typedef struct ConditionCodes {
  uint8_t z:1;
  uint8_t s:1;
  uint8_t p:1;
  uint8_t cy:1;
  uint8_t ac:1;
  uint8_t pad:3;
} ConditionCodes;


class State8080 {
 public:
   State8080();
   State8080(const State8080&);
   State8080(const std::vector<uint8_t>, const uint8_t, const uint8_t,
             const uint8_t, const uint8_t, const uint8_t, const uint8_t,
             const uint8_t, const uint16_t, const uint16_t,
             const uint8_t, const ConditionCodes);
   friend std::ostream& operator<<(std::ostream&, const State8080&);
   bool operator==(const State8080&) const;
   bool operator!=(const State8080&) const;
   State8080& operator=(const State8080&);

   void ClearState();
   int LoadMemory(FILE*);
   void LoadMemory(unsigned char*, int);
   void CycleInstruction();
   std::string ToString() const;
   // TODO: Make private!!!!!
   std::vector<uint8_t> memory;
   uint8_t a;
   uint8_t b;
   uint8_t c;
   uint8_t d;
   uint8_t e;
   uint8_t h;
   uint8_t l;
   uint16_t sp;
   uint16_t pc;
   ConditionCodes cc;
   uint8_t int_enable;
};

void ResetConditionCodes(ConditionCodes*);
void UnimplementedInstruction(State8080*);
uint8_t Parity(uint8_t);
uint8_t parity(uint8_t, uint8_t);
#endif // STATES_H_
