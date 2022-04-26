#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string s);
int count_words(string s);
int count_sent(string s);

int main(void)
{
    string s = get_string("Text: ");
    int letters = count_letters(s);
    int words = count_words(s);
    int sent = count_sent(s);

    float L = (((float)letters) / words) * 100;
    float S = (((float)sent) / words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    int ans = round(index);
    if (ans < 1)
    {
        printf("%s\n", "Before Grade 1");
    }
    else if (ans > 16)
    {
        printf("%s\n", "Grade 16+");
    }
    else
    {
        printf("Grade %i\n", ans);
    }
}

int count_letters(string s)
{
    int n = strlen(s);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(s[i]))
        {
            ans++;
        }
    }

    return ans;
}

int count_words(string s)
{
    int n = strlen(s);
    int ans = 1;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == ' ')
        {
            ans++;
        }
    }

    return ans;
}

int count_sent(string s)
{
    int n = strlen(s);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            ans++;
        }
    }

    return ans;
}