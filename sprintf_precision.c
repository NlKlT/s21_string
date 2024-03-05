#include "s21_string.h"

const char *precision(const char *format, flags *f, va_list arg_ptr) {
  if (*format == '.') {
    f->isPrecisionSet = ON;
    format++;
  }
  if (*format == '*') {
    format++;
    f->precision = va_arg(arg_ptr, int);
  }
  if (isDigit(*format)) {
    char tmp[BUFFERSIZE] = {'\0'};
    for (int i = 0; isDigit(*format); i++, format++) tmp[i] = *format;
    f->precision = atoi(tmp);
  }
  return format;
}