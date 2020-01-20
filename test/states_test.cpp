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
const static uint8_t int_enable_2 = 1;
const static uint8_t z_2 = 1;
const static uint8_t s_2 = 1;
const static uint8_t p_2 = 1;
const static uint8_t cy_2 = 1;
const static uint8_t ac_2 = 1;
const static uint8_t pad_2 = 1;

struct State8080Test : testing::Test {
  State8080* state;
  State8080* state_2;
  State8080* state_3;
  ConditionCodes* cc_2;
  Registers* regs_2;

  State8080Test()
  {
    cc_2 = new ConditionCodes(z_2, s_2, p_2, cy_2, ac_2, pad_2);
    regs_2 = new Registers(a_2, b_2, c_2, d_2, e_2, h_2, l_2, sp_2, pc_2);

    state = new State8080;
    state_2 = new State8080(memory_2, *regs_2, int_enable_2, *cc_2);
    state_3 = new State8080;
  }

  virtual ~State8080Test()
  {
    delete state;
    delete state_2;
    delete state_3;
    delete cc_2;
    delete regs_2;
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
  EXPECT_EQ(ROM_SIZE, state->memory.size());
  for (unsigned int i = 0; i < ROM_SIZE; i++) {
    EXPECT_EQ(0x00, state->memory[i]);
  }
  EXPECT_EQ(true, state->regs.IsClear());
  EXPECT_EQ(0, state->int_enable);
  EXPECT_EQ(true, state->cc.IsClear());
}

TEST_F(State8080Test, FullInitialization) {
  EXPECT_EQ(ROM_SIZE, state_2->memory.size());
  for (unsigned int i = 0; i < memory_2.size(); i++) {
    EXPECT_EQ(memory_2[i], state_2->memory[i]);
  }
  for (unsigned int i = memory_2.size(); i < ROM_SIZE; i++) {
    EXPECT_EQ(0x00, state_2->memory[i]);
  }
  EXPECT_EQ(true, regs_2->operator==(state_2->regs));
  EXPECT_EQ(int_enable_2, state_2->int_enable);
  EXPECT_EQ(true, cc_2->operator==(state_2->cc));
}

TEST_F(State8080Test, CopyInitialization) {
  State8080* my_state = new State8080(*state_2);

  EXPECT_EQ(state_2->memory.size(), my_state->memory.size());
  for (unsigned int i = 0; i < my_state->memory.size(); i++) {
    EXPECT_EQ(state_2->memory[i], my_state->memory[i]);
  }
  EXPECT_EQ(true, state_2->regs.operator==(my_state->regs));
  EXPECT_EQ(state_2->int_enable, my_state->int_enable);
  EXPECT_EQ(true, state_2->cc.operator==(my_state->cc));

  // Can this lead to a memory leak?  Google Test should always run the full
  // test, right?...
  delete(my_state);
}

TEST_F(State8080Test, StateFreed) {
  state_2->ClearState();
  EXPECT_EQ(ROM_SIZE, state_2->memory.size());
  for (unsigned int i = 0; i < ROM_SIZE; i++) {
    EXPECT_EQ(0x00, state_2->memory[i]);
  }
  EXPECT_EQ(true, state_2->regs.IsClear());
  EXPECT_EQ(0, state_2->int_enable);
  EXPECT_EQ(true, state_2->cc.IsClear());
}

//////////////////////////////////////////////////
//   ___                                        //
//  / _ \                                       //
// / /_\ \ ___ ___ ___  ___ ___  ___  _ __ ___  //
// |  _  |/ __/ __/ _ \/ __/ __|/ _ \| '__/ __| //
// | | | | (_| (_|  __/\__ \__ \ (_) | |  \__ \ //
// \_| |_/\___\___\___||___/___/\___/|_|  |___/ //
//                                              //
//////////////////////////////////////////////////

TEST_F(State8080Test, AllAccessors) {
  EXPECT_EQ(a_2, state_2->get_a());
  EXPECT_EQ(b_2, state_2->get_b());
  EXPECT_EQ(c_2, state_2->get_c());
  EXPECT_EQ(d_2, state_2->get_d());
  EXPECT_EQ(e_2, state_2->get_e());
  EXPECT_EQ(h_2, state_2->get_h());
  EXPECT_EQ(l_2, state_2->get_l());
  EXPECT_EQ(sp_2, state_2->get_sp());
  EXPECT_EQ(pc_2, state_2->get_pc());
  EXPECT_EQ(z_2, state_2->get_z());
  EXPECT_EQ(s_2, state_2->get_s());
  EXPECT_EQ(p_2, state_2->get_p());
  EXPECT_EQ(cy_2, state_2->get_cy());
  EXPECT_EQ(ac_2, state_2->get_ac());
  EXPECT_EQ(pad_2, state_2->get_pad());
}

///////////////////////////////////////////////
// ___  ___      _        _                  //
// |  \/  |     | |      | |                 //
// | .  . |_   _| |_ __ _| |_ ___  _ __ ___  //
// | |\/| | | | | __/ _` | __/ _ \| '__/ __| //
// | |  | | |_| | || (_| | || (_) | |  \__ \ //
// \_|  |_/\__,_|\__\__,_|\__\___/|_|  |___/ //
//                                           //
///////////////////////////////////////////////

TEST_F(State8080Test, AllMutators) {
  state_3->set_a(a_2);
  state_3->set_b(b_2);
  state_3->set_c(c_2);
  state_3->set_d(d_2);
  state_3->set_e(e_2);
  state_3->set_h(h_2);
  state_3->set_l(l_2);
  state_3->set_sp(sp_2);
  state_3->set_pc(pc_2);
  state_3->set_z(z_2);
  state_3->set_s(s_2);
  state_3->set_p(p_2);
  state_3->set_cy(cy_2);
  state_3->set_ac(ac_2);
  state_3->set_pad(pad_2);

  EXPECT_EQ(a_2, state_3->get_a());
  EXPECT_EQ(b_2, state_3->get_b());
  EXPECT_EQ(c_2, state_3->get_c());
  EXPECT_EQ(d_2, state_3->get_d());
  EXPECT_EQ(e_2, state_3->get_e());
  EXPECT_EQ(h_2, state_3->get_h());
  EXPECT_EQ(l_2, state_3->get_l());
  EXPECT_EQ(sp_2, state_3->get_sp());
  EXPECT_EQ(pc_2, state_3->get_pc());
  EXPECT_EQ(z_2, state_3->get_z());
  EXPECT_EQ(s_2, state_3->get_s());
  EXPECT_EQ(p_2, state_3->get_p());
  EXPECT_EQ(cy_2, state_3->get_cy());
  EXPECT_EQ(ac_2, state_3->get_ac());
  EXPECT_EQ(pad_2, state_3->get_pad());
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
  std::string expected = "        C=1, P=1, S=1, Z=1\n        A $10 B $22 C $30 D $44 E $50 H $66 L $70 SP $dead PC $beef\n";
  std::string actual = state_2->ToString();
  EXPECT_EQ(expected, actual);
}

TEST_F(State8080Test, LoadMemoryFromBuffer) {
  unsigned char buffer[4] = {0x86, 0x75, 0x30, 0x90};
  state->LoadMemory(buffer, 4);

  for (unsigned int i = 0; i < 4; i++) {
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
  for (unsigned int i = 0; i < 9; i++) {
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
  std::string expected = "        C=1, P=1, S=1, Z=1\n        A $10 B $22 C $30 D $44 E $50 H $66 L $70 SP $dead PC $beef\n";

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
  EXPECT_EQ(false, state_2->operator==(*state));
  EXPECT_EQ(false, state->operator==(*state_3));
  EXPECT_EQ(false, state_3->operator==(*state));
  EXPECT_EQ(true, state_2->operator==(*state_3));
  EXPECT_EQ(true, state_3->operator==(*state_2));
}

TEST_F(State8080Test, NotEqualityOperatorOverload) {
  *state_3 = *state_2;

  EXPECT_EQ(false, state->operator!=(*state));
  EXPECT_EQ(false, state_2->operator!=(*state_2));
  EXPECT_EQ(false, state_3->operator!=(*state_3));
  EXPECT_EQ(true, state->operator!=(*state_2));
  EXPECT_EQ(true, state_2->operator!=(*state));
  EXPECT_EQ(true, state->operator!=(*state_3));
  EXPECT_EQ(true, state_3->operator!=(*state));
  EXPECT_EQ(false, state_2->operator!=(*state_3));
  EXPECT_EQ(false, state_3->operator!=(*state_2));
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
