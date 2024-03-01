/*Finds the first character in the string str1 that matches any character
 * specified in str2.*/

#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  size_t len = 0;  // заменить на s21_size_t
  while (str2[len] != '\0') {
    len++;
  }

  while (*str1 != '\0') {
    for (size_t i = 0; i < len; i++) {  // s21_size_t
      if (*str1 == str2[i]) {
        return (char *)str1;
      }
    }
    str1++;
  }
  return NULL;  // s21_NULL
}

// #include <string.h>
// int main() {
//   const char *str1 = "creamrrr";
//   const char *str2 = "a";
//   printf("%s\n", strpbrk(str1, str2));
//   printf("%s", s21_strpbrk(str1, str2));
// }