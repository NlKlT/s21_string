#include "test.h"

START_TEST(test_s21_strstr_1) {
  char str1[] = "123456789";
  char str2[] = "345";
  ck_assert_str_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_2) {
  char str1[] = "123";
  char str2[] = "";
  ck_assert_str_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_3) {
  char str1[] = "word word word";
  char str2[] = "or";
  ck_assert_str_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_4) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_str_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_5) {
  char str1[] = "word";
  char str2[] = "d";
  ck_assert_str_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_6) {
  char str1[] = "word";
  char str2[] = "\0";
  ck_assert_str_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_7) {
  char str1[] = "word";
  char str2[] = "words";
  ck_assert_ptr_null(s21_strstr(str1, str2));
  ck_assert_ptr_null(strstr(str1, str2));
}
END_TEST

Suite *make_strstr_suite(void) {
  Suite *s = suite_create("strstr");
  TCase *tc_strings = tcase_create("strings");
  suite_add_tcase(s, tc_strings);
  tcase_add_test(tc_strings, test_s21_strstr_1);
  tcase_add_test(tc_strings, test_s21_strstr_2);
  tcase_add_test(tc_strings, test_s21_strstr_3);
  tcase_add_test(tc_strings, test_s21_strstr_4);
  tcase_add_test(tc_strings, test_s21_strstr_5);
  tcase_add_test(tc_strings, test_s21_strstr_6);
  tcase_add_test(tc_strings, test_s21_strstr_7);
  return s;
}