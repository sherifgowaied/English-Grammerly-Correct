// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
int numberofwords ;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //make a copy for word in lowercase letter
    int s = strlen(word) ;
    char tmpstring[strlen(word) + 1] ;
    //copying over string lenght of the world
    for (int i = 0 ; i < s ; i++)
    {
        tmpstring[i] =  tolower(word[i]) ;
        
    }
    //get the hashindex from the copy
    int indexoftext = hash(tmpstring) ;
    // check the word if it in the dictonary or not

    for (node *tmp = table[indexoftext] ; tmp != NULL ; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true ;

        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // the frist letter of word - ascii to get her index in hash table
    int index = word[0] - 97 ;
    return index ;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    numberofwords = 0 ;
    // open dictornary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fclose(file);
        return false ;
    }
    //read every string in the file
    //open new node word
    char word1[LENGTH + 1] ;
    while (fscanf(file, " %s ", word1) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false ;
        }
        //copy each word in dictonary to the tmp node
        strcpy(n->word, word1);
        //index every tmp node in hash tabe due her index
        n->next = NULL ;
        int index = hash(word1) ;
        n->next = table[index] ;
        table[index] = n ;
        // counting number of word in directornary
        numberofwords++ ;

    }
    fclose(file); 
    return true ;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // dictionary size counter
    int counter = 0;

    // iterate through hashtable
    for (int i = 0; i < N ; i++)
    {
        // set pointer to head of list
        node *cursor = table[i];

        // traverse list
        while (cursor != NULL)
        {
            counter++;
            cursor = cursor->next;
        }
    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // free the malloc of the hash table from every table[n] and throw every linked list
    for (int i = 0 ; i < N  ; i++)
    {
        node *cursor = table[i] ;
        while (cursor != NULL)
        {
            node *tmp = cursor ;
            cursor = cursor->next ;
            free(tmp) ;
        }

    }

    return true;
}
