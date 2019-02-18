/*
 * mario.c
 *
 * This program prints a half
 * pyramid using spaces and hashes.
 * The height of the pyramid is determined
 * by the input entered by the user
 */
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    /*
     * Prompts the user for a positive integer
     * no greater than 23
     */
    int height;

    do
    {
        printf("Enter a height for your pyramid: ");
        height = get_int();
    }
    while ((height < 0) || (height > 23));

    // Determines the base of the pyramid
    int base = height + 1;

    /*
     * Calculates slots for spaces
     * and hashes
     */
    int space_slot = base - 2;
    int hash_slot = base - space_slot;

    // Draws the pyramid
    for (int row = 0; row < height; row++)
    {
        for (int space = 0; space < space_slot; space++)
        {
            printf(" ");
        }

        for (int hash = 0; hash < hash_slot; hash++)
        {
            printf("#");
        }

        printf("\n");

        /*
         * Decrements the spaces
         * and increments the hashes
         */
        space_slot--; hash_slot++;
    }
}