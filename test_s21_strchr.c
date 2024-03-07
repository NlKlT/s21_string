#include "test.h"

START_TEST(s21_strchr_test1) {
    char str[] = "abcde";
    char symbol = 'a';
    ck_assert_str_eq(s21_strchr(str, symbol), strchr(str, symbol));
}
END_TEST

START_TEST(s21_strchr_test2) {
    char str[] = "abcde";
    char symbol = 'e';
    ck_assert_str_eq(s21_strchr(str, symbol), strchr(str, symbol));
}
END_TEST

START_TEST(s21_strchr_test3) {
    char str[] = "12345";
    char symbol = 'e';
    ck_assert_str_eq(s21_strchr(str, symbol), strchr(str, symbol));
}
END_TEST

START_TEST(s21_strchr_test4) {
    char str[] = "12345";
    char symbol = '1';
    ck_assert_str_eq(s21_strchr(str, symbol), strchr(str, symbol));
}
END_TEST

START_TEST(s21_strchr_test5) {
    char str[] = "12345";
    char symbol = '5';
    ck_assert_str_eq(s21_strchr(str, symbol), strchr(str, symbol));
}
END_TEST

START_TEST(s21_strchr_test6) {
    char str[] = "abcde";
    char symbol = 'c';
    ck_assert_str_eq(s21_strchr(str, symbol), strchr(str, symbol));
}
END_TEST

Suite *make_strchr_suite(void) {
    Suite *suite;
    suite = suite_create("s21_string+ checking");
    TCase *tc_strchr = tcase_create("strchr_test");
    suite_add_tcase(suite, tc_strchr);
    tcase_add_test(tc_strchr, s21_strchr_test1);
    tcase_add_test(tc_strchr, s21_strchr_test2);
    tcase_add_test(tc_strchr, s21_strchr_test3);
    tcase_add_test(tc_strchr, s21_strchr_test4);
    tcase_add_test(tc_strchr, s21_strchr_test5);
    tcase_add_test(tc_strchr, s21_strchr_test6);
}