#include "test.h"

void runtest(Suite *make_suite, int *result);

int main(void) {
  int result = 0;

  runtest(make_strpbrk_suite(), &result);
  runtest(make_strrchr_suite(), &result);
  runtest(make_strstr_suite(), &result);
  runtest(make_strtok_suite(), &result);

  return (result == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void runtest(Suite *make_suite, int *result) {
  int n;
  SRunner *sr;
  sr = srunner_create(make_suite);
  srunner_run_all(sr, CK_NORMAL);
  n = srunner_ntests_failed(sr);
  *result += n;
  srunner_free(sr);
}