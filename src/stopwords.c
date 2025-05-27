#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "../include/stopwords.h"

void loadStopwords(const char *filename, StopwordNode **head) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Gagal membuka file stopwords: %s\n", filename);
        return;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = 0; // hapus newline

        StopwordNode *baru = malloc(sizeof(StopwordNode));
        baru->word = strdup(buffer);
        baru->next = NULL;

        // Tambahkan ke akhir list
        if (*head == NULL) {
            *head = baru;
        } else {
            StopwordNode *curr = *head;
            while (curr->next != NULL)
                curr = curr->next;
            curr->next = baru;
        }
    }

    fclose(fp);
    printf("Stopwords berhasil dimuat!\n");
}
