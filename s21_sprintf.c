#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  format_part parameters = {0};
  s21_size_t i = 0;
  s21_memset(str, 0, s21_strlen(str));
  while (*format) {
    s21_memset(&parameters, 0, sizeof(parameters));
    parameters.precision = -1;

    if (*format == '%') {
      format++;
      if (is_flag(*format)) {
        while (is_flag(*format)) {
          sprintf_check_flag(&parameters, format++);
        }
      }
      if (is_digit(*format) || *format == '*') {
        format = sprintf_str_int(&parameters.width, format++, &args);
        if (parameters.width < 0) {
          parameters.flag_minus = 1;
          parameters.width *= -1;
        }
      }
      if (*format == '.') {
        parameters.point = 1;
        parameters.precision = 0;
        format++;
        if (is_digit(*format) || *format == '*') {
          format = sprintf_str_int(&parameters.precision, format++, &args);
        }
      }
      if (is_length(*format)) {
        while (is_length(*format)) {
          parameters.length = *format;
          format++;
        }
      }
      if (is_specifier(*format)) {
        parameters.specifier = *format;
        format++;
      }
      sprintf_default_precision(&parameters);
      str = sprintf_check_specifier(str, &i, &args, &parameters);
    } else {
      str[i] = *format;
      i++;
      format++;
      str[i] = '\0';
    }
  }
  va_end(args);
  return (int)s21_strlen(str);
}

void sprintf_default_precision(format_part *parameters) {
  if (parameters->point && parameters->precision <= 0) {
    parameters->precision = 0;
  }
  if (!parameters->point && s21_strchr("eEfgG", parameters->specifier)) {
    parameters->precision = 6;
  }
}

void sprintf_check_flag(format_part *parameters, const char *format) {
  switch (*format) {
    case '-':
      parameters->flag_minus = 1;
      break;
    case '+':
      parameters->flag_plus = 1;
      break;
    case ' ':
      parameters->flag_space = 1;
      break;
    case '#':
      parameters->flag_sharp = 1;
      break;
    case '0':
      parameters->flag_zero = 1;
      break;
  }
  if (parameters->flag_minus == 1 && parameters->flag_zero == 1) {
    parameters->flag_zero = 0;
  }
  if (parameters->flag_plus == 1 && parameters->flag_space == 1) {
    parameters->flag_space = 0;
  }
}

char *sprintf_check_specifier(char *str, s21_size_t *str_len, va_list *args,
                              format_part *parameters) {
  char *string_from_cs = s21_NULL;
  string_from_cs = calloc(
      (parameters->width * 2 + parameters->precision * 2 + 1024), sizeof(char));

  if (string_from_cs != s21_NULL) {
    switch (parameters->specifier) {
      case 'c':
        string_from_cs[0] = va_arg(*args, int);
        string_from_cs[1] = '\0';
        sprintf_make_str_flags(parameters, string_from_cs);
        sprintf_make_str_width(parameters, string_from_cs);
        break;
      case 'd':
      case 'i':
        sprintf_spec_di(string_from_cs, args, parameters);
        break;
      case 'e':
      case 'E':
        sprintf_spec_eE(string_from_cs, args, parameters);
        break;
      case 'f':
        sprintf_spec_f(string_from_cs, args, parameters);
        break;
      case 'g':
      case 'G':
        sprintf_spec_gG(string_from_cs, args, parameters);
        break;
      case 'n': {
        int *p = va_arg(*args, int *);
        *p = (int)*str_len;
        break;
      }
      case 'o':
        sprintf_spec_o(string_from_cs, args, parameters);
        break;
      case 'p':
        sprintf_spec_p(string_from_cs, args, parameters);
        break;
      case 's':
        parameters->flag_space = 0;
        parameters->flag_plus = 0;
        parameters->flag_sharp = 0;
        sprintf_spec_s(string_from_cs, args, parameters);
        break;
      case 'u':
        sprintf_spec_u(string_from_cs, args, parameters);
        break;
      case 'x':
      case 'X':
        sprintf_spec_xX(string_from_cs, args, parameters);
        break;
      case '%':
        s21_strcat(string_from_cs, "%");
        break;
    }

    s21_strcat(str, string_from_cs);
    free(string_from_cs);
    *str_len = s21_strlen(str);
  }
  return str;
}

