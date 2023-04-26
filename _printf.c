#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

void print_unsigned(unsigned int u, char *buffer, int *buffer_index);
void print_octal(unsigned int o, char *buffer, int *buffer_index);
void print_hex(unsigned int x, int uppercase, char *buffer, int *buffer_index);
int count_digits(unsigned int num);
void print_binary(unsigned int b, char *buffer, int *buffer_index);
void flush_buffer(char *buffer, int *buffer_index);

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    const char *p;
    char buffer[BUFFER_SIZE];
    int buffer_index = 0;

    va_start(args, format);

    for (p = format; *p != '\0'; p++)
    {
        if (*p != '%')
        {
            buffer[buffer_index++] = *p;
            count++;

            if (buffer_index == BUFFER_SIZE)
            {
                flush_buffer(buffer, &buffer_index);
            }
            continue;
        }

        flush_buffer(buffer, &buffer_index);
        p++;

        switch (*p)
        {
            case 'u':
            {
                unsigned int u = va_arg(args, unsigned int);
                print_unsigned(u, buffer, &buffer_index);
                count += count_digits(u);
                break;
            }
            case 'o':
            {
                unsigned int o = va_arg(args, unsigned int);
                print_octal(o, buffer, &buffer_index);
                count += count_digits(o);
                break;
            }
            case 'x':
            {
                unsigned int x = va_arg(args, unsigned int);
                print_hex(x, 0, buffer, &buffer_index);
                count += count_digits(x);
                break;
            }
            case 'X':
            {
                unsigned int x = va_arg(args, unsigned int);
                print_hex(x, 1, buffer, &buffer_index);
                count += count_digits(x);
                break;
            }
            case 'b':
            {
                unsigned int b = va_arg(args, unsigned int);
                print_binary(b, buffer, &buffer_index);
                count += count_digits(b);
                break;
            }
            default:
            {
                buffer[buffer_index++] = '%';
                buffer[buffer_index++] = *p;
                count += 2;
                break;
            }
        }
    }

    flush_buffer(buffer, &buffer_index);
    va_end(args);
    return count;
}

void print_unsigned(unsigned int u, char *buffer, int *buffer_index)
{
    if (u / 10 != 0)
        print_unsigned(u / 10, buffer, buffer_index);
    buffer[*buffer_index++] = '0' + (u % 10);
}

void print_octal(unsigned int o, char *buffer, int *buffer_index)
{
    if (o / 8 != 0)
        print_octal(o / 8, buffer, buffer_index);
    buffer[*buffer_index++] = '0' + (o % 8);
}

void print_hex(unsigned int x, int uppercase, char *buffer, int *buffer_index)
{
    char c;
    if (x / 16 != 0)
        print_hex(x / 16, uppercase, buffer, buffer_index);
    c = (x % 16) + (x % 16 < 10 ? '0' : (uppercase ? 'A' : 'a') - 10);
    buffer[*buffer_index++] = c;
}

int count_digits(unsigned int num)
{
    int count = 0;
    while (num > 0)
    {
        count++;
        num /= 10;
    }
    return count;
}

void print_binary(unsigned int b, char *buffer, int *buffer_index)
{
    if (b / 2 != 0)
        print_binary(b / 2, buffer, buffer_index);
    buffer[*buffer_index++] = '0' + (b % 2);
}

void flush_buffer(char *buffer, int *buffer_index)
{
    if (*buffer_index > 0)
    {
        write(1, buffer, *buffer_index);
        *buffer_index = 0;
    }
}

