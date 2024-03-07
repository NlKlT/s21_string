char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t ptr = strlen(dest);
  for (s21_size_t i = 0; i < n; i++) dest[ptr + i] = src[i];
  *(dest + ptr + strlen(src)) = '\0';
  return dest;
}