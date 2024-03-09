#include "test.h"

START_TEST(sprintf_test_c) {
  char str1[1024];
  char str2[1024];

  char *format = "%c [%5c] [%+-c] %*c";
  char val = 'f';
  int width = 10;
  ck_assert_int_eq(s21_sprintf(str1, format, val, 'H', L'ы', width, 's'),
                   sprintf(str2, format, val, 'H', L'ы', width, 's'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_d) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  int width = -10;

  char *format = "%d %+d [%+-11d] [%+11.3d] [%011d] %*d %+06d";
  ck_assert_int_eq(
      s21_sprintf(str1, format, 36, 45, 17, 3, -12, width, 12345, 55123455),
      sprintf(str2, format, 36, 45, 17, 3, -12, width, 12345, 55123455));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_i) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  int width = -10;

  char *format = "%.0i %+li [%+-hi] [%+11.3i] [%-011i] %.*i";
  ck_assert_int_eq(
      s21_sprintf(str1, format, 0, 45, 17, 3, -12, width, 1234500000),
      sprintf(str2, format, 0, 45, 17, 3, -12, width, 1234500000));

  ck_assert_str_eq(str1, str2);

  format = "%+4i";
  ck_assert_int_eq(s21_sprintf(str1, format, -456),
                   sprintf(str2, format, -456));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_f) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%.f %+4f %5.4f %.1f %.5f %.11f";
  ck_assert_float_eq(s21_sprintf(str1, format, 34.5, 0.0000123456, 0.000123456,
                                 0.0999, 9.999999999, 12.34),
                     sprintf(str2, format, 34.5, 0.0000123456, 0.000123456,
                             0.0999, 9.999999999, 12.34));
  ck_assert_str_eq(str1, str2);

  format = "%.f %+04f %+ 5.4f %#.f %.5f %.11f";
  ck_assert_float_eq(s21_sprintf(str1, format, 35.5, 0.0000123456, 0.000123456,
                                 0.0999, 9.999999999, 12.34),
                     sprintf(str2, format, 35.5, 0.0000123456, 0.000123456,
                             0.0999, 9.999999999, 12.34));
  ck_assert_str_eq(str1, str2);

  format = "%.5f";
  ck_assert_float_eq(s21_sprintf(str1, format, 9.9999900009999),
                     sprintf(str2, format, 9.9999900009999));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_e) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%4e %+4e %5.4E %.1e %.5E %.11e";
  ck_assert_float_eq(s21_sprintf(str1, format, 0.0000768, 0.0000123456,
                                 0.000123456, 0.0999, 9.999999999, 12.34),
                     sprintf(str2, format, 0.0000768, 0.0000123456, 0.000123456,
                             0.0999, 9.999999999, 12.34));
  ck_assert_str_eq(str1, str2);

  format = "% 4e %+04e %+ 5.4e %#.E %.5e %.11E";
  ck_assert_float_eq(s21_sprintf(str1, format, 0.0000768, 0.0000123456,
                                 0.000123456, 0.0999, 9.999999999, 12.34),
                     sprintf(str2, format, 0.0000768, 0.0000123456, 0.000123456,
                             0.0999, 9.999999999, 12.34));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_g) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "% 4g %+4g %+5.4G %.1g %.5G %.11g %.5g";
  ck_assert_float_eq(
      s21_sprintf(str1, format, 0.0000768, 0.0000123456, 0.000123456, 0.0999,
                  9.999999999, 12.34, 9.99999),
      sprintf(str2, format, 0.0000768, 0.0000123456, 0.000123456, 0.0999,
              9.999999999, 12.34, 9.99999));
  ck_assert_str_eq(str1, str2);

  format = "% 4g %+04g %+5.4g %#.G %.5g %.11G %.1g";
  ck_assert_float_eq(
      s21_sprintf(str1, format, 0.0000768, 0.0000123456, 0.000123456, 0.0999,
                  9.999999999, 12.34, 0.0000002),
      sprintf(str2, format, 0.0000768, 0.0000123456, 0.000123456, 0.0999,
              9.999999999, 12.34, 0.0000002));
  ck_assert_str_eq(str1, str2);

  format = "%#4g";
  ck_assert_float_eq(s21_sprintf(str1, format, 10.05000000),
                     sprintf(str2, format, 10.05000000));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_n) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  int n1 = 0;
  int n2 = 0;

  char *format = "Text for test %nwritting";
  ck_assert_int_eq(s21_sprintf(str1, format, &n1), sprintf(str2, format, &n2));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(sprintf_test_o) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%#4o %+4o %5.4o %.1o %.5o %.11o %.1o";
  ck_assert_int_eq(s21_sprintf(str1, format, 11, -18, 789, 456, 7890, 54, 5678),
                   sprintf(str2, format, 11, -18, 789, 456, 7890, 54, 5678));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_s) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "Test %s %.5s";
  ck_assert_int_eq(s21_sprintf(str1, format, "Prize", "You are winner!!!"),
                   sprintf(str2, format, "Prize", "You are winner!!!"));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_u) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%#4u %+4u %5.4u %.1u %.5u %.11u";
  ck_assert_int_eq(s21_sprintf(str1, format, 11, -18, 789, 456, 7890, 54),
                   sprintf(str2, format, 11, -18, 789, 456, 7890, 54));
  ck_assert_str_eq(str1, str2);

  format = "%.0u %+.4u %5.4u %.1u %.5u %.11u";
  ck_assert_int_eq(s21_sprintf(str1, format, 0, -18, 789, 456, 7890, 0),
                   sprintf(str2, format, 0, -18, 789, 456, 7890, 0));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_test_x) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%#4X %+4x %5.4x %.1X %.5x %.11u";
  ck_assert_int_eq(s21_sprintf(str1, format, 11, -18, 789, 456, 7890, 54),
                   sprintf(str2, format, 11, -18, 789, 456, 7890, 54));
  ck_assert_str_eq(str1, str2);

  format = "%0#X";
  ck_assert_int_eq(s21_sprintf(str1, format, 110), sprintf(str2, format, 110));
  ck_assert_str_eq(str1, str2);
}
END_TEST

// OTHER SPRINTF TESTS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

