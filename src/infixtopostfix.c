#include"header.h"

void trim(string str){
    int j=0;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] != ' '){
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int is_operator(char symbol){  
    if(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '(' || symbol == ')'){  
        return 1;  
    }  
    return 0;  
}

int prec(char c){
    if(c == '^'){
        return 3;
    }
    else if(c == '/' || c == '*'){
        return 2;
    }
    else if (c == '+' || c == '-'){
        return 1;
    }
    else{
        return -1;
    }
}

void infixtopostfix(string str, string result){
    int rindex = 0;
    int sindex = -1;
    char stack[1000];
    for(int i = 0; i < strlen(str); i++){
        char c = str[i];
        if(c >= '0' && c <= '9'){
            if(is_operator(str[i+1])){
                result[rindex++] = c;
                result[rindex++] = '_';
            }
            else{
                result[rindex++] = c;
            }
        }
        else if(c == '('){
            stack[++sindex] = c;
        }
        else if(c == ')'){
            while(sindex >= 0 && stack[sindex] != '('){
                result[rindex++] = stack[sindex--];
                result[rindex++] = '_';
            }
            stack[sindex--];
        }
        else{
            while(sindex >= 0 && (prec(c) <= prec(stack[sindex]))){
                result[rindex++] = stack[sindex--];
                result[rindex++] = '_';
            }
            stack[++sindex] = c;
        }
    }
    while(sindex >= 0){
        result[rindex++] = stack[sindex--];
        result[rindex++] = '_';
    }
    result[rindex] = '\0';
}

int main(){
    char str[200];
    printf("Enter: ");
    scanf("%[^\n]", str);
    trim(str);
    char res[1000];
    infixtopostfix(str, res);
    printf("%s", res);
    // stack skt;
    // skt = NULL;
    // dll arr[2];
    // init_dll(&arr[0]);
    // init_dll(&arr[1]);
    // int j = 0;
    // for(int i = 0; i < strlen(str); i++){
    //     if(is_operator(str[i])){
    //         j++;
    //         continue;
    //     }
    //     int d = ctoi(str[i]);
    //     //printf("%d \n", d);
    //     append(&arr[j], d);
    // }
    // printNum(&arr[0]);
    // printNum(&arr[1]);
    // for(int i = 0; i < strlen(str); i++){
    //     push(&skt, &str[i]);
    // }
    // printf("Now \n");
    // for(int j = 0; j < strlen(str); j++){
    //     void* k = pop(&skt);
    //     char ch = *(char*)k;
    //     printf("%d ", ((int)ch - 48));
    // }
    return 0;
}