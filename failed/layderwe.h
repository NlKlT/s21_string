#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_
#include <stdlib.h>
#define s21_NULL ((void*)0)
typedef unsigned long s21_size_t;

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);

#endif  // SRC_S21_STRING_H_