START_TEST(other_sprintf_1) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%.5i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_2) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%5d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_3) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%-5i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_4) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%+12d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_5) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%012i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_6) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%0*d";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_7) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%0.*i";
  int val = 69;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_8) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char format[] = "%0.*i %d %4.*i %013d %d";
  int val = 69;
  ck_assert_int_eq(
      s21_sprintf(str1, format, 5, val, -10431, 13, 5311, 0, -581813581),
      sprintf(str2, format, 5, val, -10431, 13, 5311, 0, -581813581));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_9) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%+5.31li";
  long int val = 698518581899;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_10) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%-16.9hi";
  short int val = 6958;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_11) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%0.*ld";
  long val = 8581385185;
  ck_assert_int_eq(s21_sprintf(str1, format, 5, val),
                   sprintf(str2, format, 5, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_12) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%.0d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_13) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "% d";
  int val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_14) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_15) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%15u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_16) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%-16u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_17) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%.51u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_18) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "% 5.51u";
  unsigned int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_19) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%hu";
  unsigned short int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_20) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%lu";
  unsigned long int val = 949149114140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_21) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%lu, %u, %hu, %.5u, %5.u";
  unsigned long int val = 949149114140;
  ck_assert_int_eq(
      s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
      sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
              (unsigned)14414, (unsigned)9681));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_22) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%15o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_23) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%-16o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_24) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%.51o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_25) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%-5.51o";
  int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_26) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%o";
  ck_assert_int_eq(s21_sprintf(str1, format, 0), sprintf(str2, format, 0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_27) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%#o";
  int val = 57175;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_28) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%hd";
  short int val = 14140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_29) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%lo";
  long int val = 949149114140;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_30) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%lo, %o, %ho, %.5o, %5.o";
  long int val = 949149114140;
  ck_assert_int_eq(
      s21_sprintf(str1, format, val, 14, 1441, 14414, 9681),
      sprintf(str2, format, val, (unsigned)14, (unsigned short)1441,
              (unsigned)14414, (unsigned)9681));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_31) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%lo";
  long int val = 84518;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_32) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%u";
  ck_assert_int_eq(s21_sprintf(str1, format, 0),
                   sprintf(str2, format, (unsigned)0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_33) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%5x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_34) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%#-10x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_35) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%.15x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_36) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%#-10x%x%X%#x%#X%5.5x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val, val, val, val, val),
                   sprintf(str2, format, val, val, val, val, val, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_37) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%#-5.10x";
  unsigned val = 858158158;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_38) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%#x";
  unsigned val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_39) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%#x";
  unsigned val = 18571;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_40) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%#hx";
  unsigned short val = 12352;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_41) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%#lx";
  unsigned long val = 18571757371571;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_42) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%#2x";
  unsigned val = 1;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_43) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%#30x";
  unsigned val = 1;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_44) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%c";
  char val = 'X';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_45) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%.5c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_46) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "% -5c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_47) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%15c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_48) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%-5.3c%c%c%c%c Hello! ABOBA";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val, 'c', 'a', 'b', 'b'),
                   sprintf(str2, format, val, 'c', 'a', 'b', 'b'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_49) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%-5.3c";
  char val = 'c';
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_50) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%s";
  char *val = "I LOVE string1S AND TESTS AND SCHOOL21 NO JOKE";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_51) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%.15s";
  char *val = "I LOVE string1S AND TESTS AND SCHOOL21 NO JOKE";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_52) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%15s";
  char *val = "69 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_53) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%-15.9s";
  char *val = "69 IS MY FAVORITE NUMBER";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_54) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG string1";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_55) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%s%s%s%s";
  char *val =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG string1";
  char *s1 = "";
  char *s2 = "87418347813748913749871389480913";
  char *s3 = "HAHAABOBASUCKER";
  ck_assert_int_eq(s21_sprintf(str1, format, val, s1, s2, s3),
                   sprintf(str2, format, val, s1, s2, s3));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_56) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%p";
  ck_assert_int_eq(s21_sprintf(str1, format, format),
                   sprintf(str2, format, format));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_58) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "%.5p";
  ck_assert_int_eq(s21_sprintf(str1, format, format),
                   sprintf(str2, format, format));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_60) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *val = "kjafdiuhfjahfjdahf";
  char *format = "%120s";
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_61) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  int ret = 0;
  char *format = "Hello, my sexy little aboba abobushka abobina %n";
  ck_assert_int_eq(s21_sprintf(str1, format, &ret),
                   sprintf(str2, format, &ret));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_62) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%Lf";
  long double val = 513515.131513515151351;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_63) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%10Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_64) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%.0Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_65) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%.Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_66) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%.15Lf";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_67) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%.15Lf";
  long double val = -15.35581134;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_68) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%Lf";
  long double val = 72537572375.1431341;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_69) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "% f";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_70) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "% .0f %.lf %Lf %f %lf %Lf";
  float val = 0;
  double val1 = 0;
  long double val2 = 3515315.153151;
  float val3 = 5.5;
  double val4 = 9851.51351;
  long double val5 = 95919539159.53151351131;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
                   sprintf(str2, format, val, val1, val2, val3, val4, val5));

  ck_assert_str_eq(str1, str2);
}
END_TEST

// START_TEST(other_sprintf_71) {
//   char str1[1024] = {0};
//   char str2[1024] = {0};
//   char *format = "%.16Le";
//   long double val = 15.35;
//   ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format,
//   val));

//   ck_assert_str_eq(str1, str2);
// }
// END_TEST

START_TEST(other_sprintf_72) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%.0Le";
  long double val = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_73) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%.Le";
  long double val = 15.000009121;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_74) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%.15Le";
  long double val = 0.000000000000000123;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_75) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%.15Le";
  long double val = -15.35581134;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_76) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%Le";
  long double val = 72537572375.1431341;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_77) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%015E";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_78) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "%15e";
  float val = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_79) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char *format = "% .0e %.le %Le %e %le %Le";
  float val = 0;
  double val1 = 0;
  long double val2 = 3515315.153151;
  float val3 = 5.5;
  double val4 = 0.094913941;
  long double val5 = 95919539159.53151351131;
  ck_assert_int_eq(s21_sprintf(str1, format, val, val1, val2, val3, val4, val5),
                   sprintf(str2, format, val, val1, val2, val3, val4, val5));

  ck_assert_str_eq(str1, str2);
}
END_TEST

// START_TEST(other_sprintf_80) {
//   char str1[1024] = {0};
//   char str2[1024] = {0};
//   char *format = "%.17LE";
//   long double val = 4134121;
//   ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format,
//   val));

//   ck_assert_str_eq(str1, str2);
// }
// END_TEST

