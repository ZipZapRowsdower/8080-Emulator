#include "include/processor.h"

#include <iomanip>
#include <iostream>
#include <sstream>

ConditionCodes::ConditionCodes() {
  this->Clear();
}

ConditionCodes::ConditionCodes(uint8_t z, uint8_t s, uint8_t p, uint8_t cy,
                               uint8_t ac, uint8_t pad) {
  this->z = z;
  this->s = s;
  this->p = p;
  this->cy = cy;
  this->ac = ac;
  this->pad = pad;
}

ConditionCodes::ConditionCodes(const ConditionCodes& obj) {
  this->z = obj.z;
  this->s = obj.s;
  this->p = obj.p;
  this->cy = obj.cy;
  this->ac = obj.ac;
  this->pad = obj.pad;
}

Registers::Registers() {
  this->Clear();
}

Registers::Registers(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e,
                      uint8_t h, uint8_t l, uint16_t sp, uint16_t pc) {
  this->a = a;
  this->b = b;
  this->c = c;
  this->d = d;
  this->e = e;
  this->h = h;
  this->l = l;
  this->sp = sp;
  this->pc = pc;
}

Registers::Registers(const Registers& obj) {
  this->a = obj.a;
  this->b = obj.b;
  this->c = obj.c;
  this->d = obj.d;
  this->e = obj.e;
  this->h = obj.h;
  this->l = obj.l;
  this->sp = obj.sp;
  this->pc = obj.pc;
}

std::ostream& operator<<(std::ostream& os, const ConditionCodes& obj) {
  return os << obj.ToString();
}

ConditionCodes& ConditionCodes::operator=(const ConditionCodes& rhs) {
  if (this == &rhs) return *this;

  this->z = rhs.z;
  this->s = rhs.s;
  this->p = rhs.p;
  this->cy = rhs.cy;
  this->ac = rhs.ac;
  this->pad = rhs.pad;

  return *this;
}

bool ConditionCodes::operator==(const ConditionCodes& rhs) const {
  return (this->z == rhs.z) &&
         (this->s == rhs.s) &&
         (this->p == rhs.p) &&
         (this->cy == rhs.cy) &&
         (this->ac == rhs.ac) &&
         (this->pad == rhs.pad);
}

bool ConditionCodes::operator!=(const ConditionCodes& rhs) const {
  return !(*this == rhs);
}

std::string ConditionCodes::ToString() const {
  std::ostringstream my_string_stream;
  my_string_stream << std::dec <<
    "        " <<
    "C=" << std::setw(1) << static_cast<int>(this->cy) << ", " <<
    "P=" << std::setw(1) << static_cast<int>(this->p) <<  ", " <<
    "S=" << std::setw(1) << static_cast<int>(this->s) <<  ", " <<
    "Z=" << std::setw(1) << static_cast<int>(this->z) <<
    std::endl;
  return my_string_stream.str();
}

std::ostream& operator<<(std::ostream& os, const Registers& obj) {
  return os << obj.ToString();
}

Registers& Registers::operator=(const Registers& rhs) {
  if (this == &rhs) return *this;

  this->a = rhs.a;
  this->b = rhs.b;
  this->c = rhs.c;
  this->d = rhs.d;
  this->e = rhs.e;
  this->h = rhs.h;
  this->l = rhs.l;
  this->sp = rhs.sp;
  this->pc = rhs.pc;

  return *this;
}

bool Registers::operator==(const Registers& rhs) const {
  return (this->a == rhs.a) &&
         (this->b == rhs.b) &&
         (this->c == rhs.c) &&
         (this->d == rhs.d) &&
         (this->e == rhs.e) &&
         (this->h == rhs.h) &&
         (this->l == rhs.l) &&
         (this->sp == rhs.sp) &&
         (this->pc == rhs.pc);
}

bool Registers::operator!=(const Registers& rhs) const {
  return !(*this == rhs);
}
std::string Registers::ToString() const {
  std::ostringstream my_string_stream;
  my_string_stream << std::hex << std::setfill('0') <<
    "        " <<
    "A $" << std::setw(2) << static_cast<int>(this->a) << " " <<
    "B $" << std::setw(2) << static_cast<int>(this->b) << " " <<
    "C $" << std::setw(2) << static_cast<int>(this->c) << " " <<
    "D $" << std::setw(2) << static_cast<int>(this->d) << " " <<
    "E $" << std::setw(2) << static_cast<int>(this->e) << " " <<
    "H $" << std::setw(2) << static_cast<int>(this->h) << " " <<
    "L $" << std::setw(2) << static_cast<int>(this->l) << " " <<
    "SP $" << std::setw(4) << static_cast<int>(this->sp) << " " <<
    "PC $" << std::setw(4) << static_cast<int>(this->pc) <<
    std::endl;
  return my_string_stream.str();
}

bool ConditionCodes::IsClear() const {
  return (this->z == 0) &&
         (this->s == 0) &&
         (this->p == 0) &&
         (this->cy == 0) &&
         (this->ac == 0) &&
         (this->pad == 0);
}

void ConditionCodes::Clear() {
  this->z = 0;
  this->s = 0;
  this->p = 0;
  this->cy = 0;
  this->ac = 0;
  this->pad = 0;
}

bool Registers::IsClear() const {
  return (this->a == 0x00) &&
         (this->b == 0x00) &&
         (this->c == 0x00) &&
         (this->d == 0x00) &&
         (this->e == 0x00) &&
         (this->h == 0x00) &&
         (this->l == 0x00) &&
         (this->sp == 0x0000) &&
         (this->pc == 0x0000);
}

void Registers::Clear() {
  this->a = 0x00;
  this->b = 0x00;
  this->c = 0x00;
  this->d = 0x00;
  this->e = 0x00;
  this->h = 0x00;
  this->l = 0x00;
  this->sp = 0x0000;
  this->pc = 0x0000;
}
