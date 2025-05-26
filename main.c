#include <stdio.h>
#include <string.h>
#include "../include/parser.h"
#include "../ADTSLL/linkedlist.h"
#include "../include/data_structures.h"
#include "../ADTstack/stack.h"

int main() {
    Stack riwayat;
    initStack(&riwayat);

    address fieldList = NULL;
    loadData("data_tubes_oke.csv", &fieldList); // Ganti sesuai nama file CSV

    int pilihan;
    do {
        printf("\n===== MENU UTAMA =====\n");
        printf("1. Tampilkan semua bidang fieldOfStudy\n");
        printf("2. Tampilkan semua paper dari bidang tertentu\n");
        printf("3. Tampilkan Top N paper terpopuler di bidang tertentu\n");
        printf("4. Cari paper berdasarkan kata kunci dalam judul\n");
        printf("5. Cari paper berdasarkan tahun publikasi\n");
        printf("6. Lihat riwayat pencarian\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar(); // hapus newline

        switch (pilihan) {
            case 1: {
                printf("\n📂 Daftar Bidang (fieldOfStudy):\n");
                address temp = fieldList;
                while (temp != NULL) {
                    FieldNode *f = (FieldNode *)temp->info;
                    printf("- %s\n", f->fieldName);
                    temp = temp->next;
                }
                break;
            }

            case 2: {
                char cari[100];
                printf("Masukkan fieldOfStudy: ");
                fgets(cari, sizeof(cari), stdin);
                cari[strcspn(cari, "\n")] = '\0';

                FieldNode *target = cariField(fieldList, cari);
                if (!target) {
                    printf("❌ Field '%s' tidak ditemukan.\n", cari);
                } else {
                    printf("\n📄 Daftar Paper dalam bidang: %s\n", cari);
                    inorderPrint(target->bstRoot);

                    // simpan riwayat
                    char *riwayatStr = (char *)malloc(strlen(cari) + 20);
                    sprintf(riwayatStr, "Field: %s", cari);
                    push(&riwayat, riwayatStr);
                }
                break;
            }

            case 3: {
                char cari[100];
                int jumlah;
                printf("Masukkan fieldOfStudy: ");
                fgets(cari, sizeof(cari), stdin);
                cari[strcspn(cari, "\n")] = '\0';

                printf("Masukkan jumlah paper teratas: ");
                scanf("%d", &jumlah);
                getchar();

                int jumlahAsli = jumlah; // ⬅️ Simpan sebelum dikurangi

                FieldNode *target = cariField(fieldList, cari);
                if (!target) {
                    printf("❌ Field '%s' tidak ditemukan.\n", cari);
                } else {
                    printf("\n🔥 Top %d paper dalam bidang %s:\n", jumlahAsli, target->fieldName);
                    printTopN(target->bstRoot, &jumlah);

                    char riwayatTop[120];
                    sprintf(riwayatTop, "Top %d - %s", jumlahAsli, cari);  // ⬅️ Gunakan nilai asli
                    push(&riwayat, strdup(riwayatTop));
                }
                break;
            }


            case 4: {
                char keyword[100];
                printf("Masukkan kata kunci: ");
                fgets(keyword, sizeof(keyword), stdin);
                keyword[strcspn(keyword, "\n")] = '\0';

                printf("\n🔍 Hasil pencarian untuk kata: \"%s\"\n", keyword);
                address temp = fieldList;
                while (temp != NULL) {
                    FieldNode *f = (FieldNode *)temp->info;
                    searchPaperByKeyword(f->bstRoot, keyword);
                    temp = temp->next;
                }

                char riwayatKeyword[120];
                sprintf(riwayatKeyword, "Keyword: %s", keyword);
                push(&riwayat, strdup(riwayatKeyword));
                break;
            }

            case 5: {
                int targetYear;
                printf("Masukkan tahun publikasi: ");
                scanf("%d", &targetYear);
                getchar();

                printf("\n📆 Paper tahun %d:\n", targetYear);
                address temp = fieldList;
                while (temp != NULL) {
                    FieldNode *f = (FieldNode *)temp->info;
                    searchPaperByYear(f->bstRoot, targetYear);
                    temp = temp->next;
                }

                char riwayatTahun[50];
                sprintf(riwayatTahun, "Tahun: %d", targetYear);
                push(&riwayat, strdup(riwayatTahun));
                break;
            }

            case 6: {
                printf("\n Riwayat Pencarian:\n");
                printStack(&riwayat);
                break;
            }

            case 0:
                printf("Terima kasih telah menggunakan aplikasi!\n");
                break;

            default:
                printf("❌ Pilihan tidak valid.\n");
        }

    } while (pilihan != 0);

    return 0;
}
