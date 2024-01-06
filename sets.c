#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------SETS----------
//A set is a list of unique keys (strings)
//They are based on Hashing algorithms that allows to manipulate data sequence
// to return a single value, but not viceversa.
//This algorithms are effected by the collision issue, 
//it means that different values could return the same value

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

Set* Create_new_set(const size_t hashmap_size) //Here hashmap size is const because don't change into this function 
                                               //but the hashmap size var of set could change 
{
    Set* set_table = malloc(sizeof(Set)); //create an heap for the new set
    if(!set_table)
    { //if malloc not be able to allocate struct in a heap or create it 
        return NULL;
    }
    set_table -> hashmap_size = hashmap_size;
    set_table -> hashmap_nodes = calloc(set_table -> hashmap_size, sizeof(StringNode*)); //Fill set nodes with a SetStringNode[hashmap_size] sets as NULL  
    if(!set_table -> hashmap_nodes)
    { //if calloc failed 
        free(set_table);
        return NULL;
    }
    return set_table;
}
size_t djb33xHash (const char* key, const size_t key_length)
{
    size_t hash = 5381; //Brutal value that guaranteed fewer collisions
    for (size_t i = 0; i < key_length; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    
    return hash;
}

FoundedNode Search(Set* table, const char* key)
{
    const size_t key_length = strlen(key);
    const size_t hash = djb33xHash(key, key_length);
    const size_t index = hash % table -> hashmap_size; //return a value from hash between 0 to hashmap_size;

    StringNode* currentNode = table -> hashmap_nodes[index];
    FoundedNode founded_node;
    founded_node.index = index;
    while (currentNode)
    {
        if(currentNode -> key_len > 0)
        {
            if((currentNode -> key_len == key_length) && !memcmp(currentNode -> key, key, key_length))
            {
                printf("Found %s at index %llu\n", key, index);
                founded_node.node_found = currentNode;
                return founded_node;
            }
        }
        currentNode = currentNode -> next;
    }

    founded_node.node_found = NULL;
    printf("String not found\n");
    return founded_node;
}

StringNode* Insert(Set* table, const char* key)
{
    FoundedNode NodeFound = Search(table, key);
    if(NodeFound.node_found)
    {
        printf("Key already exist\n");
        return NULL;
    }
    const size_t index = NodeFound.index; 
    if(!table -> hashmap_nodes[index])
    { //if there's not a node at this index
        table -> hashmap_nodes[index] = malloc(sizeof(StringNode));
        if(!table -> hashmap_nodes[index])
        {
            printf("ERROR: Node could not created!\n");
            return NULL;
        }
        table -> hashmap_nodes[index] -> key = key;
        table -> hashmap_nodes[index] -> key_len = strlen(key);
        table -> hashmap_nodes[index] -> next = NULL;

        printf("Node %zu created\n", index);
        printf("Value: %s\n", table -> hashmap_nodes[index] -> key);
        return table -> hashmap_nodes[index];
    }

    printf("COLLISION!\n");
    StringNode* new_item = malloc(sizeof(StringNode));
    if(!new_item)
    {
        printf("ERROR: Node could not appended!\n");
        return NULL;
    }
    new_item -> key = key;
    new_item -> key_len = strlen(key);
    new_item -> next = NULL;

    StringNode* head = table -> hashmap_nodes[index];
    StringNode* tail = head;
    while (head)
    {
        tail = head;
        head = head -> next;
    }
    tail -> next = new_item;
    
    printf("Node append at %zu list\n", index);
    printf("Value: %s\n", new_item -> key);
    return new_item;    
}

void Remove(Set* table, const char* key)
{
    FoundedNode NodeFound = Search(table, key);
    if(!NodeFound.node_found)
    {
        return;
    }
    const size_t index = NodeFound.index;
    if(!table -> hashmap_nodes[index] -> next)
    { //if linked list has only the head, item to remove is the head
        printf("Remove %s\n", table -> hashmap_nodes[index] -> key);
        free(table -> hashmap_nodes[index]);
    }
    else if(NodeFound.node_found == table -> hashmap_nodes[index])
    {//if linked list has more items, but item to remove is the head, it's next become the new head
        StringNode* current_head = table -> hashmap_nodes[index];
        table -> hashmap_nodes[index] = table -> hashmap_nodes[index] -> next;
        free(current_head);
    }
    else
    {
        StringNode* current_node = table -> hashmap_nodes[index];
        while (current_node -> next != NodeFound.node_found)
        {
            printf("%s\n", current_node -> key);
            current_node = current_node -> next;
        }
        StringNode* after_node_to_remove = NodeFound.node_found -> next;
        current_node -> next = after_node_to_remove;
        printf("Remove %s\n", NodeFound.node_found -> key);
        free(NodeFound.node_found);
    }
}

int main(int argc, char **argv)
{
    Set* new_set = Create_new_set(3);
    Insert(new_set, "Hello");
    printf("----------\n");
    Insert(new_set, "Hello");
    printf("----------\n");
    Insert(new_set, "GoodMorning");
    printf("----------\n");
    Insert(new_set, "GoodNight");
    printf("----------\n");
    Remove(new_set, "GoodNight");
    printf("----------\n");
    Insert(new_set, "GoodJob");
    printf("----------\n");
    FoundedNode found_node = Search(new_set, "GoodMorning");
    printf("Next: %s\n", found_node.node_found -> next -> key);



    return 0;
}