START_TEST(other_sprintf_81) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_82) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "abc"), sprintf(str2, "abc"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_83) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%c", '\t'), sprintf(str2, "%c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_84) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'),
                   sprintf(str2, "%c%c%c%c%c", '\t', '\n', '0', 'S', 's'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_85) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%s", "Drop Sega PLS"),
                   sprintf(str2, "%s", "Drop Sega PLS"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_86) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(
      s21_sprintf(str1, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"),
      sprintf(str2, "%s%s%s%s%s", "Drop", " ", "Sega", " ", "PLS"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_87) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%d", 666), sprintf(str2, "%d", 666));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_88) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%d%d%d%d", -999, 0, 666, -100),
                   sprintf(str2, "%d%d%d%d", -999, 0, 666, -100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_89) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%i", -0), sprintf(str2, "%i", -0));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_90) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%i%i%i%i", -999, 0, 666, -100),
                   sprintf(str2, "%i%i%i%i", -999, 0, 666, -100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_91) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%f", 0.0001),
                   sprintf(str2, "%f", 0.0001));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_92) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(
      s21_sprintf(str1, "%f %f %f %f", -999.666, 0.0001, 666.999, -100.001),
      sprintf(str2, "%f %f %f %f", -999.666, 0.0001, 666.999, -100.001));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_93) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%u", 100),
                   sprintf(str2, "%u", (unsigned)100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_94) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%u%u%u%u", 999, 0, 666, 100),
                   sprintf(str2, "%u%u%u%u", (unsigned)999, (unsigned)0,
                           (unsigned)666, (unsigned)100));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_95) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%8c", '\t'), sprintf(str2, "%8c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_96) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%-8c", '\t'),
                   sprintf(str2, "%-8c", '\t'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_97) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(
      s21_sprintf(str1, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'),
      sprintf(str2, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_98) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  ck_assert_int_eq(s21_sprintf(str1, "%x", (unsigned)INT32_MIN),
                   sprintf(str2, "%x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%x", 0), sprintf(str2, "%x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%x", INT32_MAX),
                   sprintf(str2, "%x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_99) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%X", (unsigned)INT32_MIN),
                   sprintf(str2, "%X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%X", 0), sprintf(str2, "%x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%X", INT32_MAX),
                   sprintf(str2, "%X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_100) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(
      s21_sprintf(str1, "%x%x%x%x%x", 12340987, 135, 0, -1230, -123213123),
      sprintf(str2, "%x%x%x%x%x", 12340987, 135, 0, -1230, -123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_101) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(
      s21_sprintf(str1, "%X%X%X%X%X", 12340987, 135, 0, -1230, -123213123),
      sprintf(str2, "%X%X%X%X%X", 12340987, 135, 0, -1230, -123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_102) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%-3x", (unsigned)INT32_MIN),
                   sprintf(str2, "%-3x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-3x", 0), sprintf(str2, "%-3x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-3x", INT32_MAX),
                   sprintf(str2, "%-3x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_103) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%13x", (unsigned)INT32_MIN),
                   sprintf(str2, "%13x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%13x", 0), sprintf(str2, "%13x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%13x", INT32_MAX),
                   sprintf(str2, "%13x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_104) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%-60X", INT32_MIN),
                   sprintf(str2, "%-60X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-60X", 0), sprintf(str2, "%-60X", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%-60X", INT32_MAX),
                   sprintf(str2, "%-60X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_105) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%7X", (unsigned)INT32_MIN),
                   sprintf(str2, "%7X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%7X", 0), sprintf(str2, "%7X", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%7X", INT32_MAX),
                   sprintf(str2, "%7X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_106) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(
      s21_sprintf(str1, "%2x%-7x%9x%11x%0x", 12340987, 100, 0, 1, -666999),
      sprintf(str2, "%2x%-7x%9x%11x%0x", 12340987, 100, 0, 1, -666999));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_107) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  ck_assert_int_eq(
      s21_sprintf(str1, "%2X%-7X%9X%11X%0X", 12340987, 100, 0, 1, -666999),
      sprintf(str2, "%2X%-7X%9X%11X%0X", 12340987, 100, 0, 1, -666999));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_108) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%#x", INT32_MIN),
                   sprintf(str2, "%#x", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#x", 0), sprintf(str2, "%#x", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#x", INT32_MAX),
                   sprintf(str2, "%#x", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_109) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%#X", INT32_MIN),
                   sprintf(str2, "%#X", (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#X", 0), sprintf(str2, "%#X", 0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%#X", INT32_MAX),
                   sprintf(str2, "%#X", INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_110) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(
      s21_sprintf(str1, "%#x%#x%3x%#32x%#-1x", 87, 1222224535, -13, -0,
                  123213123),
      sprintf(str2, "%#x%#x%3x%#32x%#-1x", 87, 1222224535, -13, -0, 123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_111) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(
      s21_sprintf(str1, "%#X%#X%3X%#32X%#-1X", 87, 1222224535, -13, -0,
                  123213123),
      sprintf(str2, "%#X%#X%3X%#32X%#-1X", 87, 1222224535, -13, -0, 123213123));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_112) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, INT32_MIN),
                   sprintf(str2, "%*x", 11, (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, 0),
                   sprintf(str2, "%*x", 11, 0));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*x", 11, INT32_MAX),
                   sprintf(str2, "%*x", 11, INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_113) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, INT32_MIN),
                   sprintf(str2, "%*X", 11, (unsigned)INT32_MIN));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, 0),
                   sprintf(str2, "%*X", 11, 0));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%*X", 11, INT32_MAX),
                   sprintf(str2, "%*X", 11, INT32_MAX));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_114) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%#*x%*x%-12x%3x%*x", 9, 127312897, 0, -1,
                               199, -123978, 3, -1251),
                   sprintf(str2, "%#*x%*x%-12x%3x%*x", 9, 127312897, -0, -1,
                           199, -123978, 3, -1251));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_115) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%#*X%*X%-12X%3X%*X", 9, 127312897, 0, -1,
                               199, -123978, 3, -1251),
                   sprintf(str2, "%#*X%*X%-12X%3X%*X", 9, 127312897, 0, -1, 199,
                           -123978, 3, -1251));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_116) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  int a = s21_sprintf(str1, "%*.6x", 11, 0);
  int b = sprintf(str2, "%*.6x", 11, 0);
  ck_assert_int_eq(a, b);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_117) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  int a = s21_sprintf(str1, "%*.6X", 11, INT32_MIN);
  int b = sprintf(str2, "%*.6X", 11, (unsigned)INT32_MIN);
  ck_assert_int_eq(a, b);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_118) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  int a = s21_sprintf(
      str1, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x", 3, 126714,
      4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9, 41, -41, 33);
  int b = sprintf(str2, "%#3.*x%#3x%-7.*x%#-1.8x%4.3x%#2.15x%*.*x%*.1x%3x%-1x",
                  3, 126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, 419, 9,
                  41, -41, 33);
  ck_assert_int_eq(a, b);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_119) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(
      s21_sprintf(str1, "%#3.*X%#3x%-7.*X%#-1.8X%4.3X%#2.15x%*.*X%*.1X%3X%-1X",
                  3, -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9,
                  41, -41, 33),
      sprintf(str2, "%#3.*X%#3x%-7.*X%#-1.8X%4.3X%#2.15x%*.*X%*.1X%3X%-1X", 3,
              -126714, 4444444, 0, 6423235, 0, 666, 999, 13, 5, -419, 9, 41,
              -41, 33));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_120) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%hx", -11),
                   sprintf(str2, "%hx", (unsigned short)-11));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hx", 0),
                   sprintf(str2, "%hx", (unsigned short)0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hx", 11),
                   sprintf(str2, "%hx", (unsigned short)11));
  ck_assert_str_eq(str1, str2);
  long unsigned int val = INT32_MAX;
  ck_assert_int_eq(s21_sprintf(str1, "%lx", val), sprintf(str2, "%lx", val));
  ck_assert_str_eq(str1, str2);
  long unsigned int v = 0;
  ck_assert_int_eq(s21_sprintf(str1, "%lx", v), sprintf(str2, "%lx", v));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_121) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(s21_sprintf(str1, "%hx", -11),
                   sprintf(str2, "%hx", (unsigned short)-11));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hx", 0),
                   sprintf(str2, "%hx", (unsigned short)0));
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(s21_sprintf(str1, "%hx", 11),
                   sprintf(str2, "%hx", (unsigned short)11));
  ck_assert_str_eq(str1, str2);
  long unsigned int val = INT32_MAX;
  ck_assert_int_eq(s21_sprintf(str1, "%lx", val), sprintf(str2, "%lx", val));
  ck_assert_str_eq(str1, str2);
  long unsigned int v = 0;
  ck_assert_int_eq(s21_sprintf(str1, "%lx", v), sprintf(str2, "%lx", v));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_122) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%10ld";

  ck_assert_int_eq(s21_sprintf(str1, format, 1), sprintf(str2, format, 1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_123) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%1.1f";

  ck_assert_int_eq(s21_sprintf(str1, format, 1.1), sprintf(str2, format, 1.1));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_124) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%8.3c";

  ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_125) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%+5.5d aboba";

  int val = 10000;
  int a = s21_sprintf(str1, format, val);
  int b = sprintf(str2, format, val);
  ck_assert_int_eq(a, b);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_126) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%7.7f";

  ck_assert_int_eq(s21_sprintf(str1, format, 11.123456),
                   sprintf(str2, format, 11.123456));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_127) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%7.4s";

  ck_assert_int_eq(s21_sprintf(str1, format, "aboba floppa"),
                   sprintf(str2, format, "aboba floppa"));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_128) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%6.6u";

  ck_assert_int_eq(s21_sprintf(str1, format, 12341151),
                   sprintf(str2, format, 12341151));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_129) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%li%ld%lu";

  ck_assert_int_eq(s21_sprintf(str1, format, 666666666666, 777, 111),
                   sprintf(str2, format, 666666666666, 777, 111));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_130) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%hi%hd%hu";

  ck_assert_int_eq(s21_sprintf(str1, format, 666, -777, 111),
                   sprintf(str2, format, 666, -777, 111));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_131) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%+li%+lu%+d%+lf";

  ck_assert_int_eq(s21_sprintf(str1, format, -123, 321, -5555, -1213.123),
                   sprintf(str2, format, -123, 321, -5555, -1213.123));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_132) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%-11.11li%-35.5lu%-3.5ld%33.16Lf";
  long double k = 333.33213;

  ck_assert_int_eq(
      s21_sprintf(str1, format, 66666666666, 5555555555, 44444444444, k),
      sprintf(str2, format, 66666666666, 5555555555, 44444444444, k));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_133) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "% 0.0li% 0.0lu% 0.0ld % 0.0lf";

  ck_assert_int_eq(s21_sprintf(str1, format, 1, 222, 33333333333, -166513.1232),
                   sprintf(str2, format, 1, 222, 33333333333, -166513.1232));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_134) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "% 0.0hi% 0.0hu% 0.0hd % 0.0hf";

  ck_assert_int_eq(s21_sprintf(str1, format, 1, 222, 33333333333, -166513.1232),
                   sprintf(str2, format, 1, 222, 33333333333, -166513.1232));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_135) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "% c";

  ck_assert_int_eq(s21_sprintf(str1, format, 'a'), sprintf(str2, format, 'a'));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_136) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "% s";

  ck_assert_int_eq(s21_sprintf(str1, format, "aboba likes floppa"),
                   sprintf(str2, format, "aboba likes floppa"));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_137) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "% s% c";

  ck_assert_int_eq(s21_sprintf(str1, format, "", 'f'),
                   sprintf(str2, format, "", 'f'));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_138) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%210s";

  ck_assert_int_eq(s21_sprintf(str1, format, "AHHAHAHA\0AHHAHAHAH"),
                   sprintf(str2, format, "AHHAHAHA\0AHHAHAHAH"));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_139) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%-115s";

  ck_assert_int_eq(s21_sprintf(str1, format, "Nick her"),
                   sprintf(str2, format, "Nick her"));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_140) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%+2.1c%+4.2d%+5.4i%+10.2f%+55.55s%+1.1u";

  ck_assert_int_eq(
      s21_sprintf(str1, format, 'f', 21, 42, 666.666,
                  "Lorem ipsum dolor sit amet. Aut quam ducimus.", 11),
      sprintf(str2, format, 'f', 21, 42, 666.666,
              "Lorem ipsum dolor sit amet. Aut quam ducimus.", 11));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_141) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%.f";

  ck_assert_int_eq(s21_sprintf(str1, format, 121.123),
                   sprintf(str2, format, 121.123));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_142) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  int n1;
  int n2;
  int a = s21_sprintf(str1, "%d%n", 123, &n1);
  int b = sprintf(str2, "%d%n", 123, &n2);

  ck_assert_int_eq(a, b);
  ck_assert_int_eq(n1, n2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_143) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%-.f";

  ck_assert_int_eq(s21_sprintf(str1, format, 111.111),
                   sprintf(str2, format, 111.111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_144) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%-.1d";

  ck_assert_int_eq(s21_sprintf(str1, format, 111), sprintf(str2, format, 111));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_145) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%e";
  double x = 111;
  ck_assert_int_eq(s21_sprintf(str1, format, x), sprintf(str2, format, x));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_146) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%e%e%e%e";

  ck_assert_int_eq(s21_sprintf(str1, format, 11.111, 222.2222, 666., -555.125),
                   sprintf(str2, format, 11.111, 222.2222, 666., -555.125));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_147) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%Le";
  long double x = 122.1231;

  ck_assert_int_eq(s21_sprintf(str1, format, x), sprintf(str2, format, x));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_148) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%.10e";

  ck_assert_int_eq(s21_sprintf(str1, format, 111.184314818),
                   sprintf(str2, format, 111.184314818));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_149) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%5.3e%3.2e%lf";

  ck_assert_int_eq(s21_sprintf(str1, format, 0.000111, 111.555, 1.999),
                   sprintf(str2, format, 0.000111, 111.555, 1.999));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_150) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%E";

  ck_assert_int_eq(s21_sprintf(str1, format, 0.666666),
                   sprintf(str2, format, 0.666666));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_151) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%E%E%E";

  ck_assert_int_eq(s21_sprintf(str1, format, 0.0000999, 111.9999, 6.666),
                   sprintf(str2, format, 0.0000999, 111.9999, 6.666));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_152) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%e ABOBA %Lf %Lf %Le";
  long double c = 848181;
  long double a = 0.00000001;
  long double b = 1111111.11;
  ck_assert_int_eq(s21_sprintf(str1, format, 123.123, a, b, c),
                   sprintf(str2, format, 123.123, a, b, c));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_153) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%#e Floppa %#E%#f";

  ck_assert_int_eq(s21_sprintf(str1, format, 123.111, 0.0000999, 0.555),
                   sprintf(str2, format, 123.111, 0.0000999, 0.555));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_154) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%.Lf";
  long double a = 7.9418438184;

  ck_assert_int_eq(s21_sprintf(str1, format, a), sprintf(str2, format, a));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_155) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%#5p";
  int a = 5;
  ck_assert_int_eq(s21_sprintf(str1, format, &a), sprintf(str2, format, &a));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_156) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%.5o";

  ck_assert_int_eq(s21_sprintf(str1, format, 12345),
                   sprintf(str2, format, 12345));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_157) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%#5lX";
  long hex = 314818438141;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_158) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%g";
  double hex = 0.50300;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_159) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%lg";
  double hex = 5131.43141;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_160) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%g";
  double hex = 0.123000;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_161) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%.5g";
  double hex = 0.123000;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_162) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  ck_assert_int_eq(
      s21_sprintf(str1, "%.0g %.1g %.5g", 0.123000, 0.123000, 0.123000),
      sprintf(str2, "%.0g %.1g %.5g", 0.123000, 0.123000, 0.123000));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_163) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%.g";
  double hex = 0.123000;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_164) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%.g";
  double hex = 0.0004;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_165) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%g";
  double hex = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_166) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%.5g";
  double hex = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_167) {
  char a1[1024] = {0};
  char aa1[1024] = {0};
  int a = 10;
  char *format_str1 = "Positive %%, %d";
  int result1 = s21_sprintf(a1, format_str1, a);
  int result_origin1 = sprintf(aa1, format_str1, a);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a1, aa1);

  char a2[1024] = {0};
  char aa2[1024] = {0};
  int b = -10;
  char *format_str2 = "Negative %%, %d";
  result1 = s21_sprintf(a2, format_str2, b);
  result_origin1 = sprintf(aa2, format_str2, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a2, aa2);

  char a3[1024] = {0};
  char aa3[1024] = {0};
  b = -100000, a = -1234556;
  char *format_str3 = "Negative %%, %d%d";
  result1 = s21_sprintf(a3, format_str3, b, a);
  result_origin1 = sprintf(aa3, format_str3, b, a);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a3, aa3);

  char a4[1024] = {0};
  char aa4[1024] = {0};
  const char *format_str4 = "%%, %d";
  result1 = s21_sprintf(a4, format_str4, a);
  result_origin1 = sprintf(aa4, format_str4, a);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a4, aa4);

  char a5[1024] = {0};
  char aa5[1024] = {0};
  a = 123456;
  b = -123456;
  const char *format_str5 = " *one, %% %+-10.0d % 10.0d";
  result1 = s21_sprintf(a5, format_str5, a, b);
  result_origin1 = sprintf(aa5, format_str5, a, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a5, aa5);

  char a6[1024] = {0};
  char aa6[1024] = {0};

  const char *format_str6 = " *one %%%%%%%%%%%%%%, %%  %*.*d %*.*d";
  result1 = s21_sprintf(a6, format_str6, 5, 10, a, 7, 10, b);
  result_origin1 = sprintf(aa6, format_str6, 5, 10, a, 7, 10, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a6, aa6);

  char a7[1024] = {0};
  char aa7[1024] = {0};

  const char *format_str7 = " *one %%%%%%%%%%%%%%, %%  [%*.*d] [%*.*d]";
  result1 = s21_sprintf(a7, format_str7, 5, 10, a, 7, 10, b);
  result_origin1 = sprintf(aa7, format_str7, 5, 10, a, 7, 10, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a7, aa7);

  char a8[1024] = {0};
  char aa8[1024] = {0};

  const char *format_str8 = " *one %%%%%%%%%%%%%%, %%  [% *.*d] [% *.*d]";
  result1 = s21_sprintf(a8, format_str8, 5, 10, a, 7, 10, b);
  result_origin1 = sprintf(aa8, format_str8, 5, 10, a, 7, 10, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a8, aa8);

  char a9[1024] = {0};
  char aa9[1024] = {0};

  const char *format_str9 = " *one %%%%%%%%%%%%%%, %%  [%   *.*d ] [%   *.*d]";
  result1 = s21_sprintf(a9, format_str9, 5, 10, a, 7, 10, b);
  result_origin1 = sprintf(aa9, format_str9, 5, 10, a, 7, 10, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a9, aa9);

  char a10[1024] = {0};
  char aa10[1024] = {0};
  a = 0;
  b = 0;
  const char *format_str10 =
      " *one %%%%%%%%%%%%%%, % %  [%   *.*d ] [%   *.*d] %%";
  result1 = s21_sprintf(a10, format_str10, 5, 10, a, 7, 10, b);
  result_origin1 = sprintf(aa10, format_str10, 5, 10, a, 7, 10, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a10, aa10);

  char a11[1024] = {0};
  char aa11[1024] = {0};
  a = 11;
  b = -11;
  const char *format_str11 =
      " *one %%%%%%%%%%%%%%, % %  [%   *.*d ] [%   *.*d] asd";
  result1 = s21_sprintf(a11, format_str11, 5, 10, a, 7, 10, b);
  result_origin1 = sprintf(aa11, format_str11, 5, 10, a, 7, 10, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a11, aa11);

  char a12[1024] = {0};
  char aa12[1024] = {0};
  a = 11123;
  b = -114456;
  const char *format_str12 = " *one %%%%%%%%%%%%%%,[%*.*d ][%*.*d]Dota2";
  result1 = s21_sprintf(a12, format_str12, 10, 0, a, 10, 0, b);
  result_origin1 = sprintf(aa12, format_str12, 10, 0, a, 10, 0, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a12, aa12);

  char a13[1024] = {0};
  char aa13[1024] = {0};
  a = 11123;
  b = -114456;
  const char *format_str13 = " *one %%%%%%%%%%%%%%,[%*.*d ][%*.*d]Dota2";
  result1 = s21_sprintf(a13, format_str13, 0, 0, a, 0, 0, b);
  result_origin1 = sprintf(aa13, format_str13, 0, 0, a, 0, 0, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a13, aa13);

  char a14[1024] = {0};
  char aa14[1024] = {0};
  a = 123456;
  b = -123456;
  const char *format_str14 = " *one, %% %+-0.0d % +0.0d";
  result1 = s21_sprintf(a14, format_str14, a, b);
  result_origin1 = sprintf(aa14, format_str14, a, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a14, aa14);

  char a15[1024] = {0};
  char aa15[1024] = {0};
  a = 123456;
  b = -123456;
  const char *format_str15 = " *one, %% %+-0.0d %% % +0.0d";
  result1 = s21_sprintf(a15, format_str15, a, b);
  result_origin1 = sprintf(aa15, format_str15, a, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a15, aa15);

  char a16[1024] = {0};
  char aa16[1024] = {0};
  a = 12345;
  b = 1234;
  const char *format_str16 = " *one, %% %+d %% %+d";
  result1 = s21_sprintf(a16, format_str16, a, b);
  result_origin1 = sprintf(aa16, format_str16, a, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a16, aa16);

  char a17[1024] = {0};
  char aa17[1024] = {0};
  a = 12345;
  b = 1234;
  const char *format_str17 = " *one, %% %- d %% % -d";
  result1 = s21_sprintf(a17, format_str17, a, b);
  result_origin1 = sprintf(aa17, format_str17, a, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a17, aa17);

  char a18[1024] = {0};
  char aa18[1024] = {0};
  a = -12345;
  b = -1234;
  const char *format_str18 = " *one, %% %- d %% % -d, 12345";
  result1 = s21_sprintf(a18, format_str18, a, b);
  result_origin1 = sprintf(aa18, format_str18, a, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a18, aa18);

  char a19[1024] = {0};
  char aa19[1024] = {0};
  a = 11123;
  b = -114456;
  const char *format_str19 = " *one %%%%%%%%%%%%%%,[%*.*d ][%*.*d]";
  result1 = s21_sprintf(a19, format_str19, -11, 12, a, 12, -11, b);
  result_origin1 = sprintf(aa19, format_str19, -11, 12, a, 12, -11, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a19, aa19);

  char a20[1024] = {0};
  char aa20[1024] = {0};
  a = -11123;
  b = 114456;
  const char *format_str20 = " *one %%%%%%%%%%%%%%,[%*.*d ][%*.*d]";
  result1 = s21_sprintf(a20, format_str20, -11, 0, a, 0, -11, b);
  result_origin1 = sprintf(aa20, format_str20, -11, 0, a, 0, -11, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a20, aa20);

  char a21[1024] = {0};
  char aa21[1024] = {0};
  a = -11123;
  b = 114456;
  const char *format_str21 = " *one %%%%%%%%%%%%%%,[%*.*d ][%*.*d]";
  result1 = s21_sprintf(a21, format_str21, 0, -11, a, -11, 0, b);
  result_origin1 = sprintf(aa21, format_str21, 0, -11, a, -11, 0, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a21, aa21);

  char a22[1024] = {0};
  char aa22[1024] = {0};
  a = -1113;
  b = -4456;
  const char *format_str22 = " *one %%%%%%%%%%%%%%,[%*.*d ][%*.*d]";
  result1 = s21_sprintf(a22, format_str22, -11, -11, a, -11, -11, b);
  result_origin1 = sprintf(aa22, format_str22, -11, -11, a, -11, -11, b);
  ck_assert_int_eq(result1, result_origin1);
  ck_assert_str_eq(a22, aa22);
}
END_TEST

