#ifndef LINKED_H
#define LINKED_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct int_node
{
    struct int_node* next;
    int value;
    unsigned int count;

}IntNode;

IntNode* GetTail(IntNode* head);
void Append(IntNode **head, const int valueToAppend);
unsigned int Length(IntNode* head);
IntNode* PopList(IntNode** head);
void RemoveAt(IntNode** head, const unsigned int index);
void Remove(IntNode** head, const int valueToRemove);
void Reverse(IntNode** head);
void FreeNodes(IntNode** head);

#endif