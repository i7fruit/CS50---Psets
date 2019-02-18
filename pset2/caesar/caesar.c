/*
 * caesar.c
 * Nzefili Macaulay
 *
 * This program takes plaintext from the user
 * and encrypts it using a key entered by the
 * user at the command line, and displays it
 * to the screen
 *
 * The encryption is done using the following formula:
 *
 * c[i] = (p[i] + key) MOD 26
 *
 * where c[i] = i'th character of ciphertext
 *       p[i] = The alphabetical index of the i'th character of the plaintext
 *       key = secret key entered at the command line
 *       MOD 26 is used to give the wrap-around effect
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h> // For the atoi() function
#include <ctype.h> // For the character functions

int alpha_index(char a);

int main(int argc, string argv[])
{
    // Returns an error code if the argument count is not 2
    if (argc != 2)
    {
        printf("USAGE:./program_name argv1\n");
        return 1;
    }

    if (argc == 2)
    {
        // Prompts the user for input
        printf("plaintext: ");
    }

    // Gets input from the user
    string p_txt = get_string();

    // Converts the key to an integer
    int key = atoi(argv[1]);

    // Declares an array to store the ciphertext
    int c_txt[strlen(p_txt)];

    printf("ciphertext: ");

    // Iterates over the characters of the plaintext
    for (int i = 0, n = strlen(p_txt); i < n; i++)
    {
        c_txt[i] = (alpha_index(p_txt[i]) + key) % 26;

        // Converts and displays back to ASCII
        if (isupper(p_txt[i]))
        {
            c_txt[i] = c_txt[i] + 'A';
            printf("%c", (char)c_txt[i]);
        }

        else if (islower(p_txt[i]))
        {
            c_txt[i] = c_txt[i] + 'a';
            printf("%c", (char)c_txt[i]);
        }

        // Just prints out the plaintext if it's not an alphabet
        else if (!(isalpha(p_txt[i])))
        {
            printf("%c", p_txt[i]);
        }
    }
    printf("\n");

    return 0;
}

/*
 * The alpha_index() function determines
 * the alphabetical index of any uppercase
 * or lowercase alphabet in English by assigning
 * the numbers 0 through 25 to the alphabets A through Z.
 *
 * It does this by modulo dividing the integer value of a given
 * ASCII alphabet by 'A' if uppercase, and 'a' if lowercase
 */
int alpha_index(char a)
{
    if (isupper(a))
    {
        return a % 'A';
    }

    else if (islower(a))
    {
        return a % 'a';
    }

    return 0;
}