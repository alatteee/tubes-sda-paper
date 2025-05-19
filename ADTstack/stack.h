#ifndef STACK_H
#define STACK_H

#include "../ADTSLL/linkedlist.h"

typedef struct {
    address top;
} Stack;

void initStack(Stack *s);
void push(Stack *s, infotype nilai);
infotype pop(Stack *s);
bool isStackEmpty(Stack *s);
void printStack(Stack *s);

#endif