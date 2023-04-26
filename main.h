/* main.h */
#ifndef MAIN_H
#define MAIN_H
#define BUFFER_SIZE 1024

#include <stdarg.h>
#include <unistd.h>

int _printf(const char *format, ...);
void print_unsigned(unsigned int u, char *buffer, int *buffer_index);
void print_octal(unsigned int o, char *buffer, int *buffer_index);
void print_hex(unsigned int x, int uppercase, char *buffer, int *buffer_index);
int count_digits(unsigned int num);
void print_binary(unsigned int b, char *buffer, int *buffer_index);
void flush_buffer(char *buffer, int *buffer_index);

#endif /* MAIN_H */

