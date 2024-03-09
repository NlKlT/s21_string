#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, size_t n) {
    const unsigned char *u1, *u2;
    u1 = str1, u2 = str2;

    for (; n--; u1++, u2++) {
        if (*u1 != *u2) {
            return (*u1 - *u2);
        }
    }
    return 0;
}
