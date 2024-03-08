#include "test.h"

START_TEST(s21_strncmp_test1) {
    char s21_str1[] = "abcde";
    char s21_str2[] = "abcde";
    char str1[] = "abcde";
    char str2[] = "abcde";
    ck_assert_int_eq(s21_strncmp(s21_str1, s21_str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(s21_strncmp_test2) {
    char s21_str1[] = "abcde";
    char s21_str2[] = "abcDE";
    char str1[] = "abcde";
    char str2[] = "abcDE";
    ck_assert_int_eq(s21_strncmp(s21_str1, s21_str2, 5), strncmp(str1, str2, 5));
}
END_TEST

START_TEST(s21_strncmp_test3) {
    char s21_str1[] = "abcde";
    char s21_str2[] = "abcDE";
    char str1[] = "abcde";
    char str2[] = "abcDE";
    ck_assert_int_eq(s21_strncmp(s21_str1, s21_str2, 3), strncmp(str1, str2, 3));
}
END_TEST

START_TEST(s21_strncmp_test4) {
    char s21_str1[] = "abcde";
    char s21_str2[] = "abcDE";
    char str1[] = "abcde";
    char str2[] = "abcDE";
    ck_assert_int_eq(s21_strncmp(s21_str1, s21_str2, 1), strncmp(str1, str2, 1));
}
END_TEST

START_TEST(s21_strncmp_test5) {
    char s21_str1[] = "abcde";
    char s21_str2[] = "abcDE";
    char str1[] = "abcde";
    char str2[] = "abcDE";
    ck_assert_int_eq(s21_strncmp(s21_str1, s21_str2, 0), strncmp(str1, str2, 0));
}
END_TEST

START_TEST(s21_strncmp_test6) {
    char s21_str1[] = "abcde";
    char s21_str2[] = "abcde";
    char str1[] = "abcde";
    char str2[] = "abcde";
    ck_assert_int_eq(s21_strncmp(s21_str1, s21_str2, 10), strncmp(str1, str2, 10));
}
END_TEST

START_TEST(s21_strncmp_test7) {
    char s21_str1[] = "abcde";
    char s21_str2[] = "ab";
    char str1[] = "abcde";
    char str2[] = "ab";
    ck_assert_int_eq(s21_strncmp(s21_str1, s21_str2, 10), strncmp(str1, str2, 10));
}
END_TEST

Suite *make_strncmp_suite(void) {
    Suite *s = suite_create("strncmp");
    TCase *tc_strcmp = tcase_create("strncmp_test");
    suite_add_tcase(s, tc_strcmp);
    tcase_add_test(tc_strcmp, s21_strncmp_test1);
    tcase_add_test(tc_strcmp, s21_strncmp_test2);
    tcase_add_test(tc_strcmp, s21_strncmp_test3);
    tcase_add_test(tc_strcmp, s21_strncmp_test4);
    tcase_add_test(tc_strcmp, s21_strncmp_test5);
    tcase_add_test(tc_strcmp, s21_strncmp_test6);
    tcase_add_test(tc_strcmp, s21_strncmp_test7);
    return s;
}