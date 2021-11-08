#include "gtest/gtest.h"

extern "C" {
#include "input.h"
}

TEST(INPUT, create_random) {
  int *array;
  int len = 1000;
  array = create_random(len);
  ASSERT_FALSE(array == NULL);
  free(array);
  len = 0;
  array = create_random(len);
  ASSERT_TRUE(array == NULL);
}

TEST(INPUT, read_file_test) {
  int *array;
  int len;
  array = read_file(&len, "test.txt");
  ASSERT_FALSE(array == NULL);
  ASSERT_EQ(len, 100);
  free(array);
  array = read_file(&len, "doesnotexist.txt");
  ASSERT_TRUE(array == NULL);
}