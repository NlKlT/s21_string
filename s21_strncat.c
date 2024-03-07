#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t ptr = s21_strlen(dest);
  for (s21_size_t i = 0; i < n; i++) dest[ptr + i] = src[i];
  *(dest + ptr + s21_strlen(src)) = '\0';
  return dest;
}