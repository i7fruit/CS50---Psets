/**
 * resize.c (less comfortable)
 *
 * This program resizes a BMP file
 * by enlarging it by a value provided
 * by the user.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

// Function prototypes
void update_outfile(BITMAPFILEHEADER *f, BITMAPINFOHEADER *i, int scale, int *pad);
void resize(BITMAPINFOHEADER in, FILE *inf, FILE *outf, int inpad, int outpad, int scale);

int main(int argc, char *argv[])
{
    // Ensures proper usage of the program
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // Converts the argv[1] string to an integer
    int n = abs(atoi(argv[1]));

    // Checks if value to scale the bitmap by is withing range
    if (n < 1 || n > 100)
    {
        fprintf(stderr, "Scale value should be from 1 through 100\n");
        return 1;
    }

    // Arrays to store the filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // Opens the input file for reading
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // Opens the output file for writing
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // Reads the infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Reads the infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensures that the infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Saves a copy of the infile's BITMAPINFO HEADER
    BITMAPINFOHEADER bi_copy = bi;

    // Computes padding for the infile
    int infile_padding = (4 - (bi_copy.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Variable to hold padding for the outfile
    int outfile_padding;

    // Updates outfile's header
    update_outfile(&bf, &bi, n, &outfile_padding);

    // Writes the outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Writes the outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Resizes the BMP file
    resize(bi_copy, inptr, outptr, infile_padding, outfile_padding, n);

    // Closes the infile
    fclose(inptr);

    // Closes the outfile
    fclose(outptr);

    // Success
    return 0;
}

/******************************************************************************
 * The update_outfile() function changes
 * the bfSize, biWidth, biHeight, and
 * biSizeImage fields of the outfile's
 * header
 */

void update_outfile(BITMAPFILEHEADER *f, BITMAPINFOHEADER *i, int scale, int *pad)
{
    // Updates the width
    i->biWidth *= scale;

    // Updates the height
    i->biHeight *= scale;

    // Determines the padding for the oufile (if needed)
    *pad = (4 - (i->biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Determines the size of the image
    i->biSizeImage = ((sizeof(RGBTRIPLE) * i->biWidth) + *pad) * abs(i->biHeight);

    // Determines the size of the file
    f->bfSize = i->biSizeImage + f->bfOffBits;
}

/******************************************************************************
 * The resize() function scales a BMP file upwards
 * according to the value of scale define by the user.
 * It iterates over each scanline in the input file,
 * writing each of its pixels multiple times to the
 * output file
 */

void resize(BITMAPINFOHEADER in, FILE *inf, FILE *outf, int inpad, int outpad, int scale)
{
    // Iterates over the scanlines of the infile
    for (int i = 0, Height = abs(in.biHeight); i < Height; i++)
    {
        // Resizes vertically
        for (int m = 0; m < scale; m++)
        {
            // Iterates over pixels in scanline
            for (int j = 0; j < in.biWidth; j++)
            {
                // Temporary storage
                RGBTRIPLE triple;

                // Reads RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inf);

                // Writes RGB triple to outfile to scale
                for (int k = 0; k < scale; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outf);
                }
            }

            // Skips over the infile padding, if any
            fseek(inf, inpad, SEEK_CUR);

            // Adds padding to outfile if needed
            for (int l = 0; l < outpad; l++)
            {
                fputc(0x00, outf);
            }

            // Returns pointer in infile to start of scanline to be rewritten
            if (m + 1 != scale)
            {
                fseek(inf, -((sizeof(RGBTRIPLE) * in.biWidth) + inpad), SEEK_CUR);
            }
        }
    }
}