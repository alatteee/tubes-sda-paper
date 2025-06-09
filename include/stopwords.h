#ifndef STOPWORDS_H
#define STOPWORDS_H

#include "data_structures.h"

// Fungsi untuk memuat stopword dari file eksternal ke dalam linked list StopwordNode
void loadStopwords(const char *filename, StopwordNode **head);

#endif