char *sprintf_str_int(int *number, const char *format, va_list *args) {
  char width_string[21] = {0};
  int count = 0;
  while (is_digit(*format)) {
    width_string[count] = *format;
    format++;
    count++;
  }
  for (int i = 0, s = s21_strlen(width_string); i < s; i++) {
    *number += (width_string[i] - '0') * pow(10, count - i - 1);
  }

  if (*format == '*') {
    *number = va_arg(*args, int);
    format++;
  }
  return (char *)format;
}

void sprintf_int_str(format_part *parameters, char *string_from_cs,
                     long double number) {
  char point[4932] = {0};
  int check = 1;
  int i = 0;

  if (s21_strchr("dioxX", parameters->specifier) &&
      parameters->precision == 0 && number == 0 && parameters->point) {
    point[0] = '\0';
    check = 0;
  }
  while (check) {
    int digit = 0;
    if (number >= 10) {
      digit = (int)fmod(number, 10);
      number = (number - digit) / 10;
    } else {
      digit = (int)number;
      check = 0;
    }

    point[i] = (char)(digit + '0');
    i++;
  }

  point[i] = '\0';
  sprintf_reverse_str(point);
  s21_strcat(string_from_cs, point);
}

void sprintf_ul_str(char *string_from_cs, unsigned long long number,
                    format_part *parameters) {
  char *point = s21_NULL;
  int flag = 1;

  point = string_from_cs;

  while (flag) {
    int digit = 0;
    if (number >= 10) {
      digit = (int)fmod(number, 10);
      number = (number - digit) / 10;
    } else {
      digit = (int)number;
      flag = 0;
    }
    *(point++) = (char)(digit + '0');
  }
  if (parameters->precision == 0 && number == 0 && parameters->point)
    string_from_cs[0] = '\0';
  *point = '\0';
  sprintf_reverse_str(string_from_cs);
}

void sprintf_ol_str(char *string_from_cs, unsigned long long number,
                    int prefix) {
  char *point = s21_NULL;
  int flag = 1;

  point = string_from_cs;

  while (flag) {
    unsigned int digit;
    if (number > 7) {
      digit = number % 8;
      number = (number - digit) / 8;
    } else {
      digit = number;
      flag = 0;
    }
    *(point++) = (char)(digit + '0');
  }

  if (prefix == 1) *(point++) = '0';
  *point = '\0';
  sprintf_reverse_str(string_from_cs);
}

void sprintf_hl_str(char *string_from_cs, unsigned long long number,
                    format_part *parameters) {
  char *point = s21_NULL;
  int flag = 1, shift = 0;
  point = string_from_cs;
  shift = parameters->specifier == 'x' ? 32 : 0;

  while (flag) {
    unsigned int digit;
    if (number > 15) {
      digit = number % 16;
      number = (number - digit) / 16;
    } else {
      digit = number;
      flag = 0;
    }
    if (digit < 10)
      *(point++) = (char)(digit + '0');
    else
      *(point++) = (char)(digit + 'A' + shift - 10);
  }
  *point = '\0';
  if (number == 0) parameters->flag_sharp = 0;
  sprintf_reverse_str(string_from_cs);
}

void sprintf_float_str(char *string_from_cs, long double number,
                       format_part *parameters) {
  long double left = 0;
  long double right = 0;
  right = modfl(number, &left);

  if (s21_strchr("gG", parameters->specifier) && parameters->precision <= 0) {
    parameters->precision = 1;
  }
  if (parameters->precision <= 0) {
    if (right == 0.500000 && fmod(left, 2) == 0.0) {
      sprintf_int_str(parameters, string_from_cs, left);
    } else if (right == 0.500000 && (int)left % 2 != 0) {
      sprintf_int_str(parameters, string_from_cs, left + 1);
    } else {
      sprintf_int_str(parameters, string_from_cs, roundl(number));
    }
  } else {
    long double rounded_number =
        roundl(number * pow(10, parameters->precision)) /
        pow(10, parameters->precision);

    rounded_number += pow(10, -1 * (parameters->precision + 20));

    right = modfl(rounded_number, &left);

    sprintf_int_str(parameters, string_from_cs, left);
    s21_strcat(string_from_cs, ".");

    // long double r_right = roundl(right * pow(10, parameters->precision));
    long double r_right = rint(right * pow(10, parameters->precision));

    int zero_after_dot = 0;
    while (right < 1 && zero_after_dot < parameters->precision) {
      right *= 10;
      zero_after_dot++;
    }
    for (int i = 0; i < zero_after_dot - 1; i++) {
      s21_strcat(string_from_cs, "0");
    }

    r_right = roundl(r_right);
    sprintf_int_str(parameters, string_from_cs, r_right);
  }
}

