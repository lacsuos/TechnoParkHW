#include "sum.h"
#include "input.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#define DEFAULT 100000000


int main(int argc, char **argv)
{
    int len, option;
    char *options = "-:F::R::";
    long long result;
    int *array;
    if (argc < 2)
    {
        printf("There are no arguments here!\nCreating random array size of 10^8...\n");
        len = DEFAULT;
        array = create_random(len);
    }
    else
    {
        while ((option = getopt(argc, argv, options)) != -1)
        {
            printf("opt=%c, optarg=%s\n", option, optarg);
            switch (option)
            {
            case 'F':
                printf("There are will be filefunc\n");
                break;
            case 'R':
                len = optarg ? atoi(optarg) : DEFAULT;
                array = create_random(len);
                break;
            default:
                break;
            }
        }
    }
    printf("Calculating...\n");
    error_t flag = calculate_sum(&result, array, len);
    int test = (int) flag;
    switch (flag)
    {
    case SUM_SUCCES:
        printf("SUCCES! Result=%lld", result);
        break;
    case SUM_SEMAPHORE:
        printf("Unable to init semaphore! Error\n");
        return -1;
    case SUM_PTHREADCOND:
        printf("Condition method error! (timeout or unable to init)\n");
        return -1;
    case SUM_PTHREADCREATE:
        printf("Unable to create thread! Error\n");
        return -1;
    case SUM_PTHREADJOIN:
        printf("Unable to join thread! Error\n");
        return -1;
    case SUM_PTHREADMUTEX:
        printf("Unable to lock/unlock mutex! Error\n");
        return -1;
    case SUM_MEMORYERROR:
        printf("Memorry allocation error!\n");
        return -1;
    default:
        break;
    }
    free(array);
    printf("%lld\n", result);
    return 0;
}