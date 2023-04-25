#include <stdarg.h>
#include <stdio.h>

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
            default: {
                // If an unsupported specifier is encountered, print it as-is.
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

int main() {
    _printf("Hello, %s! I have %c%c%c%c %d%% of my tasks done today.\n", "John", 'C', 'o', 'd', 'e', 75);

    return 0;
}

