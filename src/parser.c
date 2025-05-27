#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data_structures.h"

// Fungsi bantu: bandingkan string tanpa memperhatikan huruf besar/kecil
int compareIgnoreCase(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower(*a) != tolower(*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == *b;
}

// Bersihkan tanda kutip dari string (kalau ada)
void cleanQuotes(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (*src != '"') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

// Cek apakah kata termasuk stopword
int isStopWord(const char *word, StopwordNode *stopwords) {
    StopwordNode *curr = stopwords;
    while (curr != NULL) {
        if (compareIgnoreCase(curr->word, word)) return 1;
        curr = curr->next;
    }
    return 0;
}

// Cari FieldNode
FieldNode *cariField(FieldNode *head, const char *fieldName) {
    while (head != NULL) {
        if (compareIgnoreCase(head->fieldName, fieldName)) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// Buat KeywordNode dan tambah ke list
void tambahKeyword(KeywordNode **head, const char *word) {
    KeywordNode *baru = malloc(sizeof(KeywordNode));
    baru->keyword = strdup(word);
    baru->next = NULL;

    if (*head == NULL) {
        *head = baru;
    } else {
        KeywordNode *temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = baru;
    }
}

// Buat PaperNode dan isi keywordList
PaperNode *buatPaper(const char *title, int inCitations, int year, StopwordNode *stopwords) {
    PaperNode *p = malloc(sizeof(PaperNode));
    p->title = strdup(title);
    p->inCitations = inCitations;
    p->year = year;
    p->next = NULL;
    p->keywordList = NULL;

    char judulCopy[300];
    strcpy(judulCopy, title);

    char *token = strtok(judulCopy, " ");
    while (token != NULL) {
        if (!isStopWord(token, stopwords)) {
            tambahKeyword(&(p->keywordList), token);
        }
        token = strtok(NULL, " ");
    }

    return p;
}

// Tambah PaperNode ke akhir daftar paper
void tambahPaper(PaperNode **head, PaperNode *baru) {
    if (*head == NULL) {
        *head = baru;
    } else {
        PaperNode *temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = baru;
    }
}

// Tambah FieldNode ke akhir fieldList
void tambahField(FieldNode **head, FieldNode *baru) {
    if (*head == NULL) {
        *head = baru;
    } else {
        FieldNode *temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = baru;
    }
}

// Load CSV dan bangun struktur
void loadData(const char *filename, FieldNode **fieldList, StopwordNode *stopwords) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Gagal membuka file %s\n", filename);
        return;
    }

    char baris[1024];
    fgets(baris, sizeof(baris), fp); // skip header

    while (fgets(baris, sizeof(baris), fp)) {
        char field[100], title[300];
        int inCitations, year;

        int parsed = sscanf(baris, "%99[^,],%299[^,],%d,%d", field, title, &inCitations, &year);
        if (parsed != 4) continue;

        cleanQuotes(field);
        cleanQuotes(title);

        FieldNode *f = cariField(*fieldList, field);
        if (!f) {
            f = malloc(sizeof(FieldNode));
            f->fieldName = strdup(field);
            f->paperList = NULL;
            f->next = NULL;
            tambahField(fieldList, f);
        }

        PaperNode *p = buatPaper(title, inCitations, year, stopwords);
        tambahPaper(&(f->paperList), p);
    }

    fclose(fp);
    printf("Data berhasil dimuat!\n");
}
