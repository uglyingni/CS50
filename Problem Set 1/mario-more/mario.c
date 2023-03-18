#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_bricks(int height);
int main(void)
{
    int n = get_height();
    print_bricks(n);
}

int get_height(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}

void print_bricks(int height)
{
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < height; b++)
        {
            if ((a + b + 1) < height)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("  ");
        for (int b = 0; b < height; b++)
        {
            if (a >= b)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}