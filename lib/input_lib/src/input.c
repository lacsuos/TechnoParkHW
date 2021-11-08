#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFF_SIZE 1024

int *read_file(int *len, const char *path) {
  FILE *fd;
  int k = 0;
  int element;
  int buff_size = BUFF_SIZE;
  int *array = (int *)calloc(buff_size, sizeof(int));
  if (array == NULL) {
    printf("Unable to allocate memory!\n");
    return NULL;
  }
  fd = fopen(path, "r+");

  if (fd == NULL) {
    printf("Wrong path!\n");
    free(array);
    return NULL;
  }

  while ((fscanf(fd, "%d", &element) != EOF)) {
    if (k >= buff_size) {
      buff_size += BUFF_SIZE;
      array = realloc(array, buff_size * sizeof(int));
    }
    array[k] = element;
    k += 1;
  }
  *len = k;
  fclose(fd);
  return array;
}

int *create_random(const int len) {
  srand(time(NULL));
  int *array = (int *)calloc(len, sizeof(int));
  if (array == NULL) {
    printf("Unable to allocate memory!\n");
    return NULL;
  }
  for (int i = 0; i < len; i++) {
    array[i] = 1;  // rand() % 100;
  }
  return array;
}