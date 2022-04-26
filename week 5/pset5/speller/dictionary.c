// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1170;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int pos = hash(word);
    node *tmp = table[pos];
    if (tmp == NULL)
    {
        return false;
    }
    while (tmp != NULL)
    {
        if (strcasecmp(tmp -> word, word) == 0)
        {
            return true;
        }
        else
        {
            tmp = tmp -> next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    char first = toupper(word[0]);
    int lexpos = first - 65;
    int len = strlen(word);
    int hashret = 0;
    hashret = (lexpos * LENGTH) + len - 1;
    return hashret;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //first off ensuring everything in the table points to NULL initially for safety things lmao
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    //opening the dictionary file
    FILE *wordy = fopen(dictionary, "r");
    //checking if the dictionary file is null or not
    if (wordy == NULL)
    {
        return false;
    }
    //reading one word at a time from the dictionary and actually loading the words into the dictionary
    char readword[LENGTH + 1];
    while (fscanf(wordy, "%s", readword) != EOF)
    {
        node *n = malloc(sizeof(node));
        unsigned int pos = hash(readword);
        strcpy(n -> word, readword);
        n -> next = table[pos];
        table[pos] = n;
    }
    
    fclose(wordy);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int size = 0;
    node *tmp = NULL;
    for (int i = 0; i < N; i++)
    {
        tmp = table[i];
        while (tmp != NULL)
        {
            size++;
            tmp = tmp -> next;
        }
    }
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *tmp = NULL;
    int big = size();
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        tmp = table[i];
        while (tmp != NULL)
        {
            node *tonext = tmp -> next;
            free(tmp);
            tmp = tonext;
            count++;
        }
    }
    return (count == big);
}
