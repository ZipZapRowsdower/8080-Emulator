#include <iostream>
#include <string>

#include <gtest/gtest.h>

// TODO: Remove relative path
#include "../src/include/states.h"

// TODO: This is hardcoded into two locations!!!!!! BAD!!!!!
const int ROM_SIZE = 0x2000;

// File name for LoadMemoryFromFile test
char* test_file_name;

struct State8080Test : testing::Test {
  State8080* state;
  State8080* state2;
  State8080* state3;

  State8080Test()
  {
    state = new State8080;
    state2 = new State8080;
    state3 = new State8080;
  }

  virtual ~State8080Test()
  {
    delete state;
    delete state2;
    delete state3;
  }
};

TEST_F(State8080Test, DefaultInitialization) {
  EXPECT_EQ(0, state->a);
  EXPECT_EQ(0, state->b);
  EXPECT_EQ(0, state->c);
  EXPECT_EQ(0, state->d);
  EXPECT_EQ(0, state->e);
  EXPECT_EQ(0, state->h);
  EXPECT_EQ(0, state->l);
  EXPECT_EQ(0, state->sp);
  EXPECT_EQ(0, state->pc);
  EXPECT_EQ(ROM_SIZE, state->memory.size());
  for (int i = 0; i < ROM_SIZE; i++) {
    EXPECT_EQ(0x00, state->memory[i]);
  }
  EXPECT_EQ(0, state->cc.z);
  EXPECT_EQ(0, state->cc.s);
  EXPECT_EQ(0, state->cc.p);
  EXPECT_EQ(0, state->cc.cy);
  EXPECT_EQ(0, state->cc.ac);
  EXPECT_EQ(0, state->cc.pad);
  EXPECT_EQ(0, state->int_enable);
}

TEST_F(State8080Test, FullInitialization) {
  std::vector<uint8_t> memory = {0xBE, 0xEF, 0xCA, 0xCE};
  uint8_t a = 0x10;
  uint8_t b = 0x22;
  uint8_t c = 0x30;
  uint8_t d = 0x44;
  uint8_t e = 0x50;
  uint8_t h = 0x66;
  uint8_t l = 0x70;
  uint16_t sp = 0xDEAD;
  uint16_t pc = 0xBEEF;
  uint8_t int_enable = 0;
  ConditionCodes cc;
  cc.z = 0;
  cc.s = 1;
  cc.p = 1;
  cc.cy = 1;
  cc.ac = 0;
  cc.pad = 0;

  State8080* my_state = new State8080(memory, a, b, c, d, e, h, l, sp, pc,
                                      int_enable, cc);

  EXPECT_EQ(ROM_SIZE, my_state->memory.size());
  for (int i = 0; i < memory.size(); i++) {
    EXPECT_EQ(memory[i], my_state->memory[i]);
  }
  EXPECT_EQ(a, my_state->a);
  EXPECT_EQ(b, my_state->b);
  EXPECT_EQ(c, my_state->c);
  EXPECT_EQ(d, my_state->d);
  EXPECT_EQ(e, my_state->e);
  EXPECT_EQ(h, my_state->h);
  EXPECT_EQ(l, my_state->l);
  EXPECT_EQ(sp, my_state->sp);
  EXPECT_EQ(pc, my_state->pc);
  EXPECT_EQ(0, my_state->int_enable);
  for (int i = memory.size(); i < ROM_SIZE; i++) {
    EXPECT_EQ(0x00, my_state->memory[i]);
  }
  EXPECT_EQ(cc.z, my_state->cc.z);
  EXPECT_EQ(cc.s, my_state->cc.s);
  EXPECT_EQ(cc.p, my_state->cc.p);
  EXPECT_EQ(cc.cy, my_state->cc.cy);
  EXPECT_EQ(cc.ac, my_state->cc.ac);
  EXPECT_EQ(cc.pad, my_state->cc.pad);

  delete(my_state);
}

TEST_F(State8080Test, CopyInitialization) {
  std::vector<uint8_t> memory = {0xBE, 0xEF, 0xCA, 0xCE};
  state->a = 0x10;
  state->b = 0x22;
  state->c = 0x30;
  state->d = 0x44;
  state->e = 0x50;
  state->h = 0x66;
  state->l = 0x70;
  state->sp = 0xDEAD;
  state->pc = 0xBEEF;
  for (int i = 0; i < memory.size(); i++) {
    state->memory[i] = memory[i];
  }
  state->cc.z = 0;
  state->cc.s = 1;
  state->cc.p = 1;
  state->cc.cy = 1;
  state->cc.ac = 0;
  state->cc.pad = 0;
  state->int_enable = 0;

  State8080* my_state = new State8080(*state);

  EXPECT_EQ(0x10, my_state->a);
  EXPECT_EQ(0x22, my_state->b);
  EXPECT_EQ(0x30, my_state->c);
  EXPECT_EQ(0x44, my_state->d);
  EXPECT_EQ(0x50, my_state->e);
  EXPECT_EQ(0x66, my_state->h);
  EXPECT_EQ(0x70, my_state->l);
  EXPECT_EQ(0xDEAD, my_state->sp);
  EXPECT_EQ(0xBEEF, my_state->pc);
  EXPECT_EQ(ROM_SIZE, my_state->memory.size());
  for (int i = 0; i < memory.size(); i++) {
    EXPECT_EQ(memory[i], my_state->memory[i]);
  }
  for (int i = memory.size(); i < ROM_SIZE; i++) {
    EXPECT_EQ(0x00, my_state->memory[i]);
  }
  EXPECT_EQ(0, my_state->cc.z);
  EXPECT_EQ(1, my_state->cc.s);
  EXPECT_EQ(1, my_state->cc.p);
  EXPECT_EQ(1, my_state->cc.cy);
  EXPECT_EQ(0, my_state->cc.ac);
  EXPECT_EQ(0, my_state->cc.pad);
  EXPECT_EQ(0, my_state->int_enable);

  delete(my_state);
}

