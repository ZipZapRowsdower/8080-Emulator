#ifndef PROCESSOR_H_
#define PROCESSOR_H_
#include <cstdint>
#include <string>

// The bits of the status register
class ConditionCodes {
 public:
  ConditionCodes();
  ConditionCodes(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
  ConditionCodes(const ConditionCodes&);
  ConditionCodes& operator=(const ConditionCodes&);
  friend std::ostream& operator<<(std::ostream&, const ConditionCodes&);
  bool operator==(const ConditionCodes&) const;
  bool operator!=(const ConditionCodes&) const;
  void Clear();
  bool IsClear() const;
  std::string ToString() const;
  uint8_t get_z() const;
  uint8_t get_s() const;
  uint8_t get_p() const;
  uint8_t get_cy() const;
  uint8_t get_ac() const;
  uint8_t get_pad() const;
  void set_z(const uint8_t);
  void set_s(const uint8_t);
  void set_p(const uint8_t);
  void set_cy(const uint8_t);
  void set_ac(const uint8_t);
  void set_pad(const uint8_t);
 private:
  uint8_t z:1;
  uint8_t s:1;
  uint8_t p:1;
  uint8_t cy:1;
  uint8_t ac:1;
  uint8_t pad:3;
};

// All registers except the status register
class Registers {
 public:
  Registers();
  Registers(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t,
            uint16_t, uint16_t);
  Registers(const Registers&);
  Registers& operator=(const Registers&);
  friend std::ostream& operator<<(std::ostream&, const Registers&);
  bool operator==(const Registers&) const;
  bool operator!=(const Registers&) const;
  void Clear();
  bool IsClear() const;
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
  void set_a(const uint8_t);
  void set_b(const uint8_t);
  void set_c(const uint8_t);
  void set_d(const uint8_t);
  void set_e(const uint8_t);
  void set_h(const uint8_t);
  void set_l(const uint8_t);
  void set_sp(const uint16_t);
  void set_pc(const uint16_t);
 private:
  uint8_t a;
  uint8_t b;
  uint8_t c;
  uint8_t d;
  uint8_t e;
  uint8_t h;
  uint8_t l;
  uint16_t sp;
  uint16_t pc;
};

#endif // PROCESSOR_H_
