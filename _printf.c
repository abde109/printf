#include "main.h"

int _printf(const char *format, ...) {
    va_list args;
    int count = 0;
    const char *p;

    va_start(args, format);

    for (p = format; *p != '\0'; p++) {
        if (*p != '%') {
            putchar(*p);
            count++;
            continue;
        }

        p++;

        switch (*p) {
            case 'c': {
                int c = va_arg(args, int);
                putchar(c);
                count++;
                break;
            }
            case 's': {
                const char *s = va_arg(args, const char *);
                while (*s) {
                    putchar(*s);
                    count++;
                    s++;
                }
                break;
            }
            case '%': {
                putchar('%');
                count++;
                break;
            }
            case 'd': {
                int d = va_arg(args, int);
                int num_chars = printf("%d", d);
                count += num_chars;
                break;
            }
            default: {
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

