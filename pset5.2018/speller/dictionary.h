// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Max number of valid characters.
#define MAX 27

// Needed to calculate node subscript
#define CASE 'a'

// Keeps track of dictionary word count
unsigned int count;

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

// File pointer to point to the dictionary file
FILE *fptr;

// Struct definition
typedef struct node
{
    bool is_word;
    struct node *children[MAX];
}
node;

// Variable to store pointer to the start of the trie
node *root;

// Creates a new node
node *create(void);

// Frees each node in a trie recursively
void deallocate(node *letter);

#endif // DICTIONARY_H
