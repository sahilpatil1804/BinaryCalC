#include"header.h"
#include"list.c"
#include"stack.c"

void trim(string str){
    int j=0;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] != ' '){
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int is_operator(char symbol) {  
    if(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') {  
        return 1;  
    }  
    return 0;  
}

int main(){
    char str[200];
    printf("Enter: ");
    scanf("%[^\n]", str);
    trim(str);
    stack skt;
    skt = NULL;
    for(int i = 0; i < strlen(str); i++){
        push(&skt, &str[i]);
    }
    printf("Now \n");
    for(int j = 0; j < strlen(str); j++){
        void* k = pop(&skt);
        char ch = *(char*)k;
        printf("%d ", ((int)ch - 48));
    }
    return 0;
}