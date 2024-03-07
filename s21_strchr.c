char *s21_strchr(const char *str, int c) {
  s21_size_t len = strlen(str);
  char *ans = NULL;
  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] == c) {
      ans = (char *)(i + str);
      break;
    }
  }
  return ans;
}