#include "s21_string.h"

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) return s21_NULL;

  s21_size_t len = s21_strlen(str);
  void *res = calloc(len + 1, sizeof(char));
  if (res != s21_NULL) {
    char *upper_str = (char *)res;
    for (s21_size_t i = 0; i < len; ++i) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        upper_str[i] = str[i] - ('a' - 'A');
      } else {
        upper_str[i] = str[i];
      }
    }
  }
  return res;
}