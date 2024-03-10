#include "test.h"

START_TEST(test_s21_strtok_1) {
  char str1[] = "word1/word2/word3/word4";
  char str2[] = "word1/word2/word3/word4";
  char str3[] = "/";
  ck_assert_pstr_eq(s21_strtok(str1, str3), strtok(str2, str3));
}
END_TEST

START_TEST(test_s21_strtok_2) {
  char str1[] = "";
  char str2[] = "";
  char str3[] = ",";
  ck_assert_pstr_eq(s21_strtok(str1, str3), strtok(str2, str3));
}
END_TEST

START_TEST(test_s21_strtok_3) {
  char str1[] = "word1/word2/word3";
  char str2[] = "word1/word2/word3";
  char str3[] = "";
  ck_assert_pstr_eq(s21_strtok(str1, str3), strtok(str2, str3));
}
END_TEST

START_TEST(test_s21_strtok_4) {
  char str1[] = "\0word1/word2/word3";
  char str2[] = "\0word1/word2/word3";
  char str3[] = "/";
  ck_assert_pstr_eq(s21_strtok(str1, str3), strtok(str2, str3));
}
END_TEST

START_TEST(test_s21_strtok_5) {
  char str1[] = "word1/word2/word3";
  char str2[] = "word1/word2/word3";
  char str3[] = "/word3";
  ck_assert_pstr_eq(s21_strtok(str1, str3), strtok(str2, str3));
}
END_TEST

START_TEST(test_s21_strtok_6) {
  char str1[] = "word1/word2/word3";
  char str2[] = "word1/word2/word3";
  char str3[] = "\0";
  ck_assert_pstr_eq(s21_strtok(str1, str3), strtok(str2, str3));
}
END_TEST

START_TEST(test_s21_strtok_7) {
  char str1[] = "";
  char str2[] = "";
  char str3[] = "";
  ck_assert_pstr_eq(s21_strtok(str1, str3), strtok(str2, str3));
}
END_TEST

Suite *make_strtok_suite(void) {
  Suite *s = suite_create("strtok");
  TCase *tc_strings = tcase_create("strings");
  suite_add_tcase(s, tc_strings);
  tcase_add_test(tc_strings, test_s21_strtok_1);
  tcase_add_test(tc_strings, test_s21_strtok_2);
  tcase_add_test(tc_strings, test_s21_strtok_3);
  tcase_add_test(tc_strings, test_s21_strtok_4);
  tcase_add_test(tc_strings, test_s21_strtok_5);
  tcase_add_test(tc_strings, test_s21_strtok_6);
  tcase_add_test(tc_strings, test_s21_strtok_7);
  return s;
}