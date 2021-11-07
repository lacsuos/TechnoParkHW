#pragma once
typedef enum{
    SUM_SUCCES = 0,
    SUM_MEMORYERROR,
    SUM_PTHREADMUTEX,
    SUM_PTHREADCOND,
    SUM_PTHREADCREATE,
    SUM_PTHREADJOIN,
    SUM_SEMAPHORE
} error_t;

error_t calculate_sum(long long *result, const int *array, const int len);