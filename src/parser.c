#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // untuk tolower
#include "data_structures.h"
#include "../ADTSLL/linkedlist.h"

// Fungsi untuk membuat Paper
Paper *buatPaper(const char *title, int inCitations, int year) {
    Paper *p = (Paper *)malloc(sizeof(Paper));
    p->title = strdup(title);
    p->inCitations = inCitations;
    p->year = year;
    p->left = p->right = NULL;
    return p;
}

// Fungsi insert ke BST (berdasarkan inCitations)
Paper *insertPaper(Paper *root, Paper *newPaper) {
    if (!root) return newPaper;
    if (newPaper->inCitations < root->inCitations)
        root->left = insertPaper(root->left, newPaper);
    else
        root->right = insertPaper(root->right, newPaper);
    return root;
}

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

// Cari FieldNode di linked list
FieldNode *cariField(address head, const char *fieldName) {
    address temp = head;
    while (temp != NULL) {
        FieldNode *f = (FieldNode *)temp->info;
        if (compareIgnoreCase(f->fieldName, fieldName)) {
            return f;
        }
        temp = temp->next;
    }
    return NULL;
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

// Load CSV dan bangun struktur data
void loadData(const char *filename, address *fieldList) {
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

        cleanQuotes(field);  // hapus " di dalam fieldName

        FieldNode *f = cariField(*fieldList, field);
        if (!f) {
            f = (FieldNode *)malloc(sizeof(FieldNode));
            f->fieldName = strdup(field);
            f->bstRoot = NULL;
            addAkhir(fieldList, f);
        }

        Paper *p = buatPaper(title, inCitations, year);
        f->bstRoot = insertPaper(f->bstRoot, p);
    }

    fclose(fp);
    printf("Data berhasil dimuat!\n");
}

void inorderPrint(Paper *root) {
    if (!root) return;
    inorderPrint(root->left);
    printf("- \"%s\" (%d sitasi, %d)\n", root->title, root->inCitations, root->year);
    inorderPrint(root->right);
}

void printTopN(Paper *root, int *n) {
    if (!root || *n <= 0) return;

    printTopN(root->right, n);

    if (*n > 0) {
        printf("- \"%s\" (%d sitasi, %d)\n", root->title, root->inCitations, root->year);
        (*n)--;
    }

    printTopN(root->left, n);
}

void searchPaperByKeyword(Paper *root, const char *keyword) {
    if (!root) return;

    searchPaperByKeyword(root->left, keyword);

    if (strstr(root->title, keyword) != NULL) {
        printf("- \"%s\" (%d sitasi, %d)\n", root->title, root->inCitations, root->year);
    }

    searchPaperByKeyword(root->right, keyword);
}

void searchPaperByYear(Paper *root, int targetYear) {
    if (!root) return;

    searchPaperByYear(root->left, targetYear);

    if (root->year == targetYear) {
        printf("- \"%s\" (%d sitasi, %d)\n", root->title, root->inCitations, root->year);
    }

    searchPaperByYear(root->right, targetYear);
}
