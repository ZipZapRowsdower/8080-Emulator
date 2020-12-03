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
   State8080(const std::vector<uint8_t>&, const Registers&, uint8_t, const ConditionCodes&);
   friend std::ostream& operator<<(std::ostream&, const State8080&);
   bool operator==(const State8080&) const;
   bool operator!=(const State8080&) const;
   State8080& operator=(const State8080&);

   void ClearState();
   void LoadMemory(const void*, size_t);
   void CycleInstruction();
   [[nodiscard]] std::string ToString() const;
   [[nodiscard]] uint8_t get_a() const;
   [[nodiscard]] uint8_t get_b() const;
   [[nodiscard]] uint8_t get_c() const;
   [[nodiscard]] uint8_t get_d() const;
   [[nodiscard]] uint8_t get_e() const;
   [[nodiscard]] uint8_t get_h() const;
   [[nodiscard]] uint8_t get_l() const;
   [[nodiscard]] uint16_t get_sp() const;
   [[nodiscard]] uint16_t get_pc() const;
   [[nodiscard]] uint8_t get_z() const;
   [[nodiscard]] uint8_t get_s() const;
   [[nodiscard]] uint8_t get_p() const;
   [[nodiscard]] uint8_t get_cy() const;
   [[nodiscard]] uint8_t get_ac() const;
   [[nodiscard]] uint8_t get_pad() const;
   void set_a(uint8_t);
   void set_b(uint8_t);
   void set_c(uint8_t);
   void set_d(uint8_t);
   void set_e(uint8_t);
   void set_h(uint8_t);
   void set_l(uint8_t);
   void set_sp(uint16_t);
   void set_pc(uint16_t);
   void set_z(uint8_t);
   void set_s(uint8_t);
   void set_p(uint8_t);
   void set_cy(uint8_t);
   void set_ac(uint8_t);
   void set_pad(uint8_t);
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
