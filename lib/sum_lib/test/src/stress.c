#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "sum.h"

#define SIZE 1000000000
#define NANO 1000000000
#define REPEATS 5

long long to_int(struct timespec start, struct timespec end) {
  return NANO * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}

int main() {
  int len = SIZE;
  int *array;
  long long result;
  struct timespec start, end;

  array = (int *)calloc(len, sizeof(int));
  if (array == NULL) {
    printf("Memory error!\n");
    return -1;
  }

  for (int i = 0; i < len; ++i) {
    array[i] = 1;
  }

  sum_error_t flag;
  long long mean = 0;
  for (int i = 0; i < REPEATS; ++i) {
    clock_gettime(CLOCK_MONOTONIC, &start);
    flag = calculate_sum(&result, array, len);
    clock_gettime(CLOCK_MONOTONIC, &end);
    long long time = to_int(start, end);
    mean += time;
  }
  mean /= REPEATS;
  switch (flag) {
    case SUM_SUCCES:
      printf("SUCCES! Result=%lld\n", result);
      free(array);
      break;
    case SUM_SEMAPHORE:
      printf("Unable to init semaphore! Error\n");
      free(array);
      return -1;
    case SUM_PTHREADCREATE:
      printf("Unable to create thread! Error\n");
      free(array);
      return -1;
    case SUM_PTHREADJOIN:
      printf("Unable to join thread! Error\n");
      free(array);
      return -1;
    case SUM_PTHREADMUTEX:
      printf("Unable to lock/unlock mutex! Error\n");
      free(array);
      return -1;
    case SUM_MEMORYERROR:
      printf("Memorry allocation error!\n");
      free(array);
      return -1;
    default:
      break;
  }

  FILE *fd;
  fd = fopen("time.txt", "a");
  if (fd == NULL) {
    printf("Unable to open file\n");
    return -1;
  }
  fprintf(fd, "Result: %llu.%llu\n", (unsigned long long)mean / NANO,
          (unsigned long long)mean % NANO);
  fclose(fd);
  return 0;
}