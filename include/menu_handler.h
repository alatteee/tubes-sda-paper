#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "data_structures.h"
#include "stack.h"

void tampilkanSemuaField(FieldNode *fieldList);
void menuField(FieldNode *fieldList, Stack *riwayat);
void submenuField(FieldNode *target, Stack *riwayat);
void tampilSemuaPaper(PaperNode *paperList);
void tampilTopNPaper(PaperNode *paperList, int n);
void cariKeyword(PaperNode *paperList, const char *keyword);
void cariTahun(PaperNode *paperList, int tahun);

#endif
