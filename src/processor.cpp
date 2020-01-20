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
  this->z = obj.get_z();
  this->s = obj.get_s();
  this->p = obj.get_p();
  this->cy = obj.get_cy();
  this->ac = obj.get_ac();
  this->pad = obj.get_pad();
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
  this->a = obj.get_a();
  this->b = obj.get_b();
  this->c = obj.get_c();
  this->d = obj.get_d();
  this->e = obj.get_e();
  this->h = obj.get_h();
  this->l = obj.get_l();
  this->sp = obj.get_sp();
  this->pc = obj.get_pc();
}

uint8_t ConditionCodes::get_z() const { return this->z; }
uint8_t ConditionCodes::get_s() const { return this->s; }
uint8_t ConditionCodes::get_p() const { return this->p; }
uint8_t ConditionCodes::get_cy() const { return this->cy; }
uint8_t ConditionCodes::get_ac() const { return this->ac; }
uint8_t ConditionCodes::get_pad() const { return this->pad; }

uint8_t Registers::get_a() const { return this->a; }
uint8_t Registers::get_b() const { return this->b; }
uint8_t Registers::get_c() const { return this->c; }
uint8_t Registers::get_d() const { return this->d; }
uint8_t Registers::get_e() const { return this->e; }
uint8_t Registers::get_h() const { return this->h; }
uint8_t Registers::get_l() const { return this->l; }
uint16_t Registers::get_sp() const { return this->sp; }
uint16_t Registers::get_pc() const { return this->pc; }

void ConditionCodes::set_z(const uint8_t z) { this->z = z; }
void ConditionCodes::set_s(const uint8_t s) { this->s = s; }
void ConditionCodes::set_p(const uint8_t p) { this->p = p; }
void ConditionCodes::set_cy(const uint8_t cy) { this->cy = cy; }
void ConditionCodes::set_ac(const uint8_t ac) { this->ac = ac; }
void ConditionCodes::set_pad(const uint8_t pad) { this->pad = pad; }

void Registers::set_a(const uint8_t a) { this->a = a; }
void Registers::set_b(const uint8_t b) { this->b = b; }
void Registers::set_c(const uint8_t c) { this->c = c; }
void Registers::set_d(const uint8_t d) { this->d = d; }
void Registers::set_e(const uint8_t e) { this->e = e; }
void Registers::set_h(const uint8_t h) { this->h = h; }
void Registers::set_l(const uint8_t l) { this->l = l; }
void Registers::set_sp(const uint16_t sp) { this->sp = sp; }
void Registers::set_pc(const uint16_t pc) { this->pc = pc; }

std::ostream& operator<<(std::ostream& os, const ConditionCodes& obj) {
  return os << obj.ToString();
}

ConditionCodes& ConditionCodes::operator=(const ConditionCodes& rhs) {
  if (this == &rhs) return *this;

  this->z = rhs.get_z();
  this->s = rhs.get_s();
  this->p = rhs.get_p();
  this->cy = rhs.get_cy();
  this->ac = rhs.get_ac();
  this->pad = rhs.get_pad();

  return *this;
}

bool ConditionCodes::operator==(const ConditionCodes& rhs) const {
  return (this->z == rhs.get_z()) &&
         (this->s == rhs.get_s()) &&
         (this->p == rhs.get_p()) &&
         (this->cy == rhs.get_cy()) &&
         (this->ac == rhs.get_ac()) &&
         (this->pad == rhs.get_pad());
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

  this->a = rhs.get_a();
  this->b = rhs.get_b();
  this->c = rhs.get_c();
  this->d = rhs.get_d();
  this->e = rhs.get_e();
  this->h = rhs.get_h();
  this->l = rhs.get_l();
  this->sp = rhs.get_sp();
  this->pc = rhs.get_pc();

  return *this;
}

bool Registers::operator==(const Registers& rhs) const {
  return (this->a == rhs.get_a()) &&
         (this->b == rhs.get_b()) &&
         (this->c == rhs.get_c()) &&
         (this->d == rhs.get_d()) &&
         (this->e == rhs.get_e()) &&
         (this->h == rhs.get_h()) &&
         (this->l == rhs.get_l()) &&
         (this->sp == rhs.get_sp()) &&
         (this->pc == rhs.get_pc());
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
