#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // User must pass in exactly 1 command line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    FILE *img = NULL;

    // Buffer to store the bytes of a block
    BYTE buffer[512];

    // To store the filenames
    char filename[8];

    // Counter for naming each file
    int counter = 0;

    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        // checks if start of img in buffer, a new block
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if start of a new img and first image, wehre counter is 0
            // then write a new image
            if (counter == 0)
            {
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), 512, img);
                counter += 1;
            }

            // From the second image on, if its a new image,
            // closes the last image and writes new image
            else if (counter > 0)
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), 512, img);
                counter += 1;
            }
        }
        // If not yet a new image
        // keep writing the image
        else if (counter > 0)
        {
            fwrite(&buffer, sizeof(BYTE), 512, img);
        }

    }

    // Close file
    fclose(file);
    fclose(img);
}