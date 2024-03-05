#include <stdio.h>

char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

typedef struct {
  int precision;
  char length;
} flags;

const char *length(const char *format, flags *f);
const char *precision(const char *format, flags *f, va_list arg_ptr);