#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    for (int i = 0; i < height; i++)
    {
        for (int j = i + 1; j < height; j++) //printing the upside-down triangle of spaces
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++) //printing the left triangle
        {
            printf("#");
        }
        printf("  ");//printing the spaces in between or the gap
        for (int j = 0; j <= i; j++) //printing the right triangle
        {
            printf("#");
        }
        printf("\n");
    }
}