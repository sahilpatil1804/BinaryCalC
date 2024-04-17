#include"header.h"
#include"operations.h"
#include"list.c"

dll* add(dll* list1, dll* list2);
dll* subtract(dll* list1, dll* list2);
void addZeroes(dll* list, int x){
    if(x==0) return;
    while(x--){
        append(list, 0);
    }
}

void trimZeroes(dll* list){
    if(list->head == NULL) return;
    node* temp = list->head;
    node* temp2 = (list->dec) ? list->tail : NULL;
    while(temp2 != list->dec && temp2){
        if(temp2->data == 0){
            temp2 = temp2->prev;
            removeAtEnd(list);
        }
        else break;
    }
    if(temp2){
        if(temp2->data == 0 && temp2 == list->dec){
            removeAtEnd(list);
            list->dec = NULL;
        }
    }
    while(temp->next && temp->next != list->dec){
        if(temp->data == 0){
            temp = temp->next;
            removeNode(list);
        }
        else return;
    }
}

int compare(dll* list1, dll* list2){
    trimZeroes(list1);
    trimZeroes(list2);
    if(lenl(list1) < lenl(list2)){
        return -1;
    }
    else if (lenl(list1) == lenl(list2)){
        node* temp1 = list1->head;
        node* temp2 = list2->head;
        while(temp1 && temp2){
            int d1 = temp1 ? temp1->data : 0;
            int d2 = temp2 ? temp2->data : 0;
            if(d1 > d2){
                return 1;
            }
            else if(d1 < d2){
                return -1;
            }
            if(temp1){
                temp1 = temp1->next;
            }
            if(temp2){
                temp2 = temp2->next;
            }
        }
        return 0;
    }
    return 1;
}

dll* add(dll* list1, dll* list2){
    int carry=0, sum;
    dll* res = malloc(sizeof(dll));
    init_dll(res);
    if(list1->isNegative && list2->isNegative) res->isNegative = true;
    else if(list1->isNegative || list2->isNegative){
        if(list1->isNegative) return subtract(list2, list1);
        else if(list2->isNegative) return subtract(list1, list2);
    }
    if(lenr(list1) > lenr(list2)){
        addZeroes(list2, lenr(list1) - lenr(list2));
    }
    else if(lenr(list2) > lenr(list1)){
        addZeroes(list1, lenr(list2) - lenr(list1));
    }
    node* first = list1->tail;
    node* second = list2->tail;
    while(first != NULL || second != NULL){
        sum = carry + (first ? first->data : 0) + (second ? second->data : 0);
        carry = (sum >= 10) ? 1 : 0;
        sum %= 10;
        addFront(res, sum);
        if(first){
            if(first == list1->dec){
                res->dec = res->head;
            }
            first = first->prev;
        }
        if(second){
            if(second == list2->dec){
                res->dec = res->head;
            }
            second = second->prev;
        }
    }
    if(carry > 0){
        addFront(res, carry);
    }
    return res;
}

dll* subtract(dll* list1, dll* list2){
    int borrow=0, sum;
    dll* res = malloc(sizeof(dll));
    init_dll(res);
    if(compare(list1, list2) == -1){
        res = subtract(list2, list1);
        res->isNegative = true;
        return res;
    }
    else if (compare(list1, list2) == 0){
        addZeroes(res,1);
        return res;
    }
    //adds zeroes to make the length of number equal after the decimal point
    if(lenr(list1) > lenr(list2)){
        addZeroes(list2, lenr(list1) - lenr(list2));
    }
    else if(lenr(list2) > lenr(list1)){
        addZeroes(list1, lenr(list2) - lenr(list1));
    }
    node* first = list1->tail;
    node* second = list2->tail;
    while(first != NULL || second != NULL){
        sum = (first ? first->data : 0) - (second ? second->data : 0) - borrow;
        borrow = (sum < 0) ? 1 : 0;
        if(sum < 0){
            sum += 10;
        }
        addFront(res, sum);
        if(first){
            if(first == list1->dec){
                res->dec = res->head;
            }
            first = first->prev;
        }
        if(second){
            if(second == list2->dec){
                res->dec = res->head;
            }
            second = second->prev;
        }
    }
    return res;
}

dll* multiply(dll* list1, dll* list2){
    dll* res = malloc(sizeof(dll));
    dll* res2;
    init_dll(res);
    append(res, 0);
    trimZeroes(list1);
    trimZeroes(list2);
    dll* num = malloc(sizeof(dll));
    copy(list1, num);
    //printNum(num);
    num->isNegative = false;
    //printNum(num);
    node* temp = list2->tail;
    while(temp){
        int i = temp->data;
        while(i--){
            res2 = res;
            res = add(res, num);
            destroy(res2);
            //printNum(res);
        }
        append(num, 0);
        if(num->dec){
            num->dec = num->dec->next;
        }
        temp = temp->prev;
    }
    if(list1->isNegative || list2->isNegative){
        res->isNegative = true;
        if(list1->isNegative && list2->isNegative){
            res->isNegative = false;
        }
    }
    int daa = lenr(list2);
    if(!res->dec){
        addZeroes(res, 1);
        res->dec = res->tail;
    }
    while(daa > 0){
        daa--;
        if(res->dec) res->dec = res->dec->prev;
        else{
            addFront(res, 0);
            res->dec = res->dec->prev;
        }
    }
    if(res->dec == res->head) addFront(res, 0);
    return res;
}

/*int main(){
    dll* list1 = malloc(sizeof(dll));
    dll* list2 = malloc(sizeof(dll));
    dll* list3;
    init_dll(list1);
    init_dll(list2);
    addZeroes(list1, 3);
    append(list1, 2);
    append(list1, 3);
    append(list1, 3);
    append(list1, 5);
    addZeroes(list1, 2);
    append(list1, 9);
    list1->isNegative = true;
    append(list2, 3);
    append(list2, 5);
    addZeroes(list2, 5);
    list2->dec = list2->tail;
    append(list2, 3);
    append(list2, 3);
    list2->isNegative = false;
    list3 = multiply(list1, list2);
    printNum(list1);
    printNum(list2);
    printNum(list3);
    // addZeroes(list1, 2);
    // list1->isNegative = true;
    // append(list2, 0);
    // append(list2, 3);
    // printNum(list1);
    // printNum(list2);
    // multiply(list1, list2);
    // printNum(list3);
    return 0;
}*/