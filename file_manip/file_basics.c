#define _CRT_SECURE_NO_WARNINGS

/*
   ATTENTION: WINDOWS OS diverges in two points from UNIX based OS in text file read/write operations:

1) In WINDOWS, if a file is opened in text mode which default of fopen function, it will be read from and written to new line character('\n')
as two bytes (13 10) but actually showing it as one byte (10). In binary mode it will be read from and written to as one byte(10). Write a file
in text mode with new line characters and read in binary and text mode in order to see the difference.

2) In WINDOWS, since text files are marked with Ctrl+Z(control character) at the end which corresponds to 26 in ASCII, when reading from a file
in text mode, if the file contains 26 value in any byte, program stops reading considering it is EOF. Put 26(putch(26)) in any place of a file
and read it in text mode in order to see it.

 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void write_random_lines(FILE* fp, int line_count, int min_len, int max_len)
{
    srand(time(NULL));

    for (int i = 0; i < line_count; ++i)
    {
        const int n = rand() % (max_len - min_len + 1) + min_len;
        for (int j = 0 ; j < n; ++j)
        {
            fputc(rand() % 26 + 'A', fp);
        }
        fputc('\n', fp);
    }
}

void print_file(FILE* fp)
{
    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        putchar(c);
        //_getch();
    }
}

void copy_file(FILE* dst, FILE* src) // Open both files in binary mode first in caller funciton
{
    int c;
    int byte_count = 0;
    while ((c = fgetc(src)) != EOF)
    {
        fputc(c, dst);
        ++byte_count;
    }
    
    printf("%d byte(s) copied from source file to destination file\n", byte_count);
}

void print_file_bytes(FILE* fp)
{
    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        printf("%d ", c);
        //_getch();
    }
}

int main(int argc, char *argv[])
{
    FILE* src = fopen("a.txt", "rb");

    if (!src)
    {
        fprintf(stderr, "file cannot be opened\n");
        return 1;
    }

    FILE* dst = fopen("b.txt", "wb");

    if (!dst)
    {
        fprintf(stderr, "file cannot be created\n");
        return 2;
    }

    copy_file(dst, src);
        
    fclose(src);
    fclose(dst);
}

