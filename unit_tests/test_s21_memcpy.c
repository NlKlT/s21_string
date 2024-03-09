#include "test.h"

START_TEST(test_s21_memcpy_1) {
  char test_1[10] = "12345";
  char test_2[] = "  ";
  ck_assert_str_eq(s21_memcpy(test_1, test_2, 2), memcpy(test_1, test_2, 2));
}
END_TEST

START_TEST(test_s21_memcpy_2) {
  char test_3[20] = "///  ";
  char test_4[] = "   ///";
  ck_assert_str_eq(s21_memcpy(test_3, test_4, 6), memcpy(test_3, test_4, 6));
}
END_TEST

START_TEST(test_s21_memcpy_3) {
  char test_5[30] = "";
  char test_6[] = "4444";
  ck_assert_str_eq(s21_memcpy(test_5, test_6, 4), memcpy(test_5, test_6, 4));
}
END_TEST

START_TEST(test_s21_memcpy_4) {
  char test_5[30] = "";
  char test_7[] = "123\0123";
  ck_assert_str_eq(s21_memcpy(test_5, test_7, 6), memcpy(test_5, test_7, 6));
}
END_TEST

Suite *make_memcpy_suite(void) {
  Suite *s = suite_create("memcpy");
  TCase *tc_strings = tcase_create("strings");
  suite_add_tcase(s, tc_strings);
  tcase_add_test(tc_strings, test_s21_memcpy_1);
  tcase_add_test(tc_strings, test_s21_memcpy_2);
  tcase_add_test(tc_strings, test_s21_memcpy_3);
  tcase_add_test(tc_strings, test_s21_memcpy_4);
  return s;
}