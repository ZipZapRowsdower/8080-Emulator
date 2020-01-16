#include <gtest/gtest.h>

TEST(Emulator, One) {
  EXPECT_EQ(0, 0);
}

TEST(Emulator, Two) {
  EXPECT_NE(0, 1);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
