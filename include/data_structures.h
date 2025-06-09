#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// KeywordNode: anak dari PaperNode
typedef struct KeywordNode {
    char *keyword;                   // Menyimpan keyword (kata kunci) dari sebuah paper
    struct KeywordNode *next;       // Pointer ke keyword berikutnya (membentuk linked list)
} KeywordNode;

// PaperNode: anak dari FieldNode
typedef struct PaperNode {
    char *title;                    // Menyimpan judul paper
    int inCitations;               // Menyimpan jumlah sitasi masuk
    int year;                      // Menyimpan tahun publikasi paper
    KeywordNode *keywordList;      // Pointer ke daftar keyword (linked list KeywordNode)
    struct PaperNode *next;        // Pointer ke paper berikutnya (membentuk linked list)
} PaperNode;

// FieldNode: anak dari Root FieldOfStudy
typedef struct FieldNode {
    char *fieldName;               // Menyimpan nama bidang studi
    PaperNode *paperList;          // Pointer ke daftar paper dalam bidang ini (linked list PaperNode)
    struct FieldNode *next;        // Pointer ke bidang studi berikutnya (membentuk linked list)
} FieldNode;

// StopwordNode: untuk menyimpan daftar stopwords (jika mau pakai linked list)
typedef struct StopwordNode {
    char *word;                    // Menyimpan satu stopword
    struct StopwordNode *next;     // Pointer ke stopword berikutnya (membentuk linked list)
} StopwordNode;


#endif
