#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <stdio.h>
#include <stdlib.h>

#define s21_NULL ((void*)0)
typedef unsigned long s21_size_t;

#ifdef __linux
#define MAX_ERRNO 134
#define UNKNOWN_ERROR "Unknown error "
#endif

#ifdef __APPLE__
#define MAX_ERRNO 107
#define UNKNOWN_ERROR "Unknown error: "
#endif

// Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
// указатель на строку с сообщением об ошибке. Нужно объявить макросы,
// содержащие массивы сообщений об ошибке для операционных систем mac и linux.
// Описания ошибок есть в оригинальной библиотеке. Проверка текущей ОС
// осуществляется с помощью директив.

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, size_t n);
char *s21_strchr(const char *str, int c);  // для работы нужна функция s21_strlen
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strncat(char *dest, const char *src, size_t n);  // для работы нужна функция s21_strlen
int s21_strncmp(const char *str1, const char *str2, size_t n);
char *s21_strncpy(char *dest, const char *src, size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

#endif  // SRC_S21_STRING_H_