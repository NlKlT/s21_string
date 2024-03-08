#include "flag_check.h"
// функция должна запускаться, если в строке найдет идентификатор '%'. Она
// проверяет, является ли следующий за '%' символ флагом.
int flag_check(char *str, char flag) {
  int ans = 1;
  switch (flag) {
    case '-':
      if (minus_flag == 0)
        minus_flag = 1;  // проверяем, что флаг не был активирован до этого.
                         // Если был - это значит, что текущий символ уже не
                         // флаг, а строка, которую мы считываем.
      else
        ans = 0;
      break;
    case '+':
      if (plus_flag == 0)
        plus_flag = 1;
      else
        ans = 0;
      break;
    case ' ':
      if (space_flag == 0)
        space_flag = 1;
      else
        ans = 0;
      break;
    case '0':
      if (zero_flag == 0)
        zero_flag = 1;
      else
        ans = 0;
      break;
    case '#':
      if (hashtag_flag)
        hashtag_flag = 1;
      else
        ans = 0;
      break;
    default:
      ans = 0;
  }
  return ans;
}

// Если ans = 1, то необходимо проверить, является ли следующий символ в строке
// флагом, иначе - переходим к проверке ширины (функция format_length)
