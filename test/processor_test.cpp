#include <gtest/gtest.h>

// TODO: Remove relative path
#include "../src/include/processor.h"

struct ProcessorTest : testing::Test {
  ConditionCodes* cc_1;

  ProcessorTest()
  {
    cc_1 = new ConditionCodes;
  }

  virtual ~ProcessorTest()
  {
    delete cc_1;
  }
};


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
