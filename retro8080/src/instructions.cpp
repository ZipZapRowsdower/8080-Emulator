#include "instructions.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

int Disassemble8080Op(std::vector<uint8_t> codebuffer, int pc) {
  unsigned char *code = &codebuffer[pc];
  int opbytes = 1; // Default op length for 8080
  printf("%04x ", pc);

  // Mnemonics taken from Emulator 101, description taken from Intel 8080A datasheet
  switch (*code) {
    case 0x00: printf("NOP"); break; // No-operation
    case 0x01: printf("LXI   B,0x%02x%02x", code[2], code[1]); opbytes = 3; break; // Load immediate register pair B & C
    case 0x02: printf("STAX  B"); break; // Store A Indirect
    case 0x03: printf("INX   B"); break;  // Increment B & C registers
    case 0x04: printf("INR   B"); break;  // Increment register
    case 0x05: printf("DCR   B"); break;  // Decrement register
    case 0x06: printf("MVI   B, #$%02x", code[1]); opbytes = 2; break; // Move immediate register
    case 0x07: printf("RLC"); break; // Rotate A left
    case 0x08: printf("Op code %02x not defined", *code); break;
    case 0x09: printf("DAD   B"); break; // Add B & C to H & L
    case 0x0a: printf("LDAX  B"); break; // Load A indirect
    case 0x0b: printf("DCX   B"); break; // Decrement B & C
    case 0x0c: printf("INR   C"); break; // Increment register
    case 0x0d: printf("DCR   C"); break; // Decrement register
    case 0x0e: printf("MVI   C, #$%02x", code[1]); opbytes = 2; break; // Move immediate register
    case 0x0f: printf("RRC"); break; // Rotate A right
    case 0x10: printf("Op code %02x not defined", *code); break;
    case 0x11: printf("LXI   D, #$%02x%02x", code[2], code[1]); opbytes = 3; break; // Load immediate register pair D & E
    case 0x12: printf("STAX  D"); break; // Store A indirect
    case 0x13: printf("INX   D"); break; // Increment D & E register
    case 0x14: printf("INR   D"); break; // Increment register
    case 0x15: printf("DCR   D"); break; // Decrement register
    case 0x16: printf("MVI   D, #$%02x", code[1]); opbytes = 2; break; // Move immediate register
    case 0x17: printf("RAL"); break; // Rotate A left through carry
    case 0x18: printf("Op code %02x not defined", *code); break;
    case 0x19: printf("DAD   D"); break; // Add D & E to H & L
    case 0x1a: printf("LDAX  D"); break; // Load A indirect
    case 0x1b: printf("DCX   D"); break; // Decrement D & E
    case 0x1c: printf("INR   E"); break; // Increment register
    case 0x1d: printf("DCR   E"); break; // Decrement register
    case 0x1e: printf("MVI   E, #$%02x", code[1]); opbytes = 2; break; // Move immediate register
    case 0x1f: printf("RAR"); break; // Rotate A right through carry
    case 0x20: printf("Op code %02x not defined", *code); break;
    case 0x21: printf("LXI   H, #$%02x%02x", code[2], code[1]); opbytes = 3; break; // Load immediate register pair H & L
    case 0x22: printf("SHLD  $%02x%02x", code[2], code[1]); opbytes = 3; break; // Store H & L direct
    case 0x23: printf("INX   H"); break; // Increment H & L registers
    case 0x24: printf("INR   H"); break; // Increment register
    case 0x25: printf("DCR   H"); break; // Decrement register
    case 0x26: printf("MVI   H, #$%02x", code[1]); opbytes = 2; break; // Move immediate register
    case 0x27: printf("DAA"); break; // Decimal adjust A (???)
    case 0x28: printf("Op code %02x not defined", *code); break;
    case 0x29: printf("DAD   H"); break; // Add H & L to H & L
    case 0x2a: printf("LHLD  $%02x%02x", code[2], code[1]); opbytes = 3; break; // Load H & L direct
    case 0x2b: printf("DCX   H"); break; // Decrement H & L
    case 0x2c: printf("INR   L"); break; // Increment register
    case 0x2d: printf("DCR   L"); break; // Decrement register
    case 0x2e: printf("MVI   L, #$%02x", code[1]); opbytes = 2; break; // Move immediate register
    case 0x2f: printf("CMA"); break; // Complement A
    case 0x30: printf("Op code %02x not defined", *code); break;
    case 0x31: printf("LXI   SP, #$%02x%02x", code[2], code[1]); opbytes = 3; break; // Load immediate stack pointer
    case 0x32: printf("STA   $%02x%02x", code[2], code[1]); opbytes = 3; break; // Store A direct
    case 0x33: printf("INX   SP"); break; // Increment stack pointer
    case 0x34: printf("INR   M"); break; // Increment memory
    case 0x35: printf("DCR   M"); break; // Decrement memory
    case 0x36: printf("MVI   M, #$%02x", code[1]); opbytes = 2; break; // Move immediate memory
    case 0x37: printf("STC"); break; // Set carry
    case 0x38: printf("Op code %02x not defined", *code); break;
    case 0x39: printf("DAD   SP"); break; // Add stack pointer to H & L
    case 0x3a: printf("LDA   $%02x%02x", code[2], code[1]); opbytes = 3; break; // Load A direct
    case 0x3b: printf("DCX   SP"); break; // Decrement stack pointer
    case 0x3c: printf("INR   A"); break; // Increment register
    case 0x3d: printf("DCR   A"); break; // Decrement register
    case 0x3e: printf("MVI   A, #$%02x", code[1]); opbytes = 2; break; // Move immediate register
    case 0x3f: printf("CMC"); break; // Complement carry
    case 0x40: printf("MOV   B, B"); break; // Move register to register
    case 0x41: printf("MOV   B, C"); break; // Move register to register
    case 0x42: printf("MOV   B, D"); break; // Move register to register
    case 0x43: printf("MOV   B, E"); break; // Move register to register
    case 0x44: printf("MOV   B, H"); break; // Move register to register
    case 0x45: printf("MOV   B, L"); break; // Move register to register
    case 0x46: printf("MOV   B, M"); break; // Move register to memory
    case 0x47: printf("MOV   B, A"); break; // Move register to register
    case 0x48: printf("MOV   C, B"); break; // Move register to register
    case 0x49: printf("MOV   C, C"); break; // Move register to register
    case 0x4a: printf("MOV   C, D"); break; // Move register to register
    case 0x4b: printf("MOV   C, E"); break; // Move register to register
    case 0x4c: printf("MOV   C, H"); break; // Move register to register
    case 0x4d: printf("MOV   C, L"); break; // Move register to register
    case 0x4e: printf("MOV   C, M"); break; // Move register to memory
    case 0x4f: printf("MOV   C, A"); break; // Move register to register
    case 0x50: printf("MOV   D, B"); break; // Move register to register
    case 0x51: printf("MOV   D, C"); break; // Move register to register
    case 0x52: printf("MOV   D, D"); break; // Move register to register
    case 0x53: printf("MOV   D, E"); break; // Move register to register
    case 0x54: printf("MOV   D, H"); break; // Move register to register
    case 0x55: printf("MOV   D, L"); break; // Move register to register
    case 0x56: printf("MOV   D, M"); break; // Move register to memory
    case 0x57: printf("MOV   D, A"); break; // Move register to register
    case 0x58: printf("MOV   E, B"); break; // Move register to register
    case 0x59: printf("MOV   E, C"); break; // Move register to register
    case 0x5a: printf("MOV   E, D"); break; // Move register to register
    case 0x5b: printf("MOV   E, E"); break; // Move register to register
    case 0x5c: printf("MOV   E, H"); break; // Move register to register
    case 0x5d: printf("MOV   E, L"); break; // Move register to register
    case 0x5e: printf("MOV   E, M"); break; // Move register to memory
    case 0x5f: printf("MOV   E, A"); break; // Move register to register
    case 0x60: printf("MOV   H, B"); break; // Move register to register
    case 0x61: printf("MOV   H, C"); break; // Move register to register
    case 0x62: printf("MOV   H, D"); break; // Move register to register
    case 0x63: printf("MOV   H, E"); break; // Move register to register
    case 0x64: printf("MOV   H, H"); break; // Move register to register
    case 0x65: printf("MOV   H, L"); break; // Move register to register
    case 0x66: printf("MOV   H, M"); break; // Move register to memory
    case 0x67: printf("MOV   H, A"); break; // Move register to register
    case 0x68: printf("MOV   L, B"); break; // Move register to register
    case 0x69: printf("MOV   L, C"); break; // Move register to register
    case 0x6a: printf("MOV   L, D"); break; // Move register to register
    case 0x6b: printf("MOV   L, E"); break; // Move register to register
    case 0x6c: printf("MOV   L, H"); break; // Move register to register
    case 0x6d: printf("MOV   L, L"); break; // Move register to register
    case 0x6e: printf("MOV   L, M"); break; // Move register to memory
    case 0x6f: printf("MOV   L, A"); break; // Move register to register
    case 0x70: printf("MOV   M, B"); break; // Move memory to register
    case 0x71: printf("MOV   M, C"); break; // Move memory to register
    case 0x72: printf("MOV   M, D"); break; // Move memory to register
    case 0x73: printf("MOV   M, E"); break; // Move memory to register
    case 0x74: printf("MOV   M, H"); break; // Move memory to register
    case 0x75: printf("MOV   M, L"); break; // Move memory to register
    case 0x76: printf("HLT"); break; // Halt [and catch fire]
    case 0x77: printf("MOV   M, A"); break; // Move memory to register
    case 0x78: printf("MOV   A, B"); break; // Move register to register
    case 0x79: printf("MOV   A, C"); break; // Move register to register
    case 0x7a: printf("MOV   A, D"); break; // Move register to register
    case 0x7b: printf("MOV   A, E"); break; // Move register to register
    case 0x7c: printf("MOV   A, H"); break; // Move register to register
    case 0x7d: printf("MOV   A, L"); break; // Move register to register
    case 0x7e: printf("MOV   A, M"); break; // Move register to memory
    case 0x7f: printf("MOV   A, A"); break; // Move register to register
    case 0x80: printf("ADD   B"); break; // Add register to A
    case 0x81: printf("ADD   C"); break; // Add register to A
    case 0x82: printf("ADD   D"); break; // Add register to A
    case 0x83: printf("ADD   E"); break; // Add register to A
    case 0x84: printf("ADD   H"); break; // Add register to A
    case 0x85: printf("ADD   L"); break; // Add register to A
    case 0x86: printf("ADD   M"); break; // Add memory to A
    case 0x87: printf("ADD   A"); break; // Add register to A
    case 0x88: printf("ADC   B"); break; // Add register to A with carry
    case 0x89: printf("ADC   C"); break; // Add register to A with carry
    case 0x8a: printf("ADC   D"); break; // Add register to A with carry
    case 0x8b: printf("ADC   E"); break; // Add register to A with carry
    case 0x8c: printf("ADC   H"); break; // Add register to A with carry
    case 0x8d: printf("ADC   L"); break; // Add register to A with carry
    case 0x8e: printf("ADC   M"); break; // Add memory to A with carry
    case 0x8f: printf("ADC   A"); break; // Add register to A with carry
    case 0x90: printf("SUB   B"); break; // Subtract register to A
    case 0x91: printf("SUB   C"); break; // Subtract register to A
    case 0x92: printf("SUB   D"); break; // Subtract register to A
    case 0x93: printf("SUB   E"); break; // Subtract register to A
    case 0x94: printf("SUB   H"); break; // Subtract register to A
    case 0x95: printf("SUB   L"); break; // Subtract register to A
    case 0x96: printf("SUB   M"); break; // Subtract memory to A
    case 0x97: printf("SUB   A"); break; // Subtract register to A
    case 0x98: printf("SBB   B"); break; // Subtract register to A with borrow
    case 0x99: printf("SBB   C"); break; // Subtract register to A with borrow
    case 0x9a: printf("SBB   D"); break; // Subtract register to A with borrow
    case 0x9b: printf("SBB   E"); break; // Subtract register to A with borrow
    case 0x9c: printf("SBB   H"); break; // Subtract register to A with borrow
    case 0x9d: printf("SBB   L"); break; // Subtract register to A with borrow
    case 0x9e: printf("SBB   M"); break; // Subtract memory to A with borrow
    case 0x9f: printf("SBB   A"); break; // Subtract register to A with borrow
    case 0xa0: printf("ANA   B"); break; // And register with A
    case 0xa1: printf("ANA   C"); break; // And register with A
    case 0xa2: printf("ANA   D"); break; // And register with A
    case 0xa3: printf("ANA   E"); break; // And register with A
    case 0xa4: printf("ANA   H"); break; // And register with A
    case 0xa5: printf("ANA   L"); break; // And register with A
    case 0xa6: printf("ANA   M"); break; // And memory with A
    case 0xa7: printf("ANA   A"); break; // And register with A
    case 0xa8: printf("XRA   B"); break; // Exclusive or register with A
    case 0xa9: printf("XRA   C"); break; // Exclusive or register with A
    case 0xaa: printf("XRA   D"); break; // Exclusive or register with A
    case 0xab: printf("XRA   E"); break; // Exclusive or register with A
    case 0xac: printf("XRA   H"); break; // Exclusive or register with A
    case 0xad: printf("XRA   L"); break; // Exclusive or register with A
    case 0xae: printf("XRA   M"); break; // Exclusive or memory with A
    case 0xaf: printf("XRA   A"); break; // Exclusive or register with A
    case 0xb0: printf("ORA   B"); break; // Or register with A
    case 0xb1: printf("ORA   C"); break; // Or register with A
    case 0xb2: printf("ORA   D"); break; // Or register with A
    case 0xb3: printf("ORA   E"); break; // Or register with A
    case 0xb4: printf("ORA   H"); break; // Or register with A
    case 0xb5: printf("ORA   L"); break; // Or register with A
    case 0xb6: printf("ORA   M"); break; // Or memory with A
    case 0xb7: printf("ORA   A"); break; // Or register with A
    case 0xb8: printf("CMP   B"); break; // Compare register with A
    case 0xb9: printf("CMP   C"); break; // Compare register with A
    case 0xba: printf("CMP   D"); break; // Compare register with A
    case 0xbb: printf("CMP   E"); break; // Compare register with A
    case 0xbc: printf("CMP   H"); break; // Compare register with A
    case 0xbd: printf("CMP   L"); break; // Compare register with A
    case 0xbe: printf("CMP   M"); break; // Compare memory with A
    case 0xbf: printf("CMP   A"); break; // Compare register with A
    case 0xc0: printf("RNZ"); break; // Return on no zero
    case 0xc1: printf("POP   B"); break; // Pop register pair B & C off stack
    case 0xc2: printf("JNZ   $%02x%02x", code[2], code[1]); opbytes = 3; break; // Jump on no zero
    case 0xc3: printf("JMP   $%02x%02x", code[2], code[1]); opbytes = 3; break; // Jump unconditional
    case 0xc4: printf("CNZ   $%02x%02x", code[2], code[1]); opbytes = 3; break; // Call on no zero
    case 0xc5: printf("PUSH  B"); break; // Push register pair B & C on stack
    case 0xc6: printf("ADI   #$%02x", code[1]); opbytes = 2; break; // Add immediate to A
    case 0xc7: printf("RST   0"); break; // Restart
    case 0xc8: printf("RZ"); break; // Return on zero
    case 0xc9: printf("RET"); break; // Return
    case 0xca: printf("JZ    $%02x%02x", code[2], code[1]); opbytes = 3; break; // Jump on zero
    case 0xcb: printf("Op code %02x not defined", *code); break;
    case 0xcc: printf("CZ    $%02x%02x", code[2], code[1]); opbytes = 3; break; // Call on zero
    case 0xcd: printf("CALL  $%02x%02x", code[2], code[1]); opbytes = 3; break; // Call on unconditional
    case 0xce: printf("ACI 0x%02x", code[1]); opbytes = 2; break; // Add immediate to A with carry
    case 0xcf: printf("RST   1"); break; // Restart
    case 0xd0: printf("RNC"); break; // Return on no carry
    case 0xd1: printf("POP   D"); break; // Pop register pair D & E off stack
    case 0xd2: printf("JNC   $%02x%02x", code[2], code[1]); opbytes = 3; break; // Jump on no carry
    case 0xd3: printf("OUT   #$%02x", code[1]); opbytes = 2; break; // Output
    case 0xd4: printf("CNC   $%02x%02x", code[2], code[1]); opbytes = 3; break; // Call on no carry
    case 0xd5: printf("PUSH  D"); break; // Push register pair D & E on stack
    case 0xd6: printf("SUI   #$%02x", code[1]); opbytes = 2; break; // Subtract immediate from A
    case 0xd7: printf("RST   2"); break; // Restart
    case 0xd8: printf("RC"); break; // Return on carry
    case 0xd9: printf("Op code %02x not defined", *code); break;
    case 0xda: printf("JC    $%02x%02x", code[2], code[1]); opbytes = 3; break; // Jump on carry
    case 0xdb: printf("IN    #$%02x", code[1]); opbytes = 2; break; // Input
    case 0xdc: printf("CC    $%02x%02x", code[2], code[1]); opbytes = 3; break; // Call on carry
    case 0xdd: printf("Op code %02x not defined", *code); break;
    case 0xde: printf("SBI   #$%02x", code[1]); opbytes = 2; break; // Subtract immediate from A with borrow
    case 0xdf: printf("RST   3"); break; // Restart
    case 0xe0: printf("RPO"); break; // Return on parity odd
    case 0xe1: printf("POP   H"); break; // Pop register pair H & L off stack
    case 0xe2: printf("JPO   $%02x%02x", code[2], code[1]); opbytes = 3; break; // Jump on parity odd
    case 0xe3: printf("XTHL"); break; // Exchange top of stack, H & L
    case 0xe4: printf("CPO   $%02x%02x", code[2], code[1]); opbytes = 3; break; // Call on parity odd
    case 0xe5: printf("PUSH  H"); break; // Push register pair H & L off stack
    case 0xe6: printf("ANI   #$%02x", code[1]); opbytes = 2; break; // And immediate with A
    case 0xe7: printf("RST   4"); break; // Restart
    case 0xe8: printf("RPE"); break; // Return on parity even
    case 0xe9: printf("PCHL"); break; // [Push?] H & L to program counter
    case 0xea: printf("JPE   $%02x%02x", code[2], code[1]); opbytes = 3; break; // Jump on parity even
    case 0xeb: printf("XCHG"); break; // Exchange D & E, H & L registers
    case 0xec: printf("CPE   $%02x%02x", code[2], code[1]); opbytes = 3; break; // Call on parity even
    case 0xed: printf("Op code %02x not defined", *code); break;
    case 0xee: printf("XRI   #$%02x", code[1]); opbytes = 2; break; // Exclusive or immediate with A
    case 0xef: printf("RST   5"); break; // Restart
    case 0xf0: printf("RP"); break; // Return on positive
    case 0xf1: printf("POP   PSW"); break; // Pop A and flags off stack
    case 0xf2: printf("JP    $%02x%02x", code[2], code[1]); opbytes = 3; break; // Jump on positive
    case 0xf3: printf("DI"); break; // Disable interrupt
    case 0xf4: printf("CP    $%02x%02x", code[2], code[1]); opbytes = 3; break; // Call on positive
    case 0xf5: printf("PUSH  PSW"); break; // Push A and flags onto stack
    case 0xf6: printf("ORI   #$%02x", code[1]); opbytes = 2; break; // Or immediate with A
    case 0xf7: printf("RST   6"); break; // Restart
    case 0xf8: printf("RM"); break; // Return on minus
    case 0xf9: printf("SPHL"); break; // [Push?] H & L to stack pointer
    case 0xfa: printf("JM    $%02x%02x", code[2], code[1]); opbytes = 3; break; // Jump on minus
    case 0xfb: printf("EI"); break; // Enable interrupts
    case 0xfc: printf("CM    $%02x%02x", code[2], code[1]); opbytes = 3; break; // Call on minus
    case 0xfd: printf("Op code %02x not defined", *code); break;
    case 0xfe: printf("CPI   #$%02x", code[1]); opbytes = 2; break; // Compare immediate with A
    case 0xff: printf("RST   7"); break; // Restart
    default:   printf("Op code %02x not valid, exiting!\n", *code); exit(2);
  }
  printf("\n");

  return opbytes;
}