void sprintf_gG_str(char *string_from_cs, long double number,
                    format_part *parameters) {
  int expo = sprintf_make_expo(number);
  if (expo < -4 || expo > parameters->precision) {
    if (parameters->precision > 0) {
      parameters->precision--;
    }
    sprintf_eE_str(string_from_cs, number, parameters);
  } else if (parameters->precision == 0) {
    parameters->precision = abs(expo);
    if (roundl(number * pow(10, parameters->precision)) /
            pow(10, parameters->precision) >
        number) {
      parameters->precision--;
    }
    sprintf_float_str(string_from_cs, number, parameters);
  } else {
    parameters->precision += expo * (-1) - 1;  // - 1
    sprintf_float_str(string_from_cs, number, parameters);
    if (!parameters->flag_sharp) {
      sprintf_delete_zero(parameters, string_from_cs);
    }
  }
}

int sprintf_make_expo(long double number) {
  int expo = 0;

  if (number > 10) {
    while (number > 10) {
      number /= 10;
      expo++;
    }
  } else if (number < 1 && number > 0) {
    while (number < 1) {
      number *= 10;
      expo--;
    }
  }

  return expo;
}

void sprintf_delete_zero(format_part *parameters, char *string_from_cs) {
  int pos = (int)s21_strlen(string_from_cs) - 1;
  if (pos > 0) {
    while (string_from_cs[pos] == '0') {
      if (!parameters->flag_sharp ||
          (parameters->flag_sharp && pos > parameters->precision)) {
        string_from_cs[pos] = '\0';
        pos--;
      }
    }
    if (!parameters->flag_sharp && string_from_cs[pos] == '.') {
      string_from_cs[pos] = '\0';
    }
  }
}

void sprintf_eE_str(char *string_from_cs, long double number,
                    format_part *parameters) {
  int expo = sprintf_make_expo(number);
  number = number / pow(10, expo);
  long double rounded_number = roundl(number * pow(10, parameters->precision)) /
                               pow(10, parameters->precision);

  if (rounded_number >= 10) {
    rounded_number /= 10;
    expo++;
  } else if (rounded_number == 0.0) {
    expo = 0;
  }

  sprintf_float_str(string_from_cs, rounded_number, parameters);

  if (s21_strchr("gG", parameters->specifier)) {
    sprintf_delete_zero(parameters, string_from_cs);
  }
  sprintf_mantissa(parameters, &string_from_cs[s21_strlen(string_from_cs)],
                   expo);
}

void sprintf_mantissa(format_part *parameters, char *mantice, int expo) {
  int start_pos = 0;
  if (parameters->flag_sharp && parameters->precision <= 0) {
    mantice[start_pos++] = '.';
  }

  if (s21_strchr("eg", parameters->specifier)) {
    mantice[start_pos++] = 'e';
  } else {
    mantice[start_pos++] = 'E';
  }

  if (expo >= 0) {
    mantice[start_pos++] = '+';
  } else {
    mantice[start_pos++] = '-';
  }

  if (abs(expo) < 10) {
    mantice[start_pos++] = '0';
    sprintf_int_str(parameters, &mantice[start_pos], abs(expo));
  } else {
    sprintf_int_str(parameters, &mantice[start_pos], abs(expo));
  }
}

void sprintf_move_string(char *string_from_cs) {
  int pos = (int)s21_strlen(string_from_cs);
  string_from_cs[pos + 1] = '\0';
  while (pos > 0) {
    string_from_cs[pos] = string_from_cs[pos - 1];
    pos--;
  }
}

