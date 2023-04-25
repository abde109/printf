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
            case 'c':
            {
                int c = va_arg(args, int);
                putchar(c);
                count++;
                break;
            }
            case 's':
            {
                const char *s = va_arg(args, const char *);
                while (*s)
                {
                    putchar(*s);
                    count++;
                    s++;
                }
                break;
            }
            case '%':
            {
                putchar('%');
                count++;
                break;
            }
            case 'd':
            case 'i':
            {
                int d = va_arg(args, int);
                if (d < 0)
                {
                    putchar('-');
                    d = -d;
                    count++;
                }
                print_number(d);
                count += snprintf(NULL, 0, "%d", d);
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

void print_number(int num)
{
    if (num == 0)
    {
        putchar('0');
        return;
    }

    if (num / 10)
        print_number(num / 10);

    putchar((num % 10) + '0');
}

