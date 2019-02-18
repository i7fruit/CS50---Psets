/**
 * recover.c
 */

#include <stdio.h>
#include <stdlib.h>

#define BLOCK 512

// Stores the strings for read and write mode
char *read = "r";
char *write = "w";

void recover(FILE *infile, unsigned char *b);

int main(int argc, char *argv[])
{
    // Checks for proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover argv[1]\n");
        return 1;
    }

    // Stores the name of the readfile
    char *card = argv[1];

    // Opens the cardfile for reading
    FILE *cardfile;
    if ((cardfile = fopen(card, read)) == 0)
    {
        fprintf(stderr, "Cannot open %s\n", card);
        return 2;
    }

    // Creates a buffer to hold bytes temporarily
    unsigned char *buffer = malloc(BLOCK * sizeof(char));
    if (buffer == NULL)
    {
        fclose(cardfile);
        fprintf(stderr, "Not enough memory\n");
        return 3;
    }

    // Recovers the jpg files
    recover(cardfile, buffer);

    // Closes the cardfile
    fclose(cardfile);

    // Deallocates memory for buffer
    free(buffer);

    return 0;
}

/*****************************************************************************
 * The recover() function iterates through
 * the bits stored in a file searching for
 * a specific arrangement of bits that
 * identify the header to a .jpg file. Once
 * detected, the funtion begins to write these
 * bits to a file for storage until a new header
 * is identified
 */

void recover(FILE *infile, unsigned char *b)
{
    // Iterates through the bytes stored on the cardfile
    while (!feof(infile))
    {
        // Reads every four bytes till a jpg header is found
        if (BLOCK == (fread(b, sizeof(char), BLOCK, infile)))
        {
            if (((b[0] == 0xff) && (b[1] == 0xd8) && (b[2] == 0xff))
                && ((b[3] & 0xf0) == 0xe0))
            {
                // Array to store name of found file
                const short size = 8;
                char pix[size];
                static short count = 0;
                sprintf(pix, "%03hi.jpg", count++);

                FILE *outfile;
                if ((outfile = fopen(pix, write)) == 0)
                {
                    fprintf(stderr, "Cannot open %s\n", pix);
                    exit(1);
                }

                // Writes to the outfile
                fwrite(b, sizeof(char), BLOCK, outfile);

                /**
                 * Continues to write to a particular file
                 * until a new jpg header is identified
                 */

                while (!feof(infile))
                {
                    if (BLOCK == (fread(b, sizeof(char), BLOCK, infile)))
                    {
                        if (!(((b[0] == 0xff) && (b[1] == 0xd8) && (b[2] == 0xff))
                              && ((b[3] & 0xf0) == 0xe0)))
                        {
                            fwrite(b, sizeof(char), BLOCK, outfile);
                        }

                        else
                        {
                            fclose(outfile);
                            fseek(infile, -BLOCK, SEEK_CUR);
                            break;
                        }
                    }

                    else
                    {
                        fclose(outfile);
                        break;
                    }
                }
            }
        }

        else
        {
            break;
        }
    }
}