#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// Struktur Paper (untuk BST per bidang)
typedef struct Paper {
    char *title;
    int inCitations;
    int year;
    struct Paper *left;
    struct Paper *right;
} Paper;

// Struktur FieldNode (disimpan dalam linked list)
typedef struct {
    char *fieldName;
    Paper *bstRoot;
} FieldNode;

#endif
