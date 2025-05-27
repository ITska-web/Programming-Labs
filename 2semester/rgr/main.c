#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 10000

/* Проверяет, является ли символ русской буквой */
int is_russian_alpha(unsigned char c)
{
    /* Русские буквы в кодировке Windows-1251 */
    return (c >= 0xC0 && c <= 0xFF) || c == 0xA8 || c == 0xB8;
}

/* Приводит русские буквы к нижнему регистру */
char to_russian_lower(unsigned char c)
{
    /* Большие русские буквы в Windows-1251 */
    if (c >= 0xC0 && c <= 0xDF)
        return c + 0x20;
    if (c == 0xA8)
        return 0xB8; /* Ё -> ё */
    return c;
}

/* Функция для проверки палиндрома */
int is_palindrome(const char *text, size_t length)
{
    size_t i;
    for (i = 0; i < length / 2; i++)
    {
        if (to_russian_lower(text[i]) != to_russian_lower(text[length - i - 1]))
        {
            return 0;
        }
    }
    return 1;
}

/* Очистка строки от всего, кроме русских букв */
void clean_string(char *str)
{
    char *p = str;
    char *q = str;

    while (*p)
    {
        if (is_russian_alpha(*p))
        {
            *q = to_russian_lower(*p);
            q++;
        }
        p++;
    }
    *q = '\0';
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    char buffer[MAX_FILE_SIZE];
    FILE *file = fopen(argv[1], "rb"); /* Открываем в бинарном режиме */

    if (file == NULL)
    {
        perror("Ошибка открытия файла");
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, MAX_FILE_SIZE - 1, file);
    buffer[bytes_read] = '\0';
    fclose(file);

    clean_string(buffer);
    size_t clean_length = strlen(buffer);

    if (clean_length == 0)
    {
        printf("Файл не содержит русских буквенных символов.\n");
        return 0;
    }

    if (is_palindrome(buffer, clean_length))
    {
        printf("Весь текст в файле является палиндромом.\n");
    }
    else
    {
        printf("Текст в файле не является палиндромом.\n");
    }

    return 0;
}