#include "stack.h"

void initStack(Stack *s) {
    s->top = NULL;
}

void push(Stack *s, infotype nilai) {
    address newNode = buatNode(nilai);
    newNode->next = s->top;
    s->top = newNode;
}

infotype pop(Stack *s) {
    if (s->top == NULL) {
        printf("Stack kosong!\n");
        return NULL;
    }

    infotype nilai = s->top->info;
    address temp = s->top;
    s->top = s->top->next;
    free(temp);
    return nilai;
}

bool isStackEmpty(Stack *s) {
    return (s->top == NULL);
}

void printStack(Stack *s) {
    address temp = s->top;
    while (temp != NULL) {
        printf("%s -> ", (char *)temp->info);  // 🟢 PAKAI (char *) CASTING!
        temp = temp->next;
    }
    printf("NULL\n");
}

