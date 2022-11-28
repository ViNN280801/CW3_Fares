#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>

static const short int BITS = 8U;

/* Обрабатывает ошибку ввода пользователем символа или строки,
когда его просят ввести число. Возвращает число, введённое пользователем */
int inputInt()
{
    /* Инициализация массива */
    char buf[256] = {0};
    scanf("%s", buf);

    /* int atoi(const char *str)
    Функция atoi() конвертирует строку, на которую указывает параметр str,
    в величину типа int. Строка должна содержать корректную запись целого числа.
    В противном случае возвращается 0 */
    while ((atoi(buf) == 0) && (buf[0] != '0'))
    {
        printf("Ошибка ввода. Введите число: ");
        scanf("%s", buf);
    }
    return atoi(buf);
}

unsigned int mirroringBits(unsigned int value)
{
    unsigned int result = 0;
    for (size_t i = 0; i < (sizeof(value) * BITS); i++)
    {
        if ((value & (1 << i)))
            result |= 1 << (((sizeof(value) * BITS) - 1) - i);
    }
    return result;
}

int main(void)
{
    /* Подключение русского языка */
    setlocale(LC_ALL, "rus");

    /* Переменная отвечающая за выбор пунктов меню */
    int menu_var = 0, submenu_var = 0;

    /* Меню */
    while (true)
    {
        printf("1. Начало работы\n2. Выход\nВвод: ");
        menu_var= inputInt();

        if (menu_var == 1)
        {
            /* Подменю */
            while (true)
            {
                printf("1. Ручной ввод\n2. Случайное число\n3. Выход\nВвод: ");
                submenu_var = inputInt();
                if (submenu_var == 1)
                {
                    printf("Введите число: ");
                    unsigned int number = inputInt();
                    unsigned int mirror = mirroringBits(number);
                    printf("%u\t%u\n", number, mirror);
                }
                else if (submenu_var == 2)
                {
                    /* Устанавливает в качестве базы текущее время */
                    srand(time(NULL));

                    unsigned int number = rand() % 10 + 1;
                    unsigned int mirror = mirroringBits(number);
                    printf("%u\t%u\n", number, mirror);
                }
                else if (submenu_var == 3)
                {
                    printf("Выход ...\n");
                    break;
                }
                else
                {
                    printf("Ошибка ввода, попробуйте ещё раз\n");
                }
            }
            /* Конец подменю */
        }
        if (menu_var == 2)
        {
            printf("Выход ...\n");
            exit(0);
        }
        else if (menu_var != 1 && menu_var != 2)
        {
            printf("Ошибка ввода, попробуйте ещё раз\n");
        }
    }
    /* Конец меню */
}