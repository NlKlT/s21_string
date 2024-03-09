void *s21_memset(void *str, int c, size_t n);
char *s21_strncat(char *dest, const char *src,
                  size_t n);  // для работы нужна функция s21_strlen
char *s21_strchr(const char *str,
                 int c);  // для работы нужна функция s21_strlen
int s21_strncmp(const char *str1, const char *str2, size_t n);