#include <dictionary.h>

Dictionary* Create_new_dictionary(const size_t hashmap_size, const unsigned int max_collision) //Here hashmap size is const because don't change into this function 
                                               //but the hashmap size var of set could change 
{
    Dictionary* set_table = malloc(sizeof(Dictionary)); //create an heap for the new set
    if(!set_table)
    { //if malloc not be able to allocate struct in a heap or create it 
        return NULL;
    }
    set_table -> hashmap_size = hashmap_size;
    set_table -> collision_count = 0;
    set_table -> pressure = max_collision;
    set_table -> hashmap_nodes = calloc(set_table -> hashmap_size, sizeof(StringIntNode*)); //Fill set nodes with a DictionaryStringIntNode[hashmap_size] sets as NULL  
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

FoundedNode Search(Dictionary* table, const char* key)
{
    const size_t key_length = strlen(key);
    const size_t hash = djb33xHash(key, key_length);
    const size_t index = hash % table -> hashmap_size; //return a value from hash between 0 to hashmap_size;

    StringIntNode* currentNode = table -> hashmap_nodes[index];
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

void Rehash(Dictionary** table)
{
    Dictionary* resized_table = Create_new_dictionary(((*table) -> hashmap_size) * 2, (*table) -> pressure);
    for (size_t i = 0; i < (*table) -> hashmap_size; i++)
    {
        StringIntNode* current_node = (*table) -> hashmap_nodes[i];
        while (current_node)
        {
            Insert(&resized_table, current_node -> key, current_node -> value);
            current_node = current_node -> next;
        }       
    }
    Dictionary* current_dict = *table;
    *table = resized_table;
    free(current_dict);
    printf("REHASHING COMPLETE!\n");
    return;
    
}

StringIntNode* Insert(Dictionary** table, const char* key, const int value)
{
    FoundedNode NodeFound = Search((*table), key);
    if(NodeFound.node_found)
    {
        printf("Key already exist\n");
        return NULL;
    }
    const size_t index = NodeFound.index; 
    if(!(*table) -> hashmap_nodes[index])
    { //if there's not a node at this index
        (*table) -> hashmap_nodes[index] = malloc(sizeof(StringIntNode));
        if(!(*table) -> hashmap_nodes[index])
        {
            printf("ERROR: Node could not created!\n");
            return NULL;
        }
        (*table) -> hashmap_nodes[index] -> key = key;
        (*table) -> hashmap_nodes[index] -> key_len = strlen(key);
        (*table) -> hashmap_nodes[index] -> value = value;
        (*table) -> hashmap_nodes[index] -> next = NULL;

        printf("Node %zu created\n", index);
        printf("Value: %s\n", (*table) -> hashmap_nodes[index] -> key);
        return (*table) -> hashmap_nodes[index];
    }

    printf("COLLISION!\n");
    StringIntNode* new_item = malloc(sizeof(StringIntNode));
    if(!new_item)
    {
        printf("ERROR: Node could not appended!\n");
        return NULL;
    }
    (*table) -> collision_count++;
    new_item -> key = key;
    new_item -> key_len = strlen(key);
    new_item -> value = value;
    new_item -> next = NULL;

    StringIntNode* head = (*table) -> hashmap_nodes[index];
    StringIntNode* tail = head;
    while (head)
    {
        tail = head;
        head = head -> next;
    }
    tail -> next = new_item;
    
    printf("Node append at %zu list\n", index);
    printf("Value: %s\n", new_item -> key);
    if((*table) -> collision_count >= (*table) -> pressure)
    {
       printf("REHASHING...\n");
       Rehash(table);
       printf("%zu\n", (*table) -> hashmap_size);
    }
    return new_item; 
   
}

void Remove(Dictionary* table, const char* key)
{
    FoundedNode NodeFound = Search(table, key);
    if(!NodeFound.node_found)
    {
        return;
    }
    const size_t index = NodeFound.index;
    if(!table -> hashmap_nodes[index] -> next)
    {
        printf("Remove %s\n", table -> hashmap_nodes[index] -> key);
        free(table -> hashmap_nodes[index]);
    }
    else if(NodeFound.node_found == table -> hashmap_nodes[index])
    {
        StringIntNode* current_head = table -> hashmap_nodes[index];
        table -> hashmap_nodes[index] = table -> hashmap_nodes[index] -> next;
        free(current_head);
    }
    else
    {
        StringIntNode* current_node = table -> hashmap_nodes[index];
        while (current_node -> next != NodeFound.node_found)
        {
            printf("%s\n", current_node -> key);
            current_node = current_node -> next;
        }
        StringIntNode* after_node_to_remove = NodeFound.node_found -> next;
        current_node -> next = after_node_to_remove;
        printf("Remove %s\n", NodeFound.node_found -> key);
        free(NodeFound.node_found);
        table -> collision_count--;
    }
}

int main(int argc, char **argv)
{
    Dictionary* new_dictionary = Create_new_dictionary(3, 1);
    Insert(&new_dictionary, "Hello", 1);
    printf("----------\n");
    Insert(&new_dictionary, "Hello", 3);
    printf("----------\n");
    Insert(&new_dictionary, "GoodMorning", 5);
    printf("----------\n");
    Insert(&new_dictionary, "GoodNight", 4);
    printf("----------\n");
    Remove(new_dictionary, "GoodNight");
    printf("----------\n");
    Insert(&new_dictionary, "GoodNight", 4);
    printf("----------\n");
    Insert(&new_dictionary, "GoodJob", 5);
    printf("----------\n");
    FoundedNode found_node = Search(new_dictionary, "GoodMorning");
    printf("----------\n");
    printf("%zu\n", new_dictionary -> hashmap_size);
    for (size_t i = 0; i < new_dictionary -> hashmap_size; i++)
    {
        printf("%zu*: ", i + 1);
        StringIntNode* current_node = new_dictionary -> hashmap_nodes[i];
        while (current_node)
        {
            printf("-> Key: %s   Value: %d", current_node -> key, current_node -> value);
            current_node = current_node -> next;
        }  
        printf("\n");     
    }





    return 0;
}
