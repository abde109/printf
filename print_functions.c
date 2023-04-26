#include "main.h"

int print_char(va_list args) {
    char c = va_arg(args, int);
    return write(1, &c, 1);
}

int print_string(va_list args) {
    char *s = va_arg(args, char *);
    int count = 0;

    while (*s) {
        count += write(1, s, 1);
        s++;
    }

    return count;
}

int print_percent(va_list args) {
    char c;
    
    (void)args;
    c = '%';
    return write(1, &c, 1);
}

