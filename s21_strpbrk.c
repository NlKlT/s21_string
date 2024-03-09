/*Finds the first character in the string str1 that matches any character
 * specified in str2.*/
#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1 != '\0') {
    for (s21_size_t i = 0; i < s21_strlen(str2);
         i++) {  // s21_strlen, s21_size_t
      if (*str1 == str2[i]) {
        return (char *)str1;
      }
    }
    str1++;
  }
  return s21_NULL;  // s21_NULL
}