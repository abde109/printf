#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

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
            case 'u':
            {
                unsigned int u = va_arg(args, unsigned int);
                print_unsigned(u);
                count += count_digits(u);
                break;
            }
            case 'o':
            {
                unsigned int o = va_arg(args, unsigned int);
                print_octal(o);
                count += count_digits(o);
                break;
            }
            case 'x':
            {
                unsigned int x = va_arg(args, unsigned int);
                print_hex(x, 0);
                count += count_digits(x);
                break;
            }
            case 'X':
            {
                unsigned int x = va_arg(args, unsigned int);
                print_hex(x, 1);
                count += count_digits(x);
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

void print_unsigned(unsigned int u)
{
    if (u / 10 != 0)
        print_unsigned(u / 10);
    putchar('0' + (u % 10));
}

void print_octal(unsigned int o)
{
    if (o / 8 != 0)
        print_octal(o / 8);
    putchar('0' + (o % 8));
}

void print_hex(unsigned int x, int uppercase)
{
    char c;
    if (x / 16 != 0)
        print_hex(x / 16, uppercase);
    c = (x % 16) + (x % 16 < 10 ? '0' : (uppercase ? 'A' : 'a') - 10);
    putchar(c);
}

int count_digits(unsigned int num)
{
    int count = 0;
    while (num > 0)
    {
        count++;
        num /= 10;
    }
    return count;
}

