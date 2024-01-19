//----------DOUBLY LINKED LIST----------
//This lists have nodes with two links(pointers) to other nodes,
// the next node, like single linked list, and the previous node
#ifndef DOUBLY_LINKED_H
#define DOUBLY_LINKED_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  doubly_linked_list_int_node
{
    struct doubly_linked_list_int_node* next;
    struct doubly_linked_list_int_node* previous;
    int value;
    unsigned int count; //it goes updated with number of elements into the list if this is the head node

}IntDoublyNode;

IntDoublyNode* GetTail(IntDoublyNode* head);
void Append(IntDoublyNode **head, int valueToAppend);
void InsertAfter(IntDoublyNode **head, int valueWhereInsert, int valueToInsert);
void InsertBefore(IntDoublyNode **head, int valueWhereInsert, int valueToInsert);
unsigned int Length(IntDoublyNode* head);
IntDoublyNode* PopList(IntDoublyNode** head);
void RemoveAt(IntDoublyNode** head, unsigned int index);
void Remove(IntDoublyNode** head, int valueToRemove);
IntDoublyNode* SplitList(IntDoublyNode* head);
void MixLists(IntDoublyNode* first_head, IntDoublyNode* second_head);
void Shuffle(IntDoublyNode** head);

#endif