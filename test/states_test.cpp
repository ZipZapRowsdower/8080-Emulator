#include <iostream>
#include <string>

#include <gtest/gtest.h>

// TODO: Remove relative path
#include "../src/include/states.h"

// TODO: This is hardcoded into two locations!!!!!! BAD!!!!!
const int ROM_SIZE = 0x2000;

// File name for LoadMemoryFromFile test
char* test_file_name;

// Initialization values for state_2
// We put these as file-scope variables rather than scoped variables for use in
// constructor unit tests
const static std::vector<uint8_t> memory_2 = {0xBE, 0xEF, 0xCA, 0xCE};
const static uint8_t a_2 = 0x10;
const static uint8_t b_2 = 0x22;
const static uint8_t c_2 = 0x30;
const static uint8_t d_2 = 0x44;
const static uint8_t e_2 = 0x50;
const static uint8_t h_2 = 0x66;
const static uint8_t l_2 = 0x70;
const static uint16_t sp_2 = 0xDEAD;
const static uint16_t pc_2 = 0xBEEF;
const static uint8_t int_enable_2 = 0;
const static uint8_t z_2 = 0;
const static uint8_t s_2 = 1;
const static uint8_t p_2 = 1;
const static uint8_t cy_2 = 1;
const static uint8_t ac_2 = 0;
const static uint8_t pad_2 = 0;

struct State8080Test : testing::Test {
  State8080* state;
  State8080* state_2;
  ConditionCodes* cc_2;
  State8080* state_3;

  State8080Test()
  {
    cc_2 = new ConditionCodes;
    cc_2->z = z_2;
    cc_2->s = s_2;
    cc_2->p = p_2;
    cc_2->cy = cy_2;
    cc_2->ac = ac_2;
    cc_2->pad = pad_2;

    state = new State8080;
    state_2 = new State8080(memory_2, a_2, b_2, c_2, d_2, e_2, h_2, l_2,
                            sp_2, pc_2, int_enable_2, *cc_2);
    state_3 = new State8080;
  }

  virtual ~State8080Test()
  {
    delete state;
    delete state_2;
    delete cc_2;
    delete state_3;
  }
};

///////////////////////////////////////////////////////////////////
//  _____                 _                   _                  //
// /  __ \               | |                 | |                 //
// | /  \/ ___  _ __  ___| |_ _ __ _   _  ___| |_ ___  _ __ ___  //
// | |    / _ \| '_ \/ __| __| '__| | | |/ __| __/ _ \| '__/ __| //
// | \__/\ (_) | | | \__ \ |_| |  | |_| | (__| || (_) | |  \__ \ //
//  \____/\___/|_| |_|___/\__|_|   \__,_|\___|\__\___/|_|  |___/ //
///////////////////////////////////////////////////////////////////

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
  EXPECT_EQ(a_2, state_2->a);
  EXPECT_EQ(b_2, state_2->b);
  EXPECT_EQ(c_2, state_2->c);
  EXPECT_EQ(d_2, state_2->d);
  EXPECT_EQ(e_2, state_2->e);
  EXPECT_EQ(h_2, state_2->h);
  EXPECT_EQ(l_2, state_2->l);
  EXPECT_EQ(sp_2, state_2->sp);
  EXPECT_EQ(pc_2, state_2->pc);
  EXPECT_EQ(int_enable_2, state_2->int_enable);
  EXPECT_EQ(ROM_SIZE, state_2->memory.size());
  for (int i = 0; i < memory_2.size(); i++) {
    EXPECT_EQ(memory_2[i], state_2->memory[i]);
  }
  for (int i = memory_2.size(); i < ROM_SIZE; i++) {
    EXPECT_EQ(0x00, state_2->memory[i]);
  }
  EXPECT_EQ(z_2, state_2->cc.z);
  EXPECT_EQ(s_2, state_2->cc.s);
  EXPECT_EQ(p_2, state_2->cc.p);
  EXPECT_EQ(cy_2, state_2->cc.cy);
  EXPECT_EQ(ac_2, state_2->cc.ac);
  EXPECT_EQ(pad_2, state_2->cc.pad);
}

TEST_F(State8080Test, CopyInitialization) {
  State8080* my_state = new State8080(*state_2);

  EXPECT_EQ(state_2->a, my_state->a);
  EXPECT_EQ(state_2->b, my_state->b);
  EXPECT_EQ(state_2->c, my_state->c);
  EXPECT_EQ(state_2->d, my_state->d);
  EXPECT_EQ(state_2->e, my_state->e);
  EXPECT_EQ(state_2->h, my_state->h);
  EXPECT_EQ(state_2->l, my_state->l);
  EXPECT_EQ(state_2->sp, my_state->sp);
  EXPECT_EQ(state_2->pc, my_state->pc);
  EXPECT_EQ(state_2->memory.size(), my_state->memory.size());
  for (int i = 0; i < my_state->memory.size(); i++) {
    EXPECT_EQ(state_2->memory[i], my_state->memory[i]);
  }
  EXPECT_EQ(state_2->cc.z, my_state->cc.z);
  EXPECT_EQ(state_2->cc.s, my_state->cc.s);
  EXPECT_EQ(state_2->cc.p, my_state->cc.p);
  EXPECT_EQ(state_2->cc.cy, my_state->cc.cy);
  EXPECT_EQ(state_2->cc.ac, my_state->cc.ac);
  EXPECT_EQ(state_2->cc.pad, my_state->cc.pad);
  EXPECT_EQ(state_2->int_enable, my_state->int_enable);

  // Can this lead to a memory leak?  Google Test should always run the full
  // test, right?...
  delete(my_state);
}

