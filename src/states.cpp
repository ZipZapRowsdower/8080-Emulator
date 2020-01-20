#include "include/states.h"

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

const int ROM_SIZE = 0x2000;

State8080::State8080() : memory(ROM_SIZE, 0x00) {
  this->ClearState();
}

State8080::State8080(const State8080& obj) {
  this->a = obj.a;
  this->b = obj.b;
  this->c = obj.c;
  this->d = obj.d;
  this->e = obj.e;
  this->h = obj.h;
  this->l = obj.l;
  this->memory = obj.memory;
  this->sp = obj.sp;
  this->pc = obj.pc;
  this->cc.z = obj.cc.z;
  this->cc.s = obj.cc.s;
  this->cc.p = obj.cc.p;
  this->cc.cy = obj.cc.cy;
  this->cc.ac = obj.cc.ac;
  this->cc.pad = obj.cc.pad;
  this->int_enable = obj.int_enable;
}

State8080::State8080(const std::vector<uint8_t> memory, const uint8_t a,
                     const uint8_t b, const uint8_t c, const uint8_t d,
                     const uint8_t e, const uint8_t h, const uint8_t l,
                     const uint16_t sp, const uint16_t pc,
                     const uint8_t int_enable, const ConditionCodes cc)
                     : memory(ROM_SIZE, 0x00) {
  // TODO: What if memory.size() > ROM_SIZE?
  for (unsigned int i = 0; i < memory.size(); i++) {
    this->memory[i] = memory[i];
  }
  this->a = a;
  this->b = b;
  this->c = c;
  this->d = d;
  this->e = e;
  this->h = h;
  this->l = l;
  this->sp = sp;
  this->pc = pc;
  this->int_enable = int_enable;
  this->cc.z = cc.z;
  this->cc.s = cc.s;
  this->cc.p = cc.p;
  this->cc.cy = cc.cy;
  this->cc.ac = cc.ac;
  this->cc.pad = cc.pad;
}


void State8080::ClearState() {
  this->a = 0;
  this->b = 0;
  this->c = 0;
  this->d = 0;
  this->e = 0;
  this->h = 0;
  this->l = 0;
  for (unsigned int i = 0; i < this->memory.size(); i++) {
    this->memory[i] = 0x00;
  }
  this->sp = 0;
  this->pc = 0;
  ResetConditionCodes(&this->cc);
  this->int_enable = 0;
}

