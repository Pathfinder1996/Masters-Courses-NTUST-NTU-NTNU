#include <stdio.h>

#define MAX_ITEM 5

typedef struct tagStack {
    int item[MAX_ITEM];
    int top;
} Stack;

int isFull(Stack *s);
int push(Stack *s, int data);
int isEmpty(Stack *s);
int pop(Stack *s, int *data);
void showStack(Stack *s);
int topItem(Stack *s);

int main(void) {
    Stack s;
    s.top = -1;

    while(1) {
        int i, num;
        printf("\n目前堆疊內容：\n");
        showStack(&s);

        printf("請輸入以下字母對堆疊操作：\n");
        printf("(A) 推入\n");
        printf("(B) 移除\n");
        printf("(C) 查看堆疊頂端的數字\n");
        printf("(D) 離開\n");

        char choice;
        scanf(" %c", &choice);

        if (choice == 'A' || choice == 'a') {
            printf("\n請輸入要推入的數字：\n");
            scanf("%d", &num);
            push(&s, num);
        }
        else if (choice == 'B' || choice == 'b') {
            int data;
            pop(&s, &data);
        }
        else if (choice == 'C' || choice == 'c') {
            printf("\n目前堆疊頂端：%d\n", topItem(&s));
        }
        else if (choice == 'D' || choice == 'd') {
            break;
        }
        else {
            printf("\n沒有這個選項！！！\n");
        }
    }
    return 0;
}

int isFull(Stack *s) {
    if (s->top == (MAX_ITEM - 1)) {
        printf("堆疊已滿，禁止非法操作\n");
        return 1;
    }
    return 0;
}

int push(Stack *s, int data) {
    if (isFull(s)) {
        return 0;
    }

    s->top = s->top + 1; //指到下一個位置 
    s->item[s->top] = data; //將資料推入
    printf("已將 %d 推入堆疊，目前在第 %d 個位置(指index)\n", data, s->top);
    return 1;
}

int isEmpty(Stack *s) {
    if (s->top == -1) {
        printf("堆疊已空\n");
        return 1;
    }
    return 0;
}

int pop(Stack *s, int *data) {
    if (isEmpty(s)) {
        return 0;
    }

    *data = s->item[s->top]; //取出資料
    s->top = s->top - 1; //指到上一個位置
    printf("已將 %d 從堆疊取出，目前在第 %d 個位置(指index)\n", *data, s->top);
    return 1;
}

void showStack(Stack *s) {
    int i;
    for (i = s->top; i >= 0; i--) {
        printf("| %d |\n", s->item[i]);
    }
    printf("\n");
}

int topItem(Stack *s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->item[s->top];
}