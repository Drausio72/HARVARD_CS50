/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

typedef struct node
{
    char word[LENGTH];
    struct node* next;
}
node;

int dictionarySize = 0;
node* hashtable[100];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{

    char lower[LENGTH + 1];
    
    for(int i = 0; i < strlen(word); i++)
    {   
        if(word[i] == '\'')
        {
            lower[i] = '\'';
        }
        else if(word[i] >= 'A' && word[i] <= 'Z')
        {
            lower[i] = (word[i] - 'A' + 'a');
        }
        else
        {
            lower[i] = word[i];
        }
     }
     
     lower[strlen(word)] = '\0';
        
     int hash = (lower[0] - 'a' + 33)%100;
        
     node* newNode = hashtable[hash];
        
     while(newNode->next != NULL)
     {
        if(strcmp(lower, newNode->word) == 0)
        {
            return true;
        }
        newNode = newNode->next;
     }
        
        
        
  

    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* text = fopen(dictionary, "r");
    
    if(text == NULL)
    {
        printf("Error loading dictionary!\n");
        return 1;
    }
    
    for(int n = 0; n < 100; n++)
    {
        hashtable[n] = malloc(sizeof(node));
        hashtable[n]->next = NULL;
    }
    
    char keyword[LENGTH];
    int c;
    int hash;
    int j = 0;
    
    while((c = fgetc(text)) != EOF)
    {
        if(c == '\n')
        {   
            keyword[j] = '\0';
            j = 0;
            
        hash = (keyword[0] - 'a' + 33)%100;
    
        node *cursor = hashtable[hash];
        
        while(cursor->next != NULL)
        {
            if(strcmp(keyword, cursor->word) == 0)
            {
                continue;
            }
            cursor = cursor->next;
        }
        
        node *newNode = malloc(sizeof(node));
        strcpy(newNode->word, keyword);
        newNode->next = hashtable[hash];
        hashtable[hash] = newNode;
        dictionarySize++;
    
        }
        else
        {   
            if(c == '\'')
            {
                keyword[j] = '\'';
            }
            else if(c >= 'A' && c <= 'Z')
            {
                keyword[j] = ((char)c - 'A' + 'a');
            }
            else
            {
                keyword[j] = (char)c;
            }
            j++;
        }
    }
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictionarySize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    node* newNode;
    node* before;
    int hash = 0;
    
    while(hash < 100)
    {
        newNode = hashtable[hash];
        
        while(newNode->next != NULL)
        {
            before = newNode;
            neode = newNode->next;
            before = NULL;
        }
        hash++;
    }
    return true;
}
