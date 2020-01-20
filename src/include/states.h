#ifndef STATES_H_
#define STATES_H_
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "processor.h"

class State8080 {
 public:
   State8080();
   State8080(const State8080&);
   State8080(const std::vector<uint8_t>, const Registers, const uint8_t,
             const ConditionCodes);
   friend std::ostream& operator<<(std::ostream&, const State8080&);
   bool operator==(const State8080&) const;
   bool operator!=(const State8080&) const;
   State8080& operator=(const State8080&);

   void ClearState();
   int LoadMemory(FILE*);
   void LoadMemory(unsigned char*, int);
   void CycleInstruction();
   std::string ToString() const;
   uint8_t get_a() const;
   uint8_t get_b() const;
   uint8_t get_c() const;
   uint8_t get_d() const;
   uint8_t get_e() const;
   uint8_t get_h() const;
   uint8_t get_l() const;
   uint16_t get_sp() const;
   uint16_t get_pc() const;
   uint8_t get_z() const;
   uint8_t get_s() const;
   uint8_t get_p() const;
   uint8_t get_cy() const;
   uint8_t get_ac() const;
   uint8_t get_pad() const;
   void set_a(const uint8_t);
   void set_b(const uint8_t);
   void set_c(const uint8_t);
   void set_d(const uint8_t);
   void set_e(const uint8_t);
   void set_h(const uint8_t);
   void set_l(const uint8_t);
   void set_sp(const uint16_t);
   void set_pc(const uint16_t);
   void set_z(const uint8_t);
   void set_s(const uint8_t);
   void set_p(const uint8_t);
   void set_cy(const uint8_t);
   void set_ac(const uint8_t);
   void set_pad(const uint8_t);
   // TODO: Make private!!!!!
   std::vector<uint8_t> memory;
   Registers regs;
   uint8_t int_enable;
   ConditionCodes cc;
};

void UnimplementedInstruction(State8080*);
uint8_t Parity(uint8_t);
uint8_t parity(uint8_t, uint8_t);
#endif // STATES_H_
