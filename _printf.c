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
            // ... (previous cases here)

            case 'b':
            {
                unsigned int b = va_arg(args, unsigned int);
                print_binary(b);
                count += snprintf(NULL, 0, "%b", b);
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

// ... (print_number function here)

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

