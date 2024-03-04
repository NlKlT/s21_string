#include "format_length.h"

int format_length(char *str, char *flag) {
  int length = 0, i = 0;
  while (isdigit(flag[i])) {
    length = length * 10 + (int)flag[i];
    i++;
  }
  return length;
}