START_TEST(other_sprintf_168) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%g";
  double hex = 0.0000005;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_169) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%5.8g";
  double hex = 0.0000005;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_170) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%g";
  double hex = 0.005;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_171) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%LG";
  long double hex = 0.000005;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_172) {
  char str1[1024] = {0};
  char str2[1024] = {0};
  char format[] = "%LG %g %G %Lg %.5g";
  long double hex = 0.000005;
  double hex1 = 41.1341;
  double hex2 = 848.9000;
  long double hex3 = 0.0843;
  double hex4 = 0.0005;
  double hex5 = 0.8481481;
  ck_assert_int_eq(s21_sprintf(str1, format, hex, hex1, hex2, hex3, hex4, hex5),
                   sprintf(str2, format, hex, hex1, hex2, hex3, hex4, hex5));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(other_sprintf_173) {
  char str1[1024] = {0};
  char str2[1024] = {0};

  char *format = "This is a simple wide char %5c";
  char w = 'c';
  int a = s21_sprintf(str1, format, w);
  int b = sprintf(str2, format, w);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_test1) {
  char str1[100] = {0};
  char str2[100] = {0};
  void *p = (void *)0x3456;
  int n1, n2;
  int r1 = sprintf(str1, "%d%o%s%c%i%e%f%E%g%u%x%G%X%n%p%%%s", 25, 342, "aboba",
                   'a', 123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u,
                   8342, 0.0000456, 1235, &n1, p, "hello my friend");
  int r2 =
      s21_sprintf(str2, "%d%o%s%c%i%e%f%E%g%u%x%G%X%n%p%%%s", 25, 342, "aboba",
                  'a', 123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u,
                  8342, 0.0000456, 1235, &n2, p, "hello my friend");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test2) {
  char str1[100] = {0};
  char str2[100] = {0};
  int r1 = sprintf(str1, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
  int r2 =
      s21_sprintf(str2, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test3) {
  char str1[100] = {0};
  char str2[100] = {0};
  int r1 = sprintf(str1, "%#+34.10g%#.10x%#15.1o%25.10s", 25.3456, 1234, 4567,
                   "HELLOMYDEARFRIEND");
  int r2 = s21_sprintf(str2, "%#+34.10g%#.10x%#15.1o%25.10s", 25.3456, 1234,
                       4567, "HELLOMYDEARFRIEND");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test4) {
  char str1[100] = {0};
  char str2[100] = {0};
  void *p = (void *)43252342;
  int r1 = sprintf(str1, "%#24.e%-15.20i%20p%020u", 43253242.4342, 4567899, p,
                   43252342u);
  int r2 = s21_sprintf(str2, "%#24.e%-15.20i%20p%020u", 43253242.4342, 4567899,
                       p, 43252342u);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
  char str3[50];
  char str4[100];
  int r3 = sprintf(str3, "%*.0f", 25, 25432.34345);
  int r4 = s21_sprintf(str4, "%*.0f", 25, 25432.34345);
  ck_assert_str_eq(str3, str4);
  ck_assert_int_eq(r3, r4);
}
END_TEST

START_TEST(s21_sprintf_test_d) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  short h = 34;
  int r1 = sprintf(
      str1, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
      335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  int r2 = s21_sprintf(
      str2, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
      335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_i) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  short h = 34;
  long l = 2353423523424;
  int r1 = sprintf(str1, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
                   34567, 225, 5230, 125, 10, 5, 456, 10, 377, l, 12, h);
  int r2 =
      s21_sprintf(str2, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
                  34567, 225, 5230, 125, 10, 5, 456, 10, 377, l, 12, h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_c) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  wint_t c1 = 'T', c2 = 'Z';
  int r1 = sprintf(str1, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a', 'e',
                   'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
  int r2 = s21_sprintf(str2, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a',
                       'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_e) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  // char *format = "%+-20e %010.*e %-*.16e %#025.10e %*.*e %*.15e %#010.*e
  // %25.16e";

  int r1 =
      sprintf(str1, "%+-20e%010.*e%-*.16e%#025.10e%*.*e%*.15e%#010.*e%25.16e",
              2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15,
              11111.22, 16, -3245.3425342, 16, -0.00123, 235423424.43252);
  int r2 = s21_sprintf(
      str2, "%+-20e%010.*e%-*.16e%#025.10e%*.*e%*.15e%#010.*e%25.16e",
      2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15, 11111.22,
      16, -3245.3425342, 16, -0.00123, 235423424.43252);

  // int r1 = sprintf(str1, "%-*.16e %#010.*e",
  // 15, -0.00123, 16, 0.00123);
  // int r2 = s21_sprintf(str2, "%-*.16e %#010.*e",
  // 15, -0.00123, 16, 0.00123);

  // ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_E) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  int r1 = sprintf(str1, "%+-25.4E%25.*E%-*.10E%#02.E%*.*E%*.15E%*E%12.16E",
                   3456.4325, 10, 23452.43242, 5, -0.05234, 25.432523432, 10, 2,
                   53242.4242, 10, 456789.43242, 25, 1111122222.34567899,
                   2345678.23453242);
  int r2 = s21_sprintf(str2, "%+-25.4E%25.*E%-*.10E%#02.E%*.*E%*.15E%*E%12.16E",
                       3456.4325, 10, 23452.43242, 5, -0.05234, 25.432523432,
                       10, 2, 53242.4242, 10, 456789.43242, 25,
                       1111122222.34567899, 2345678.23453242);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_f) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  int r1 = sprintf(
      str1, "%+-10.5f%+10.2f%15.16f%+*.10f%*.16f%-10.*f%25.*f%25.f%#+10.f%*.*f",
      2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245,
      2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
      34567.43244);
  int r2 = s21_sprintf(
      str2, "%+-10.5f%+10.2f%15.16f%+*.10f%*.16f%-10.*f%25.*f%25.f%#+10.f%*.*f",
      2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245,
      2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
      34567.43244);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_o) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  unsigned short h = 253;
  unsigned long l = 4325234324242l;
  int r1 = sprintf(str1, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                   12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
  int r2 =
      s21_sprintf(str2, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                  12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_x) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  unsigned short h = 345;
  unsigned long l = 52342353242l;
  int r1 = sprintf(str1,
                   "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%20.*"
                   "x%#10.*x%*.5hx%10.25lx",
                   235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                   8, 23452, 10, 34254, 3, 33334, 10, h, l);
  int r2 = s21_sprintf(str2,
                       "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%"
                       "20.*x%#10.*x%*.5hx%10.25lx",
                       235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
                       3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_X) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  unsigned short h = 234;
  unsigned long l = 4325243132l;
  int r1 = sprintf(str1,
                   "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%21.*X%"
                   "#12.*X%*.8hx%14.12lX",
                   235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                   8, 23452, 10, 34254, 3, 33334, 10, h, l);
  int r2 = s21_sprintf(str2,
                       "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%"
                       "21.*X%#12.*X%*.8hx%14.12lX",
                       235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
                       3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_u) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  unsigned short h = 115;
  unsigned long l = 123325242342l;
  int r1 =
      sprintf(str1, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu",
              4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u,
              20, 2432u, l, h);
  int r2 = s21_sprintf(
      str2, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu", 4321u,
      34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u, 20, 2432u, l,
      h);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_s) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  char s[10] = {'h', 'e', 'l', 'l', 'o'};
  int r1 = sprintf(str1, "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15s%15.3s",
                   "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10,
                   "QWERTY", 15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
  int r2 =
      s21_sprintf(str2, "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15s%15.3s",
                  "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10,
                  "QWERTY", 15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_p) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  void *p1 = (void *)0x123456789;
  void *p2 = (void *)4325234;
  void *p3 = (void *)0x123f324b;
  void *p4 = (void *)432520;
  int r1 = sprintf(str1, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4, p2,
                   10, p3, p1, 10, p4);
  int r2 = s21_sprintf(str2, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4,
                       p2, 10, p3, p1, 10, p4);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_percent) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  int r1 = sprintf(str1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  int r2 = s21_sprintf(str2, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_g) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  int r1 = sprintf(
      str1,
      "%g  %23g  %-10g  %015g  %#10.4g  %0#15.10g  %+10.6g  %#*.g  %-10.*g",
      2345.4324, 23445.2342, 1234.234242, 3456.3424, 0.00001234, -324234.234,
      2345.4234, 5, 23456.4324, 9, 234567.43242);
  int r2 = s21_sprintf(
      str2,
      "%g  %23g  %-10g  %015g  %#10.4g  %0#15.10g  %+10.6g  %#*.g  %-10.*g",
      2345.4324, 23445.2342, 1234.234242, 3456.3424, 0.00001234, -324234.234,
      2345.4234, 5, 23456.4324, 9, 234567.43242);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_G) {
  char str1[1000] = {0};
  char str2[1000] = {0};
  int r1 = sprintf(
      str1, "%G %#-15G%017G%#05.2G%#010.16G%+#8.6G%*.8G%#-10.*G%+#12.16G%*.*G",
      43242.43242, 0000.1234, -34252.43242, 1234.5, 111.432534243243242,
      4324.43242, 25, -3213.43242, 16, -43.43242353242342, 111.24324242, 25, 5,
      0.000000342);
  int r2 = s21_sprintf(
      str2, "%G %#-15G%017G%#05.2G%#010.16G%+#8.6G%*.8G%#-10.*G%+#12.16G%*.*G",
      43242.43242, 0000.1234, -34252.43242, 1234.5, 111.432534243243242,
      4324.43242, 25, -3213.43242, 16, -43.43242353242342, 111.24324242, 25, 5,
      0.000000342);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

Suite *make_sprintf_suite(void) {
  Suite *suite;
  suite = suite_create("sprintf");

  TCase *test_case_1 = tcase_create("sprintf_test");
  suite_add_tcase(suite, test_case_1);

  tcase_add_test(test_case_1, s21_sprintf_test1);
  tcase_add_test(test_case_1, s21_sprintf_test2);
  tcase_add_test(test_case_1, s21_sprintf_test3);
  tcase_add_test(test_case_1, s21_sprintf_test4);
  tcase_add_test(test_case_1, s21_sprintf_test_d);
  tcase_add_test(test_case_1, s21_sprintf_test_i);
  tcase_add_test(test_case_1, s21_sprintf_test_c);
  tcase_add_test(test_case_1, s21_sprintf_test_e);
  tcase_add_test(test_case_1, s21_sprintf_test_E);
  tcase_add_test(test_case_1, s21_sprintf_test_f);
  tcase_add_test(test_case_1, s21_sprintf_test_o);
  tcase_add_test(test_case_1, s21_sprintf_test_x);
  tcase_add_test(test_case_1, s21_sprintf_test_X);
  tcase_add_test(test_case_1, s21_sprintf_test_u);
  tcase_add_test(test_case_1, s21_sprintf_test_s);
  tcase_add_test(test_case_1, s21_sprintf_test_p);
  tcase_add_test(test_case_1, s21_sprintf_test_percent);
  tcase_add_test(test_case_1, s21_sprintf_test_g);
  tcase_add_test(test_case_1, s21_sprintf_test_G);

  tcase_add_test(test_case_1, sprintf_test_c);
  tcase_add_test(test_case_1, sprintf_test_s);
  tcase_add_test(test_case_1, sprintf_test_d);
  tcase_add_test(test_case_1, sprintf_test_i);
  tcase_add_test(test_case_1, sprintf_test_f);
  tcase_add_test(test_case_1, sprintf_test_e);
  tcase_add_test(test_case_1, sprintf_test_g);
  tcase_add_test(test_case_1, sprintf_test_n);
  tcase_add_test(test_case_1, sprintf_test_o);
  tcase_add_test(test_case_1, sprintf_test_u);
  tcase_add_test(test_case_1, sprintf_test_x);

  tcase_add_test(test_case_1, other_sprintf_1);
  tcase_add_test(test_case_1, other_sprintf_2);
  tcase_add_test(test_case_1, other_sprintf_3);
  tcase_add_test(test_case_1, other_sprintf_4);
  tcase_add_test(test_case_1, other_sprintf_5);
  tcase_add_test(test_case_1, other_sprintf_6);
  tcase_add_test(test_case_1, other_sprintf_7);
  tcase_add_test(test_case_1, other_sprintf_8);
  tcase_add_test(test_case_1, other_sprintf_9);
  tcase_add_test(test_case_1, other_sprintf_10);
  tcase_add_test(test_case_1, other_sprintf_11);
  tcase_add_test(test_case_1, other_sprintf_12);
  tcase_add_test(test_case_1, other_sprintf_13);
  tcase_add_test(test_case_1, other_sprintf_14);
  tcase_add_test(test_case_1, other_sprintf_15);
  tcase_add_test(test_case_1, other_sprintf_16);
  tcase_add_test(test_case_1, other_sprintf_17);
  tcase_add_test(test_case_1, other_sprintf_18);
  tcase_add_test(test_case_1, other_sprintf_19);
  tcase_add_test(test_case_1, other_sprintf_20);
  tcase_add_test(test_case_1, other_sprintf_21);
  tcase_add_test(test_case_1, other_sprintf_22);
  tcase_add_test(test_case_1, other_sprintf_23);
  tcase_add_test(test_case_1, other_sprintf_24);
  tcase_add_test(test_case_1, other_sprintf_25);
  tcase_add_test(test_case_1, other_sprintf_26);
  tcase_add_test(test_case_1, other_sprintf_27);
  tcase_add_test(test_case_1, other_sprintf_28);
  tcase_add_test(test_case_1, other_sprintf_29);
  tcase_add_test(test_case_1, other_sprintf_30);
  tcase_add_test(test_case_1, other_sprintf_31);
  tcase_add_test(test_case_1, other_sprintf_32);
  tcase_add_test(test_case_1, other_sprintf_33);
  tcase_add_test(test_case_1, other_sprintf_34);
  tcase_add_test(test_case_1, other_sprintf_35);
  tcase_add_test(test_case_1, other_sprintf_36);
  tcase_add_test(test_case_1, other_sprintf_37);
  tcase_add_test(test_case_1, other_sprintf_38);
  tcase_add_test(test_case_1, other_sprintf_39);
  tcase_add_test(test_case_1, other_sprintf_40);
  tcase_add_test(test_case_1, other_sprintf_41);
  tcase_add_test(test_case_1, other_sprintf_42);
  tcase_add_test(test_case_1, other_sprintf_43);
  tcase_add_test(test_case_1, other_sprintf_44);
  tcase_add_test(test_case_1, other_sprintf_45);
  tcase_add_test(test_case_1, other_sprintf_46);
  tcase_add_test(test_case_1, other_sprintf_47);
  tcase_add_test(test_case_1, other_sprintf_48);
  tcase_add_test(test_case_1, other_sprintf_49);
  tcase_add_test(test_case_1, other_sprintf_50);
  tcase_add_test(test_case_1, other_sprintf_51);
  tcase_add_test(test_case_1, other_sprintf_52);
  tcase_add_test(test_case_1, other_sprintf_53);
  tcase_add_test(test_case_1, other_sprintf_54);
  tcase_add_test(test_case_1, other_sprintf_55);
  tcase_add_test(test_case_1, other_sprintf_56);
  tcase_add_test(test_case_1, other_sprintf_58);
  tcase_add_test(test_case_1, other_sprintf_60);
  tcase_add_test(test_case_1, other_sprintf_61);
  tcase_add_test(test_case_1, other_sprintf_62);
  tcase_add_test(test_case_1, other_sprintf_63);
  tcase_add_test(test_case_1, other_sprintf_64);
  tcase_add_test(test_case_1, other_sprintf_65);
  tcase_add_test(test_case_1, other_sprintf_66);
  tcase_add_test(test_case_1, other_sprintf_67);
  tcase_add_test(test_case_1, other_sprintf_68);
  tcase_add_test(test_case_1, other_sprintf_69);
  tcase_add_test(test_case_1, other_sprintf_70);
  // tcase_add_test(test_case_1, other_sprintf_71);
  tcase_add_test(test_case_1, other_sprintf_72);
  tcase_add_test(test_case_1, other_sprintf_73);
  tcase_add_test(test_case_1, other_sprintf_74);
  tcase_add_test(test_case_1, other_sprintf_75);
  tcase_add_test(test_case_1, other_sprintf_76);
  tcase_add_test(test_case_1, other_sprintf_77);
  tcase_add_test(test_case_1, other_sprintf_78);
  tcase_add_test(test_case_1, other_sprintf_79);
  // tcase_add_test(test_case_1, other_sprintf_80);
  tcase_add_test(test_case_1, other_sprintf_81);
  tcase_add_test(test_case_1, other_sprintf_82);
  tcase_add_test(test_case_1, other_sprintf_83);
  tcase_add_test(test_case_1, other_sprintf_84);
  tcase_add_test(test_case_1, other_sprintf_85);
  tcase_add_test(test_case_1, other_sprintf_86);
  tcase_add_test(test_case_1, other_sprintf_87);
  tcase_add_test(test_case_1, other_sprintf_88);
  tcase_add_test(test_case_1, other_sprintf_89);
  tcase_add_test(test_case_1, other_sprintf_90);
  tcase_add_test(test_case_1, other_sprintf_91);
  tcase_add_test(test_case_1, other_sprintf_92);
  tcase_add_test(test_case_1, other_sprintf_93);
  tcase_add_test(test_case_1, other_sprintf_94);
  tcase_add_test(test_case_1, other_sprintf_95);
  tcase_add_test(test_case_1, other_sprintf_96);
  tcase_add_test(test_case_1, other_sprintf_97);
  tcase_add_test(test_case_1, other_sprintf_98);
  tcase_add_test(test_case_1, other_sprintf_99);
  tcase_add_test(test_case_1, other_sprintf_100);
  tcase_add_test(test_case_1, other_sprintf_101);
  tcase_add_test(test_case_1, other_sprintf_102);
  tcase_add_test(test_case_1, other_sprintf_103);
  tcase_add_test(test_case_1, other_sprintf_104);
  tcase_add_test(test_case_1, other_sprintf_105);
  tcase_add_test(test_case_1, other_sprintf_106);
  tcase_add_test(test_case_1, other_sprintf_107);
  tcase_add_test(test_case_1, other_sprintf_108);
  tcase_add_test(test_case_1, other_sprintf_109);
  tcase_add_test(test_case_1, other_sprintf_110);
  tcase_add_test(test_case_1, other_sprintf_111);
  tcase_add_test(test_case_1, other_sprintf_112);
  tcase_add_test(test_case_1, other_sprintf_113);
  tcase_add_test(test_case_1, other_sprintf_114);
  tcase_add_test(test_case_1, other_sprintf_115);
  tcase_add_test(test_case_1, other_sprintf_116);
  tcase_add_test(test_case_1, other_sprintf_117);
  tcase_add_test(test_case_1, other_sprintf_118);
  tcase_add_test(test_case_1, other_sprintf_119);
  tcase_add_test(test_case_1, other_sprintf_120);
  tcase_add_test(test_case_1, other_sprintf_121);
  tcase_add_test(test_case_1, other_sprintf_122);
  tcase_add_test(test_case_1, other_sprintf_123);
  tcase_add_test(test_case_1, other_sprintf_124);
  tcase_add_test(test_case_1, other_sprintf_125);
  tcase_add_test(test_case_1, other_sprintf_126);
  tcase_add_test(test_case_1, other_sprintf_127);
  tcase_add_test(test_case_1, other_sprintf_128);
  tcase_add_test(test_case_1, other_sprintf_129);
  tcase_add_test(test_case_1, other_sprintf_130);
  tcase_add_test(test_case_1, other_sprintf_131);
  tcase_add_test(test_case_1, other_sprintf_132);
  tcase_add_test(test_case_1, other_sprintf_133);
  tcase_add_test(test_case_1, other_sprintf_134);
  tcase_add_test(test_case_1, other_sprintf_135);
  tcase_add_test(test_case_1, other_sprintf_136);
  tcase_add_test(test_case_1, other_sprintf_137);
  tcase_add_test(test_case_1, other_sprintf_138);
  tcase_add_test(test_case_1, other_sprintf_139);
  tcase_add_test(test_case_1, other_sprintf_140);
  tcase_add_test(test_case_1, other_sprintf_141);
  tcase_add_test(test_case_1, other_sprintf_142);
  tcase_add_test(test_case_1, other_sprintf_143);
  tcase_add_test(test_case_1, other_sprintf_144);
  tcase_add_test(test_case_1, other_sprintf_145);
  tcase_add_test(test_case_1, other_sprintf_146);
  tcase_add_test(test_case_1, other_sprintf_147);
  tcase_add_test(test_case_1, other_sprintf_148);
  tcase_add_test(test_case_1, other_sprintf_149);
  tcase_add_test(test_case_1, other_sprintf_150);
  tcase_add_test(test_case_1, other_sprintf_151);
  tcase_add_test(test_case_1, other_sprintf_152);
  tcase_add_test(test_case_1, other_sprintf_153);
  tcase_add_test(test_case_1, other_sprintf_154);
  tcase_add_test(test_case_1, other_sprintf_155);
  tcase_add_test(test_case_1, other_sprintf_156);
  tcase_add_test(test_case_1, other_sprintf_157);
  tcase_add_test(test_case_1, other_sprintf_158);
  tcase_add_test(test_case_1, other_sprintf_159);
  tcase_add_test(test_case_1, other_sprintf_160);
  tcase_add_test(test_case_1, other_sprintf_161);
  tcase_add_test(test_case_1, other_sprintf_162);
  tcase_add_test(test_case_1, other_sprintf_163);
  tcase_add_test(test_case_1, other_sprintf_164);
  tcase_add_test(test_case_1, other_sprintf_165);
  tcase_add_test(test_case_1, other_sprintf_166);
  tcase_add_test(test_case_1, other_sprintf_167);
  tcase_add_test(test_case_1, other_sprintf_168);
  tcase_add_test(test_case_1, other_sprintf_169);
  tcase_add_test(test_case_1, other_sprintf_170);
  tcase_add_test(test_case_1, other_sprintf_171);
  tcase_add_test(test_case_1, other_sprintf_172);
  tcase_add_test(test_case_1, other_sprintf_173);

  return suite;
}