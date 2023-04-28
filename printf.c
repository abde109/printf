#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

int print_char(va_list args);
int print_string(va_list args);
int print_int(va_list args);
int print_unsigned(va_list args);
int print_octal(va_list args);
int print_hex_lower(va_list args);
int print_hex_upper(va_list args);
int print_binary(va_list args);
int print_S(va_list args);
int print_pointer(va_list args);

typedef struct specifier {
    char c;
    int (*f)(va_list);
} specifier_t;

int print_r(va_list args) {
    char *s = va_arg(args, char *);
    int count = 0;
    int len;
    int i;
    if (!s) {
        s = "(null)";
    }
    len = strlen(s);
    for (i = len - 1; i >= 0; i--) {
        write(1, &s[i], 1);
        count++;
    }
    return count;
}


specifier_t specifiers[] = {
    {'c', print_char},
    {'s', print_string},
    {'d', print_int},
    {'i', print_int},
    {'u', print_unsigned},
    {'o', print_octal},
    {'x', print_hex_lower},
    {'X', print_hex_upper},
    {'b', print_binary},
    {'S', print_S},
    {'p', print_pointer},
    {'r', print_r},
    {0, NULL}
};


int _printf(const char *format, ...) {
    va_list args;
    int i = 0, j, count = 0;

    va_start(args, format);

    while (format && format[i]) {
        if (format[i] == '%') {
            i++;
            j = 0;
            while (specifiers[j].c != 0) {
                if (specifiers[j].c == format[i]) {
                    count += specifiers[j].f(args);
                    break;
                }
                j++;
            }
        } else {
            write(1, &format[i], 1);
            count++;
        }
        i++;
    }

    va_end(args);
    return count;
}

int print_number(int n) {
    int count = 0;
    char c;
    if (n < 0) {
        write(1, "-", 1);
        count++;
        n = -n;
    }
    if (n / 10) {
        count += print_number(n / 10);
    }
    c = '0' + (n % 10);
    write(1, &c, 1);
    count++;
    return count;
}

int print_char(va_list args) {
    char c = (char)va_arg(args, int);
    write(1, &c, 1);
    return 1;
}

int print_string(va_list args) {
    char *s = va_arg(args, char *);
    int count = 0;
    if (!s) {
        s = "(null)";
    }
    while (*s) {
        write(1, s, 1);
        count++;
        s++;
    }
    return count;
}

int print_int(va_list args) {
    int n = va_arg(args, int);
    return print_number(n);
}

int print_unsigned(va_list args) {
    unsigned int n = va_arg(args, unsigned int);
    return print_number(n);
}

int print_octal(va_list args) {
    int count = 0;
    unsigned int n = va_arg(args, unsigned int);
    char buffer[32];
    int index = 0;
    int i;
    if (n == 0) {
        write(1, "0", 1);
        return 1;
    }
    while (n) {
        buffer[index++] = '0' + (n % 8);
        n /= 8;
    }
    for (i = index - 1; i >= 0; i--) {
        write(1, &buffer[i], 1);
        count++;
    }
    return count;
}

int print_hex_lower(va_list args) {
    int count = 0;
    unsigned int n = va_arg(args, unsigned int);
    char buffer[32];
    int index = 0;
    int i;
    if (n == 0) {
        write(1, "0", 1);
        return 1;
    }
    while (n) {
        unsigned int digit = n % 16;
        buffer[index++] = digit < 10 ? '0' + digit : 'a' + (digit - 10);
        n /= 16;
    }
    for (i = index - 1; i >= 0; i--) {
        write(1, &buffer[i], 1);
        count++;
    }
    return count;
}

int print_hex_upper(va_list args) {
    int count = 0;
    unsigned int n = va_arg(args, unsigned int);
    char buffer[32];
    int index = 0;
    int i;
    if (n == 0) {
        write(1, "0", 1);
        return 1;
    }
    while (n) {
        unsigned int digit = n % 16;
        buffer[index++] = digit < 10 ? '0' + digit : 'A' + (digit - 10);
        n /= 16;
    }
    for (i = index - 1; i >= 0; i--) {
        write(1, &buffer[i], 1);
	        count++;
    }
    return count;
}

int print_binary(va_list args) {
    int count = 0;
    unsigned int n = va_arg(args, unsigned int);
    char buffer[32];
    int index = 0;
    int i;
    if (n == 0) {
        write(1, "0", 1);
        return 1;
    }
    while (n) {
        buffer[index++] = '0' + (n % 2);
        n /= 2;
    }
    for (i = index - 1; i >= 0; i--) {
        write(1, &buffer[i], 1);
        count++;
    }
    return count;
}

int print_S(va_list args) {
    char *s = va_arg(args, char *);
    int count = 0;
    if (!s) {
        s = "(null)";
    }
    while (*s) {
        if (*s < 32 || *s >= 127) {
            char hex[3];
            write(1, "\\x", 2);
            count += 2;
            hex[0] = 0;
            hex[1] = 0;
            hex[2] = 0;
            sprintf(hex, "%02X", (unsigned char)*s);
            write(1, hex, 2);
            count += 2;
        } else {
            write(1, s, 1);
            count++;
        }
        s++;
    }
    return count;
}


int print_pointer(va_list args) {
    void *ptr = va_arg(args, void *);
    unsigned long addr = (unsigned long)ptr;
    char buffer[32];
    int count = 0;
    int index = 0;
    int i;
    if (!addr) {
        write(1, "(nil)", 5);
        return 5;
    }
    write(1, "0x", 2);
    count += 2;
    while (addr) {
        unsigned int digit = addr % 16;
        buffer[index++] = digit < 10 ? '0' + digit : 'a' + (digit - 10);
        addr /= 16;
    }
    for (i = index - 1; i >= 0; i--) {
        write(1, &buffer[i], 1);
        count++;
    }
    return count;
}

