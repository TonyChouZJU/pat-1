//
//  2.8.c
//  data structure
//
//  Created by Xuchao Ding on 2015-04-30.
//  Copyright (c) 2015 Xuchao Ding. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _stack {
    int type;
    double num;
    char op;
    struct _stack* next;
} Stack;

Stack* createStack(int type, double num, char op) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->type = type;
    s->next = NULL;
    if(type) {
        s->num = num;
    }
    else {
        s->op = op;
    }
    return s;
}

Stack* pop(Stack* s) {
    Stack* temp = NULL;
    if(s->next) {
        temp = s->next;
        s->next = temp->next;
    }
    return temp;
}

void push(Stack* top, Stack* node) {
    node->next = top->next;
    top->next = node;
}

typedef struct _stringstack {
    char str[16];
    struct _stringstack* next;
} StringStack;

StringStack* popString(StringStack* s) {
    StringStack* temp = NULL;
    if(s->next) {
        temp = s->next;
        s->next = temp->next;
    }
    return temp;
}

void pushString(StringStack* top, StringStack* node) {
    node->next = top->next;
    top->next = node;
}

void createStringNum(double num, char* res) {
    int n = (int)num;
    if (num < 10) {
        res[0] = '0' + n;
        res[1] = '\0';
    }
    else {
        res[0] = '1';
        res[1] = '0' + (n - 10);
        res[2] = '\0';
    }
}

void createStringOp(char op, char* res) {
    res[0] = op;
    res[1] = '\0';
}

void createStringStr(char* str1, char* str2, char op, char* res, int tag) {
    int x = 0;
    if(tag)
        res[x++] = '(';
    int i = 0;
    while(str1[i] != '\0') {
        res[x++] = str1[i++];
    }
    res[x++] = op;
    int j = 0;
    while(str2[j] != '\0') {
        res[x++] = str2[j++];
    }
    if(tag)
        res[x++] = ')';
    res[x] = '\0';
}

double calculate(double a, double b, char op) {
    double res = 0;
    switch(op) {
        case '+':
            res = b + a;
            break;
        case '-':
            res = b - a;
            break;
        case '*':
            res = 1.0 * b * a;
            break;
        case '/':
            if(a != 0) {
                res = 1.0 * b / a;
            }
            else {
                res = -32768;
            }
            break;
    }
    return res;
}

int found24 = 0;
char op[4];
double num[4];
Stack* s[7];
int x[3], y[4];
StringStack* resultString;

void loop() {
    for(x[0] = 0; x[0] < 4; x[0]++) {
        for(x[1] = 0; x[1] < 4; x[1]++) {
            for(x[2] = 0; x[2] < 4; x[2]++) {
                for(y[0] = 0; y[0] < 4; y[0]++) {
                    for(y[1] = 0; y[1] < 4; y[1]++){
                        if(y[1] == y[0])
                            continue;
                        for(y[2] = 0; y[2] < 4; y[2]++) {
                            if(y[2] == y[0] || y[2] == y[1])
                                continue;
                            for(y[3] = 0; y[3] < 4; y[3]++) {
                                if(y[3] == y[0] || y[3] == y[1] || y[3] == y[2])
                                    continue;
                                int indexop = 0;
                                int indexnum = 0;
                                Stack* expr = (Stack*)malloc(sizeof(Stack));
                                expr->next = NULL;
                                for(int i = 0; i < 7; i++) {
                                    if(s[i]->type) {
                                        s[i]->num = num[y[indexnum++]];
                                        push(expr, s[i]);
                                    }
                                    else {
                                        s[i]->op = op[x[indexop++]];
                                        Stack* ta = pop(expr);
                                        Stack* tb = pop(expr);
                                        double result = calculate(ta->num, tb->num, s[i]->op);
                                        Stack* temp = createStack(2, result, ' ');
                                        push(expr, temp);
                                        if(ta->type == 2) {
                                            free(ta);
                                        }
                                        if(tb->type == 2) {
                                            free(tb);
                                        }
                                    }
                                }
                                Stack* res = pop(expr);
                                //                                for(int i = 0; i < 7; i++) {
                                //                                    if(s[i]->type)
                                //                                        printf("%.1f ", s[i]->num);
                                //                                    else
                                //                                        printf("%c ", s[i]->op);
                                //                                }
                                //                                printf("%.1f\n", res->num);
                                if(res->num == 24.0) {
                                    found24 = 1;
                                    for(int i = 0; i < 7; i++) {
                                        if(s[i]->type) {
                                            StringStack* st = (StringStack*)malloc(sizeof(StringStack));
                                            //                                            printf("%.1f ", s[i]->num);
                                            createStringNum(s[i]->num, st->str);
                                            pushString(resultString, st);
                                        }
                                        else {
                                            StringStack* st = (StringStack*)malloc(sizeof(StringStack));
                                            //                                            printf("%c ", s[i]->op);
                                            StringStack* tb = popString(resultString);
                                            StringStack* ta = popString(resultString);
                                            int tag = 1;
                                            if(i == 6) {
                                                tag = 0;
                                            }
                                            createStringStr(ta->str, tb->str, s[i]->op, st->str, tag);
                                            pushString(resultString, st);
                                        }
                                    }
                                    //                                    printf("\n");
                                    free(res);
                                    goto BINGO;
                                }
                                free(res);
                            }
                        }
                    }
                }
            }
        }
    }
BINGO:
    return;
}

