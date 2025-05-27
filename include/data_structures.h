#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// KeywordNode: anak dari PaperNode
typedef struct KeywordNode {
    char *keyword;
    struct KeywordNode *next;
} KeywordNode;

// PaperNode: anak dari FieldNode
typedef struct PaperNode {
    char *title;
    int inCitations;
    int year;
    KeywordNode *keywordList;
    struct PaperNode *next;
} PaperNode;

// FieldNode: anak dari Root FieldOfStudy
typedef struct FieldNode {
    char *fieldName;
    PaperNode *paperList;
    struct FieldNode *next;
} FieldNode;

// StopwordNode: untuk menyimpan daftar stopwords (jika mau pakai linked list)
typedef struct StopwordNode {
    char *word;
    struct StopwordNode *next;
} StopwordNode;

#endif
