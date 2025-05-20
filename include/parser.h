#ifndef PARSER_H
#define PARSER_H

#include "data_structures.h"
#include "../ADTSLL/linkedlist.h"

void loadData(const char *filename, address *fieldList);
void inorderPrint(Paper *root);
FieldNode *cariField(address head, const char *fieldName);
void printTopN(Paper *root, int *n);
void searchPaperByKeyword(Paper *root, const char *keyword);
void searchPaperByYear(Paper *root, int targetYear);




#endif
