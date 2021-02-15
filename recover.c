#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t  BYTE;

void process_file(FILE *file);
int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{

    // Check usage
    if (argc != 2)
    {
        return 1;
    }

    char *f = argv[1];

    // Open file
    FILE *file = fopen(f, "r");
    if (file == NULL)
    {
        printf("Could not open.\n");
        return 1;
    }

    process_file(file);
    free(file);
    fclose(file);

}

void process_file(FILE *file)
{
    FILE *jpeg_file;
    int jpeg_number = 0;

    while (true)
    {

        BYTE block_card[BLOCK_SIZE];
        int read_bytes = fread(&block_card, BLOCK_SIZE, 1, file);
        if (read_bytes != 1)
        {
            break;
        }
        if (block_card[0] == 0xff && block_card[1] == 0xd8 && block_card[2] == 0xff && ((block_card[3] >= 0xe0) && (block_card[3] <= 0xef)))
        {
            if (jpeg_number > 0)
            {
                fclose(jpeg_file);
            }

            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_number);
            jpeg_file = fopen(filename, "w");
            jpeg_number++;

        }

        if (jpeg_number > 0)
        {
            fwrite(block_card, BLOCK_SIZE, 1, jpeg_file);
        }
    }

    if (jpeg_number > 0)
    {
        fclose(jpeg_file);
    }
}