#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage ./recover image\n");
        return 1;
    }

    FILE *source = fopen(argv[1], "r");

    if (source == NULL)
    {
        printf("The image file couldn't be opened\n");
        return 1;
    }

    int counter = -1;
    FILE *destination;
    char filename[sizeof(BYTE)];

    BYTE fat[512];
    while (fread(&fat, sizeof(BYTE), 512, source))
    {
        if (fat[0] == 0xff && fat[1] == 0xd8 && fat[2] == 0xff && (fat[3] & 0xf0) == 0xe0)
        {
            if (counter != -1)
            {
                fclose(destination);
            }

            counter++;
            sprintf(filename, "%03i.jpg", counter);
            destination = fopen(filename, "w");
            if (destination == NULL)
            {
                return 1;
            }

            fwrite(&fat, sizeof(BYTE), 512, destination);
        }
        else if (counter != -1)
        {
            fwrite(&fat, sizeof(BYTE), 512, destination);
        }
    }

    fclose(source);
    return 0;
}


