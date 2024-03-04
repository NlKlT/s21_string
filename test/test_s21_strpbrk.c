#include "test.h"

START_TEST(test_s21_strpbrk_1) {
  char str1[] = "";
  char str2[] = "";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_2) {
  char str1[] = "123456789";
  char str2[] = "3";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_3) {
  char str1[] = "123456789";
  char str2[] = "9";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_4) {
  char str1[] = "\0";
  char str2[] = "";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_5) {
  char str1[] = "\0";
  char str2[] = "";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_6) {
  char str1[] = "";
  char str2[] = "123";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_7) {
  char str1[] = "Words";
  char str2[] = "or";
  ck_assert_str_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

Suite *make_strpbrk_suite(void) {
  Suite *s = suite_create("strpbrk");
  TCase *tc_strings = tcase_create("strings");
  suite_add_tcase(s, tc_strings);
  tcase_add_test(tc_strings, test_s21_strpbrk_1);
  tcase_add_test(tc_strings, test_s21_strpbrk_2);
  tcase_add_test(tc_strings, test_s21_strpbrk_3);
  tcase_add_test(tc_strings, test_s21_strpbrk_4);
  tcase_add_test(tc_strings, test_s21_strpbrk_5);
  tcase_add_test(tc_strings, test_s21_strpbrk_6);
  tcase_add_test(tc_strings, test_s21_strpbrk_7);
  return s;
}