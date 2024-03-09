#include "test.h"

START_TEST(test_s21_strerror_1) {
  for (int i = 0; i < 107; i++) {
    ck_assert_pstr_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(test_s21_strerror_2) {
  ck_assert_pstr_eq(s21_strerror(-1), strerror(-1));
}
END_TEST

START_TEST(test_s21_strerror_3) {
  ck_assert_pstr_eq(s21_strerror(0), strerror(0));
}
END_TEST

START_TEST(test_s21_strerror_4) {
  ck_assert_pstr_eq(s21_strerror(130), strerror(130));
}
END_TEST

Suite *make_s21_strerror(void) {
  Suite *s = suite_create("Functions checking");
  TCase *tc_strerror = tcase_create("strerror_test");

  suite_add_tcase(s, tc_strerror);
  tcase_add_test(tc_strerror, test_s21_strerror_1);
  tcase_add_test(tc_strerror, test_s21_strerror_2);
  tcase_add_test(tc_strerror, test_s21_strerror_3);
  tcase_add_test(tc_strerror, test_s21_strerror_4);

  return s;
}
