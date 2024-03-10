#include "test.h"

START_TEST(s21_trim1_func) {
  const char *src = "*Hello, beautiful World !**";
  const char *trim_chars = "*H!";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "ello, beautiful World ");
  free(result);
}
END_TEST

START_TEST(s21_trim2_func) {
  const char *src = "**Hello, World!**";
  const char *trim_chars = "*!HdelroW, ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(s21_trim3_func) {
  const char *trim_chars = "*H!";
  char *result = s21_trim(s21_NULL, trim_chars);
  ck_assert_ptr_eq(result, s21_NULL);
  free(result);
}
END_TEST

START_TEST(s21_trim4_func) {
  const char *src = "**Hello, World!**";
  const char *trim_chars = "";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "**Hello, World!**");
  free(result);
}
END_TEST

START_TEST(s21_trim5_func) {
  const char *src = "Hello1";
  const char *trim_chars = "hello2";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello1");
  free(result);
}
END_TEST

Suite *make_trim_suite(void) {
  Suite *s = suite_create("trim");
  TCase *tc_trim = tcase_create("trim_func");
  suite_add_tcase(s, tc_trim);
  tcase_add_test(tc_trim, s21_trim1_func);
  tcase_add_test(tc_trim, s21_trim2_func);
  tcase_add_test(tc_trim, s21_trim3_func);
  tcase_add_test(tc_trim, s21_trim4_func);
  tcase_add_test(tc_trim, s21_trim5_func);

  return s;
}