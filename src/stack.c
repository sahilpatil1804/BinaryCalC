#include"header.h"

bool isEmpty(stack* s){
    return s==NULL;
}

void* pop(stack* s){
    stack temp;
    void* i;
    if(isEmpty(s))
        exit(EXIT_FAILURE);
    temp = *s;
    i = ((*s)->data);
    *s = (*s)->next;
    free(temp);
    return i;
}

// void* peek(stack* s){
    
// }

void push(stack* s, void* d){
    stack temp = malloc(sizeof(stacknode));
    if(!temp){
        exit(EXIT_FAILURE);
    }
    temp->data = d;
    temp->next = *s;
    *s = temp;
}

