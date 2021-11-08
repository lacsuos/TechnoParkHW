#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "input.h"
#include "sum.h"

#define DEFAULT 100000000

int main(int argc, char **argv) {
  int len, option;
  char *options = "-:F:R::";
  long long result;
  int *array;
  if (argc < 2) {
    printf(
        "There are no arguments here!\nCreating random array size of "
        "10^8...\n");
    len = DEFAULT;
    array = create_random(len);
  } else {
    option = getopt(argc, argv, options);
    printf("opt=%c, optarg=%s\n", option, optarg);
    switch (option) {
      case 'F':
        array = read_file(&len, optarg);
        break;
      case 'R':
        len = optarg ? atoi(optarg) : DEFAULT;
        array = create_random(len);
        break;
      default:
        break;
    }
  }
  printf("Calculating...\n");
  sum_error_t flag = calculate_sum(&result, array, len);
  switch (flag) {
    case SUM_SUCCES:
      printf("SUCCES! Result=%lld\n", result);
      free(array);
      break;
    case SUM_SEMAPHORE:
      printf("Unable to init semaphore! Error\n");
      free(array);
      return -1;
    case SUM_PTHREADCOND:
      printf("Condition method error! (timeout or unable to init)\n");
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
  return 0;
}