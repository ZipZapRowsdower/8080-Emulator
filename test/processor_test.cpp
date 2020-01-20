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
  Registers* regs_1;
  Registers* regs_2;
  Registers* regs_3;

  RegistersTest() {
    regs_1 = new Registers;
    regs_2 = new Registers(a_2, b_2, c_2, d_2, e_2, h_2, l_2, sp_2, pc_2);
    regs_3 = new Registers;
  }

  virtual ~RegistersTest() {
    delete regs_1;
    delete regs_2;
    delete regs_3;
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
  EXPECT_EQ(0x00, regs_1->a);
  EXPECT_EQ(0x00, regs_1->b);
  EXPECT_EQ(0x00, regs_1->c);
  EXPECT_EQ(0x00, regs_1->d);
  EXPECT_EQ(0x00, regs_1->e);
  EXPECT_EQ(0x00, regs_1->h);
  EXPECT_EQ(0x00, regs_1->l);
  EXPECT_EQ(0x0000, regs_1->sp);
  EXPECT_EQ(0x0000, regs_1->pc);
}

TEST_F(RegistersTest, FullRegistersInitialization) {
  EXPECT_EQ(a_2, regs_2->a);
  EXPECT_EQ(b_2, regs_2->b);
  EXPECT_EQ(c_2, regs_2->c);
  EXPECT_EQ(d_2, regs_2->d);
  EXPECT_EQ(e_2, regs_2->e);
  EXPECT_EQ(h_2, regs_2->h);
  EXPECT_EQ(l_2, regs_2->l);
  EXPECT_EQ(sp_2, regs_2->sp);
  EXPECT_EQ(pc_2, regs_2->pc);
}

