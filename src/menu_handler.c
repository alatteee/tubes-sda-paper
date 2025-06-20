#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/data_structures.h"
#include "../include/menu_handler.h"
#include "../ADTstack/stack.h"
#include "../include/parser.h"


// Menampilkan semua bidang studi
void tampilkanSemuaField(FieldNode *fieldList) {
    printf("\n Daftar Bidang (fieldOfStudy):\n");
    FieldNode *temp = fieldList;
    while (temp != NULL) {
        printf("- %s\n", temp->fieldName);  // Cetak nama field
        temp = temp->next;                 // Pindah ke field berikutnya
    }
}

// Menghitung jumlah total paper dalam daftar
int hitungTotalPaper(PaperNode *paperList) {
    int total = 0;
    while (paperList) {
        total++;
        paperList = paperList->next;
    }
    return total;
}

// Menampilkan seluruh paper secara paginasi (10 per halaman)
void tampilSemuaPaper(PaperNode *paperList) {
    int page = 0;
    int perPage = 10;
    char command;
    PaperNode *current = paperList;

    int totalPaper = hitungTotalPaper(paperList);
    int totalPage = (totalPaper + perPage - 1) / perPage; // Pembulatan ke atas

    do {
        system("cls");  // Membersihkan layar (khusus Windows)
        printf("===== Daftar Paper (Halaman %d dari %d) =====\n", page + 1, totalPage);

        PaperNode *temp = current;
        int count = 0;
        int nomor = page * perPage + 1;

        while (temp != NULL && count < perPage) {
            printf("%d. Judul       : %s\n", nomor++, temp->title);
            printf("   Tahun       : %d\n", temp->year);
            printf("   InCitations : %d\n", temp->inCitations);
            printf("--------------------------------------------------\n");
            temp = temp->next;
            count++;
        }

        // Navigasi halaman
        printf("[n] Next | [p] Previous | [x] Exit: ");
        scanf(" %c", &command);
        getchar();

        if (command == 'n' && page < totalPage - 1) {
            int skip = perPage;
            while (current != NULL && skip--) {
                current = current->next;
            }
            page++;
        } else if (command == 'p' && page > 0) {
            current = paperList;
            int back = (page - 1) * perPage;
            while (back-- && current != NULL) {
                current = current->next;
            }
            page--;
        }

    } while (command != 'x' && current != NULL);
}

// Menampilkan N paper dengan inCitations terbanyak (menggunakan selection sort)
void tampilTopNPaper(PaperNode *paperList, int n) {
    int total = 0;
    PaperNode *p = paperList;
    while (p != NULL) {
        total++;
        p = p->next;
    }

    if (n > total) n = total;

    // Buat array pointer ke PaperNode
    PaperNode **array = malloc(total * sizeof(PaperNode *));
    p = paperList;
    int i = 0;
    while (p != NULL) {
        array[i++] = p;
        p = p->next;
    }

    // Selection sort berdasarkan inCitations (descending)
    for (int i = 0; i < total - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < total; j++) {
            if (array[j]->inCitations > array[maxIdx]->inCitations) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            PaperNode *temp = array[i];
            array[i] = array[maxIdx];
            array[maxIdx] = temp;
        }
    }

    // Tampilkan hasil
    for (int i = 0; i < n; i++) {
        printf("%d. Judul       : %s\n", i + 1, array[i]->title);
        printf("   Tahun       : %d\n", array[i]->year);
        printf("   InCitations : %d\n", array[i]->inCitations);
        printf("--------------------------------------------------\n");
    }

    free(array);  // Bebaskan memori
}

// Mencari paper berdasarkan keyword (yang bukan stopword), cocok berurutan
void cariKeyword(PaperNode *paperList, const char *keywordInput, StopwordNode *stopwords) {
    char inputCopy[256];
    strcpy(inputCopy, keywordInput);

    // Pisahkan keyword berdasarkan spasi
    char *keywords[20];
    int count = 0;

    char *token = strtok(inputCopy, " ");
    while (token != NULL && count < 20) {
        if (!isStopWord(token, stopwords)) {
            keywords[count++] = token;
        }
        token = strtok(NULL, " ");
    }

    if (count == 0) {
        printf("Semua keyword adalah stopword atau kosong.\n");
        return;
    }

    int ditemukan = 0;
    PaperNode *p = paperList;
    while (p != NULL) {
        KeywordNode *start = p->keywordList;

        while (start != NULL) {
            KeywordNode *curr = start;
            int i = 0;
            while (curr != NULL && i < count && compareIgnoreCase(curr->keyword, keywords[i])) {
                curr = curr->next;
                i++;
            }

            if (i == count) {  // Semua keyword cocok dan berurutan
                printf("%d. Judul       : %s\n", ditemukan + 1, p->title);
                printf("   Tahun       : %d\n", p->year);
                printf("   InCitations : %d\n", p->inCitations);
                printf("--------------------------------------------------\n");

                ditemukan = 1;
                break;
            }

            start = start->next;
        }

        p = p->next;
    }

    if (!ditemukan) {
        printf("Tidak ada paper yang mengandung keyword '%s'.\n", keywordInput);
    }
}

