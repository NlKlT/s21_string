#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  char *rdest = dest;
  while (*dest) {
    dest++;
  }
  while ((*dest++ = *src++)) {
    // Empty body; all work is done in the while condition
  }

  return rdest;
}