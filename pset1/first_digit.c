/**
 * first_digit.c
 *
 * This program prints the first digit
 * of an integer by first checking if
 * the integer is greater than or equal
 * ten, and dividing by ten until this
 * condition fails
 */
#include <stdio.h>

int main(void)
{
    int n = 5234;
    int first;

    // Divides the integer by ten until it is less than 10
    while (n >= 10)
    {
        first = n /= 10;
    }

    printf("1st number is %i\n", first);
}