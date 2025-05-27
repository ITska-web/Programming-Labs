#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("vvedite pravilno\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error opening");
    }

    int *numbers = NULL;
    int count = 0;
    int num;

    while (fscanf(file, "%d", &num) == 1)
    {
        numbers = realloc(numbers, (count + 1) * sizeof(int));
        if (numbers == NULL)
        {
            printf("error");
        }
        numbers[count++] = num;
    }

    fclose(file);

    if (count == 0)
    {
        printf("no chisel\n");
        free(numbers);
        return 1;
    }

    double sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += numbers[i];
    }
    double srednee = sum / count;

    double minOtkl = fabs(numbers[0] - srednee);
    for (int i = 1; i < count; i++)
    {
        double otkl = fabs(numbers[i] - srednee);
        if (otkl < minOtkl)
        {
            minOtkl = otkl;
        }
    }

    printf("samoe malenkoe otklonenie ot srednego: %.2f\n", minOtkl);

    free(numbers);
    return 0;
}
