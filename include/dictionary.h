//----------DICTIONARY----------
//A dictionary is a set, where there are unique keys associate to a value of any type

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string_node
{
    struct string_node* next;
    const char* key;
    int value;
    size_t key_len;

}StringIntNode;

typedef struct founded_node
{
    StringIntNode* node_found;
    size_t index;
}FoundedNode;

typedef struct dictionary
{
    StringIntNode** hashmap_nodes; //Nuber of linked lists, one for every hash code returnable
    size_t hashmap_size; //Hash code returnable (from 0 to hasmap_size), number of nodes, number of linked lists
    unsigned int collision_count;
    unsigned int pressure;
}Dictionary;

Dictionary* Create_new_dictionary(const size_t hashmap_size, const unsigned int max_collision);
size_t djb33xHash (const char* key, const size_t key_length);
FoundedNode Search( const Dictionary* table, const char* key);
StringIntNode* Insert(Dictionary** table, const char* key, const int value);
void Rehash(Dictionary** table);
void Remove(Dictionary* table, const char* key);


#endif