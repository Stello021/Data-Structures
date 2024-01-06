#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct int_node
{
    struct int_node* next;
    int value;
    unsigned int count;

}IntNode;

IntNode* GetTail(IntNode* head)
{
    if(!head)
    {
        return NULL;
    }
    IntNode* current_node = head;
    IntNode* last_node = head;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node -> next;
    }
    return last_node;
    

}

void Append(IntNode **head, int valueToAppend)
{
    IntNode* new_node = malloc(sizeof(IntNode*));
    if(!new_node)
    {
        return;
    }
    new_node -> next = NULL; //New node become the List's tail
    new_node -> value = valueToAppend;
    if(!*head)
    { 

        *head = new_node;
        (*head) -> count = 1;
        return;
    }
     IntNode* tail = GetTail(*head);
     tail -> next = new_node;
     (*head) -> count++;
}
unsigned int Length(IntNode* head)
{
    return head -> count;
}
IntNode* PopList(IntNode** head)
{
    if(!*head)
    {
        return NULL;
    }

    IntNode* nodeToRemove = *head;
    const unsigned int current_count = nodeToRemove -> count;
    *head = (*head) -> next;
    if(*head)
    {
        (*head) -> count = current_count - 1;
    }

    nodeToRemove -> next = NULL;
    return nodeToRemove;

}

void RemoveAt(IntNode** head, unsigned int index)
{
    if(!*head)
    {
        return;
    }

    if(index < 1)
    {
        free(PopList(head));
        return;
    }

    IntNode* nodeToRemove = *head;
    IntNode* previous_node = *head;
    for (unsigned int i = 0; i < index; i++)
    {
        if(i == index - 1)
        {
            previous_node = nodeToRemove;
        }
        nodeToRemove = nodeToRemove -> next; 
    }
    previous_node -> next = nodeToRemove -> next;
    if(*head)
    {
        (*head) -> count --;
    }

    free(nodeToRemove);   
}

void Remove(IntNode** head, int valueToRemove)
{
    if(!*head)
    {
        return;
    }

    if((*head) -> value == valueToRemove)
    {
        free(PopList(head));
        return;
    }

    IntNode* nodeToRemove = *head;
    IntNode* previous_node = *head;
    while(nodeToRemove)
    {
        IntNode* auxiliary_node = nodeToRemove;
        nodeToRemove = nodeToRemove -> next;
        if(nodeToRemove -> value == valueToRemove)
        {
            previous_node = auxiliary_node;
            break;
        }
        if(nodeToRemove -> next == NULL)
        {
            printf("Node not found!\n");
            return;
        }
    }
    previous_node -> next = nodeToRemove -> next;
    if(*head)
    {
        (*head) -> count --;
    }

    free(nodeToRemove);   
}

void Reverse(IntNode** head)
{
    IntNode* previous_node = NULL;
    IntNode* current = *head;
    unsigned int current_count = (*head) -> count;
    while (current)
    {
        IntNode* next_node = current -> next;
        current-> next = previous_node;
        previous_node = current;
        current = next_node;
    }
    *head = previous_node;
    (*head) -> count = current_count;
}
void FreeNodes(IntNode** head)
{
    IntNode* current_node = *head;
    while(current_node)
    {
        IntNode* auxiliary_node = current_node;
        current_node = current_node -> next;
        free(auxiliary_node);
    }
    *head = NULL; //Linked list is now empty
}
int main(int argc, char** argv)
{ 
    IntNode* head = NULL;
    Append(&head, 15);
    Append(&head, 16);
    Append(&head, 17);
    Append(&head, 18);
    Append(&head, 19);
    Append(&head, 20);
    printf("APPEND!\n");
    int i = 0;
    for(IntNode* current = head; current != NULL; current = current -> next)
    {
        printf("%d*: %d", ++i, current -> value);
        if(current -> next != NULL)   printf(" -> %d\n", current -> next -> value);
        else 
        printf("\n");
    }
    printf("Length: %x\n", Length(head));

    printf("POP!\n");
    free(PopList(&head));

    i = 0;
    for(IntNode* current = head; current != NULL; current = current -> next)
    {
        printf("%d*: %d", ++i, current -> value);
        if(current -> next != NULL)   printf(" -> %d\n", current -> next -> value);
        else 
        printf("\n");
    }
    printf("Length: %x\n", Length(head));

    printf("REMOVEAT!\n");
    RemoveAt(&head, 3);

    i = 0;
    for(IntNode* current = head; current != NULL; current = current -> next)
    {
        printf("%d*: %d", ++i, current -> value);
        if(current -> next != NULL)   printf(" -> %d\n", current -> next -> value);
        else 
        printf("\n");
    }
    printf("Length: %x\n", Length(head));

    printf("REMOVE!\n");
    Remove(&head, 18);

    i = 0;
    for(IntNode* current = head; current != NULL; current = current -> next)
    {
        printf("%d*: %d", ++i, current -> value);
        if(current -> next != NULL)   printf(" -> %d\n", current -> next -> value);
        else 
        printf("\n");
    }
    printf("Length: %x\n", Length(head));

    printf("REVERSE!\n");
    Reverse(&head);

    i = 0;
    for(IntNode* current = head; current != NULL; current = current -> next)
    {
        printf("%d*: %d", ++i, current -> value);
        if(current -> next != NULL)   printf(" -> %d\n", current -> next -> value);
        else 
        printf("\n");
    }
    printf("Length: %x\n", Length(head));


    FreeNodes(&head);
    return 0;
}



