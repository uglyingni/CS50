#include <cs50.h>
#include <math.h>
#include <stdio.h>

const int len = 15; //16-1 最多16-digit
long get_number(void);
int checksum(long card);
void print_status(int sum, long n);
int main(void)
{
    long n = get_number();
    int sum = checksum(n);
    print_status(sum, n);
}

long get_number(void)
{
    long card;
    do
    {
        card = get_long("Number: ");
    }
    while (card < 0);
    return card;
}

int checksum(long card)
{
    int n;
    int sum = 0;
    for (int i = len; i >= 0; i--)
    {
        if (i % 2 != 0)
        {
            n = (int)(card / pow(10, i)) * 2;
            if (n >= 10)
            {
                sum += n % 10 + 1;
            }
            else
            {
                sum += n;
            }
            card -= n / 2 * pow(10, i);
        }
        else
        {
            n = (int)(card / pow(10, i));
            sum += n;
            card -= n * pow(10, i);
        }
    }
    return sum;
}

void print_status(int sum, long n)
{
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if ((int)(n / pow(10, 13)) == 34 || (int)(n / pow(10, 13)) == 37)
    {
        printf("AMEX\n");
    }
    else if ((int)(n / pow(10, 14)) >= 51 && (int)(n / pow(10, 14)) <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if ((int)(n / pow(10, 15)) == 4 || (int)(n / pow(10, 12)) == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}