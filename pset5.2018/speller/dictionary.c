// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

/******************************************************************************
 * CHECK()
 *
 * Returns true if word is in dictionary else false
 */
bool check(const char *word)
{
    // Creates traversal pointer, starting from root node
    node *trav = root;
    short i = 0;
    char c; // Variable to store each character

    // Iterates through each prefix of the trie that matches the word
    while ((c = tolower(word[i])) != '\0')
    {
        if (c != '\'')
        {
            // Returns false if child node is null
            if (trav->children[c - CASE] == NULL)
            {
                return false;
            }

            // Traverses to next node prefix if not null
            else
            {
                trav = trav->children[c - CASE];
                i++;
            }
        }

        // Executes if character is an apostrophe
        else if (c == '\'')
        {
            // Returns false if child node is null
            if (trav->children[MAX - 1] == NULL)
            {
                return false;
            }

            // Traverses to next node prefix if not null
            else
            {
                trav = trav->children[MAX - 1];
                i++;
            }
        }
    }

    return trav->is_word;
}

/******************************************************************************
 * LOAD()
 *
 * Loads dictionary into memory, returning true if successful else false
 */
bool load(const char *dictionary)
{
    // Creates the root node
    root = create();

    // Opens dictionary file for reading
    fptr = fopen(dictionary, "r");
    if (!fptr)
    {
        fprintf(stderr, "Cannot open dictionary\n");
        return false;
    }

    // Creates a traversal pointer, points it to start of trie
    node *trav = root;
    char c;

    // Iterates through every character in the dictionary
    while ((c = fgetc(fptr)) != EOF)
    {
        if (c != '\n')
        {
            if (c != '\'')
            {
                if (trav->children[c - CASE] == NULL)
                {
                    trav->children[c - CASE] = create();
                    trav = trav->children[c - CASE];
                }

                else
                {
                    trav = trav->children[c - CASE];
                }
            }

            else if (c == '\'')
            {
                if (trav->children[MAX - 1] == NULL)
                {
                    trav->children[MAX - 1] = create();
                    trav = trav->children[MAX - 1];
                }

                else
                {
                    trav = trav->children[MAX - 1];
                }
            }
        }

        else
        {
            trav->is_word = true;
            count++;
            trav = root;
        }
    }

    return true;
}

/******************************************************************************
 * CREATE()
 *
 * Creates a new node
 */
node *create(void)
{
    node *n = (node *)malloc(sizeof(node));
    if (!n)
    {
        fprintf(stderr, "Insufficient memory\n");
        exit(1);
    }

    // Initializes every element to avoid a memory leak
    for (short i = 0; i < MAX; i++)
    {
        n->children[i] = NULL;
        n->is_word = false;
    }

    return n;
}

/******************************************************************************
 * SIZE()
 *
 * Returns number of words in dictionary if loaded else 0 if not yet loaded
 */
unsigned int size(void)
{
    return count;
}

/******************************************************************************
 * UNLOAD()
 *
 * Unloads dictionary from memory, returning true if successful else false
 */
bool unload(void)
{
    // Frees memory alloted to the try
    if (root != NULL)
    {
        deallocate(root);
    }

    // Closes the dictionary file
    fclose(fptr);

    return true;
}

/******************************************************************************
 * DEALLOCATE()
 *
 * Deallocates memory alloted to every node in the trie
 */
void deallocate(node *letter)
{
    for (short i = 0; i < MAX; i++)
    {
        if (letter->children[i] != NULL)
        {
            deallocate(letter->children[i]);
        }
    }

    free(letter);
}
