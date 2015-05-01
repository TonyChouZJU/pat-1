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
    int num;
    char op;
    struct _stack* next;
} Stack;

Stack* createStack(int type, int num, char op) {
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
    if(s) {
        temp = s;
        s = s->next;
    }
    return temp;
}

void push(Stack* s, Stack* node) {
//    if(!s ) {
//        s = (Stack*)malloc(sizeof(Stack));
//        s->next = node->next;
//    }
    node->next = s;
    s = node;
}

void printStack(Stack* s) {
    if(s->type) {
        printf("%d ", s->num);
    }
    else {
        printf("%c ", s->op);
    }
}

int calculate(int a, int b, char op) {
	int res = 0;
	switch(op) {
	case '+':
		res = a + b;
		break;
	case '-':
		res = a - b;
		break;
	case '*':
		res = a * b;
		break;
	case '/':
		if(b != 0) {
			res = a / b;
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
int num[4];
Stack* s[7];
int x[3], y[4];

void loop() {
	for(x[0] = 0; x[0] < 4; x[0]++) {
		for(x[1] = 0; x[1] < 4; x[1]++) {
			for(x[2] = 0; x[2] < 4; x[2]++) {
				for(y[0] = 0; y[0] < 4; y[0]++) {
					for(y[1] = 0; y[1] < 4 && y[1] != y[0]; y[1]++){
						for(y[2] = 0; y[2] < 4 && y[2] != y[0] && y[2] != y[1]; y[2]++) {
							for(y[3] = 0; y[3] < 4 && y[3] != y[0] && y[3] != y[1] && y[3] != y[2]; y[3]++) {
								int indexop = 0;
								int indexnum = 0;
								Stack* expr = NULL;
								for(int i = 0; i < 7; i++) {
									if(s[i]->type) {
										s[i]->num = num[y[indexnum++]];
										push(expr, s[i]);
									}
									else {
										s[i]->op = op[x[indexop++]];
										Stack* ta = pop(expr);
										Stack* tb = pop(expr);
										int result = calculate(ta->num, tb->num, s[i]->op);
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
								if(res->num == 24) {
									found24 = 1;
									for(int i = 0; i < 7; i++) {
										if(s[i]->type)
											printf("%d ", s[i]->num);
										else
											printf("%c ", s[i]->op);
									}
									printf("\n");
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
}

void case3() {
    s[2]->type = 1;
    s[3]->type = 0;
    s[4]->type = 0;
    s[5]->type = 1;
}

void case4() {
    s[2]->type = 0;
    s[3]->type = 1;
    s[4]->type = 0;
    s[5]->type = 1;
}

void case5() {
    s[2]->type = 0;
    s[3]->type = 1;
    s[4]->type = 1;
    s[5]->type = 0;
}

int main() {

    op[0] = '+';
    op[1] = '-';
    op[2] = '*';
    op[3] = '/';

    for(int i = 0; i < 4; i++) {
        scanf("%d", &num[i]);
    }


    for(int i = 0; i < 7; i++) {
        s[i] = (Stack*)malloc(sizeof(Stack));
    }
    s[0]->type = 1;
    s[1]->type = 1;
    s[6]->type = 0;

    case1();
    if(found24)
    	goto exit;
    case2();
    if(found24)
        	goto exit;
    case3();
    if(found24)
        	goto exit;
    case4();
    if(found24)
        	goto exit;
    case5();
    if(found24)
        	goto exit;

    if(!found24) {
    	printf("-1\n");
    }
exit:
    return 0;
}

/*
һ���˿��Ƶ�ÿ���Ʊ�ʾһ������J��Q��K�ֱ��ʾ11��12��13������˾���ʾ6������ȡ4���ƣ����õ�4��1~13������
�������������涨Ϊ��+ ��- ��* ��/ ���֣�ʹ֮��Ϊһ������ʽ��ÿ����ֻ�ܲ���һ�����㣬4����˳�����������ϣ�
4�����������ȡ3���ҿ����ظ�ȡ���������һ�����ȼ��𣬿ɼ����ſ��ƣ�����ʹ������Ϊ24��
�����һ�ֽ�������ı��ʽ�������ű�ʾ�������ȡ����û��һ�ֽ�������������-1��ʾ�޽⡣

�����ʽ˵����

������һ���и���4��������ÿ������ȡֵ��[1, 13]��

�����ʽ˵����

���һ�ֽ�������ı��ʽ�������ű�ʾ�������ȡ����û�н�������������-1��

���������������
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
