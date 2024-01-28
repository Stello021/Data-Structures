//----------SETS----------
//A set is a list of unique keys (strings)
//They are based on Hashing algorithms that allows to manipulate data sequence
// to return a single value, but not viceversa.
//This algorithms are effected by the collision issue, 
//it means that different values could return the same value

#ifndef SETS_H
#define SETS_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string_node
{
    struct string_node* next;
    const char* key;
    size_t key_len;

}StringNode;
typedef struct founded_node
{
    StringNode* node_found;
    size_t index;
}FoundedNode;

typedef struct set
{
    StringNode** hashmap_nodes; //Nuber of linked lists, one for every hash code returnable
    size_t hashmap_size; //Hash code returnable (from 0 to hasmap_size), number of nodes, number of linked lists
}Set;

Set* Create_new_set(const size_t hashmap_size);
size_t djb33xHash (const char* key, const size_t key_length);
FoundedNode Search(const Set* table, const char* key);
StringNode* Insert(const Set* table, const char* key);
void Remove(const Set* table, const char* key);

#endif