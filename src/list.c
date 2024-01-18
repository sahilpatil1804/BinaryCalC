#include"header.h"

void init_dll(dll* newlist){
    newlist->head = NULL;
    newlist->tail = NULL;
    newlist->dec = NULL;
    newlist->isNegative = false;
}
node* init_node(int data){
    node* newnode = (node*)malloc(sizeof(node));
    if(!newnode){
        exit(EXIT_FAILURE);
    } 
    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

void append(dll* list, int data){
    node* newnode = init_node(data);
    if(!list->head){
        list->head = newnode;
        list->tail = newnode;
    }
    else{
        list->tail->next = newnode;
        newnode->prev = list->tail;
        list->tail = newnode;
    }
}

void printNum(dll* list){
    node* cur = list->head;
    if(list->isNegative) printf("-");
    while(cur){
        printf("%d", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void removeNode(dll* list){
    if(!list->head){
        return;
    }
    node* temp = list->head;
    list->head = list->head->next;
    if(!list->head){
        list->tail = NULL;
    }
    list->head->prev = NULL;
    free(temp);
}

void destroy(dll* list){
    while(list->head){
        removeNode(list);
    }
    list->tail = NULL;
    list->isNegative = false;
}

int lenl(dll* list){
    node* cur = list->head;
    int count = 0;
    while(cur && cur != list->dec){
        count++;
        cur = cur->next;
    }
    return count;
}

int lenr(dll* list){
    node* cur = list->dec;
    int count = 0;
    if(!list->dec) return 0;
    while(cur){
        count++;
        cur = cur->next;
    }
    return count;
}

