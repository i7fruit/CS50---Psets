/*
 * crack.c
 * Nzefili Macaulay
 *
 * This program takes a user's hashed password,
 * decrypts it, and prints the actual password
 * in plaintext to the screen
 */
#define _XOPEN_SOURCE // For the crypt() function
#include <unistd.h>   // For the crypt() function
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>    // For the character functions
#include <stdlib.h>   // For the exit() function

#define P_SIZE 5 // Defines the size of the array holding the password
#define S_SIZE 3 // Defines the size of the array holding the salt

int main(int argc, string argv[])
{
    // Prints a warning if the argument count is incorrect
    if (argc != 2)
    {
        printf("USAGE:./program_name argv[1]\n");
        return 1;
    }

    // Declares an array to hold the salt
    char salt[S_SIZE];

    for (int i = 0; i < S_SIZE; i++)
    {
        salt[i] = argv[1][i];
        salt[S_SIZE - 1] = '\0';
    }

    // Declares an array of characters to hold the key to be tested
    char key[P_SIZE];

    // Fills up the key with null bytes
    for (int a = 0; a < P_SIZE; a++)
    {
        key[a] = '\0';
    }

    // Trys for one-character keys
    for (int i = 0; i < 1; i++)
    {
        // Iterates over element 0
        for (int j = 65; j < 123; j++)
        {
            if (j == 91)
            {
                j = 97;
            }

            key[i] = (char)j;

            // Checks for a match between my hashed try, and the given hash
            if ((strcmp(crypt(key, salt), argv[1]) == 0))
            {
                printf("%s\n", key);
                exit(0);
            }
        }
    }

    // Try for two-character keys
    for (int i = 0; i < 1; i++)
    {
        // Iterates over element 0
        for (int j = 65; j < 123; j++)
        {
            if (j == 91)
            {
                j = 97;
            }

            key[i] = (char)j;

            // Iterates over element 1
            for (int k = 65; k < 123; k++)
            {
                if (k == 91)
                {
                    k = 97;
                }
                key[i + 1] = (char)k;

                // Checks for a match between my hashed try, and the given hash
                if ((strcmp(crypt(key, salt), argv[1]) == 0))
                {
                    printf("%s\n", key);
                    exit(0);
                }
            }
        }
    }

    // Try for three-character keys
    for (int i = 0; i < 1; i++)
    {
        // Iterates over element 0
        for (int j = 65; j < 123; j++)
        {
            if (j == 91)
            {
                j = 97;
            }

            key[i] = (char)j;

            // Iterates over element 1
            for (int k = 65; k < 123; k++)
            {
                if (k == 91)
                {
                    k = 97;
                }

                key[i + 1] = (char)k;

                // Iterates over element 2
                for (int l = 65; l < 123; l++)
                {
                    if (l == 91)
                    {
                        l = 97;
                    }

                    key[i + 2] = (char)l;

                    // Checks for a match between my hashed try, and the given hash
                    if ((strcmp(crypt(key, salt), argv[1]) == 0))
                    {
                        printf("%s\n", key);
                        exit(0);
                    }
                }
            }
        }
    }

    // Try for four-character keys
    for (int i = 0; i < 1; i++)
    {
        // Iterates over element 0
        for (int j = 65; j < 123; j++)
        {
            if (j == 91)
            {
                j = 97;
            }

            key[i] = (char)j;

            // Iterates over element 1
            for (int k = 65; k < 123; k++)
            {
                if (k == 91)
                {
                    k = 97;
                }

                key[i + 1] = (char)k;

                // Iterates over element 2
                for (int l = 65; l < 123; l++)
                {
                    if (l == 91)
                    {
                        l = 97;
                    }

                    key[i + 2] = (char)l;

                    // Iterates over element 3
                    for (int m = 65; m < 123; m++)
                    {
                        if (m == 91)
                        {
                            m = 97;
                        }

                        key[i + 3] = (char)m;

                        // Checks for a match between my hashed try, and the given hash
                        if ((strcmp(crypt(key, salt), argv[1]) == 0))
                        {
                            printf("%s\n", key);
                            exit(0);
                        }
                    }
                }
            }
        }
    }

    return 0;
}