void sprintf_make_str_flags(format_part *parameters, char *string_from_cs) {
  int pos = 0;
  if (!s21_strchr("cuo\%", parameters->specifier)) {
    if (parameters->specifier != 'x' && parameters->specifier != 'X') {
      if (parameters->sign < 0) {
        sprintf_move_string(string_from_cs);
        string_from_cs[pos] = '-';

      } else if (parameters->flag_plus) {
        sprintf_move_string(string_from_cs);
        if (parameters->sign >= 0) {
          string_from_cs[pos] = '+';
        }

      } else if (parameters->flag_space) {
        sprintf_move_string(string_from_cs);
        if (parameters->sign >= 0) {
          string_from_cs[pos] = ' ';
        }
      }
    }
    if (parameters->flag_sharp) {
      sprintf_sharp_flag(parameters, string_from_cs);
    }
  }
  if (parameters->flag_minus) {
    pos = (int)s21_strlen(string_from_cs);
    while (pos < parameters->width) {
      string_from_cs[pos++] = ' ';
    }
  }
}

void sprintf_sharp_flag(format_part *parameters, char *string_from_cs) {
  int pos = 0;
  if (s21_strchr("oxX", parameters->specifier)) {
    if (parameters->specifier == 'x' || parameters->specifier == 'X') {
      sprintf_move_string(string_from_cs);
    }

    if (parameters->specifier != 'o') {
      sprintf_move_string(string_from_cs);
    }
    string_from_cs[pos++] = '0';
    if (parameters->specifier != 'o')
      string_from_cs[pos] = parameters->specifier == 'x' ? 'x' : 'X';
    if (parameters->specifier == 'x') {
      string_from_cs[pos] = 'x';
    } else {
      string_from_cs[pos] = 'X';
    }
  }
  if (s21_strchr("eEf", parameters->specifier)) {
    if (!s21_strchr(string_from_cs, '.')) {
      string_from_cs[s21_strlen(string_from_cs)] = '.';
    }
  }
}

void sprintf_make_str_width(format_part *parameters, char *string_from_cs) {
  int pos_str = (int)s21_strlen(string_from_cs);
  int check = 0;
  if (parameters->flag_zero) {
    if (parameters->flag_plus || parameters->flag_space ||
        parameters->sign < 0 ||
        (parameters->specifier == 'o' && parameters->flag_sharp)) {
      check = 1;
    } else if (parameters->flag_sharp &&
               (parameters->specifier == 'x' || parameters->specifier == 'X')) {
      check = 2;
    }
  }

  if (parameters->width > pos_str) {
    string_from_cs[parameters->width + 1] = '\0';
    while (pos_str >= check) {
      string_from_cs[parameters->width--] = string_from_cs[pos_str--];
    }
    for (pos_str = check; pos_str <= parameters->width; pos_str++) {
      if (s21_strchr("diopuxX", parameters->specifier)) {
        if (parameters->flag_zero && !parameters->point) {
          string_from_cs[pos_str] = '0';
        } else {
          string_from_cs[pos_str] = ' ';
        }
      }
      if (s21_strchr("feEgGcs", parameters->specifier)) {
        if (parameters->flag_zero) {
          string_from_cs[pos_str] = '0';
        } else {
          string_from_cs[pos_str] = ' ';
        }
      }
    }
  }
}

void sprintf_make_str_precision(format_part *parameters, char *string_from_cs) {
  char *string_with_precision = s21_NULL;
  string_with_precision =
      calloc((int)s21_strlen(string_from_cs) + parameters->precision * 2,
             sizeof(char));
  int pos = 0;
  if (string_with_precision != s21_NULL) {
    if (s21_strchr("diouxX", parameters->specifier)) {
      while (pos < parameters->precision - (int)s21_strlen(string_from_cs)) {
        string_with_precision[pos++] = '0';
      }
      for (int i = 0; string_from_cs[i] != '\0'; i++) {
        string_with_precision[pos++] = string_from_cs[i];
      }
      s21_strcpy(string_from_cs, string_with_precision);
    }
    free(string_with_precision);
  }
}

