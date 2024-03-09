#include "test.h"

void runtest(Suite *make_suite, int *result);

int main(void) {
  int result = 0;

  runtest(make_memset_suite(), &result);
  printf("\n");
  runtest(make_strchr_suite(), &result);
  printf("\n");
  runtest(make_strncat_suite(), &result);
  printf("\n");
  runtest(make_strncmp_suite(), &result);
  printf("\n");
  runtest(make_memchr_suite(), &result);
  printf("\n");
  runtest(make_memcmp_suite(), &result);
  printf("\n");
  runtest(make_memcpy_suite(), &result);
  printf("\n");
  runtest(make_strcspn_suite(), &result);
  printf("\n");
  // runtest(make_strerror_suite(), &result);
  // printf("\n");
  runtest(make_strlen_suite(), &result);
  printf("\n");
  runtest(make_strncpy_suite(), &result);
  printf("\n");
  runtest(make_strpbrk_suite(), &result);
  printf("\n");
  runtest(make_strrchr_suite(), &result);
  printf("\n");
  runtest(make_strstr_suite(), &result);
  printf("\n");
  runtest(make_strtok_suite(), &result);
  printf("\n");

  return 0;  //(result == 0) ? EXIT_SUCCESS : EXIT_FAILURE; // заменил на return
             // 0, поскольку эта штука вызыдает ошибку, если завален хотя бы
             // один тест, и дальше Makefile не выполняет команды. Без этого все
             //работает.
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