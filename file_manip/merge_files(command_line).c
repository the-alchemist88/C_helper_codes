#define _CRT_SECURE_NO_WARNINGS

#define SIZE 100

#include <stdio.h>

// usage: <prog.exe> <filename>
int main(int argc, char* argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "<prog.exe> <filename>\n");
        return 1;
    }

    FILE* fd = fopen(argv[1], "wb");
    if (!fd)
    {
        fprintf(stderr, "file to write cannot be opened\n");
        return 2;
    }

    int byte_count = 0;
    int file_count = 0;
    char c;
    char file_name[SIZE];

    while (1)
    {
        sprintf(file_name, "partition%03d.por", file_count + 1);
        FILE* fs = fopen(file_name, "rb");
        if (!fs)
        {
            printf("file to read from has finished\n");
            break;
        }

        ++file_count;

        while ((c = fgetc(fs)) != EOF)
        {
            fputc(c, fd);
            ++byte_count;
        }
        
        fclose(fs);
    }

    for (int i = 0; i < file_count; ++i) // optional, in order to remove the partition files
    {
        sprintf(file_name, "partition%03d.por", file_count + 1);
        if (remove(file_name))
        {
            fprintf(stderr, "%s couldn't be removed\n", file_name);
            return 3;
        }
        ++file_count;
    }

    fclose(fd);

    printf("%d files merged into %s file, total %d bytes\n", file_count, argv[1], byte_count);
}

