#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data_structures.h"

// Fungsi bantu: membandingkan dua string tanpa memperhatikan huruf besar/kecil
int compareIgnoreCase(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower(*a) != tolower(*b)) {
            return 0;  // Tidak sama
        }
        a++;
        b++;
    }
    return *a == *b;  // Pastikan keduanya berakhir bersama
}

// Menghapus tanda kutip dari string (jika ada)
void cleanQuotes(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (*src != '"') {
            *dst++ = *src;  // Salin karakter kecuali tanda kutip
        }
        src++;
    }
    *dst = '\0';  // Tambahkan null-terminator
}

// Mengecek apakah kata adalah stopword (mengabaikan kapitalisasi)
int isStopWord(const char *word, StopwordNode *stopwords) {
    StopwordNode *curr = stopwords;
    while (curr != NULL) {
        if (compareIgnoreCase(curr->word, word)) return 1;
        curr = curr->next;
    }
    return 0;
}

// Mencari FieldNode berdasarkan nama field (tanpa kapitalisasi sensitif)
FieldNode *cariField(FieldNode *head, const char *fieldName) {
    while (head != NULL) {
        if (compareIgnoreCase(head->fieldName, fieldName)) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

// Membuat KeywordNode baru dan menambahkannya ke akhir list
void tambahKeyword(KeywordNode **head, const char *word) {
    KeywordNode *baru = malloc(sizeof(KeywordNode));
    baru->keyword = strdup(word);  // Duplikat kata
    baru->next = NULL;

    if (*head == NULL) {
        *head = baru;  // Langsung jadi head
    } else {
        KeywordNode *temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = baru;
    }
}

// Membuat PaperNode dari judul dan menambahkan keyword yang bukan stopword
PaperNode *buatPaper(const char *title, int inCitations, int year, StopwordNode *stopwords) {
    PaperNode *p = malloc(sizeof(PaperNode));
    p->title = strdup(title);
    p->inCitations = inCitations;
    p->year = year;
    p->next = NULL;
    p->keywordList = NULL;

    // Tokenisasi judul untuk ekstrak keyword
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

// Menambahkan PaperNode ke dalam field, dengan urutan berdasarkan inCitations menurun
void tambahPaper(FieldNode *field, PaperNode *newPaper) {
    if (!field || !newPaper) return;

    PaperNode **current = &(field->paperList);

    // Sisipkan berdasarkan urutan descending inCitations
    while (*current && (*current)->inCitations > newPaper->inCitations) {
        current = &((*current)->next);
    }

    newPaper->next = *current;
    *current = newPaper;
}

// Menambahkan FieldNode ke akhir fieldList
void tambahField(FieldNode **head, FieldNode *baru) {
    if (*head == NULL) {
        *head = baru;  // Langsung jadi head
    } else {
        FieldNode *temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = baru;
    }
}

// Membaca file CSV dan membangun struktur FieldNode dan PaperNode
void loadData(const char *filename, FieldNode **fieldList, StopwordNode *stopwords) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Gagal membuka file %s\n", filename);
        return;
    }

    char baris[1024];
    fgets(baris, sizeof(baris), fp); // Lewati baris header CSV

    // Baca setiap baris data
    while (fgets(baris, sizeof(baris), fp)) {
        char field[100], title[300];
        int inCitations, year;

        // Parsing CSV berdasarkan format: field,title,inCitations,year
        int parsed = sscanf(baris, "%99[^,],%299[^,],%d,%d", field, title, &inCitations, &year);
        if (parsed != 4) continue;  // Skip baris rusak

        cleanQuotes(field);
        cleanQuotes(title);

        // Cari field, jika tidak ada buat baru
        FieldNode *f = cariField(*fieldList, field);
        if (!f) {
            f = malloc(sizeof(FieldNode));
            f->fieldName = strdup(field);
            f->paperList = NULL;
            f->next = NULL;
            tambahField(fieldList, f);
        }

        // Buat paper dan tambahkan ke field
        PaperNode *p = buatPaper(title, inCitations, year, stopwords);
        tambahPaper(f, p);
    }

    fclose(fp);
    printf("Data berhasil dimuat!\n");
}
