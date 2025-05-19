#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void* infotype;

typedef struct Node *address;
typedef struct Node {
    infotype info;
    address next;
} Node;

// Fungsi dasar
address buatNode(infotype nilai);
void addAkhir(address *head, infotype nilai);
void tampilList(address head);

#endif
