#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

void write_random_lines(FILE* fp, int line_count, int min_len, int max_len) // create a text file filled with random alphabetic characters 
{
    srand((unsigned int)time(NULL));

    for (int i = 0; i < line_count; ++i)
    {
        const int n = rand() % (max_len - min_len + 1) + min_len;
        for (int j = 0; j < n; ++j)
        {
            fputc(rand() % 26 + 'A', fp);
        }
        fputc('\n', fp);
    }
}

// prog.exe filename chunk
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "<prog.exe> <filename> <chunk>\n");
        return 1;
    }

    //FILE* fs = fopen("Demo.txt", "wb"); 
    //write_random_lines(fs, 100, 40, 50);

    FILE* fs = fopen(argv[1], "rb");

    if (!fs)
    {
        fprintf(stderr, "file cannot be opened\n");
        return 2;
    }
    
    int chunk = atoi(argv[2]);
    char dest_file_name[SIZE];
    int file_count = 0;
    int byte_count = 0;
    char c;

    FILE* fd = NULL;

    while ((c = fgetc(fs)) != EOF)
    {
        if (!fd)
        {
            sprintf(dest_file_name, "partition%03d.por", file_count + 1);
            fd = fopen(dest_file_name, "wb");
            if (!fd)
            {
                fprintf(stderr, "file cannot be opened\n");
                return 3;
            }
            ++file_count;
        }

        fputc(c, fd);
        ++byte_count;

        if (byte_count % chunk == 0)
        {
            fclose(fd);
            fd = NULL;
        }
    }

    fclose(fs);

    if (!fd)
        fclose(fd);

    printf("%s file of size %d byte(s) is partitioned into %d files each of max size %d bytes\n", argv[1], byte_count, file_count, chunk);
}

