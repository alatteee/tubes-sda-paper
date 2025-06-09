#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "../include/data_structures.h"
#include "../ADTstack/stack.h"
#include "../include/stopwords.h"
#include "../include/menu_handler.h"

int main() {
    Stack riwayat;               // Stack untuk menyimpan riwayat interaksi user
    initStack(&riwayat);         // Inisialisasi stack

    FieldNode *fieldList = NULL;       // Linked list untuk semua bidang studi
    StopwordNode *stopwords = NULL;    // Linked list stopwords

    // Load daftar stopwords dari file
    loadStopwords("stopwords.txt", &stopwords);

    // Load data paper dan field dari file CSV
    loadData("data_tubes_clean.csv", &fieldList, stopwords);

    int pilihan;  // Variabel untuk menyimpan input pilihan menu
    do {
        // Tampilkan menu utama
        printf("=========================================\n");
        printf("                MENU UTAMA               \n");
        printf("=========================================\n");
        printf("1. Tampilkan semua bidang fieldOfStudy\n");
        printf("2. Telusuri FieldOfStudy tertentu\n");
        printf("3. Lihat riwayat pencarian\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar();  // Menangkap newline agar tidak terbawa ke input berikutnya

        switch (pilihan) {
            case 1:
                // Tampilkan semua field dan simpan ke riwayat
                tampilkanSemuaField(fieldList);
                push(&riwayat, strdup("Lihat semua fieldOfStudy"));
                break;
            case 2:
                // Telusuri detail field tertentu
                menuField(fieldList, &riwayat, stopwords);
                break;
            case 3:
                // Tampilkan riwayat pencarian pengguna
                tampilkanRiwayat(&riwayat);
                break;
            case 0:
                // Keluar dari aplikasi
                printf("Terima kasih telah menggunakan aplikasi!\n");
                break;
            default:
                printf(" Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);  // Ulangi hingga user memilih keluar

    return 0;  // Program selesai
}
