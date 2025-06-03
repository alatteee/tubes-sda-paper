#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "data_structures.h"
#include "../ADTstack/stack.h"

void tampilkanSemuaField(FieldNode *fieldList);
void menuField(FieldNode *fieldList, Stack *riwayat, StopwordNode *stopwords);
void submenuField(FieldNode *target, Stack *riwayat, StopwordNode *stopwords);
void cariKeyword(PaperNode *paperList, const char *keyword, StopwordNode *stopwords);
void tampilSemuaPaper(PaperNode *paperList);
void tampilTopNPaper(PaperNode *paperList, int n);
void cariTahun(PaperNode *paperList, int tahun);
void tampilkanRiwayat(Stack *riwayat);

#endif
