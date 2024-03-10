#include "test.h"

START_TEST(s21_insert1_func) {
  const char *src = "Hello, world!";
  const char *str = "beautiful ";
  s21_size_t start_index = 7;
  void *result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, "Hello, beautiful world!");
  free(result);
}
END_TEST

START_TEST(s21_insert2_func) {
  const char *src = "Hello";
  const char *str = "";
  s21_size_t start_index = 3;
  void *result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(s21_insert3_func) {
  const char *src = "";
  const char *str = "";
  s21_size_t start_index = 7;
  void *result = s21_insert(src, str, start_index);
  ck_assert_ptr_eq(result, s21_NULL);
  free(result);
}
END_TEST

START_TEST(s21_insert4_func) {
  const char *src = "Hello";
  const char *str = "beautiful ";
  s21_size_t start_index = 9;
  void *result = s21_insert(src, str, start_index);
  ck_assert_ptr_eq(result, s21_NULL);
  free(result);
}
END_TEST

START_TEST(s21_insert5_func) {
  const char *src = "";
  const char *str = "beautiful ";
  s21_size_t start_index = 0;
  void *result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, "beautiful ");
  free(result);
}
END_TEST

START_TEST(s21_insert6_func) {
  const char *src = s21_NULL;
  const char *str = s21_NULL;
  s21_size_t start_index = 3;
  void *result = s21_insert(src, str, start_index);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

START_TEST(s21_insert7_func) {
  const char *src = s21_NULL;
  const char *str = "beautiful";
  s21_size_t start_index = 3;
  void *result = s21_insert(src, str, start_index);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

START_TEST(s21_insert8_func) {
  const char *src = "It is life";
  const char *str = s21_NULL;
  s21_size_t start_index = 3;
  void *result = s21_insert(src, str, start_index);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

START_TEST(s21_insert9_func) {
  const char *src = "Hello";
  const char *str = "Start ";
  s21_size_t start_index = 0;
  void *result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, "Start Hello");
  free(result);
}
END_TEST

START_TEST(s21_insert10_func) {
  const char *src = "Hello";
  const char *str = "End";
  s21_size_t start_index = 5;
  void *result = s21_insert(src, str, start_index);
  ck_assert_str_eq(result, "HelloEnd");
  free(result);
}
END_TEST

Suite *make_insert_suite(void) {
  Suite *s = suite_create("insert");
  TCase *tc_insert = tcase_create("insert_func");
  suite_add_tcase(s, tc_insert);
  tcase_add_test(tc_insert, s21_insert1_func);
  tcase_add_test(tc_insert, s21_insert2_func);
  tcase_add_test(tc_insert, s21_insert3_func);
  tcase_add_test(tc_insert, s21_insert4_func);
  tcase_add_test(tc_insert, s21_insert5_func);
  tcase_add_test(tc_insert, s21_insert6_func);
  tcase_add_test(tc_insert, s21_insert7_func);
  tcase_add_test(tc_insert, s21_insert8_func);
  tcase_add_test(tc_insert, s21_insert9_func);
  tcase_add_test(tc_insert, s21_insert10_func);

  return s;
}
