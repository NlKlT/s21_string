#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *trimmed_str = s21_NULL;
  if (src != s21_NULL && trim_chars != s21_NULL) {
    s21_size_t start = 0;
    s21_size_t end = s21_strlen(src) - 1;
    while (src[start] && s21_strchr(trim_chars, src[start]) != s21_NULL) {
      start++;
    }
    while (end > start && s21_strchr(trim_chars, src[end]) != s21_NULL) {
      end--;
    }
    if (start <= end) {
      s21_size_t len = end - start + 2;
      trimmed_str = (char *)calloc(len, sizeof(char));
      if (trimmed_str != s21_NULL) {
        s21_strncpy(trimmed_str, src + start, end - start + 1);
      }
    } else {
      trimmed_str = (char *)calloc(1, sizeof(char));
    }
  }
  return trimmed_str;
}