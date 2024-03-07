#include "test.h"

START_TEST(test_s21_memcmp_1) {
  char test1[] = "Dog Bark Every Hour";
  char test2[] = "Dog dont sleep";
  ck_assert_uint_eq(s21_memcmp(test1, test2, 16) < 0, memcmp(test1, test2, 16) < 0);
}
END_TEST

START_TEST(test_s21_memcmp_2) {
  char test1[] = "Dog Bark Every Hour";
  char test3[] = "\0";
  ck_assert_uint_eq(s21_memcmp(test1, test3, 2) > 0, memcmp(test1, test3, 2) > 0);
}
END_TEST

START_TEST(test_s21_memcmp_3) {
  char test2[] = "Dog dont sleep";
  char test3[] = "\0";
  ck_assert_uint_eq(s21_memcmp(test2, test3, 2) > 0, memcmp(test2, test3, 2) > 0);
}
END_TEST

START_TEST(test_s21_memcmp_4) {
  char test4[] = "good\0 work";
  char test1[] = "Dog Bark Every Hour";
  ck_assert_uint_eq(s21_memcmp(test4, test1, 9) > 0, memcmp(test4, test1, 9) > 0);
}
END_TEST

START_TEST(test_s21_memcmp_5) {
  char test4[] = "good\0 work";
  char test5[] = "good\0 work";
  ck_assert_uint_eq(s21_memcmp(test4, test5, 7) == 0, memcmp(test4, test5, 7) == 0);
}
END_TEST

Suite *make_memcmp_suite(void) {
  Suite *s = suite_create("memcmp");
  TCase *tc_strings = tcase_create("strings");
  suite_add_tcase(s, tc_strings);
  tcase_add_test(tc_strings, test_s21_memcmp_1);
  tcase_add_test(tc_strings, test_s21_memcmp_2);
  tcase_add_test(tc_strings, test_s21_memcmp_3);
  tcase_add_test(tc_strings, test_s21_memcmp_4);
  tcase_add_test(tc_strings, test_s21_memcmp_5);
  return s;
}