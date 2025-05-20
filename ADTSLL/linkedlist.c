#include "linkedlist.h"

address buatNode(infotype nilai) {
    address newNode = (address)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->info = nilai;
        newNode->next = NULL;
    }
    return newNode;
}

void addAkhir(address *head, infotype nilai) {
    address newNode = buatNode(nilai);
    if (*head == NULL) {
        *head = newNode;
    } else {
        address temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void tampilList(address head) {
    address temp = head;
    while (temp != NULL) {
        printf("%s -> ", (char *)temp->info);  
    }
    printf("NULL\n");
}

