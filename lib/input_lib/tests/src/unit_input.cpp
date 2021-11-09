#include "gtest/gtest.h"

extern "C" {
#include "input.h"
}

TEST(INPUT, create_random) {
  int *array;
  int len = 1000;
  array = create_random(len);
  ASSERT_FALSE(array == nullptr);
  free(array);
}

TEST(INPUT, read_file_test) {
  int *array;
  int len;
  array = read_file(&len, "../../../../lib/input_lib/tests/src/test.txt");
  ASSERT_FALSE(array == nullptr);
  ASSERT_EQ(len, 100);
  free(array);
  array = read_file(&len, "doesnotexist.txt");
  ASSERT_TRUE(array == nullptr);
}