TEST_F(RegistersTest, CopyConstructorInitialization) {
  Registers* my_regs = new Registers(*regs_2);

  EXPECT_EQ(regs_2->a, my_regs->a);
  EXPECT_EQ(regs_2->b, my_regs->b);
  EXPECT_EQ(regs_2->c, my_regs->c);
  EXPECT_EQ(regs_2->d, my_regs->d);
  EXPECT_EQ(regs_2->e, my_regs->e);
  EXPECT_EQ(regs_2->h, my_regs->h);
  EXPECT_EQ(regs_2->l, my_regs->l);
  EXPECT_EQ(regs_2->sp, my_regs->sp);
  EXPECT_EQ(regs_2->pc, my_regs->pc);

  delete my_regs;
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

TEST_F(ConditionCodesTest, AllAccessors) {
  EXPECT_EQ(z_2, cc_2->get_z());
  EXPECT_EQ(s_2, cc_2->get_s());
  EXPECT_EQ(p_2, cc_2->get_p());
  EXPECT_EQ(cy_2, cc_2->get_cy());
  EXPECT_EQ(ac_2, cc_2->get_ac());
  EXPECT_EQ(pad_2, cc_2->get_pad());
}

TEST_F(RegistersTest, AllAccessors) {
  EXPECT_EQ(a_2, regs_2->get_a());
  EXPECT_EQ(b_2, regs_2->get_b());
  EXPECT_EQ(c_2, regs_2->get_c());
  EXPECT_EQ(d_2, regs_2->get_d());
  EXPECT_EQ(e_2, regs_2->get_e());
  EXPECT_EQ(h_2, regs_2->get_h());
  EXPECT_EQ(l_2, regs_2->get_l());
  EXPECT_EQ(sp_2, regs_2->get_sp());
  EXPECT_EQ(pc_2, regs_2->get_pc());
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

TEST_F(ConditionCodesTest, AllMutators) {
  cc_3->set_z(z_2);
  cc_3->set_s(s_2);
  cc_3->set_p(p_2);
  cc_3->set_cy(cy_2);
  cc_3->set_ac(ac_2);
  cc_3->set_pad(pad_2);

  EXPECT_EQ(z_2, cc_3->get_z());
  EXPECT_EQ(s_2, cc_3->get_s());
  EXPECT_EQ(p_2, cc_3->get_p());
  EXPECT_EQ(cy_2, cc_3->get_cy());
  EXPECT_EQ(ac_2, cc_3->get_ac());
  EXPECT_EQ(pad_2, cc_3->get_pad());
}

TEST_F(RegistersTest, AllMutators) {
  regs_3->set_a(a_2);
  regs_3->set_b(b_2);
  regs_3->set_c(c_2);
  regs_3->set_d(d_2);
  regs_3->set_e(e_2);
  regs_3->set_h(h_2);
  regs_3->set_l(l_2);
  regs_3->set_sp(sp_2);
  regs_3->set_pc(pc_2);

  EXPECT_EQ(a_2, regs_3->get_a());
  EXPECT_EQ(b_2, regs_3->get_b());
  EXPECT_EQ(c_2, regs_3->get_c());
  EXPECT_EQ(d_2, regs_3->get_d());
  EXPECT_EQ(e_2, regs_3->get_e());
  EXPECT_EQ(h_2, regs_3->get_h());
  EXPECT_EQ(l_2, regs_3->get_l());
  EXPECT_EQ(sp_2, regs_3->get_sp());
  EXPECT_EQ(pc_2, regs_3->get_pc());
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
  regs_2->Clear();

  EXPECT_EQ(true, regs_1->operator==(*regs_2));
}

TEST_F(RegistersTest, IsClear) {
  EXPECT_EQ(true, regs_1->IsClear());
  EXPECT_EQ(false, regs_2->IsClear());
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
  std::string actual = regs_2->ToString();
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
  buffer << *regs_2;

  std::string actual = buffer.str();
  EXPECT_EQ(expected, actual);
}

TEST_F(RegistersTest, EqualsOperatorOverload) {
  *regs_3 = *regs_2;

  EXPECT_EQ(regs_3->a, regs_2->a);
  EXPECT_EQ(regs_3->b, regs_2->b);
  EXPECT_EQ(regs_3->c, regs_2->c);
  EXPECT_EQ(regs_3->d, regs_2->d);
  EXPECT_EQ(regs_3->e, regs_2->e);
  EXPECT_EQ(regs_3->h, regs_2->h);
  EXPECT_EQ(regs_3->l, regs_2->l);
  EXPECT_EQ(regs_3->sp, regs_2->sp);
  EXPECT_EQ(regs_3->pc, regs_2->pc);
}

TEST_F(RegistersTest, EqualityOperatorOverload) {
  *regs_3 = *regs_2;

  EXPECT_EQ(true, regs_1->operator==(*regs_1));
  EXPECT_EQ(true, regs_2->operator==(*regs_2));
  EXPECT_EQ(true, regs_3->operator==(*regs_3));
  EXPECT_EQ(false, regs_1->operator==(*regs_2));
  EXPECT_EQ(false, regs_2->operator==(*regs_1));
  EXPECT_EQ(false, regs_1->operator==(*regs_3));
  EXPECT_EQ(false, regs_3->operator==(*regs_1));
  EXPECT_EQ(true, regs_2->operator==(*regs_3));
  EXPECT_EQ(true, regs_3->operator==(*regs_2));
}

TEST_F(RegistersTest, NotEqualityOperatorOverload) {
  *regs_3 = *regs_2;

  EXPECT_EQ(false, regs_1->operator!=(*regs_1));
  EXPECT_EQ(false, regs_2->operator!=(*regs_2));
  EXPECT_EQ(false, regs_3->operator!=(*regs_3));
  EXPECT_EQ(true, regs_1->operator!=(*regs_2));
  EXPECT_EQ(true, regs_2->operator!=(*regs_1));
  EXPECT_EQ(true, regs_1->operator!=(*regs_3));
  EXPECT_EQ(true, regs_3->operator!=(*regs_1));
  EXPECT_EQ(false, regs_2->operator!=(*regs_3));
  EXPECT_EQ(false, regs_3->operator!=(*regs_2));
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
