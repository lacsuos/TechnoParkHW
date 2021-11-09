#include <stdlib.h>

#include "sum.h"

#define DEFAULT 100000000

sum_error_t calculate_sum(long long* result, const int* array, const int len) {
  if (array == NULL) {
    return SUM_MEMORYERROR;
  }
  int k = 1;
  long long sum = 0;
  while (k <= 10) {
    for (int i = 0; k + 10 * i < len; ++i) {
      sum += array[k + 10 * i];
    }
    ++k;
  }
  *result = sum;
  return SUM_SUCCES;
}
