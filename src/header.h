
#ifndef HEADER_H
#define HEADER_H
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef unsigned long long int ull;
typedef long long int ll;
typedef char* string;

typedef struct node{
    int data;
    struct node* prev;
    struct node* next;  
} node;

typedef struct{
    bool isNegative;
    node* head;
    node* tail;
    node* dec;
} dll;

typedef dll* num;

typedef struct stacknode{
    void* data;
    struct stacknode* next;
} stacknode;

typedef stacknode* stack;

//DLL Functions->
void init_dll(dll* newlist);
node* init_node(int data);
void append(dll* list, int data);
void printNum(dll* list);
void removeNode(dll* list);
void destroy(dll* list);
int lenl(dll* list);
int lenr(dll* list);

//Stack Functions->
bool isEmpty(stack* s);
void* pop(stack* s);
void push(stack* s, void* d);

#endif