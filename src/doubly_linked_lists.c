#include <doubly_linked_lists.h>

IntDoublyNode* GetTail(IntDoublyNode* head)
{
    if(!head)
    {
        return NULL;
    }
    IntDoublyNode* current_node = head;
    IntDoublyNode* last_node = head;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node -> next;
    }
    return last_node;
}

void Append(IntDoublyNode **head, const int valueToAppend)
{
    IntDoublyNode* new_node = malloc(sizeof(IntDoublyNode*));
    if(!new_node)
    {
        return;
    }
    new_node -> next = NULL; //New node become the List's tail
    new_node -> value = valueToAppend;

    IntDoublyNode* tail = GetTail(*head);
    if(!tail)
    {
        *head = new_node;
        (*head) -> previous = NULL;
        (*head) -> count = 1;
    }
    else
    {
        tail -> next = new_node;
        new_node -> previous = tail;
        (*head) -> count++;
    }
}
void InsertAfter(IntDoublyNode **head, const int valueWhereInsert, const int valueToInsert) 
{
    if(!*head)
    {
        return;
    }
    IntDoublyNode* tail = GetTail(*head);
    if(tail -> value == valueWhereInsert)
    {
        Append(head, valueToInsert);
        return;
    }

    IntDoublyNode* new_node = malloc(sizeof(IntDoublyNode*));
    if(!new_node)
    {
        return;
    }
    new_node -> next = NULL; 
    new_node -> value = valueToInsert;

    IntDoublyNode* nodeWhereInsert = *head;
    while(nodeWhereInsert)
    {
        if(nodeWhereInsert -> value == valueWhereInsert)
        {
            break;
        }
        if(nodeWhereInsert -> next == NULL)
        {
            printf("Node not found!\n");
            printf("Node: %d\n", nodeWhereInsert -> value);
            return;
        }
        nodeWhereInsert = nodeWhereInsert -> next;
    }
    new_node -> next = nodeWhereInsert -> next;
    new_node -> previous = nodeWhereInsert;
    nodeWhereInsert -> next -> previous = new_node;
    nodeWhereInsert -> next = new_node;
    (*head) -> count++;

}

void InsertBefore(IntDoublyNode **head, const int valueWhereInsert, const int valueToInsert) 
{
    if(!*head)
    {
        return;
    }

    IntDoublyNode* new_node = malloc(sizeof(IntDoublyNode*));
    if(!new_node)
    {
        return;
    }
    new_node -> next = NULL; 
    new_node -> value = valueToInsert;

    if((*head) -> value == valueWhereInsert)
    {
        unsigned int current_count = (*head) -> count;
        new_node -> previous = NULL;
        new_node -> next = *head;
        (*head) -> previous = new_node;
        *head = new_node;
        (*head) -> count = current_count + 1;
        return;
    }
    IntDoublyNode* nodeWhereInsert = (*head) -> next;
    while(nodeWhereInsert)
    {
        if(nodeWhereInsert -> value == valueWhereInsert)
        {
            break;
        }
        if(nodeWhereInsert -> next == NULL)
        {
            printf("Node not found!\n");
            printf("Node: %d\n", nodeWhereInsert -> value);
            return;
        }
        nodeWhereInsert = nodeWhereInsert -> next;
    }
    new_node -> next = nodeWhereInsert;
    new_node -> previous = nodeWhereInsert -> previous;
    new_node -> previous -> next = new_node;
    nodeWhereInsert ->  previous = new_node;
    (*head) -> count++;

}

unsigned int Length(const IntDoublyNode* head)
{
    return head -> count;
}

IntDoublyNode* PopList(IntDoublyNode** head)
{
    if(!*head)
    {
        return NULL;
    }

    IntDoublyNode* nodeToRemove = *head;
    const unsigned int current_count = nodeToRemove -> count;
    *head = (*head) -> next;
    (*head) -> previous = NULL;
    if(*head)
    {
        (*head) -> count = current_count - 1;
    }

    nodeToRemove -> next = NULL;
    nodeToRemove -> previous = NULL;
    return nodeToRemove;

}

void RemoveAt(IntDoublyNode** head, const unsigned int index)
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

    IntDoublyNode* nodeToRemove = *head;
    IntDoublyNode* previous_node = (*head) -> previous;
    for (unsigned int i = 0; i < index; i++)
    {
        nodeToRemove = nodeToRemove -> next; 
    }
    previous_node = nodeToRemove -> previous;
    nodeToRemove -> next -> previous = nodeToRemove -> previous;
    previous_node -> next = nodeToRemove -> next;
    if(*head)
    {
        (*head) -> count --;
    }

    free(nodeToRemove);   
}

void Remove(IntDoublyNode** head, const int valueToRemove)
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

    IntDoublyNode* nodeToRemove = *head;
    IntDoublyNode* previous_node = (*head) -> previous;
    while(nodeToRemove)
    {
        nodeToRemove = nodeToRemove -> next;
        if(nodeToRemove -> value == valueToRemove)
        {
            break;
        }
        if(nodeToRemove -> next == NULL)
        {
            printf("Node not found!\n");
            return;
        }
    }
    previous_node = nodeToRemove -> previous;
    nodeToRemove -> next -> previous = nodeToRemove -> previous;
    previous_node -> next = nodeToRemove -> next;
    if(*head)
    {
        (*head) -> count --;
    }

    free(nodeToRemove);   
}

