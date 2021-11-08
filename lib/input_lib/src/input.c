#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int *create_random(const int len)
{
    srand(time(NULL));
    int *array = (int *)calloc(len, sizeof(int));
    if (array == NULL){
        printf("memorry error!");
        return NULL;}
    for (int i = 0; i < len; i++)
    {
        array[i] = 1;//rand() % 100;
    }
    return array;
}