TEST_F(State8080Test, ToString1) {
  std::string expected = "        C=0, P=0, S=0, Z=0\n        A $00 B $00 C $00 D $00 E $00 H $00 L $00 SP $0000 PC $0000\n";
  std::string actual = state->ToString();
  EXPECT_EQ(expected, actual);
}

TEST_F(State8080Test, ToString2) {
  state->a = 0x10;
  state->b = 0x22;
  state->c = 0x30;
  state->d = 0x44;
  state->e = 0x50;
  state->h = 0x66;
  state->l = 0x70;
  state->sp = 0xDEAD;
  state->pc = 0xBEEF;
  state->cc.z = 0;
  state->cc.s = 1;
  state->cc.p = 1;
  state->cc.cy = 1;
  state->cc.ac = 0;
  state->cc.pad = 0;
  std::string expected = "        C=1, P=1, S=1, Z=0\n        A $10 B $22 C $30 D $44 E $50 H $66 L $70 SP $dead PC $beef\n";
  std::string actual = state->ToString();
  EXPECT_EQ(expected, actual);
}

TEST_F(State8080Test, StreamInsertionOverload) {
  state->a = 0x10;
  state->b = 0x22;
  state->c = 0x30;
  state->d = 0x44;
  state->e = 0x50;
  state->h = 0x66;
  state->l = 0x70;
  state->sp = 0xDEAD;
  state->pc = 0xBEEF;
  state->cc.z = 0;
  state->cc.s = 1;
  state->cc.p = 1;
  state->cc.cy = 1;
  state->cc.ac = 0;
  state->cc.pad = 0;
  std::string expected = "        C=1, P=1, S=1, Z=0\n        A $10 B $22 C $30 D $44 E $50 H $66 L $70 SP $dead PC $beef\n";

  std::ostringstream buffer;
  buffer << *state;

  std::string actual = buffer.str();
  EXPECT_EQ(expected, actual);
}

TEST_F(State8080Test, EqualsOverload) {
  // State 1 is uninitialized, State 2 and 3 are different objects but are
  // functionally equivalent
  std::vector<uint8_t> memory = {0xBE, 0xEF, 0xCA, 0xCE};
  state2->a = 0x10;
  state2->b = 0x22;
  state2->c = 0x30;
  state2->d = 0x44;
  state2->e = 0x50;
  state2->h = 0x66;
  state2->l = 0x70;
  state2->sp = 0xDEAD;
  state2->pc = 0xBEEF;
  for (int i = 0; i < memory.size(); i++) {
    state2->memory[i] = memory[i];
  }
  state2->cc.z = 0;
  state2->cc.s = 1;
  state2->cc.p = 1;
  state2->cc.cy = 1;
  state2->cc.ac = 0;
  state2->cc.pad = 0;

  state3->a = 0x10;
  state3->b = 0x22;
  state3->c = 0x30;
  state3->d = 0x44;
  state3->e = 0x50;
  state3->h = 0x66;
  state3->l = 0x70;
  state3->sp = 0xDEAD;
  state3->pc = 0xBEEF;
  for (int i = 0; i < memory.size(); i++) {
    state3->memory[i] = memory[i];
  }
  state3->cc.z = 0;
  state3->cc.s = 1;
  state3->cc.p = 1;
  state3->cc.cy = 1;
  state3->cc.ac = 0;
  state3->cc.pad = 0;

  // We use the function call here instead of the operator because Google Test,
  // in its infinite wisdom, redefines the == operator
  EXPECT_EQ(true, state->operator==(*state));
  EXPECT_EQ(true, state2->operator==(*state2));
  EXPECT_EQ(true, state3->operator==(*state3));
  EXPECT_EQ(false, state->operator==(*state2));
  EXPECT_EQ(false, state->operator==(*state3));
  EXPECT_EQ(true, state2->operator==(*state3));
}

