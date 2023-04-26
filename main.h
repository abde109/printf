#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>

int _printf(const char *format, ...);
void print_number(int num);
void print_binary(unsigned int num);
int count_binary_digits(unsigned int num);
void print_unsigned(unsigned int num);
void print_octal(unsigned int num);
void print_hex(unsigned int num, int uppercase);

#endif /* MAIN_H */

