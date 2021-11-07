#include "sum.h"
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static sem_t semaphore;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct {
  const int *array;
  long long sum;
  int len;
  int k;
} data_t;

static void *thread_func(void *arg) {
  int errflag;
  data_t *data = (data_t *)arg;
  errflag = sem_wait(&semaphore);
  if (errflag){
    printf("Semaphore error! Executing program...\n");
    exit(-1);
  }
  long long sum = 0;

  errflag = pthread_mutex_lock(&mutex);
  if (errflag) {
    printf("Unable to create mutex lock. Executing program...\n");
    exit(-1);
  }

  int k = ++data->k;
  errflag = pthread_cond_signal(&cond);

  errflag = pthread_mutex_unlock(&mutex);
  if (errflag) {
    printf("Unable to unlock mutex. Executing program...\n");
    exit(-1);
  }

  for (int i = 0; k + 10 * i < data->len; ++i) {
    sum += data->array[k + 10 * i];
  }

  errflag = pthread_mutex_lock(&mutex);
  if (errflag) {
    printf("Unable to create mutex lock. Executing program...\n");
    exit(-1);
  }
  data->sum += sum;
  errflag = pthread_mutex_unlock(&mutex);
  if (errflag) {
    printf("Unable to unlock mutex. Executing program...\n");
    exit(-1);
  }
  errflag = sem_post(&semaphore);
  if (errflag){
    printf("Semaphore error! Executing program...\n");
    exit(-1);
  }
  return NULL;
}

error_t calculate_sum(long long *result, const int *array, const int len) {
  int kernels = sysconf(_SC_NPROCESSORS_CONF);
  printf("kernels %d\n", kernels);
  struct timespec timeout;
  timeout.tv_sec = time(NULL) + 1;
  timeout.tv_nsec = 0;
  pthread_t *pthreads = (pthread_t *)malloc(10 * sizeof(pthread_t));
  if (pthreads == NULL) {
    free(pthreads);
    return SUM_MEMORYERROR;
  }

  int errflag;
  data_t input = {array, 0, len, 0};
  errflag = sem_init(&semaphore, 0, kernels);
  if (errflag){
    free(pthreads);
    return SUM_SEMAPHORE;
  }
  for (int k = 0; k < 10; ++k) {
    errflag = pthread_create((pthreads + k), NULL, thread_func, &input);
    if (errflag) {
      free(pthreads);
      return SUM_PTHREADCREATE;
    }

    errflag = pthread_mutex_lock(&mutex);
    if (errflag) {
      free(pthreads);
      return SUM_PTHREADMUTEX;
    }

    while (input.k == k && input.k != 10) {
      errflag = pthread_cond_timedwait(&cond, &mutex, &timeout);
      if (errflag == ETIMEDOUT) {
        free(pthreads);
        return SUM_PTHREADCOND;
      }
    }

    errflag = pthread_mutex_unlock(&mutex);
    if (errflag) {
      free(pthreads);
      return SUM_PTHREADMUTEX;
    }
  }
  
  for (int i = 0; i < 10; i++) {
    errflag = pthread_join(pthreads[i], NULL);
    if (errflag) {
      return SUM_PTHREADJOIN;
    }
  }
  *result = input.sum;
  return SUM_SUCCES;
}