/*
 * credit.c
 *
 * This program uses Luhn's Algorithm
 * to check if the credit card number
 * entered by a user is valid or not.
 *
 * It also identifies if the card is
 * a VisaCard, Mastercard, or American
 * Express card. The program identifies
 * valid cards outside of these three as
 * "Unknown"
 */
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    /*
     * Prompts the user for a credit
     * card number.
     */
    long long cc_number;

    do
    {
        printf("Number: ");
        cc_number = get_long_long();
    }
    // Loops while digits are < 10 or > 16
    while ((cc_number < 1000000000) || (cc_number > 9999999999999999));

    /*
     * Determines the length of the card number.
     * copy_ccnmbr is a copy of the credit card
     * number used to determine the length so that
     * the original number is not modified
     */
    long long length = 0, copy_ccnmbr = cc_number;

    while (copy_ccnmbr != 0)
    {
        copy_ccnmbr /= 10;
        length++;
    }

    // Calculates the checksum of the card
    long long i = 0, j = 0, x = 0, y = 0, total = 0;

    for (i = 1, j = 1; i <= length; i++, j = j * 10)
    {
        if ((i % 2) == 0) // Identifies even-numbered positions
        {
            x = ((cc_number / j) % 10);
            y = x * 2;

            if (y > 9)
            {
                total = total + (y / 10) + (y % 10); // Sums up digits of a 2-digit number
                x = 0;
            }
            else
            {
                total = total + y;
                x = 0;
            }
        }
        else
        {
            x = ((cc_number / j) % 10);
            total = total + x;
            x = 0;
        }
    }

    // Determines the company identifier
    long long coy_ID = cc_number;

    if ((total % 10) == 0)
    {
        while (coy_ID >= 100)
        {
            coy_ID = coy_ID / 10;
        }

        if (((length == 13) || (length == 16)) && ((coy_ID > 39) && (coy_ID < 50)))
        {
            printf("Visa\n");
        }

        else if ((length == 16) && ((coy_ID > 50) && (coy_ID < 56)))
        {
            printf("Mastercard\n");
        }

        else if ((length == 15) && ((coy_ID == 34) || (coy_ID == 37)))
        {
            printf("American Express\n");
        }

        else
        {
            printf("Unknown\n");
        }
    }

    else
    {
        printf("Invalid\n");
    }
}