s21_size_t s21_strlen(const char *str) {
  s21_size_t res = 0;
  char *p = (char *)str;
  while (*p != '\0') {
    p++;
    res++;
  }
  return res;
}