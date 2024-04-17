#include"header.h"
#include"operations.c"
//#include"list.c"
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

int is_operator(char symbol){  
    if(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/'){  
        return 1;  
    }  
    return 0;  
}
int is_digit(char symbol){
    if((symbol >= '0' && symbol <= '9') || symbol == '.') return 1;
    else return 0;
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
    int i = 0;
    while(i < strlen(str)){
        if(is_digit(str[i])){
            while(is_digit(str[i])){
                result[rindex++] = str[i++];
            }
            result[rindex++] = '_';
        }
        else if(str[i] == '('){
            stack[++sindex] = str[i++];
        }
        else if(str[i] == ')'){
            while(sindex >= 0 && stack[sindex] != '('){
                result[rindex++] = stack[sindex--];
                result[rindex++] = '_';
            }
            sindex--;
            i++;
        }
        else if(is_operator(str[i])){
            while(sindex >= 0 && (prec(str[i]) <= prec(stack[sindex]))){
                result[rindex++] = stack[sindex--];
                result[rindex++] = '_';
            }
            stack[++sindex] = str[i++];
        }
        else i++;
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
    printf("%s\n", res);
    stack skt;
    skt = NULL;
    dll* num1;
    dll* num2;
    dll* num3;
    //dll* temp = (dll*)malloc(sizeof(dll));
    //init_dll(temp);
    int i = 0;
    while( i < strlen(res)){
        if(res[i] == '_'){
            i++;
            continue;
        }
        else if(is_digit(res[i])){
            dll* temp = (dll*)malloc(sizeof(dll));
            init_dll(temp);
            while(is_digit(res[i])){
                if(res[i] == '.'){
                    int d = ctoi(res[i+1]);
                    append(temp, d);
                    temp->dec = temp->tail;
                    i += 2;
                    continue;
                }
                else{int d = ctoi(res[i]);
                append(temp, d);}
                i++;
            }
            //printNum(temp);
            push(&skt, temp);
        }
        else if(is_operator(res[i])){
            if(skt)num1 = (dll*)pop(&skt);
            if(skt)num2 = (dll*)pop(&skt);
            //printNum(num1);
            //printNum(num2);
            if(res[i] == '+'){
                num3 =  add(num2, num1);
            }
            else if(res[i] == '-'){
                num3 = subtract(num2, num1);
            }
            else if(res[i] == '*'){
                num3 = multiply(num1, num2);
            }
            push(&skt, num3);
            printNum(num3);
            i++;
        }
        else i++;
    }
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