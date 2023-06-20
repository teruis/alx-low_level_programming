#include "main.h"

/**
 * main - Entry point
 * Description: prints putchar using putchar prototype
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
  char str[] = "_putchar";
  int ch;

  /* Iterate through the string, calling _putchar() for each character */
  for (ch = 0; ch < 8; ch++)
    _putchar(str[ch]);

  /* Print a newline character */
  _putchar('\n');

  /* Return 0 to indicate success */
  return (0);
}
