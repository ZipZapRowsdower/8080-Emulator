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
