#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (!src || !str) return s21_NULL;

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  if (start_index > src_len) return s21_NULL;
  s21_size_t new_len = src_len + str_len + 1;
  char *new_str = calloc(new_len, sizeof(char));

  s21_strncpy(new_str, src, start_index);
  s21_strcpy(new_str + start_index, str);
  s21_strcpy(new_str + start_index + str_len, src + start_index);

  return new_str;
}