TEST_F(State8080Test, StateFreed) {
  state_2->ClearState();
  EXPECT_EQ(0, state_2->a);
  EXPECT_EQ(0, state_2->b);
  EXPECT_EQ(0, state_2->c);
  EXPECT_EQ(0, state_2->d);
  EXPECT_EQ(0, state_2->e);
  EXPECT_EQ(0, state_2->h);
  EXPECT_EQ(0, state_2->l);
  EXPECT_EQ(0, state_2->sp);
  EXPECT_EQ(0, state_2->pc);
  EXPECT_EQ(ROM_SIZE, state_2->memory.size());
  for (int i = 0; i < ROM_SIZE; i++) {
    EXPECT_EQ(0x00, state_2->memory[i]);
  }
  EXPECT_EQ(0, state_2->cc.z);
  EXPECT_EQ(0, state_2->cc.s);
  EXPECT_EQ(0, state_2->cc.p);
  EXPECT_EQ(0, state_2->cc.cy);
  EXPECT_EQ(0, state_2->cc.ac);
  EXPECT_EQ(0, state_2->cc.pad);
  EXPECT_EQ(0, state_2->int_enable);
}

////////////////////////
//  _____    _______  //
// |_   _|  / /  _  | //
//   | |   / /| | | | //
//   | |  / / | | | | //
//  _| |_/ /  \ \_/ / //
//  \___/_/    \___/  //
//                    //
////////////////////////

TEST_F(State8080Test, ToString1) {
  std::string expected = "        C=0, P=0, S=0, Z=0\n        A $00 B $00 C $00 D $00 E $00 H $00 L $00 SP $0000 PC $0000\n";
  std::string actual = state->ToString();
  EXPECT_EQ(expected, actual);
}

TEST_F(State8080Test, ToString2) {
  std::string expected = "        C=1, P=1, S=1, Z=0\n        A $10 B $22 C $30 D $44 E $50 H $66 L $70 SP $dead PC $beef\n";
  std::string actual = state_2->ToString();
  EXPECT_EQ(expected, actual);
}

TEST_F(State8080Test, LoadMemoryFromBuffer) {
  unsigned char buffer[4] = {0x86, 0x75, 0x30, 0x90};
  state->LoadMemory(buffer, 4);

  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(buffer[i], state->memory[i]);
  }
}

TEST_F(State8080Test, LoadMemoryFromFile) {
  FILE *f = fopen(test_file_name, "rb");
  if (f==NULL)
  {
      printf("error: Couldn't open %s\n", test_file_name);
      exit(1);
  }

  // Duplication
  state->LoadMemory(f);
  unsigned char results[9] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x09, 0x08};
  for (int i = 0; i < 9; i++) {
    EXPECT_EQ(results[i], state->memory[i]);
  }
}

////////////////////////////////////////////////////
//  _____                      _                  //
// |  _  |                    | |                 //
// | | | |_ __   ___ _ __ __ _| |_ ___  _ __ ___  //
// | | | | '_ \ / _ \ '__/ _` | __/ _ \| '__/ __| //
// \ \_/ / |_) |  __/ | | (_| | || (_) | |  \__ \ //
//  \___/| .__/ \___|_|  \__,_|\__\___/|_|  |___/ //
//       | |                                      //
//       |_|                                      //
////////////////////////////////////////////////////

TEST_F(State8080Test, StreamInsertionOverload) {
  std::string expected = "        C=1, P=1, S=1, Z=0\n        A $10 B $22 C $30 D $44 E $50 H $66 L $70 SP $dead PC $beef\n";

  std::ostringstream buffer;
  buffer << *state_2;

  std::string actual = buffer.str();
  EXPECT_EQ(expected, actual);
}

// TODO: The following two tests are circular
TEST_F(State8080Test, EqualOperatorOverload) {
  *state = *state_2;

  EXPECT_EQ(true, state->operator==(*state_2));
  EXPECT_EQ(true, state_2->operator==(*state));
}

TEST_F(State8080Test, EqualityOperatorOverload) {
  *state_3 = *state_2;

  // We use the function call here instead of the operator because Google Test,
  // in its infinite wisdom, redefines the == operator
  EXPECT_EQ(true, state->operator==(*state));
  EXPECT_EQ(true, state_2->operator==(*state_2));
  EXPECT_EQ(true, state_3->operator==(*state_3));
  EXPECT_EQ(false, state->operator==(*state_2));
  EXPECT_EQ(false, state->operator==(*state_3));
  EXPECT_EQ(true, state_2->operator==(*state_3));
}

TEST_F(State8080Test, NotEqualityOperatorOverload) {
  *state_3 = *state_2;

  EXPECT_EQ(false, state->operator!=(*state));
  EXPECT_EQ(false, state_2->operator!=(*state_2));
  EXPECT_EQ(false, state_3->operator!=(*state_3));
  EXPECT_EQ(true, state->operator!=(*state_2));
  EXPECT_EQ(true, state->operator!=(*state_3));
  EXPECT_EQ(false, state_2->operator!=(*state_3));
}

////////////////////////////
// ___  ___      _        //
// |  \/  |     (_)       //
// | .  . | __ _ _ _ __   //
// | |\/| |/ _` | | '_ \  //
// | |  | | (_| | | | | | //
// \_|  |_/\__,_|_|_| |_| //
//                        //
////////////////////////////

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  test_file_name = argv[1];
  return RUN_ALL_TESTS();
}
