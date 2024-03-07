#include "test.h"

START_TEST(test_s21_memchr_1) {
  char test1[] = "123456";
  char test2 = '4';
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, test2, 6),
                    (unsigned long)memchr(test1, test2, 6));
}
END_TEST

START_TEST(test_s21_memchr_2) {
  char test1[] = "123456";
  char test3 = '7';
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, test3, 6),
                    (unsigned long)memchr(test1, test3, 6));
}
END_TEST

START_TEST(test_s21_memchr_3) {
  char test4[] = "hello/\0";
  char test6 = 'h';
  ck_assert_uint_eq((unsigned long)s21_memchr(test4, test6, 6),
                    (unsigned long)memchr(test4, test6, 6));
}
END_TEST

START_TEST(test_s21_memchr_4) {
  char test5[] = "h";
  char test7 = ' ';
  ck_assert_uint_eq((unsigned long)s21_memchr(test5, test7, 1),
                    (unsigned long)memchr(test5, test7, 1));
}
END_TEST

START_TEST(test_s21_memchr_5) {
  char test4[] = "hello/\0";
  char test8 = '/';
  ck_assert_uint_eq((unsigned long)s21_memchr(test4, test8, 6),
                    (unsigned long)memchr(test4, test8, 6));
}
END_TEST

START_TEST(test_s21_memchr_6) {
  char test4[] = "hello/\0";
  char test9 = '\0';
  ck_assert_uint_eq((unsigned long)s21_memchr(test4, test9, 6),
                    (unsigned long)memchr(test4, test9, 6));
}
END_TEST

Suite *make_memchr_suite(void) {
  Suite *s = suite_create("memchr");
  TCase *tc_strings = tcase_create("strings");
  suite_add_tcase(s, tc_strings);
  tcase_add_test(tc_strings, test_s21_memchr_1);
  tcase_add_test(tc_strings, test_s21_memchr_2);
  tcase_add_test(tc_strings, test_s21_memchr_3);
  tcase_add_test(tc_strings, test_s21_memchr_4);
  tcase_add_test(tc_strings, test_s21_memchr_5);
  tcase_add_test(tc_strings, test_s21_memchr_6);
  return s;
}