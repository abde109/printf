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

void print_unsigned(unsigned int num)
{
    if (num == 0)
    {
        putchar('0');
        return;
    }

    if (num / 10)
        print_unsigned(num / 10);

    putchar((num % 10) + '0');
}

void print_octal(unsigned int num)
{
    if (num == 0)
    {
        putchar('0');
        return;
    }

    if (num / 8)
        print_octal(num / 8);

    putchar((num % 8) + '0');
}

void print_hex(unsigned int num, int uppercase)
{
    char *hex_digits;

    if (num == 0)
    {
        putchar('0');
        return;
    }

    hex_digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";

    if (num / 16)
        print_hex(num / 16, uppercase);

    putchar(hex_digits[num % 16]);
}

