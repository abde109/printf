#include "main.h"

typedef struct spec_handler {
    char specifier;
    int (*handler)(va_list);
} spec_handler_t;

int handle_specifier(char specifier, va_list args) {
    spec_handler_t spec_handlers[] = {
        {'c', print_char},
        {'s', print_string},
        {'%', print_percent},
        {'\0', NULL}
    };

    int i = 0;
    while (spec_handlers[i].specifier) {
        if (specifier == spec_handlers[i].specifier)
            return spec_handlers[i].handler(args);
        i++;
    }

    return 0;
}

int _printf(const char *format, ...) {
    va_list args;
    int count = 0;

    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;
            count += handle_specifier(*format, args);
        } else {
            count += write(1, format, 1);
        }
        format++;
    }

    va_end(args);

    return count;
}

