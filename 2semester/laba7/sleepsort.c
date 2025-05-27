#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *sleep_print(void *arg)
{
    int a = *(int *)arg;
    usleep(a * 1000); // num микросекунд (* 1000 для точности)
    printf("%d ", a);
    return NULL;
}

int main()
{
    int array[] = {
        42, 187, 5, 249, 123, 156, 789, 99, 175,
        321, 245, 12, 199, 450, 220, 777, 188, 64, 133,
        911, 240, 210, 512, 2200, 777, 1888, 64, 1333,
        911, 2400, 2100, 512, 1666, 888, 2300, 27, 1450,
        1001, 2500, 404, 1950, 111, 2250, 888, 1776, 50, 1234};
    int n = sizeof(array) / sizeof(array[0]);
    pthread_t threads[n];

    for (int i = 0; i < n; i++)
        pthread_create(&threads[i], NULL, sleep_print, &array[i]);

    for (int i = 0; i < n; i++)
        pthread_join(threads[i], NULL);

    printf(" \n");

    return 0;
}