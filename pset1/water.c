/*
 * water.c
 *
 * This program calculates the number of
 * bottles of water used, depending on how
 * much time in minutes a user spends in taking
 * a shower
 */

#include <stdio.h>
#include <cs50.h>

int bottles_used(int input);

int main(void)
{
    // Prompts the user for input
    int minutes;

    do
    {
        printf("Minutes: ");
        minutes = get_int();
    }
    while (minutes < 0);

    /*
     * Prints the number of bottles used.
     * Also calls the bottles_used function
     */
    printf("Bottles: %i\n", bottles_used(minutes));
}

/* This function outputs the
 * number of bottles used by
 * multiplying the minutes entered
 * by the user, by the litteral 12.
 * 12 is the number of bottles used in
 * one minute in the shower.
 *
 * The function takes in an argument of the
 * type int, and returns a value of type int
 */
int bottles_used(int input)
{
    return input * 12;
}