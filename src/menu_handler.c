#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/data_structures.h"
#include "../include/menu_handler.h"
#include "../ADTstack/stack.h"
#include "../include/parser.h"


void tampilkanSemuaField(FieldNode *fieldList) {
    printf("\n Daftar Bidang (fieldOfStudy):\n");
    FieldNode *temp = fieldList;
    while (temp != NULL) {
        printf("- %s\n", temp->fieldName);
        temp = temp->next;
    }
}

int hitungTotalPaper(PaperNode *paperList) {
    int total = 0;
    while (paperList) {
        total++;
        paperList = paperList->next;
    }
    return total;
}


void tampilSemuaPaper(PaperNode *paperList) {
    int page = 0;
    int perPage = 10;
    char command;
    PaperNode *current = paperList;

    int totalPaper = hitungTotalPaper(paperList);
    int totalPage = (totalPaper + perPage - 1) / perPage; // pembulatan ke atas

    do {
        system("cls"); // clear screen
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


void tampilTopNPaper(PaperNode *paperList, int n) {
    for (int i = 0; i < n; i++) {
        PaperNode *max = NULL, *p = paperList;
        while (p != NULL) {
            if (p->inCitations != -1 && (!max || p->inCitations > max->inCitations)) {
                max = p;
            }
            p = p->next;
        }
        if (max) {
            printf("%d. Judul       : %s\n", i + 1, max->title);
            printf("   Tahun       : %d\n", max->year);
            printf("   InCitations : %d\n", max->inCitations);
            printf("--------------------------------------------------\n");
            max->inCitations = -1;
        }
    }

    // Reset nilai citation agar tidak -1
    PaperNode *reset = paperList;
    while (reset != NULL) {
        if (reset->inCitations == -1) reset->inCitations = 0;
        reset = reset->next;
    }
}


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

void cariTahun(PaperNode *paperList, int tahun) {
    int ditemukan = 0;
    PaperNode *p = paperList;

    while (p != NULL) {
        if (p->year == tahun) {
            printf("%d. Judul       : %s\n", ditemukan + 1, p->title);
            printf("   Tahun       : %d\n", p->year);
            printf("   InCitations : %d\n", p->inCitations);
            printf("--------------------------------------------------\n");
            ditemukan++;

            ditemukan = 1;
        }
        p = p->next;
    }

    if (!ditemukan) {
        printf("Tidak ada paper yang diterbitkan pada tahun %d.\n", tahun);
    }
}

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
                int tahun = getValidYear("Masukkan tahun: "); // Validasi input tahun
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
        printf("%s\n", (char *)curr->info);  // Cast karena info-nya void*
        curr = curr->next;
    }
}

#endif
