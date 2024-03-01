/*Searches for the last occurrence of the character c (an unsigned char) in the
 * string pointed to by the argument str.*/
#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  for (s21_size_t i = s21_strlen(str); i >= 0; i--) {  // s21_strlen, s21_size_t
    if (str[i] == c) {
      return ((char *)str) + i;
    }
  }
  return s21_NULL;  // s21_NULL
}