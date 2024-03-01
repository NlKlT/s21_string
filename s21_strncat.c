char *s21_strncat(char *dest, const char *src, size_t n) {
  size_t ptr = s21_strlen(dest);
  for (size_t i = 0; i < n; i++) dest[ptr + i] = src[i];
  *(dest + ptr + s21_strlen(src)) = '\0';
  return dest;
}