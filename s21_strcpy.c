#include "s21_string.h"

// Basic implementation of s21_strcpy
char *s21_strcpy(char *dest, const char *src) {
  char *save = dest;
  while ((*dest++ = *src++))
    ;
  return save;
}