void sprintf_reverse_str(char *string_from_cs) {
  char c = ' ';
  s21_size_t length = s21_strlen(string_from_cs);
  for (s21_size_t i = 0; i < length / 2; i++) {
    c = string_from_cs[i];
    string_from_cs[i] = string_from_cs[length - 1 - i];
    string_from_cs[length - 1 - i] = c;
  }
}

void sprintf_spec_di(char *string_from_cs, va_list *args,
                     format_part *parameters) {
  long int ld_number = 0;
  short int sh_number = 0;
  int number = 0;
  switch (parameters->length) {
    case 'h':
      sh_number = (short int)va_arg(*args, int);
      sprintf_make_sign(sh_number, parameters);
      sprintf_int_str(parameters, string_from_cs, sh_number * parameters->sign);
      break;
    case 'l':
      ld_number = (long int)va_arg(*args, long int);
      sprintf_make_sign(ld_number, parameters);
      sprintf_int_str(parameters, string_from_cs, ld_number * parameters->sign);
      break;
    default:
      number = va_arg(*args, int);
      sprintf_make_sign(number, parameters);
      sprintf_int_str(parameters, string_from_cs, number * parameters->sign);
      break;
  }
  sprintf_make_str_precision(parameters, string_from_cs);
  sprintf_make_str_flags(parameters, string_from_cs);
  sprintf_make_str_width(parameters, string_from_cs);
}

void sprintf_spec_eE(char *string_from_cs, va_list *args,
                     format_part *parameters) {
  long double l_number = 0;
  double number = 0;
  switch (parameters->length) {
    case 'L':
      l_number = va_arg(*args, long double);
      sprintf_make_sign(l_number, parameters);
      sprintf_eE_str(string_from_cs, l_number * parameters->sign, parameters);
      break;
    default:
      number = va_arg(*args, double);
      sprintf_make_sign(number, parameters);
      sprintf_eE_str(string_from_cs, number * parameters->sign, parameters);
      break;
  }

  sprintf_make_str_flags(parameters, string_from_cs);
  sprintf_make_str_width(parameters, string_from_cs);
}

void sprintf_spec_f(char *string_from_cs, va_list *args,
                    format_part *parameters) {
  long double l_number = 0;
  double d_number = 0;

  switch (parameters->length) {
    case 'L':
      l_number = va_arg(*args, long double);
      sprintf_make_sign(l_number, parameters);
      sprintf_float_str(string_from_cs, l_number * parameters->sign,
                        parameters);
      break;
    case 'l':
    default:
      d_number = va_arg(*args, double);
      sprintf_make_sign(d_number, parameters);
      sprintf_float_str(string_from_cs, d_number * parameters->sign,
                        parameters);
      break;
  }
  sprintf_make_str_flags(parameters, string_from_cs);
  sprintf_make_str_width(parameters, string_from_cs);
}

void sprintf_spec_gG(char *string_from_cs, va_list *args,
                     format_part *parameters) {
  long double l_number = 0;
  double number = 0;

  switch (parameters->length) {
    case 'L':
      l_number = va_arg(*args, long double);
      sprintf_make_sign(l_number, parameters);
      sprintf_gG_str(string_from_cs, l_number * parameters->sign, parameters);
      break;
    case 'l':
    default:
      number = va_arg(*args, double);
      sprintf_make_sign(number, parameters);
      sprintf_gG_str(string_from_cs, number * parameters->sign, parameters);
      break;
  }

  sprintf_make_str_flags(parameters, string_from_cs);
  sprintf_make_str_width(parameters, string_from_cs);
}

void sprintf_spec_o(char *string_from_cs, va_list *args,
                    format_part *parameters) {
  unsigned long int ld_number = 0;
  unsigned short int sd_number = 0;
  unsigned int number = 0;

  switch (parameters->length) {
    case 'h':
      sd_number = (unsigned short int)va_arg(*args, unsigned int);
      sprintf_ol_str(string_from_cs, sd_number, parameters->flag_sharp);
      break;
    case 'l':
      ld_number = (unsigned long int)va_arg(*args, unsigned long int);
      sprintf_ol_str(string_from_cs, ld_number, parameters->flag_sharp);
      break;
    default:
      number = va_arg(*args, unsigned int);
      sprintf_ol_str(string_from_cs, number, parameters->flag_sharp);
      break;
  }
  sprintf_make_str_precision(parameters, string_from_cs);
  sprintf_make_str_flags(parameters, string_from_cs);
  sprintf_make_str_width(parameters, string_from_cs);
}

