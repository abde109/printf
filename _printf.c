#include "main.h"

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    const char *p;

    va_start(args, format);

    for (p = format; *p != '\0'; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            count++;
            continue;
        }

        p++;

        switch (*p)
        {
            case 'b':
            {
                unsigned int b = va_arg(args, unsigned int);
                print_binary(b);
                count += count_binary_digits(b);
                break;
            }
            default:
            {
                putchar('%');
                putchar(*p);
                count += 2;
                break;
            }
        }
    }

    va_end(args);
    return count;
}


void print_binary(unsigned int num)
{
    if (num == 0)
    {
        putchar('0');
        return;
    }

    if (num / 2)
        print_binary(num / 2);

    putchar((num % 2) + '0');
}

int count_binary_digits(unsigned int num)
{
    int count = 0;
    if (num == 0)
        return 1;

    while (num != 0)
    {
        num /= 2;
        count++;
    }
    return count;
}

