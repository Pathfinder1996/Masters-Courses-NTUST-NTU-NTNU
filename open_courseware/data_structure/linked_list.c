#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNode {
    int data;
    struct LinkedListNode *next;
} LLNode;

void showNode(LLNode *head);
int addNode(LLNode **head, int data);
int insertNode(LLNode **head, int data, int position);
int deleteNode(LLNode **head, int data);
int getLength(LLNode *head);

int main() {
    LLNode *head = NULL;

    while (1) {
        printf("\n目前鏈結串列內容： ");
        showNode(head);

        printf("請輸入以下字母對鏈結串列操作：\n");
        printf("(A) 新增節點\n");
        printf("(B) 插入節點 (到指定index)\n");
        printf("(C) 刪除節點\n");
        printf("(D) 查詢鏈結串列長度\n");
        printf("(E) 離開\n");

        char choice;
        scanf(" %c", &choice);

        if (choice == 'A' || choice == 'a') {
            int data;
            printf("\n請輸入要新增的節點值：\n");
            scanf("%d", &data);
            addNode(&head, data);
        }
        else if (choice == 'B' || choice == 'b') {
            int data, position;
            printf("\n請輸入要插入的節點值：\n");
            scanf("%d", &data);
            printf("\n請輸入要插入的位置：\n");
            scanf("%d", &position);
            insertNode(&head, data, position);
        }
        else if (choice == 'C' || choice == 'c') {
            int data;
            printf("\n請輸入要刪除的節點值：\n");
            scanf("%d", &data);
            deleteNode(&head, data);
        }
        else if (choice == 'D' || choice == 'd') {
            printf("\n鏈結串列長度：%d\n", getLength(head));
        }
        else if (choice == 'E' || choice == 'e') {
            break;
        }
        else {
            printf("\n沒有這個選項！！！\n");
        }

    }

    // 釋放
    while(head != NULL) {
        LLNode *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

void showNode(LLNode *head) {
    LLNode *p = head;

    if (p == NULL) {
        printf("NULL\n");
        return;
    }

    while (p != NULL) {
        printf("%d --> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

int addNode(LLNode **head, int data) {
    LLNode *newNode = malloc(sizeof(LLNode));

    if (newNode == NULL) {
        return 0;
    }

    // 新節點的值 = 輸入參數的data
    newNode->data = data; 
    newNode->next = NULL;

    if (*head == NULL) {
        // head為NULL 新節點是第一個節點
        *head = newNode;
    } else {
        // 反之 直到找到最後一個節點
        LLNode *p = *head;
        while (p->next != NULL) {
            p = p->next;
        }
        // 將最後一個節點的next指向新節點
        p->next = newNode;
    }

    return 1;
}

int insertNode(LLNode **head, int data, int position) {
    LLNode *newNode = malloc(sizeof(LLNode));

    if (newNode == NULL) {
        return 0;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        printf("鏈結串列為空 無法插入節點\n");
        return 0;
    } 
    else {
        LLNode *p = *head;
        int i = 1;
        while (p->next != NULL && i < position) {
            p = p->next;
            i = i + 1;
        }
        // 將新節點的next指向p的next
        newNode->next = p->next;
        // 將p的next指向新節點
        p->next = newNode;
    }

    return 1;
}

LLNode *getPreNode(LLNode *head, LLNode *target) {
    LLNode *p, *q;
    p = head;
    q = head->next;

    while(q != NULL && q != target) {
        p = q;
        q = q->next;
    }

    if (q == target) {
        return p;
    } else {
        return NULL;
    }
}

int deleteNode(LLNode **head, int data) {
    if (*head == NULL) {
        printf("鏈結串列為空 無法刪除\n");
        return 0;
    }

    LLNode *p = *head;
    LLNode *preNode = NULL;

    if (p->data == data) {
        *head = p->next;
        free(p);
        return 1;
    }

    while (p != NULL && p->data != data) {
        preNode = p;
        p = p->next;
    }

    if (p == NULL) {
        printf("找不到要刪除的節點\n");
        return 0;
    }

    preNode->next = p->next;
    free(p);

    return 1;
}

int getLength(LLNode *head) {
    LLNode *p = head;
    int length = 0;

    while (p != NULL) {
        length = length + 1;
        p = p->next;
    }

    return length;
}