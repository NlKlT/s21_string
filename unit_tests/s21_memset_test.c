#include "test.h"

START_TEST(s21_memset_test1) {
    char str[] = "abcde";
    char s21_str[] = "abcde";
    char symbol = 'W';
    int n = 1;
    ck_assert_str_eq(s21_memset(s21_str, symbol, n), memset(str, symbol, n));
}
END_TEST

START_TEST(s21_memset_test2) {
    char str[] = "ABCDE";
    char s21_str[] = "abcde";
    char symbol = 'W';
    int n = 2;
    ck_assert_str_eq(s21_memset(s21_str, symbol, n), memset(str, symbol, n));
}
END_TEST

START_TEST(s21_memset_test3) {
    char str[] = "abcde";
    char s21_str[] = "abcde";
    char symbol = 'w';
    int n = 3;
    ck_assert_str_eq(s21_memset(s21_str, symbol, n), memset(str, symbol, n));
}
END_TEST

START_TEST(s21_memset_test4) {
    char str[] = "abcde";
    char s21_str[] = "abcde";
    char symbol = '4';
    int n = 4;
    ck_assert_str_eq(s21_memset(s21_str, symbol, n), memset(str, symbol, n));
}
END_TEST

START_TEST(s21_memset_test5) {
    char str[] = "abcde";
    char s21_str[] = "abcde";
    char symbol = '$';
    int n = 5;
    ck_assert_str_eq(s21_memset(s21_str, symbol, n), memset(str, symbol, n));
}
END_TEST

START_TEST(s21_memset_test6) {
    char str[] = "abcde";
    char s21_str[] = "abcde";
    char symbol = '\n';
    int n = 3;
    ck_assert_str_eq(s21_memset(s21_str, symbol, n), memset(str, symbol, n));
}
END_TEST

START_TEST(s21_memset_test7) {
    char str[] = "abcde";
    char s21_str[] = "abcde";
    char symbol = '\0';
    int n = 3;
    ck_assert_str_eq(s21_memset(s21_str, symbol, n), memset(str, symbol, n));
}
END_TEST

Suite *suite_s21_memset(void) {
  Suite *suite;
  suite = suite_create("s21_string+ checking");
  TCase *tc_memset = tcase_create("memset_test");
  suite_add_tcase(suite, tc_memset);
  tcase_add_test(tc_memset, s21_memset_test1);
  tcase_add_test(tc_memset, s21_memset_test2);
  tcase_add_test(tc_memset, s21_memset_test3);
  tcase_add_test(tc_memset, s21_memset_test4);
  tcase_add_test(tc_memset, s21_memset_test5);
  tcase_add_test(tc_memset, s21_memset_test6);
  tcase_add_test(tc_memset, s21_memset_test7);
  return suite;
}