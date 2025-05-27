#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100
#define M 100

typedef struct
{
    char destination[N];
    int train_number;
    char departure_time[6];
} Train;

void writeTrainsToFile(const char *filename, Train *trains, int n)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Не удалось открыть");
        return;
    }
    fwrite(trains, sizeof(Train), n, file);

    fclose(file);
}

int readTrainsFromFile(const char *filename, Train *trains)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Не удалось открыть файл");
        return 0;
    }

    int count = fread(trains, sizeof(Train), M, file);

    fclose(file);
    return count;
}

void searchTrains(Train *trains, int count)
{
    int choice;
    printf("По какому полю поиск?\n");
    printf("1. Название пункта назначения\n");
    printf("2. Номер поезда\n");
    printf("3. Время отправления\n");

    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        char destination[N];
        printf("Введите название пункта назначения: ");
        scanf("%s", destination);
        int found = 0;
        for (int i = 0; i < count; i++)
        {
            if (strcmp(trains[i].destination, destination) == 0)
            {
                printf("Найден поезд: %s, Номер: %d, Время отправления: %s\n",
                       trains[i].destination,
                       trains[i].train_number,
                       trains[i].departure_time);
                found = 1;
            }
        }
        if (!found)
        {
            printf("Поезд не найден.\n");
        }
        break;
    }
    case 2:
    {
        int train_number;
        printf("Введите номер поезда: ");
        scanf("%d", &train_number);
        int found = 0;
        for (int i = 0; i < count; i++)
        {
            if (trains[i].train_number == train_number)
            {
                printf("Найден поезд: %s, Номер: %d, Время отправления: %s\n",
                       trains[i].destination,
                       trains[i].train_number,
                       trains[i].departure_time);
                found = 1;
            }
        }
        if (!found)
        {
            printf("Поезд не найден.\n");
        }
        break;
    }
    case 3:
    {
        char time[6];
        printf("Введите время отправления (HH:MM): ");
        scanf("%5s", time);
        int found = 0;
        for (int i = 0; i < count; i++)
        {
            if (strcmp(trains[i].departure_time, time) == 0)
            {
                printf("Найден поезд: %s, Номер: %d, Время отправления: %s\n",
                       trains[i].destination,
                       trains[i].train_number,
                       trains[i].departure_time);
                found = 1;
            }
        }
        if (!found)
        {
            printf("Поезд с таким временем отправления не найден.\n");
        }
        break;
    }
    default:
        printf("Некорректный выбор.\n");
    }
}

int main()
{
    Train trains[M];
    int n;

    printf("Введите количество поездов для записи в файл: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("\nВведите данные для поезда #%d:\n", i + 1);
        printf("Название пункта назначения: ");
        scanf("%s", trains[i].destination);
        printf("Номер поезда: ");
        scanf("%d", &trains[i].train_number);
        printf("Время отправления: ");
        scanf("%5s", trains[i].departure_time);
    }

    writeTrainsToFile("trains.bin", trains, n);
    int count = readTrainsFromFile("trains.bin", trains);

    if (count > 0)
    {
        searchTrains(trains, count);
    }
    else
    {
        printf("Ошибка при чтении данных.\n");
    }

    return 0;
}