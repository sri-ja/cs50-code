#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key \n");
        return 1;
    }
    else
    {
        if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters. \n");
            return 1;
        }
        else
        {
            int arr[26];
            for (int i = 0; i < 26; i++)
            {
                arr[i] = 0;
            }
            
            for (int i = 0, n = strlen(argv[1]); i < n; i++)
            {
                if (isalpha(argv[1][i]))
                {
                    char ch = tolower(argv[1][i]);
                    arr[ch - 97]++;
                }
                else
                {
                    printf("Key must contain only alphabets \n");
                    return 1;
                }
            }

            //checking if there are any duplicates
            for (int i = 0; i < 26; i++)
            {
                if (arr[i] > 1)
                {
                    printf("Key must not contain any duplicate alphabets.");
                    return 1;
                }
            }

            //doing the actual conversion if everything else is fine
            string text = get_string("plaintext: ");
            printf("ciphertext: ");
            for (int i = 0, n = strlen(text); i < n; i++)
            {
                if (isalpha(text[i]))
                {
                    if (isupper(text[i]))
                    {
                        text[i] = argv[1][text[i] - 65];
                        text[i] = toupper(text[i]);
                    }
                    else if (islower(text[i]))
                    {
                        text[i] = argv[1][text[i] - 97];
                        text[i] = tolower(text[i]);
                    }
                }
            }
            printf("%s\n", text);
        }
    }
    return 0;
}