#include <stddef.h> // здесь определен тип size_t и макрос NULL

void *s21_memset(void *str, int c, size_t n);
char *s21_strncat(char *dest, const char *src, size_t n); // для работы нужна функция s21_strlen
char *s21_strchr(const char *str, int c); // для работы нужна функция s21_strlen
int s21_strncmp(const char *str1, const char *str2, size_t n);

void *s21_memset(void *str, int c, size_t n) {
    for (size_t i = 0; i <= n; i++) *((char *) str + i) = c;
    return str; 
}

char *s21_strncat(char *dest, const char *src, size_t n) { 
    size_t ptr = s21_strlen(dest);
    for (size_t i = 0; i < n; i++) dest[ptr + i] = src[i];
    *(dest + ptr + s21_strlen(src)) = '\0';
    return dest;
}

char *s21_strchr(const char *str, int c) {
    size_t len = s21_strlen(str);
    char *ans = NULL;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == c) {
            ans = (char *) (i + str);
            break;
        }
    }
    return ans;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
    int ans = 0;
    for (size_t i = 0; i < n; i++) {
        if (str1[i] != str2[i]) {
            ans = (int) str1[i] - (int) str2[i];
            break;
        }
    }
    return ans;
}