// Menampilkan paper yang sesuai dengan tahun tertentu
void cariTahun(PaperNode *paperList, int tahun) {
    int ditemukan = 0;
    PaperNode *p = paperList;

    while (p != NULL) {
        if (p->year == tahun) {
            printf("%d. Judul       : %s\n", ditemukan + 1, p->title);
            printf("   Tahun       : %d\n", p->year);
            printf("   InCitations : %d\n", p->inCitations);
            printf("--------------------------------------------------\n");
            ditemukan = 1;  // Menandai ditemukan
        }
        p = p->next;
    }

    if (!ditemukan) {
        printf("Tidak ada paper yang diterbitkan pada tahun %d.\n", tahun);
    }
}

// Fungsi untuk validasi input bilangan bulat positif
int getValidInt(const char *prompt) {
    char input[100];
    int value;
    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin)) {
            if (sscanf(input, "%d", &value) == 1 && value > 0) {
                return value;
            } else {
                printf("Input tidak valid! Masukkan angka yang benar.\n");
            }
        }
    }
}

// Fungsi untuk validasi input tahun (antara 1800–2025)
int getValidYear(const char *prompt) {
    char input[100];
    int value;
    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin)) {
            if (sscanf(input, "%d", &value) == 1 && value >= 1800 && value <= 2025) {
                return value;
            } else {
                printf("Input tidak valid! Masukkan tahun antara 1800 dan 2025.\n");
                while (getchar() != '\n');
            }
        }
    }
}

// Menu lanjutan setelah field dipilih
void submenuField(FieldNode *target, Stack *riwayat, StopwordNode *stopwords){
    int sub;
    do {
        printf("=========================================\n");
        printf("        Menu Field: %s    \n", target->fieldName);
        printf("=========================================\n");
        printf("1. Tampilkan semua judul paper\n");
        printf("2. Tampilkan Top N paper\n");
        printf("3. Cari paper berdasarkan keyword\n");
        printf("4. Cari paper berdasarkan tahun\n");
        printf("5. Kembali ke Menu Utama\n");
        printf("Pilih menu: ");
        scanf("%d", &sub);
        getchar();

        switch (sub) {
            case 1: {
                printf("\n Semua Judul Paper dalam %s:\n", target->fieldName);
                tampilSemuaPaper(target->paperList);
                char r[150];
                sprintf(r, "Tampilkan semua paper - %s", target->fieldName);
                push(riwayat, strdup(r));
                break;
            }
            case 2: {
                int n = getValidInt("Masukkan jumlah top paper: ");
                tampilTopNPaper(target->paperList, n);
                char r[150];
                sprintf(r, "Top %d paper - %s", n, target->fieldName);
                push(riwayat, strdup(r));
                break;
            }
            case 3: {
                char key[100];
                printf("Masukkan keyword: ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = '\0';

                printf("\n Paper dengan keyword '%s' di bidang %s:\n", key, target->fieldName);
                cariKeyword(target->paperList, key, stopwords);

                char r[150];
                sprintf(r, "Cari keyword '%s' di %s", key, target->fieldName);
                push(riwayat, strdup(r));
                break;
            }
            case 4: {
                int tahun = getValidYear("Masukkan tahun: ");
                printf("\n Paper tahun %d di bidang %s:\n", tahun, target->fieldName);
                cariTahun(target->paperList, tahun);
                char r[150];
                sprintf(r, "Cari tahun %d di %s", tahun, target->fieldName);
                push(riwayat, strdup(r));
                break;
            }
            case 5:
                printf("Kembali ke menu utama...\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (sub != 5);
}

// Menu utama untuk memilih field dan masuk ke submenu
void menuField(FieldNode *fieldList, Stack *riwayat, StopwordNode *stopwords) {
    char cari[100];
    printf("Masukkan fieldOfStudy: ");
    fgets(cari, sizeof(cari), stdin);
    cari[strcspn(cari, "\n")] = '\0';

    FieldNode *target = cariField(fieldList, cari);
    if (!target) {
        printf(" Field '%s' tidak ditemukan.\n", cari);
    } else {
        char riwayatStr[120];
        sprintf(riwayatStr, "Masuk Field: %s", target->fieldName);
        push(riwayat, strdup(riwayatStr));
        submenuField(target, riwayat, stopwords);
    }
}

// Menampilkan riwayat interaksi pengguna dari stack
void tampilkanRiwayat(Stack *riwayat) {
    printf("=========================================\n");
    printf("             Riwayat Pencarian           \n");
    printf("=========================================\n");

    if (isStackEmpty(riwayat)) {
        printf("Belum ada riwayat pencarian.\n");
        return;
    }

    address curr = riwayat->top;
    while (curr != NULL) {
        printf("%s\n", (char *)curr->info);  // Cetak informasi dari stack (riwayat)
        curr = curr->next;
    }
}

#endif
