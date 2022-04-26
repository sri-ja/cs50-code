#include <cs50.h>
#include <stdio.h>

int checksum(long n);
int number_of_digits(long n);

int main(void)
{
    long card = get_long("Number: "); //taking the card number from user
    int digits = number_of_digits(card); //calculating the number of digits
    int validity = checksum(card); //checking if it's valid
    if (validity == 1)
    {
        if (digits == 15) //checking if it's an american express card
        {
            int start = card / 10000000000000;
            if (start == 34 || start == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (digits == 13) //checking if it's a visa card
        {
            int start = card / 1000000000000;
            if (start == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (digits == 16)
        {
            int start = card / 100000000000000;
            if (start == 51 || start == 52 || start == 53 || start == 54 || start == 55) //checking if it's a mastercard
            {
                printf("MASTERCARD\n");
            }
            else
            {
                start = card / 1000000000000000;
                if (start == 4) //checking if it's a visa card
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int checksum(long n) //checking if it's a valid card number
{
    int sum = 0;
    int checker = 0;
    while (n > 0)
    {
        int dig = n % 10; //extracting digits from the end
        if (checker == 0)
        {
            sum = sum + dig;
            checker = 1;
        }
        else
        {
            dig = dig * 2; //finding the product of every second number from the end
            while (dig > 0) //adding the digits of the product to the sum variable
            {
                sum = sum + (dig % 10);
                dig = dig / 10;
            }
            checker = 0;
        }
        n = n / 10;
    }
    if (sum % 10 == 0)
    {
        return 1; //true if it's a valid card number
    }
    else
    {
        return 0; //false if it's not a valid card number
    }
}

int number_of_digits(long n) //finding the number of digits
{
    int num = 0;
    while (n > 0)
    {
        num++;
        n = n / 10;
    }
    return num;
}