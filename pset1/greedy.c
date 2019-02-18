/*
 * greedy.c
 *
 * This program calculates the minimum
 * number of coins required to give a
 * user change
 */
#include <stdio.h>
#include <cs50.h>
#include <math.h> // Included for the round() function

int main(void)
{
    // This asks the user for the amount of change owed
    float change;
    int coin_count = 0;

    do
    {
        printf("How much change is owed?\n");
        change = get_float();
    }
    while (change < 0.00);

    /*
     * This converts the change to cents
     * and then is rounded off to avoid
     * errors from floating-point impresision
     */
    change = round(change * 100);

    /*
     * Determines the minimum number
     * of coins used.
     */
    while (change >= 25)
    {
        coin_count++;
        change -= 25;
    }

    while (change >= 10)
    {
        coin_count++;
        change -= 10;
    }

    while (change >= 5)
    {
        coin_count++;
        change -= 5;
    }

    while (change >= 1)
    {
        coin_count++;
        change -= 1;
    }

    printf("%i coins\n", coin_count);
}