void sprintf_spec_s(char *string_from_cs, va_list *args,
                    format_part *parameters) {
  char *string = s21_NULL;
  string = va_arg(*args, char *);
  if (s21_strlen(string) > 1020) {
    string_from_cs = realloc(string_from_cs,
                             ((parameters->width + parameters->precision) * 2 +
                              1024 + (int)s21_strlen(string)) *
                                 sizeof(char));
  }
  if (string_from_cs != s21_NULL) {
    if (parameters->precision > -1)
      s21_strncat(string_from_cs, string, parameters->precision);
    else
      s21_strcat(string_from_cs, string);
    sprintf_make_str_precision(parameters, string_from_cs);
    sprintf_make_str_flags(parameters, string_from_cs);
    sprintf_make_str_width(parameters, string_from_cs);
  }
}

void sprintf_spec_u(char *string_from_cs, va_list *args,
                    format_part *parameters) {
  unsigned short us_number = 0;
  unsigned long ul_number = 0;
  unsigned int u_number = 0;

  switch (parameters->length) {
    case 'h':
      us_number = (unsigned short)va_arg(*args, unsigned int);
      sprintf_ul_str(string_from_cs, us_number, parameters);
      break;
    case 'l':
      ul_number = (unsigned long)va_arg(*args, unsigned long);
      sprintf_ul_str(string_from_cs, ul_number, parameters);
      break;
    default:
      u_number = (unsigned int)va_arg(*args, unsigned int);
      sprintf_ul_str(string_from_cs, u_number, parameters);
      break;
  }

  sprintf_make_str_precision(parameters, string_from_cs);
  sprintf_make_str_flags(parameters, string_from_cs);
  sprintf_make_str_width(parameters, string_from_cs);
}

void sprintf_spec_xX(char *string_from_cs, va_list *args,
                     format_part *parameters) {
  unsigned long int ld_number = 0;
  unsigned short int sd_number = 0;
  unsigned int number = 0;

  switch (parameters->length) {
    case 'h':
      sd_number = (unsigned short int)va_arg(*args, unsigned int);
      sprintf_hl_str(string_from_cs, sd_number, parameters);
      break;
    case 'l':
      ld_number = (unsigned long int)va_arg(*args, unsigned long int);
      sprintf_hl_str(string_from_cs, ld_number, parameters);
      break;
    default:
      number = (unsigned int)va_arg(*args, unsigned int);
      sprintf_hl_str(string_from_cs, number, parameters);
      break;
  }
  sprintf_make_str_precision(parameters, string_from_cs);
  sprintf_make_str_flags(parameters, string_from_cs);
  sprintf_make_str_width(parameters, string_from_cs);
}

void sprintf_spec_p(char *string_from_cs, va_list *args,
                    format_part *parameters) {
  int width = parameters->width < 15 ? 15 : parameters->width;
  char *str_start = s21_NULL;
  str_start = string_from_cs;
  int *p = va_arg(*args, int *);
  char buf[4] = "x0";
  if (p == s21_NULL) {
    s21_strcpy(buf, "0x0");
  }
  for (int *j = p, k = 0; j && k < width;
       j = (void *)(((s21_size_t)j) >> 4), k++) {
    unsigned int dig = ((s21_size_t)j) % 0x10;
    if (dig < 10)
      *(str_start++) = (char)('0' + dig);
    else
      *(str_start++) = (char)('a' + (dig - 10));
  }
  *str_start = '\0';
  s21_strcat(string_from_cs, buf);
  sprintf_reverse_str(string_from_cs);
  sprintf_make_str_precision(parameters, string_from_cs);
  sprintf_make_str_flags(parameters, string_from_cs);
  sprintf_make_str_width(parameters, string_from_cs);
}

void sprintf_make_sign(double number, format_part *parameters) {
  if (number < 0) {
    parameters->sign = -1;
  } else {
    parameters->sign = 1;
  }
  if (parameters->flag_space == 1 && parameters->sign == -1) {
    parameters->flag_space = 0;
  }
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
