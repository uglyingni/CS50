#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    // Check for invalid file
    if (!file)
    {
        return 1;
    }

    char filename[8];
    BYTE buffer[512];
    FILE *image = NULL;
    int counter = 0;

    while (fread(buffer, 1, 512, file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", counter);
            image = fopen(filename, "w");
            fwrite(buffer, 1, 512, image);
            fclose(image);
            counter++;
        }
        else
        {
            if (counter > 0)
            {
                image = fopen(filename, "a");
                fwrite(buffer, 512, 1, image);
                fclose(image);
            }
        }
    }
    fclose(file);
    return 0;
}