#include <cs50.h>
#include <stdio.h>

int main(void)
{   int height;
    do
    {
        height = get_int("Height: ");
    }
    while(height <  1 || height > 8);

    for(int row = 0; row< height; row++)
    {
        for(int space = height - row - 1; space > 0; space--)
        {
            printf(" ");
        }
        for(int k = 0; k < row + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }

}