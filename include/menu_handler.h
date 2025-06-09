#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "data_structures.h"
#include "../ADTstack/stack.h"

// Menampilkan semua field of study yang tersedia
void tampilkanSemuaField(FieldNode *fieldList);

// Menangani menu utama untuk memilih field
void menuField(FieldNode *fieldList, Stack *riwayat, StopwordNode *stopwords);

// Menangani submenu setelah sebuah field dipilih
void submenuField(FieldNode *target, Stack *riwayat, StopwordNode *stopwords);

// Mencari paper yang mengandung keyword tertentu
void cariKeyword(PaperNode *paperList, const char *keyword, StopwordNode *stopwords);

// Menampilkan seluruh paper dalam sebuah field
void tampilSemuaPaper(PaperNode *paperList);

// Menampilkan N paper teratas berdasarkan kriteria (kemungkinan besar inCitations)
void tampilTopNPaper(PaperNode *paperList, int n);

// Mencari dan menampilkan paper berdasarkan tahun terbit
void cariTahun(PaperNode *paperList, int tahun);

// Menampilkan riwayat pencarian/interaksi yang tersimpan dalam stack
void tampilkanRiwayat(Stack *riwayat);

#endif
