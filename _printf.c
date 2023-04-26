#include "main.h"

void print_unsigned(unsigned int u);
void print_octal(unsigned int o);
void print_hex(unsigned int x, int uppercase);
int count_digits(unsigned int num);
int count_octal_digits(unsigned int num);
int count_hex_digits(unsigned int num);

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
                count += count_octal_digits(o);
                break;
            }
            case 'x':
            {
                unsigned int x = va_arg(args, unsigned int);
                print_hex(x, 0);
                count += count_hex_digits(x);
                break;
            }
            case 'X':
            {
                unsigned int x = va_arg(args, unsigned int);
                print_hex(x, 1);
                count += count_hex_digits(x);
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
    if (u >= 10)
    {
        print_unsigned(u / 10);
    }
    putchar('0' + u % 10);
}

void print_octal(unsigned int o)
{
    if (o >= 8)
    {
        print_octal(o / 8);
    }
    putchar('0' + o % 8);
}

void print_hex(unsigned int x, int uppercase)
{
    if (x >= 16)
    {
        print_hex(x / 16, uppercase);
    }
    if (x % 16 < 10)
    {
        putchar('0' + x % 16);
    }
    else
    {
        putchar((uppercase ? 'A' : 'a') + x % 16 - 10);
    }
}

int count_digits(unsigned int num)
{
    int count = 0;
    do
    {
        count++;
        num /= 10;
    } while (num > 0);
    return count;
}

int count_octal_digits(unsigned int num)
{
    int count = 0;
    do
    {
        count++;
        num /= 8;
    } while (num > 0);
    return count;
}

int count_hex_digits(unsigned int num)
{
    int count = 0;
    do
    {
        count++;
        num /= 16;
    } while (num > 0);
    return count;
}

