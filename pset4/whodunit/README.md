# Questions

## What's `stdint.h`?

*stdint.h is a header file that contains the definitions of exact-width integer types such as*
*int32_t and uint64_t which allows programmers to work with integers in a machine-independent manner*

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

*Using these data types ensures that a programmer gets integers of an exact number of bits that he has declared*
*without having to worry about how the particular system on which the program is being compiled defines integers*

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

**1** *byte*, **4** *bytes*, **4** *bytes, and* **2** *bytes respectively*.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

*The first two bytes of any BMP file in ASCII must be* **BM**

## What's the difference between `bfSize` and `biSize`?

*bfSize refers to the* **size (in bytes) of the whole bitmap file**
*biSize refers to the* **size (in bytes) of the BITMAPINFOHEADER structure**

## What does it mean if `biHeight` is negative?

*It means that the bitmap pixel data is arranged from the* **top down with its origin at the upper-left corner**

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

*The* **biBitCount field** *specifies the BMP's color depth*

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

*fopen might return NULL if the file to be read doesn't exist,*
*is corrupted, or if the user doesn't have permission to open it*

## Why is the third argument to `fread` always `1` in our code?

*The argument is always 1 because only one unit of information, which is of the size*
*(in bytes) of the structure the user intends to read from or write to, is needed*

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

*It assigns a value of* **3**

## What does `fseek` do?

*fseek arbitrarily moves the file pointer around the file so that information can be*
*written to or read from locations within the file that would normally not be pointed*
*to using sequencial access*

## What is `SEEK_CUR`?

*This is an argument in the fseek() function that instructs the function to position*
*the file pointer for reading or writing information at its current position in the file*