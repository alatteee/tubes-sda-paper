#ifndef PARSER_H
#define PARSER_H

#include "data_structures.h"

// Membaca file CSV dan membangun struktur FieldNode → PaperNode → KeywordNode
void loadData(const char *filename, FieldNode **fieldList, StopwordNode *stopwords);

// Cari Field berdasarkan nama (case-insensitive)
FieldNode *cariField(FieldNode *head, const char *fieldName);

// Bandingkan 2 string tanpa memperhatikan kapital
int compareIgnoreCase(const char *a, const char *b);

// Bersihkan tanda kutip dari string (jika ada)
void cleanQuotes(char *str);

// Tambahkan Paper ke akhir list PaperNode
void tambahPaper(PaperNode **head, PaperNode *baru);

// Tambahkan Field ke akhir list FieldNode
void tambahField(FieldNode **head, FieldNode *baru);

// Tambahkan Keyword ke akhir list KeywordNode
void tambahKeyword(KeywordNode **head, const char *word);

// Cek apakah kata termasuk dalam daftar stopword
int isStopWord(const char *word, StopwordNode *stopwords);

#endif
