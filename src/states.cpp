#include "include/states.h"

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

const int ROM_SIZE = 0x2000;

State8080::State8080() : memory(ROM_SIZE, 0x00) {
  this->ClearState();
}

State8080::State8080(const State8080& obj) {
  this->regs = obj.regs;
  this->memory = obj.memory;
  this->int_enable = obj.int_enable;
  this->cc = obj.cc;
}

State8080::State8080(const std::vector<uint8_t>& memory,
                     const Registers& regs, const uint8_t int_enable,
                     const ConditionCodes& cc)
                     : memory(ROM_SIZE, 0x00) {
  // TODO: What if memory.size() > ROM_SIZE?
  for (unsigned int i = 0; i < memory.size(); i++) {
    this->memory[i] = memory[i];
  }
  this->regs = regs;
  this->int_enable = int_enable;
  this->cc = cc;
}

uint8_t State8080::get_a() const { return this->regs.get_a(); }
uint8_t State8080::get_b() const { return this->regs.get_b(); }
uint8_t State8080::get_c() const { return this->regs.get_c(); }
uint8_t State8080::get_d() const { return this->regs.get_d(); }
uint8_t State8080::get_e() const { return this->regs.get_e(); }
uint8_t State8080::get_h() const { return this->regs.get_h(); }
uint8_t State8080::get_l() const { return this->regs.get_l(); }
uint16_t State8080::get_sp() const { return this->regs.get_sp(); }
uint16_t State8080::get_pc() const { return this->regs.get_pc(); }
uint8_t State8080::get_z() const { return this->cc.get_z(); }
uint8_t State8080::get_s() const { return this->cc.get_s(); }
uint8_t State8080::get_p() const { return this->cc.get_p(); }
uint8_t State8080::get_cy() const { return this->cc.get_cy(); }
uint8_t State8080::get_ac() const { return this->cc.get_ac(); }
uint8_t State8080::get_pad() const { return this->cc.get_pad(); }

void State8080::set_a(const uint8_t a) { this->regs.set_a(a); }
void State8080::set_b(const uint8_t b) { this->regs.set_b(b); }
void State8080::set_c(const uint8_t c) { this->regs.set_c(c); }
void State8080::set_d(const uint8_t d) { this->regs.set_d(d); }
void State8080::set_e(const uint8_t e) { this->regs.set_e(e); }
void State8080::set_h(const uint8_t h) { this->regs.set_h(h); }
void State8080::set_l(const uint8_t l) { this->regs.set_l(l); }
void State8080::set_sp(const uint16_t sp) { this->regs.set_sp(sp); }
void State8080::set_pc(const uint16_t pc) { this->regs.set_pc(pc); }
void State8080::set_z(const uint8_t z) { this->cc.set_z(z); }
void State8080::set_s(const uint8_t s) { this->cc.set_s(s); }
void State8080::set_p(const uint8_t p) { this->cc.set_p(p); }
void State8080::set_cy(const uint8_t cy) { this->cc.set_cy(cy); }
void State8080::set_ac(const uint8_t ac) { this->cc.set_ac(ac); }
void State8080::set_pad(const uint8_t pad) { this->cc.set_pad(pad); }

void State8080::ClearState() {
  for (unsigned char & i : this->memory) {
    i = 0x00;
  }
  this->regs.Clear();
  this->int_enable = 0;
  this->cc.Clear();
}

std::string State8080::ToString() const {
  std::ostringstream my_string_stream;
  my_string_stream << this->cc << this->regs;
  return my_string_stream.str();
}

std::ostream& operator<<(std::ostream& os, const State8080& obj) {
  return os << obj.ToString();
}

bool State8080::operator==(const State8080& rhs) const {
  return (this->memory == rhs.memory) &&
         (this->regs == rhs.regs) &&
         (this->cc == rhs.cc) &&
         (this->int_enable == rhs.int_enable);
}

bool State8080::operator!=(const State8080& rhs) const {
  return !(*this == rhs);
}

State8080& State8080::operator=(const State8080& rhs) {
  if (this == &rhs) return *this;

  this->memory = rhs.memory;
  this->regs = rhs.regs;
  this->int_enable = rhs.int_enable;
  this->cc = rhs.cc;

  return *this;
}

long State8080::LoadMemory(FILE* f) {
  // Get the file size and read it into a memory buffer
  fseek(f, 0L, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0L, SEEK_SET);

  fread(&(this->memory[0]), fsize, 1, f);

  return fsize;
}

void State8080::LoadMemory(unsigned char* buffer, int length) {
  memcpy(&(this->memory[0]), buffer, length);
}

