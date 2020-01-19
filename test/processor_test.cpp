#include <gtest/gtest.h>

// TODO: Remove relative path
#include "../src/include/processor.h"

struct ProcesserTest : testing::Test {
  ConditionCodes* cc_1;

  ProcesserTest()
  {
    cc_1 = new ConditionCodes;
  }

  virtual ~ProcesserTest()
  {
    delete cc_1;
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

TEST_F(ProcesserTest, DefaultInitialization) {
  EXPECT_EQ(0, cc_1->z);
  EXPECT_EQ(0, cc_1->s);
  EXPECT_EQ(0, cc_1->p);
  EXPECT_EQ(0, cc_1->cy);
  EXPECT_EQ(0, cc_1->ac);
  EXPECT_EQ(0, cc_1->pad);
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
