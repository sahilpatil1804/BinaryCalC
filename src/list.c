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

void addFront(dll* list, int data){
    node* newnode = init_node(data);
    if(!list->head){
        list->head = newnode;
        list->tail = newnode;
    }
    else{
        list->head->prev = newnode;
        newnode->next = list->head;
        list->head = newnode;
    }
}

void printNum(dll* list){
    if(list == NULL) return;
    if(list->head == NULL) return;
    node* cur = list->head;
    if(list->isNegative) printf("-");
    while(cur){
        if(cur == list->dec) printf(".");
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
    if(list->head){
        list->head->prev = NULL;
    }
    else{
        list->tail = NULL;
    }
    free(temp);
}

void removeAtEnd(dll* list){
    if(!list->head){
        return;
    }
    node* temp = list->tail;
    list->tail = list->tail->prev;
    if(list->tail){
        list->tail->next = NULL;
    }
    else{
        list->head = NULL;
    }
    free(temp);
}

void destroy(dll* list){
    while(list->head){
        removeNode(list);
    }
    list->tail = NULL;
    list->dec = NULL;
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

int len(dll* list){
    return lenr(list) + lenl(list);
}

void copy(dll* src, dll* dest){
    init_dll(dest);
    dest->isNegative = (src->isNegative) ? true : false;
    node* cur = src->head;
    while(cur){
        append(dest, cur->data);
        dest->dec = (cur == src->dec) ? dest->tail : dest->dec;
        cur = cur->next;
    }
}

// int main(){
//     dll* list1 = malloc(sizeof(dll));
//     init_dll(list1);
//     append(list1, 3);
//     append(list1, 4);
//     append(list1, 3);
//     list1->dec = list1->tail;
//     append(list1, 0);
//     addFront(list1, 0);
//     list1->isNegative = true;
//     dll* cpy = malloc(sizeof(dll));
//     copy(list1, cpy);
//     printNum(list1);
//     printNum(cpy);
//     destroy(list1);
//     append(list1, 2);
//     append(list1, 3);
//     removeAtEnd(list1);
//     removeAtEnd(list1);
//     printNum(list1);
//     return 0;
// }