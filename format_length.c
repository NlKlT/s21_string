#include "format_length.h"

int format_length(char *str, char *flag) {
  int length = 0, i = 0;
  if (flag[0] == '*')
    length_as_parametr = 1;  // в таком случае, мы считываем длину из первого
                             // параметра форматируемой строки.
  while (isdigit(flag[i])) {
    length = length * 10 + (int)flag[i];
    i++;
  }
  return length;
}