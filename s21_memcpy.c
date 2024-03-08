#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *csrc = (char *)src;
  char *cdest = (char *)dest;
  for (size_t i = 0; i < n; i++) {
    cdest[i] = csrc[i];
  }
  return dest;
}
