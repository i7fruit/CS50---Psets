/**
 * resize.c (more comfortable)
 *
 * This program resizes a BMP file
 * by enlarging or reducing it by
 * a value provided by the user.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

// Function prototypes
void update_outfile(BITMAPFILEHEADER *f, BITMAPINFOHEADER *i, float scale, int *pad);

void read_infile_scanline(BITMAPINFOHEADER *g, RGBTRIPLE arr[][g->biWidth], int inpad, FILE *from);

void write_outfile_scanline(BITMAPINFOHEADER *h, BITMAPINFOHEADER *i, RGBTRIPLE arr[abs(i->biHeight)][i->biWidth], int outpad,
                            FILE *to, float scale);

int main(int argc, char *argv[])
{
    // Ensures proper usage of the program
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize f infile outfile\n");
        return 1;
    }

    // Converts the argv[1] string to an integer
    float f = atof(argv[1]);

    // Checks if value to scale the bitmap by is withing range
    if (f < 0.0 || f > 100.0)
    {
        fprintf(stderr, "Scale value should be from 0.0 through 100.0\n");
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
    update_outfile(&bf, &bi, f, &outfile_padding);

    // Writes the outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Writes the outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Creates a multidimentional array to store the pixels in the infile
    RGBTRIPLE temp[abs(bi_copy.biHeight)][bi_copy.biWidth];

    // Reads RGB triples from the input file
    read_infile_scanline(&bi_copy, temp, infile_padding, inptr);

    // Writes RGB triples to the output file
    write_outfile_scanline(&bi, &bi_copy, temp, outfile_padding, outptr, f);

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

void update_outfile(BITMAPFILEHEADER *f, BITMAPINFOHEADER *i, float scale, int *pad)
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
 * The read_infile_scanline() function
 * reads the scanlines of the infile
 * and stores them in a temporary
 * holding array
 */

void read_infile_scanline(BITMAPINFOHEADER *g, RGBTRIPLE arr[][g->biWidth], int inpad, FILE *from)
{
    // Iterates over the infile's scanlines
    for (int i = 0, infile_Height = abs(g->biHeight); i < infile_Height; i++)
    {
        // Iterates over pixels in the scanline
        for (int j = 0; j < g->biWidth; j++)
        {
            // Temporary storage
            RGBTRIPLE triple;

            // Reads RGB triple from the infile
            fread(&triple, sizeof(RGBTRIPLE), 1, from);

            // Saves RGB triple to the multidimentional array
            arr[i][j] = triple;
        }

        // Skips over the infile padding, if any
        fseek(from, inpad, SEEK_CUR);
    }
}

/******************************************************************************
 * The write_outfile_scanline() function
 * reads the triples stored in the temporary array
 * and writes them to the outfile
 */

void write_outfile_scanline(BITMAPINFOHEADER *h, BITMAPINFOHEADER *i, RGBTRIPLE arr[abs(i->biHeight)][i->biWidth], int outpad,
                            FILE *to, float scale)
{
    // Determines pixels to write to the outfile
    int k = 0;

    // Resizes vertically by iterating through each scanline in the output file
    for (h->biHeight = abs(h->biHeight); k < h->biHeight; k++)
    {
        // Resizes horizontally by iterating through each pixel in the scanline
        for (int l = 0; l < h->biWidth; l++)
        {
            int row = (int)(k / scale);
            int col = (int)(l / scale);

            // Writes RGB triples to the outfile
            fwrite(&arr[row][col], sizeof(RGBTRIPLE), 1, to);
        }

        // Adds padding to outfile if needed
        for (int m = 0; m < outpad; m++)
        {
            fputc(0x00, to);
        }
    }
}