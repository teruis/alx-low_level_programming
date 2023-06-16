#include <stdio.h>
#include <ctype.h>

/**
 * main - Program that prints all the numbers of base 16 in lowercase,
 * followed by a new line.
 *
 * You can only use the putchar function (every other function (printf,
 * puts, etc…) is forbidden).
 * All your code should be in the main function.
 * You can only use putchar three times in your code.

 * Return: 0.
*/

#include <stdio.h>

int main() {
  int i;
  for (i = 0; i <= 15; i++) {
    putchar(i + '0');
  }
  for (i = 10; i <= 15; i++) {
    putchar(i - 10 + 'a');
  }
  putchar('\n');
  return 0;
}
