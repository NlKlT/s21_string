#ifndef SRC_TEST_TESTS_H
#define SRC_TEST_TESTS_H

#include <check.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

Suite *make_strpbrk_suite(void);
Suite *make_strrchr_suite(void);
Suite *make_strstr_suite(void);
Suite *make_strtok_suite(void);

#endif  // SRC_TEST_TESTS_H