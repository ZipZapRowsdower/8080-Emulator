#include <gtest/gtest.h>

// TODO: Remove relative path
#include "../src/include/processor.h"

const static uint8_t a_2 = 0x10;
const static uint8_t b_2 = 0x22;
const static uint8_t c_2 = 0x30;
const static uint8_t d_2 = 0x44;
const static uint8_t e_2 = 0x50;
const static uint8_t h_2 = 0x66;
const static uint8_t l_2 = 0x70;
const static uint16_t sp_2 = 0xDEAD;
const static uint16_t pc_2 = 0xBEEF;
const static uint8_t z_2 = 1;
const static uint8_t s_2 = 1;
const static uint8_t p_2 = 1;
const static uint8_t cy_2 = 1;
const static uint8_t ac_2 = 1;
const static uint8_t pad_2 = 1;

struct ConditionCodesTest : testing::Test {
  ConditionCodes* cc_1;
  ConditionCodes* cc_2;
  ConditionCodes* cc_3;

  ConditionCodesTest() {
    cc_1 = new ConditionCodes;
    cc_2 = new ConditionCodes(z_2, s_2, p_2, cy_2, ac_2, pad_2);
    cc_3 = new ConditionCodes;
  }

  virtual ~ConditionCodesTest() {
    delete cc_1;
    delete cc_2;
    delete cc_3;
  }
};

struct RegistersTest : testing::Test {
  Registers* registers_1;
  Registers* registers_2;
  Registers* registers_3;

  RegistersTest() {
    registers_1 = new Registers;
    registers_2 = new Registers(a_2, b_2, c_2, d_2, e_2, h_2, l_2, sp_2, pc_2);
    registers_3 = new Registers;
  }

