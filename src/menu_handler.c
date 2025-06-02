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

void tampilSemuaPaper(PaperNode *paperList) {
    PaperNode *p = paperList;
    while (p != NULL) {
        printf("- \"%s\" (%d sitasi, %d)\n", p->title, p->inCitations, p->year);
        p = p->next;
    }
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
            printf("- \"%s\" (%d sitasi, %d)\n", max->title, max->inCitations, max->year);
            max->inCitations = -1;
        }
    }
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
                printf("- \"%s\" (%d sitasi, %d)\n", p->title, p->inCitations, p->year);
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
            printf("- \"%s\" (%d sitasi, %d)\n", p->title, p->inCitations, p->year);
            ditemukan = 1;
        }
        p = p->next;
    }

    if (!ditemukan) {
        printf("Tidak ada paper yang diterbitkan pada tahun %d.\n", tahun);
    }
}


void submenuField(FieldNode *target, Stack *riwayat, StopwordNode *stopwords){
    int sub;
    do {
        printf("\n===== Menu Field: %s =====\n", target->fieldName);
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
                int n;
                printf("Masukkan jumlah top paper: ");
                scanf("%d", &n);
                getchar();
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
                int tahun;
                printf("Masukkan tahun: ");
                scanf("%d", &tahun);
                getchar();
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
    printf("\n===== Riwayat Pencarian =====\n");

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
