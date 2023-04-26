#include "main.h"
#include <unistd.h>
#include <stdlib.h>

void print_int(int n);

int _printf(const char *format, ...)
{
    va_list args;
    const char *p;
    int count = 0;

    va_start(args, format);

    for (p = format; *p != '\0'; p++)
    {
        if (*p != '%')
        {
            write(1, p, 1);
            count++;
            continue;
        }

        p++;

        switch (*p)
        {
            case 'd':
            case 'i':
            {
                int num = va_arg(args, int);
                print_int(num);
                count += (num < 0) ? 1 : 0;
                while (num != 0)
                {
                    count++;
                    num /= 10;
                }
                break;
            }
            default:
            {
                write(1, p - 1, 1);
                write(1, p, 1);
                count += 2;
                break;
            }
        }
    }

    va_end(args);
    return count;
}

void print_int(int n)
{
    char c;
    if (n < 0)
    {
        write(1, "-", 1);
        n = -n;
    }
    if (n / 10 != 0)
    {
        print_int(n / 10);
    }
    c = '0' + (n % 10);
    write(1, &c, 1);
}