void case1() {
    s[2]->type = 1;
    s[3]->type = 1;
    s[4]->type = 0;
    s[5]->type = 0;
    loop();
}

void case2() {
    s[2]->type = 1;
    s[3]->type = 0;
    s[4]->type = 1;
    s[5]->type = 0;
    loop();
}

void case3() {
    s[2]->type = 1;
    s[3]->type = 0;
    s[4]->type = 0;
    s[5]->type = 1;
    loop();
}

void case4() {
    s[2]->type = 0;
    s[3]->type = 1;
    s[4]->type = 0;
    s[5]->type = 1;
    loop();
}

void case5() {
    s[2]->type = 0;
    s[3]->type = 1;
    s[4]->type = 1;
    s[5]->type = 0;
    loop();
}

int main() {
    
    op[0] = '+';
    op[1] = '-';
    op[2] = '*';
    op[3] = '/';
    
    for(int i = 0; i < 4; i++) {
        scanf("%lf", &num[i]);
    }
    
    for(int i = 0; i < 7; i++) {
        s[i] = (Stack*)malloc(sizeof(Stack));
    }
    s[0]->type = 1;
    s[1]->type = 1;
    s[6]->type = 0;
    
    resultString = (StringStack*)malloc(sizeof(StringStack));
    resultString->next = NULL;
    
    case1();
    if(!found24)
        case2();
    if(!found24)
        case3();
    if(!found24)
        case4();
    if(!found24)
        case5();
    
    StringStack* temp = resultString;
    while(temp->next) {
        printf("%s\n", temp->next->str);
        temp = temp->next;
    }
    
    if(!found24) {
        printf("-1\n");
    }
exit:
    return 0;
}

/*
 一副扑克牌的每张牌表示一个数（J、Q、K分别表示11、12、13，两个司令都表示6）。任取4张牌，即得到4个1~13的数，请添加运算符（规定为加+ 减- 乘* 除/ 四种）使之成为一个运算式。每个数只能参与一次运算，4个数顺序可以任意组合，4个运算符任意取3个且可以重复取。运算遵从一定优先级别，可加括号控制，最终使运算结果为24。请输出一种解决方案的表达式，用括号表示运算优先。如果没有一种解决方案，则输出-1表示无解。
 
 输入格式说明：
 
 输入在一行中给出4个整数，每个整数取值在[1, 13]。
 
 输出格式说明：
 
 输出一种解决方案的表达式，用括号表示运算优先。如果没有解决方案，请输出-1。
 1
 2 3 12 12
 ((3-2)*12)+12
 2
 5 5 5 5
 (5*5)-(5/5)
 3
 1 3 5 6
 (1+(3*6))+5
 4
 8 13 9 4
 8+((13-9)*4)
 5
 2 13 7 7
 2*(13-(7/7))
 6
 5 5 5 2
 -1
 */
