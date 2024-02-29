int s21_strncmp(const char *str1, const char *str2, size_t n) {
  int ans = 0;
  for (size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i]) {
      ans = (int)str1[i] - (int)str2[i];
      break;
    }
  }
  return ans;
}