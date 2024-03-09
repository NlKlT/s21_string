#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_NULL ((void *)0)
typedef unsigned long s21_size_t;

#ifdef __linux
#define MAX_ERRNO 134
#define UNKNOWN_ERROR "Unknown error "
#endif

#ifdef __APPLE__
#define MAX_ERRNO 107
#define UNKNOWN_ERROR "Unknown error: "
#endif

// Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
// указатель на строку с сообщением об ошибке. Нужно объявить макросы,
// содержащие массивы сообщений об ошибке для операционных систем mac и linux.
// Описания ошибок есть в оригинальной библиотеке. Проверка текущей ОС
// осуществляется с помощью директив.

// для sprintf
#define is_flag(ch) \
  ((ch) == '-' || (ch) == '+' || (ch) == ' ' || (ch) == '#' || (ch) == '0')

#define is_digit(ch) ((ch) >= '0' && (ch) <= '9')

#define is_length(ch) ((ch) == 'h' || (ch) == 'l' || (ch) == 'L')

#define is_specifier(ch)                                                      \
  ((ch) == 'c' || (ch) == 'd' || (ch) == 'i' || (ch) == 'e' || (ch) == 'E' || \
   (ch) == 'f' || (ch) == 'g' || (ch) == 'G' || (ch) == 'o' || (ch) == 's' || \
   (ch) == 'u' || (ch) == 'x' || (ch) == 'X' || (ch) == 'p' || (ch) == 'n' || \
   (ch) == '%')

char *s21_strncat(char *dest, const char *src, s21_size_t n);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strchr(const char *str,
                 int c);  // для работы нужна функция s21_strlen
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);

char *s21_strncat(char *dest, const char *src,
                  s21_size_t n);  // для работы нужна функция s21_strlen
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
char *s21_strcat(char *dest, const char *src);
char *s21_strcpy(char *dest, const char *src);
int s21_sprintf(char *str, const char *format, ...);

// для sprintf

typedef struct format_part {
  int flag_minus;
  int flag_plus;
  int flag_space;
  int flag_sharp;
  int flag_zero;
  int width;
  int precision;
  char length;
  char specifier;
  int sign;
  int point;
} format_part;

void sprintf_check_flag(format_part *parameters, const char *format);
void sprintf_default_precision(format_part *parameters);
char *sprintf_check_specifier(char *str, s21_size_t *str_len, va_list *args,
                              format_part *parameters);
void sprintf_move_string(char *string_from_cs);
void sprintf_reverse_str(char *string_from_cs);
void sprintf_make_str_precision(format_part *parameters, char *string_from_cs);

char *sprintf_str_int(int *number, const char *format, va_list *args);
void sprintf_int_str(format_part *parameters, char *string_from_cs,
                     long double number);
void sprintf_eE_str(char *string_from_cs, long double number,
                    format_part *parameters);
void sprintf_float_str(char *string_from_cs, long double number,
                       format_part *parameters);
void sprintf_gG_str(char *string_from_cs, long double number,
                    format_part *parameters);
void sprintf_ol_str(char *string_from_cs, unsigned long long number,
                    int prefix);
void sprintf_ul_str(char *string_from_cs, unsigned long long number,
                    format_part *parameters);
void sprintf_hl_str(char *string_from_cs, unsigned long long number,
                    format_part *parameters);

void sprintf_make_str_flags(format_part *parameters, char *string_from_cs);
void sprintf_make_str_width(format_part *parameters, char *string_from_cs);

void sprintf_spec_di(char *string_from_cs, va_list *args,
                     format_part *parameters);
void sprintf_spec_eE(char *string_from_cs, va_list *args,
                     format_part *parameters);
void sprintf_spec_f(char *string_from_cs, va_list *args,
                    format_part *parameters);
void sprintf_spec_gG(char *string_from_cs, va_list *args,
                     format_part *parameters);
void sprintf_spec_o(char *string_from_cs, va_list *args,
                    format_part *parameters);
void sprintf_spec_p(char *string_from_cs, va_list *args,
                    format_part *parameters);
void sprintf_spec_s(char *string_from_cs, va_list *args,
                    format_part *parameters);
void sprintf_spec_u(char *string_from_cs, va_list *args,
                    format_part *parameters);
void sprintf_spec_xX(char *string_from_cs, va_list *args,
                     format_part *parameters);

void sprintf_sharp_flag(format_part *parameters, char *string_from_cs);
void sprintf_delete_zero(format_part *parameters, char *string_from_cs);
void sprintf_mantissa(format_part *parameters, char *mantice, int notation);

int sprintf_make_expo(long double number);
void sprintf_make_sign(double number, format_part *parameters);

#endif  // SRC_S21_STRING_H_