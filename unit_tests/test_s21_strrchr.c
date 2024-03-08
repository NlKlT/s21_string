#include "test.h"

// START_TEST(test_s21_strrchr_1) {
//   char str1[] = "";
//   char str2 = '';
//   ck_assert_str_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
// }
// END_TEST

START_TEST(test_s21_strrchr_2) {
  char str1[] = "123453783";
  char str2 = '3';
  ck_assert_str_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(test_s21_strrchr_3) {
  char str1[] = "123456789";
  char str2 = '3';
  ck_assert_str_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(test_s21_strrchr_4) {
  char str1[] = "words";
  int str2 = 'o';
  ck_assert_str_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(test_s21_strrchr_5) {
  char str1[] = "words";
  int str2 = '\0';
  ck_assert_str_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

// START_TEST(test_s21_strrchr_6) {
//   char str1[] = "words";
//   char str2 = (int) '';
//   ck_assert_str_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
// }
// END_TEST

START_TEST(test_s21_strrchr_7) {
  char str1[] = "words";
  int str2 = 's';
  ck_assert_str_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

Suite *make_strrchr_suite(void) {
  Suite *s = suite_create("strrchr");
  TCase *tc_strings = tcase_create("strings");
  suite_add_tcase(s, tc_strings);
  //tcase_add_test(tc_strings, test_s21_strrchr_1);
  tcase_add_test(tc_strings, test_s21_strrchr_2);
  tcase_add_test(tc_strings, test_s21_strrchr_3);
  tcase_add_test(tc_strings, test_s21_strrchr_4);
  tcase_add_test(tc_strings, test_s21_strrchr_5);
  //tcase_add_test(tc_strings, test_s21_strrchr_6);
  tcase_add_test(tc_strings, test_s21_strrchr_7);
  return s;
}