  virtual ~RegistersTest() {
    delete registers_1;
    delete registers_2;
    delete registers_3;
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

TEST_F(ConditionCodesTest, DefaultConditionCodeInitialization) {
  EXPECT_EQ(0, cc_1->z);
  EXPECT_EQ(0, cc_1->s);
  EXPECT_EQ(0, cc_1->p);
  EXPECT_EQ(0, cc_1->cy);
  EXPECT_EQ(0, cc_1->ac);
  EXPECT_EQ(0, cc_1->pad);
}

TEST_F(ConditionCodesTest, FullConditionCodeInitialization) {
  EXPECT_EQ(z_2, cc_2->z);
  EXPECT_EQ(s_2, cc_2->s);
  EXPECT_EQ(p_2, cc_2->p);
  EXPECT_EQ(cy_2, cc_2->cy);
  EXPECT_EQ(ac_2, cc_2->ac);
  EXPECT_EQ(pad_2, cc_2->pad);
}

TEST_F(ConditionCodesTest, CopyConstructorInitialization) {
  ConditionCodes* my_cc = new ConditionCodes(*cc_2);

  EXPECT_EQ(cc_2->z, my_cc->z);
  EXPECT_EQ(cc_2->s, my_cc->s);
  EXPECT_EQ(cc_2->p, my_cc->p);
  EXPECT_EQ(cc_2->cy, my_cc->cy);
  EXPECT_EQ(cc_2->ac, my_cc->ac);
  EXPECT_EQ(cc_2->pad, my_cc->pad);

  delete my_cc;
}

TEST_F(RegistersTest, DefaultRegistersInitialization) {
  EXPECT_EQ(0x00, registers_1->a);
  EXPECT_EQ(0x00, registers_1->b);
  EXPECT_EQ(0x00, registers_1->c);
  EXPECT_EQ(0x00, registers_1->d);
  EXPECT_EQ(0x00, registers_1->e);
  EXPECT_EQ(0x00, registers_1->h);
  EXPECT_EQ(0x00, registers_1->l);
  EXPECT_EQ(0x0000, registers_1->sp);
  EXPECT_EQ(0x0000, registers_1->pc);
}

TEST_F(RegistersTest, FullRegistersInitialization) {
  EXPECT_EQ(a_2, registers_2->a);
  EXPECT_EQ(b_2, registers_2->b);
  EXPECT_EQ(c_2, registers_2->c);
  EXPECT_EQ(d_2, registers_2->d);
  EXPECT_EQ(e_2, registers_2->e);
  EXPECT_EQ(h_2, registers_2->h);
  EXPECT_EQ(l_2, registers_2->l);
  EXPECT_EQ(sp_2, registers_2->sp);
  EXPECT_EQ(pc_2, registers_2->pc);
}

TEST_F(RegistersTest, CopyConstructorInitialization) {
  Registers* my_registers = new Registers(*registers_2);

  EXPECT_EQ(registers_2->a, my_registers->a);
  EXPECT_EQ(registers_2->b, my_registers->b);
  EXPECT_EQ(registers_2->c, my_registers->c);
  EXPECT_EQ(registers_2->d, my_registers->d);
  EXPECT_EQ(registers_2->e, my_registers->e);
  EXPECT_EQ(registers_2->h, my_registers->h);
  EXPECT_EQ(registers_2->l, my_registers->l);
  EXPECT_EQ(registers_2->sp, my_registers->sp);
  EXPECT_EQ(registers_2->pc, my_registers->pc);

  delete my_registers;
}

/////////////////////////////////
//  _   _ _   _ _ _ _          //
// | | | | | (_) (_) |         //
// | | | | |_ _| |_| |_ _   _  //
// | | | | __| | | | __| | | | //
// | |_| | |_| | | | |_| |_| | //
//  \___/ \__|_|_|_|\__|\__, | //
//                       __/ | //
//                      |___/  //
/////////////////////////////////

TEST_F(ConditionCodesTest, Clear) {
  cc_2->Clear();

  EXPECT_EQ(true, cc_1->operator==(*cc_2));
}

TEST_F(ConditionCodesTest, IsClear) {
  EXPECT_EQ(true, cc_1->IsClear());
  EXPECT_EQ(false, cc_2->IsClear());
}

TEST_F(RegistersTest, Clear) {
  registers_2->Clear();

  EXPECT_EQ(true, registers_1->operator==(*registers_2));
}

TEST_F(RegistersTest, IsClear) {
  EXPECT_EQ(true, registers_1->IsClear());
  EXPECT_EQ(false, registers_2->IsClear());
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

TEST_F(ConditionCodesTest, ToString) {
  std::string expected = "        C=1, P=1, S=1, Z=1\n";
  std::string actual = cc_2->ToString();
  EXPECT_EQ(expected, actual);
}

TEST_F(RegistersTest, ToString) {
  std::string expected = "        A $10 B $22 C $30 D $44 E $50 H $66 L $70 SP $dead PC $beef\n";
  std::string actual = registers_2->ToString();
  EXPECT_EQ(expected, actual);
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

TEST_F(ConditionCodesTest, StreamInsertionOverload) {
  std::string expected = "        C=1, P=1, S=1, Z=1\n";

  std::ostringstream buffer;
  buffer << *cc_2;

  std::string actual = buffer.str();
  EXPECT_EQ(expected, actual);
}

TEST_F(ConditionCodesTest, EqualsOperatorOverload) {
  *cc_3 = *cc_2;

  EXPECT_EQ(cc_3->z, cc_2->z);
  EXPECT_EQ(cc_3->s, cc_2->s);
  EXPECT_EQ(cc_3->p, cc_2->p);
  EXPECT_EQ(cc_3->cy, cc_2->cy);
  EXPECT_EQ(cc_3->ac, cc_2->ac);
  EXPECT_EQ(cc_3->pad, cc_2->pad);
}

TEST_F(ConditionCodesTest, EqualityOperatorOverload) {
  *cc_3 = *cc_2;

  EXPECT_EQ(true, cc_1->operator==(*cc_1));
  EXPECT_EQ(true, cc_2->operator==(*cc_2));
  EXPECT_EQ(true, cc_3->operator==(*cc_3));
  EXPECT_EQ(false, cc_1->operator==(*cc_2));
  EXPECT_EQ(false, cc_2->operator==(*cc_1));
  EXPECT_EQ(false, cc_1->operator==(*cc_3));
  EXPECT_EQ(false, cc_3->operator==(*cc_1));
  EXPECT_EQ(true, cc_2->operator==(*cc_3));
  EXPECT_EQ(true, cc_3->operator==(*cc_2));
}

TEST_F(ConditionCodesTest, NotEqualityOperatorOverload) {
  *cc_3 = *cc_2;

  EXPECT_EQ(false, cc_1->operator!=(*cc_1));
  EXPECT_EQ(false, cc_2->operator!=(*cc_2));
  EXPECT_EQ(false, cc_3->operator!=(*cc_3));
  EXPECT_EQ(true, cc_1->operator!=(*cc_2));
  EXPECT_EQ(true, cc_2->operator!=(*cc_1));
  EXPECT_EQ(true, cc_1->operator!=(*cc_3));
  EXPECT_EQ(true, cc_3->operator!=(*cc_1));
  EXPECT_EQ(false, cc_2->operator!=(*cc_3));
  EXPECT_EQ(false, cc_3->operator!=(*cc_2));
}

TEST_F(RegistersTest, StreamInsertionOverload) {
  std::string expected = "        A $10 B $22 C $30 D $44 E $50 H $66 L $70 SP $dead PC $beef\n";

  std::ostringstream buffer;
  buffer << *registers_2;

  std::string actual = buffer.str();
  EXPECT_EQ(expected, actual);
}

TEST_F(RegistersTest, EqualsOperatorOverload) {
  *registers_3 = *registers_2;

  EXPECT_EQ(registers_3->a, registers_2->a);
  EXPECT_EQ(registers_3->b, registers_2->b);
  EXPECT_EQ(registers_3->c, registers_2->c);
  EXPECT_EQ(registers_3->d, registers_2->d);
  EXPECT_EQ(registers_3->e, registers_2->e);
  EXPECT_EQ(registers_3->h, registers_2->h);
  EXPECT_EQ(registers_3->l, registers_2->l);
  EXPECT_EQ(registers_3->sp, registers_2->sp);
  EXPECT_EQ(registers_3->pc, registers_2->pc);
}

TEST_F(RegistersTest, EqualityOperatorOverload) {
  *registers_3 = *registers_2;

  EXPECT_EQ(true, registers_1->operator==(*registers_1));
  EXPECT_EQ(true, registers_2->operator==(*registers_2));
  EXPECT_EQ(true, registers_3->operator==(*registers_3));
  EXPECT_EQ(false, registers_1->operator==(*registers_2));
  EXPECT_EQ(false, registers_2->operator==(*registers_1));
  EXPECT_EQ(false, registers_1->operator==(*registers_3));
  EXPECT_EQ(false, registers_3->operator==(*registers_1));
  EXPECT_EQ(true, registers_2->operator==(*registers_3));
  EXPECT_EQ(true, registers_3->operator==(*registers_2));
}

TEST_F(RegistersTest, NotEqualityOperatorOverload) {
  *registers_3 = *registers_2;

  EXPECT_EQ(false, registers_1->operator!=(*registers_1));
  EXPECT_EQ(false, registers_2->operator!=(*registers_2));
  EXPECT_EQ(false, registers_3->operator!=(*registers_3));
  EXPECT_EQ(true, registers_1->operator!=(*registers_2));
  EXPECT_EQ(true, registers_2->operator!=(*registers_1));
  EXPECT_EQ(true, registers_1->operator!=(*registers_3));
  EXPECT_EQ(true, registers_3->operator!=(*registers_1));
  EXPECT_EQ(false, registers_2->operator!=(*registers_3));
  EXPECT_EQ(false, registers_3->operator!=(*registers_2));
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
  return RUN_ALL_TESTS();
}