std::string State8080::ToString() const {
  std::ostringstream my_string_stream;
  my_string_stream << std::dec <<
    "        " <<
    "C=" << std::setw(1) << static_cast<int>(this->cc.cy) << ", " <<
    "P=" << std::setw(1) << static_cast<int>(this->cc.p) <<  ", " <<
    "S=" << std::setw(1) << static_cast<int>(this->cc.s) <<  ", " <<
    "Z=" << std::setw(1) << static_cast<int>(this->cc.z) <<
                  std::endl;
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

std::ostream& operator<<(std::ostream& os, const State8080& obj) {
  return os << obj.ToString();
}

bool State8080::operator==(const State8080& rhs) const {
  return (this->a == rhs.a) &&
         (this->b == rhs.b) &&
         (this->c == rhs.c) &&
         (this->d == rhs.d) &&
         (this->e == rhs.e) &&
         (this->h == rhs.h) &&
         (this->l == rhs.l) &&
         (this->memory == rhs.memory) &&
         (this->sp == rhs.sp) &&
         (this->pc == rhs.pc) &&
         (this->cc.z == rhs.cc.z) &&
         (this->cc.s == rhs.cc.s) &&
         (this->cc.p == rhs.cc.p) &&
         (this->cc.cy == rhs.cc.cy) &&
         (this->cc.ac == rhs.cc.ac) &&
         (this->cc.pad == rhs.cc.pad) &&
         (this->int_enable == rhs.int_enable);
}

bool State8080::operator!=(const State8080& rhs) const {
  return !(*this == rhs);
}

State8080& State8080::operator=(const State8080& rhs) {
  if (this == &rhs) return *this;

  this->a = rhs.a;
  this->b = rhs.b;
  this->c = rhs.c;
  this->d = rhs.d;
  this->e = rhs.e;
  this->h = rhs.h;
  this->l = rhs.l;
  this->memory = rhs.memory;
  this->sp = rhs.sp;
  this->pc = rhs.pc;
  this->cc.z = rhs.cc.z;
  this->cc.s = rhs.cc.s;
  this->cc.p = rhs.cc.p;
  this->cc.cy = rhs.cc.cy;
  this->cc.ac = rhs.cc.ac;
  this->cc.pad = rhs.cc.pad;
  this->int_enable = rhs.int_enable;

  return *this;
}

int State8080::LoadMemory(FILE* f) {
  // Get the file size and read it into a memory buffer
  fseek(f, 0L, SEEK_END);
  int fsize = ftell(f);
  fseek(f, 0L, SEEK_SET);

  fread(&(this->memory[0]), fsize, 1, f);

  return fsize;
}

void State8080::LoadMemory(unsigned char* buffer, int length) {
  memcpy(&(this->memory[0]), buffer, length);
}

void ResetConditionCodes(ConditionCodes* cc) {
  cc->z = 0;
  cc->s = 0;
  cc->p = 0;
  cc->cy = 0;
  cc->ac = 0;
  cc->pad = 0;
}

void State8080::CycleInstruction() {
  unsigned char *opcode = &this->memory[this->pc];

  switch (*opcode)
  {
    case 0x00: // NOP
      break;
    case 0x01: // LXI B, word
      this->c = opcode[1];
      this->b = opcode[2];
      this->pc += 2;
      break;
    case 0x0f: // RRC
      {
      uint8_t x = this->a;
      this->a = ((x & 1) << 7) | (x >> 1);
      this->cc.cy = (1 == (x & 1));
      }
      break;
    case 0x1f: // RAR
      {
      uint8_t x = this->a;
      this->a = (this->cc.cy << 7) | (x >> 1);
      this->cc.cy = (1 == (x & 1));
      }
      break;
    case 0x2f: // CMA
      this->a = ~this->a;
      break;
    case 0x41: // MOV B, C
      this->b = this->c;
      break;
    case 0x42: // MOV B, D
      this->b = this->d;
      break;
    case 0x43: // MOV B, E
      this->b = this->e;
      break;
    case 0x81: // ADD C
      {
      // answer expanded to 16 bits to easily determine carry bits
      uint16_t answer = (uint16_t) this->a + (uint16_t) this->c;
      this->cc.z = ((answer & 0xff) == 0);
      this->cc.s = ((answer & 0x80) != 0);
      this->cc.cy = (answer > 0xff);
      this->cc.p = Parity(answer & 0xff);
      this->a = answer & 0xff;
      }
      break;
    case 0x86: // ADD M
      {
      uint16_t offset = (this->h << 8) | (this->l);
      uint16_t answer = (uint16_t) this->a + this->memory[offset];
      this->cc.z = ((answer & 0xff) == 0);
      this->cc.s = ((answer & 0x80) != 0);
      this->cc.cy = (answer > 0xff);
      this->cc.p = Parity(answer & 0xff);
      this->a = answer & 0xff;
      }
      break;
    case 0xc1: // POP B
      this->c = this->memory[this->sp];
      this->b = this->memory[this->sp+1];
      this->sp += 2;
      break;
    case 0xc2: // JNZ address
      if (0 == this->cc.z)
      {
        this->pc = (opcode[2] << 8) | opcode[1];
      }
      else
      {
        // Address has two bytes, must advance
        this->pc += 2;
      }
      break;
    case 0xc3: // JMP address
      this->pc = (opcode[2] << 8) | opcode[1];
      break;
    case 0xc5: // PUSH B
      {
      this->memory[this->sp-1] = this->b;
      this->memory[this->sp-2] = this->c;
      this->sp = this->sp - 2;
      }
      break;
    case 0xc6: // ADI byte
      {
      uint16_t answer = (uint16_t) this->a + (uint16_t) opcode[1];
      this->cc.z = ((answer & 0xff) == 0);
      this->cc.s = ((answer & 0x80) == 0);
      this->cc.cy = (answer > 0xff);
      this->cc.p = Parity(answer & 0xff);
      this->a = answer & 0xff;
      }
      break;
    case 0xc9: // RET
      // Pop return address off the stack (see comment in case 0xcd)
      this->pc = this->memory[this->sp] | (this->memory[this->sp+1] << 8);
      this->sp += 2;
      break;
    case 0xcd: // CALL address
      {
      // Set return address.  The actual return address will be pc+2, but here
      // we're accounting for the fact that we always increment by 1 at the
      // end of this subroutine
      uint16_t ret = this->pc+2;
      // Store return address on stack (which grows downwards) in big
      // endian format
      this->memory[this->sp-1] = (ret >> 8) & 0xff;
      this->memory[this->sp-2] = (ret & 0xff);
      // Move the stack pointer (again, grows downwards)
      this->sp = this->sp -2;
      // JMP to address
      this->pc = (opcode[2] << 8) | opcode[1];
      }
      break;
    case 0xe6: // ANI byte
      {
      uint8_t x = this->a & opcode[1];
      this->cc.z = (x == 0);
      this->cc.s = (0x80 == (x & 0x80));
      this->cc.p = parity(x, 8);
      this->cc.cy = 0;
      this->a = x;
      this->pc += 1;
      }
      break;
    case 0xf1: // POP PSW
      {
      this->a = this->memory[this->sp+1];
      uint8_t psw = this->memory[this->sp];
      this->cc.z = (0x01 == (psw & 0x01));
      this->cc.s = (0x02 == (psw & 0x02));
      this->cc.p = (0x04 == (psw & 0x04));
      this->cc.cy = (0x08 == (psw & 0x08));
      this->cc.ac = (0x10 == (psw & 0x10));
      this->sp += 2;
      }
      break;
    case 0xf5: // PUSH PSW
      {
      this->memory[this->sp-1] = this->a;
      uint8_t psw = (this->cc.z |
                     this->cc.s << 1 |
                     this->cc.p << 2 |
                     this->cc.cy << 3 |
                     this->cc.ac << 4);
      this->memory[this->sp-2] = psw;
      this->sp -= 2;
      }
      break;
    case 0xfe: // CPI byte
      {
      uint8_t x = this->a - opcode[1];
      this->cc.z = (x == 0);
      this->cc.s = (0x80 == (x & 0x80));
      // Is parity set correctly?
      this->cc.p = parity(x, 8);
      this->cc.cy = (this->a < opcode[1]);
      this->pc++;
      }
      break;
    default:
      UnimplementedInstruction(this);
      break;
  }
  this->pc += 1; // every instruction has an opcode
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
