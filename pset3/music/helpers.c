// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

#include "helpers.h"

//The size of the NOTES array
#define NOTES_SIZE 12

//Function prototypes
short find_position(char arr[]);
int get_frequency(short oct, short k);

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int a = atoi(&fraction[0]);
    int b = atoi(&fraction[2]);

    return (float)a / b * 8.0;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    short octave = 0, n = strlen(note);
    short i;
    int f = 0;

    /**
     * A character array to store the non-digit
     * parts of the note.
     */

    char c[n + 1];

    //Changes the entry to uppercase if user typed lowercase
    for (i = 0; i < n; i++)
    {
        c[i] = toupper(note[i]);
    }

    //Truncates the digit part of the note stored in the char c[] array
    if (n == 2 || n == 3)
    {
        c[n - 1] = '\0';
    }

    //Adjusts for Flats and Sharps
    if (c[1] == 'B')
    {
        if (c[0] == 'F')
        {
            c[0] = 'E';
            c[1] = '\0';
        }

        else if (c[0] == 'A')
        {
            c[0] = 'G';
            c[1] = '#';
        }

        else
        {
            c[0] = c[0] - 1;
            c[1] = '#';
        }
    }

    else if (c[1] == '#' && c[0] == 'E')
    {
        c[0] = 'F';
        c[1] = '\0';
    }

    //Separates note from octave
    if (n == 2 || n == 3)
    {
        octave = atoi(&note[n - 1]);
    }

    //Finds the position of the note in the NOTES array
    short k = find_position(c);

    //Computes the frequency
    return f = get_frequency(octave, k);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // Function returns true if the user typed Enter
    if (strcmp(s, "\0") == 0)
    {
        return true;
    }

    return false;
}

/**
 * The find_positon() function takes an array
 * of characters and compares them to the characters
 * stored in the NOTES array using the strcmp() function.
 * It returns to the caller number of the element in the NOTES array
 * that holds the character that matches its argument
 */

short find_position(char arr[])
{
    //Notes in an octave
    const string NOTES[] = {"C", "C#", "D", "D#", "E", "F",
                            "F#", "G", "G#", "A", "A#", "B"
                           };

    short k = 0;

    for (; k < NOTES_SIZE; k++)
        if (strcmp(arr, NOTES[k]) == 0)
        {
            break;
        }

    return k;
}

/**
 * The get_frequency function takes as arguments
 * the numbers representing the octave of the note,
 * as well as what element in the NOTES array holds
 * the non-digit part of the note.
 *
 * It calculates the number of notes between that particular
 * note and A4, and then computes the frequency of the note
 * using the formular f = 440 * 2^n/12, where n is the
 * number of notes from A4
 */

int get_frequency(short oct, short p)
{
    //Notes in an octave
    const string NOTES[] = {"C", "C#", "D", "D#", "E", "F",
                            "F#", "G", "G#", "A", "A#", "B"
                           };

    //Finds number of notes from note A4
    int freq = 0, b = 0;

    //For notes before the 4th octave
    if (oct < 4)
        for (; p < NOTES_SIZE; p++)
        {
            if (strcmp("A", NOTES[p]) == 0 && oct == 4)
            {
                break;
            }

            else
            {
                b--;
            }

            if (p == 11)
            {
                p = -1;
                oct++;
            }
        }

    //For notes after the 4th octave
    else if (oct > 4)
    {
        for (; p > -1; p--)
        {
            if (strcmp("A", NOTES[p]) == 0 && oct == 4)
            {
                break;
            }

            else
            {
                b++;
            }

            if (p == 0)
            {
                p = 12;
                oct--;
            }
        }
    }

    //For notes within the 4th octave
    else if (oct == 4)
    {
        if (p < 10)
        {
            for (; p < NOTES_SIZE; p++)
            {
                if (strcmp("A", NOTES[p]) == 0 && oct == 4)
                {
                    break;
                }

                else
                {
                    b--;
                }
            }
        }

        else if (p > 8)
        {
            for (; p > -1; p--)
            {
                if (strcmp("A", NOTES[p]) == 0 && oct == 4)
                {
                    break;
                }

                else
                {
                    b++;
                }

                if (p == 0)
                {
                    p = 12;
                    oct--;
                }
            }
        }

        else
        {
            return 440;
        }
    }

    //Computes the frequency
    float z = pow(2, (float)b / 12);
    return freq = round(440 * z);
}
