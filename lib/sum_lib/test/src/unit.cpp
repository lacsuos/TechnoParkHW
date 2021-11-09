#include <random>

#include "gtest/gtest.h"

extern "C" {
#include "sum.h"
}

TEST(SUM, calculate_sum) {
  long long result;
  int len = 1000;
  int *array = (int *)calloc(len, sizeof(int));
  ASSERT_EQ(calculate_sum(&result, array, len), SUM_SUCCES);
  ASSERT_EQ(result, 0);
  for (int i = 0; i < len; i++) {
    array[i] = 1;
  }
  ASSERT_EQ(calculate_sum(&result, array, len), SUM_SUCCES);
  ASSERT_EQ(result, 999);
  free(array);
  array = nullptr;
  ASSERT_EQ(calculate_sum(&result, array, len), SUM_MEMORYERROR);
}

TEST(SUM, calculate_sum_random) {
  long long result;
  int len = 100000000;
  int *array = (int *)calloc(len, sizeof(int));
  for (int i = 0; i < len; i++) {
    array[i] = rand() % 10;
  }
  ASSERT_EQ(calculate_sum(&result, array, len), SUM_SUCCES);
  free(array);
}