TEST_F(State8080Test, NotEqualsOverload) {
  std::vector<uint8_t> memory = {0xBE, 0xEF, 0xCA, 0xCE};
  state2->a = 0x10;
  state2->b = 0x22;
  state2->c = 0x30;
  state2->d = 0x44;
  state2->e = 0x50;
  state2->h = 0x66;
  state2->l = 0x70;
  state2->sp = 0xDEAD;
  state2->pc = 0xBEEF;
  for (int i = 0; i < memory.size(); i++) {
    state2->memory[i] = memory[i];
  }
  state2->cc.z = 0;
  state2->cc.s = 1;
  state2->cc.p = 1;
  state2->cc.cy = 1;
  state2->cc.ac = 0;
  state2->cc.pad = 0;

  state3->a = 0x10;
  state3->b = 0x22;
  state3->c = 0x30;
  state3->d = 0x44;
  state3->e = 0x50;
  state3->h = 0x66;
  state3->l = 0x70;
  state3->sp = 0xDEAD;
  state3->pc = 0xBEEF;
  for (int i = 0; i < memory.size(); i++) {
    state3->memory[i] = memory[i];
  }
  state3->cc.z = 0;
  state3->cc.s = 1;
  state3->cc.p = 1;
  state3->cc.cy = 1;
  state3->cc.ac = 0;
  state3->cc.pad = 0;

  EXPECT_EQ(false, state->operator!=(*state));
  EXPECT_EQ(false, state2->operator!=(*state2));
  EXPECT_EQ(false, state3->operator!=(*state3));
  EXPECT_EQ(true, state->operator!=(*state2));
  EXPECT_EQ(true, state->operator!=(*state3));
  EXPECT_EQ(false, state2->operator!=(*state3));
}

TEST_F(State8080Test, EqualOperatorOverload) {
  std::vector<uint8_t> memory = {0xBE, 0xEF, 0xCA, 0xCE};
  state->a = 0x10;
  state->b = 0x22;
  state->c = 0x30;
  state->d = 0x44;
  state->e = 0x50;
  state->h = 0x66;
  state->l = 0x70;
  state->sp = 0xDEAD;
  state->pc = 0xBEEF;
  for (int i = 0; i < memory.size(); i++) {
    state3->memory[i] = memory[i];
  }
  state->cc.z = 0;
  state->cc.s = 1;
  state->cc.p = 1;
  state->cc.cy = 1;
  state->cc.ac = 0;
  state->cc.pad = 0;

  *state2 = *state;

  EXPECT_EQ(true, state->operator==(*state2));
  EXPECT_EQ(true, state2->operator==(*state));
}

TEST_F(State8080Test, LoadMemoryFromBuffer) {
  unsigned char buffer[4] = {0x86, 0x75, 0x30, 0x90};
  state->LoadMemory(buffer, 4);

  EXPECT_EQ(buffer[0], state->memory[0]);
  EXPECT_EQ(buffer[1], state->memory[1]);
  EXPECT_EQ(buffer[2], state->memory[2]);
  EXPECT_EQ(buffer[3], state->memory[3]);
}

TEST_F(State8080Test, LoadMemoryFromFile) {
  FILE *f = fopen(test_file_name, "rb");
  if (f==NULL)
  {
      printf("error: Couldn't open %s\n", test_file_name);
      exit(1);
  }

  state->LoadMemory(f);
  unsigned char results[9] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x09, 0x08};
  EXPECT_EQ(results[0], state->memory[0]);
  EXPECT_EQ(results[1], state->memory[1]);
  EXPECT_EQ(results[2], state->memory[2]);
  EXPECT_EQ(results[3], state->memory[3]);
  EXPECT_EQ(results[4], state->memory[4]);
  EXPECT_EQ(results[5], state->memory[5]);
  EXPECT_EQ(results[6], state->memory[6]);
  EXPECT_EQ(results[7], state->memory[7]);
  EXPECT_EQ(results[8], state->memory[8]);
}

TEST_F(State8080Test, StateFreed) {
  state->ClearState();
  EXPECT_EQ(0, state->a);
  EXPECT_EQ(0, state->b);
  EXPECT_EQ(0, state->c);
  EXPECT_EQ(0, state->d);
  EXPECT_EQ(0, state->e);
  EXPECT_EQ(0, state->h);
  EXPECT_EQ(0, state->l);
  EXPECT_EQ(0, state->sp);
  EXPECT_EQ(0, state->pc);
  EXPECT_EQ(ROM_SIZE, state->memory.size());
  for (int i = 0; i < ROM_SIZE; i++) {
    EXPECT_EQ(0x00, state->memory[i]);
  }
  EXPECT_EQ(0, state->cc.z);
  EXPECT_EQ(0, state->cc.s);
  EXPECT_EQ(0, state->cc.p);
  EXPECT_EQ(0, state->cc.cy);
  EXPECT_EQ(0, state->cc.ac);
  EXPECT_EQ(0, state->cc.pad);
  EXPECT_EQ(0, state->int_enable);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  test_file_name = argv[1];
  return RUN_ALL_TESTS();
}
