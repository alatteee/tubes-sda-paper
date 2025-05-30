#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "../include/data_structures.h"
#include "../ADTstack/stack.h"
#include "../include/stopwords.h"
#include "../include/menu_handler.h"

int main() {
    Stack riwayat;
    initStack(&riwayat);

    FieldNode *fieldList = NULL;
    StopwordNode *stopwords = NULL;
    loadStopwords("stopwords.txt", &stopwords);
    loadData("data_tubes_clean.csv", &fieldList, stopwords);

    int pilihan;
    do {
        printf("\n===== MENU UTAMA =====\n");
        printf("1. Tampilkan semua bidang fieldOfStudy\n");
        printf("2. Telusuri FieldOfStudy tertentu\n");
        printf("3. Lihat riwayat pencarian\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1:
                tampilkanSemuaField(fieldList);
                push(&riwayat, strdup("Lihat semua fieldOfStudy"));
                break;
            case 2:
                menuField(fieldList, &riwayat, stopwords);
                break;
            case 3:
                printf("\n Riwayat Pencarian:\n");
                printStack(&riwayat);
                break;
            case 0:
                printf("Terima kasih telah menggunakan aplikasi!\n");
                break;
            default:
                printf(" Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);

    return 0;
}
