#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "../include/stopwords.h"

// Fungsi untuk memuat stopwords dari file eksternal ke dalam linked list
void loadStopwords(const char *filename, StopwordNode **head) {
    FILE *fp = fopen(filename, "r");  // Buka file stopwords dalam mode read
    if (!fp) {
        printf("Gagal membuka file stopwords: %s\n", filename);
        return;
    }

    char buffer[100];  // Buffer untuk menyimpan setiap baris (kata)
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = 0;  // Hapus karakter newline di akhir baris

        // Alokasi memori untuk node baru dan salin kata ke dalamnya
        StopwordNode *baru = malloc(sizeof(StopwordNode));
        baru->word = strdup(buffer);  // Duplikat string dari buffer
        baru->next = NULL;

        // Tambahkan node ke akhir linked list
        if (*head == NULL) {
            *head = baru;  // Jika list kosong, node menjadi head
        } else {
            StopwordNode *curr = *head;
            while (curr->next != NULL)  // Iterasi ke node terakhir
                curr = curr->next;
            curr->next = baru;  // Tambahkan node baru di akhir
        }
    }

    fclose(fp);  // Tutup file setelah selesai membaca
    printf("Stopwords berhasil dimuat!\n");
}
