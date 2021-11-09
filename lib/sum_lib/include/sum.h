#pragma once

typedef enum {
  SUM_SUCCES = 0,
  SUM_MEMORYERROR,
  SUM_PTHREADMUTEX,
  SUM_PTHREADCREATE,
  SUM_PTHREADJOIN,
  SUM_SEMAPHORE
} sum_error_t;

sum_error_t calculate_sum(long long *result, const int *array, const int len);