void State8080::CycleInstruction() {
  unsigned char *opcode = &this->memory[this->get_pc()];

  switch (*opcode)
  {
/*
    case 0x00: // NOP
      break;
    case 0x01: // LXI B, word
      this->regs.c = opcode[1];
      this->regs.b = opcode[2];
      this->regs.pc += 2;
      break;
    case 0x0f: // RRC
      {
      uint8_t x = this->regs.a;
      this->regs.a = ((x & 1) << 7) | (x >> 1);
      this->cc.cy = (1 == (x & 1));
      }
      break;
    case 0x1f: // RAR
      {
      uint8_t x = this->regs.a;
      this->regs.a = (this->cc.cy << 7) | (x >> 1);
      this->cc.cy = (1 == (x & 1));
      }
      break;
    case 0x2f: // CMA
      this->regs.a = ~this->regs.a;
      break;
    case 0x41: // MOV B, C
      this->regs.b = this->regs.c;
      break;
    case 0x42: // MOV B, D
      this->regs.b = this->regs.d;
      break;
    case 0x43: // MOV B, E
      this->regs.b = this->regs.e;
      break;
    case 0x81: // ADD C
      {
      // answer expanded to 16 bits to easily determine carry bits
      uint16_t answer = (uint16_t) this->regs.a + (uint16_t) this->regs.c;
      this->cc.z = ((answer & 0xff) == 0);
      this->cc.s = ((answer & 0x80) != 0);
      this->cc.cy = (answer > 0xff);
      this->cc.p = Parity(answer & 0xff);
      this->regs.a = answer & 0xff;
      }
      break;
    case 0x86: // ADD M
      {
      uint16_t offset = (this->regs.h << 8) | (this->regs.l);
      uint16_t answer = (uint16_t) this->regs.a + this->memory[offset];
      this->cc.z = ((answer & 0xff) == 0);
      this->cc.s = ((answer & 0x80) != 0);
      this->cc.cy = (answer > 0xff);
      this->cc.p = Parity(answer & 0xff);
      this->regs.a = answer & 0xff;
      }
      break;
    case 0xc1: // POP B
      this->regs.c = this->memory[this->regs.sp];
      this->regs.b = this->memory[this->regs.sp+1];
      this->regs.sp += 2;
      break;
    case 0xc2: // JNZ address
      if (0 == this->cc.z)
      {
        this->regs.pc = (opcode[2] << 8) | opcode[1];
      }
      else
      {
        // Address has two bytes, must advance
        this->regs.pc += 2;
      }
      break;
    case 0xc3: // JMP address
      this->regs.pc = (opcode[2] << 8) | opcode[1];
      break;
    case 0xc5: // PUSH B
      {
      this->memory[this->regs.sp-1] = this->regs.b;
      this->memory[this->regs.sp-2] = this->regs.c;
      this->regs.sp = this->regs.sp - 2;
      }
      break;
    case 0xc6: // ADI byte
      {
      uint16_t answer = (uint16_t) this->regs.a + (uint16_t) opcode[1];
      this->cc.z = ((answer & 0xff) == 0);
      this->cc.s = ((answer & 0x80) == 0);
      this->cc.cy = (answer > 0xff);
      this->cc.p = Parity(answer & 0xff);
      this->regs.a = answer & 0xff;
      }
      break;
    case 0xc9: // RET
      // Pop return address off the stack (see comment in case 0xcd)
      this->regs.pc = this->memory[this->regs.sp] | (this->memory[this->regs.sp+1] << 8);
      this->regs.sp += 2;
      break;
    case 0xcd: // CALL address
      {
      // Set return address.  The actual return address will be pc+2, but here
      // we're accounting for the fact that we always increment by 1 at the
      // end of this subroutine
      uint16_t ret = this->regs.pc+2;
      // Store return address on stack (which grows downwards) in big
      // endian format
      this->memory[this->regs.sp-1] = (ret >> 8) & 0xff;
      this->memory[this->regs.sp-2] = (ret & 0xff);
      // Move the stack pointer (again, grows downwards)
      this->regs.sp = this->regs.sp -2;
      // JMP to address
      this->regs.pc = (opcode[2] << 8) | opcode[1];
      }
      break;
    case 0xe6: // ANI byte
      {
      uint8_t x = this->regs.a & opcode[1];
      this->cc.z = (x == 0);
      this->cc.s = (0x80 == (x & 0x80));
      this->cc.p = parity(x, 8);
      this->cc.cy = 0;
      this->regs.a = x;
      this->regs.pc += 1;
      }
      break;
    case 0xf1: // POP PSW
      {
      this->regs.a = this->memory[this->regs.sp+1];
      uint8_t psw = this->memory[this->regs.sp];
      this->cc.z = (0x01 == (psw & 0x01));
      this->cc.s = (0x02 == (psw & 0x02));
      this->cc.p = (0x04 == (psw & 0x04));
      this->cc.cy = (0x08 == (psw & 0x08));
      this->cc.ac = (0x10 == (psw & 0x10));
      this->regs.sp += 2;
      }
      break;
    case 0xf5: // PUSH PSW
      {
      this->memory[this->regs.sp-1] = this->regs.a;
      uint8_t psw = (this->cc.z |
                     this->cc.s << 1 |
                     this->cc.p << 2 |
                     this->cc.cy << 3 |
                     this->cc.ac << 4);
      this->memory[this->regs.sp-2] = psw;
      this->regs.sp -= 2;
      }
      break;
    case 0xfe: // CPI byte
      {
      uint8_t x = this->regs.a - opcode[1];
      this->cc.z = (x == 0);
      this->cc.s = (0x80 == (x & 0x80));
      // Is parity set correctly?
      this->cc.p = parity(x, 8);
      this->cc.cy = (this->regs.a < opcode[1]);
      this->regs.pc++;
      }
      break;
*/
    default:
      UnimplementedInstruction(this);
      break;
  }
  this->set_pc(this->get_pc() + 1); // every instruction has an opcode
}

void UnimplementedInstruction(State8080* state) {
  // pc will have advanced one, so undo that
  std::cout << "Error: Unimplemented instruction" << std::endl;
  exit(1);
}

uint8_t parity(uint8_t value, uint8_t idunno) {
  std::cout << "parity() not implemented" << std::endl;
  exit(1);
}

uint8_t Parity(uint8_t value) {
  std:: cout << "Parity() not implemented" << std::endl;
  exit(1);
}