IntDoublyNode* SplitList(IntDoublyNode* head)
{
    IntDoublyNode* double_speed_node = head;
    IntDoublyNode* normal_speed_node = head;
    /*In this way when double speed node will arrive to the end, *head will arrive at the half of list */
    while (double_speed_node -> next != NULL)
    {
        double_speed_node = double_speed_node -> next -> next;
        normal_speed_node = normal_speed_node -> next;
    }
    //Split list
    IntDoublyNode* half_head = normal_speed_node;
    half_head -> previous -> next = NULL;
    half_head -> previous = NULL;
    return half_head;
}

void MixLists(IntDoublyNode* first_head, IntDoublyNode* second_head)
{
    IntDoublyNode* new_head = NULL;
    while (second_head)
    {
        if(!new_head)
        {
            new_head = second_head;
        }
        else
        {
            new_head -> next = second_head;
            new_head -> previous = second_head -> previous;
            new_head = second_head;
        }

        IntDoublyNode* next = second_head -> next;
        second_head -> next = NULL;
        second_head = next;


        IntDoublyNode* temp = first_head;
        first_head = second_head;
        second_head = temp;
    }
}
void Shuffle(IntDoublyNode** head)
{
    unsigned int current_count = (*head) -> count;
    IntDoublyNode* half_head = SplitList(*head);
    IntDoublyNode* tail = GetTail(*head);
    MixLists(*head, half_head);
    *head = half_head;
    IntDoublyNode* new_tail = GetTail(*head);
    new_tail -> previous = tail;
    (*head) -> count = current_count;
}

int main(int argc, char** argv)
{ 
    IntDoublyNode* head = NULL;
    Append(&head, 15);
    Append(&head, 16);
    Append(&head, 17);
    Append(&head, 18);
    Append(&head, 19);
    Append(&head, 20);
    printf("APPEND!\n");
    int i = 0;
    for(IntDoublyNode* current = head; current != NULL; current = current -> next)
    {
        if(current -> previous != NULL)   printf("%d*: %d <-", ++i, current -> previous -> value);
        else 
        printf("%d*:", ++i);        
        printf(" %d", current -> value);
        if(current -> next != NULL)   printf(" -> %d\n", current -> next -> value);
        else 
        printf("\n");
    }
    printf("Length: %x\n", Length(head));

    printf("POP!\n");
    free(PopList(&head));

    i = 0;
    for(IntDoublyNode* current = head; current != NULL; current = current -> next)
    {
        if(current -> previous != NULL)   printf("%d*: %d <-", ++i, current -> previous -> value);
        else 
        printf("%d*:", ++i);        
        printf(" %d", current -> value);
        if(current -> next != NULL)   printf(" -> %d\n", current -> next -> value);
        else 
        printf("\n");
    }
    printf("Length: %x\n", Length(head));

    printf("REMOVEAT!\n");
    RemoveAt(&head, 3);

    i = 0;
    for(IntDoublyNode* current = head; current != NULL; current = current -> next)
    {
        if(current -> previous != NULL)   printf("%d*: %d <-", ++i, current -> previous -> value);
        else 
        printf("%d*:", ++i);        
        printf(" %d", current -> value);
        if(current -> next != NULL)   printf(" -> %d\n", current -> next -> value);
        else 
        printf("\n");
    }
    printf("Length: %x\n", Length(head));

    printf("REMOVE!\n");
    Remove(&head, 18);

    i = 0;
    for(IntDoublyNode* current = head; current != NULL; current = current -> next)
    {
        if(current -> previous != NULL)   printf("%d*: %d <-", ++i, current -> previous -> value);
        else 
        printf("%d*:", ++i);        
        printf(" %d", current -> value);
        if(current -> next != NULL)   printf(" -> %d\n", current -> next -> value);
        else 
        printf("\n");
    }
    printf("Length: %x\n", Length(head));

    printf("INSERT AFTER!\n");
    InsertAfter(&head, 16, 3);

    i = 0;
    for(IntDoublyNode* current = head; current != NULL; current = current -> next)
    {
        if(current -> previous != NULL)   printf("%d*: %d <-", ++i, current -> previous -> value);
        else 
        printf("%d*:", ++i);        
        printf(" %d", current -> value);
        if(current -> next != NULL)   printf(" -> %d\n", current -> next -> value);
        else 
        printf("\n");
    }
    printf("Length: %x\n", Length(head));

    printf("INSERT BEFORE!\n");
    InsertBefore(&head, 16, 4);

    i = 0;
    for(IntDoublyNode* current = head; current != NULL; current = current -> next)
    {
        if(current -> previous != NULL)   printf("%d*: %d <-", ++i, current -> previous -> value);
        else 
        printf("%d*:", ++i);        
        printf(" %d", current -> value);
        if(current -> next != NULL)   printf(" -> %d\n", current -> next -> value);
        else 
        printf("\n");
    }
    printf("Length: %x\n", Length(head));


    Append(&head, 5);
    Append(&head, 6);

    i = 0;
    for(IntDoublyNode* current = head; current != NULL; current = current -> next)
    {
        if(current -> previous != NULL)   printf("%d*: %d <-", ++i, current -> previous -> value);
        else 
        printf("%d*:", ++i);        
        printf(" %d", current -> value);
        if(current -> next != NULL)   printf(" -> %d\n", current -> next -> value);
        else 
        printf("\n");
    }
    printf("Length: %x\n", Length(head));
    
    printf("SHUFFLE!\n");
    Shuffle(&head);

    i = 0;
    for(IntDoublyNode* current = head; current != NULL; current = current -> next)
    {
        if(current -> previous != NULL)   printf("%d*: %d <-", ++i, current -> previous -> value);
        else 
        printf("%d*:", ++i);        
        printf(" %d", current -> value);
        if(current -> next != NULL)   printf(" -> %d\n", current -> next -> value);
        else 
        printf("\n");
    }
    printf("Length: %x\n", Length(head));






}

