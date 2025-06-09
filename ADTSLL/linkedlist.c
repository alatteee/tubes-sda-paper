#include "linkedlist.h"

// Fungsi untuk membuat node baru dengan nilai yang diberikan
address buatNode(infotype nilai) {
    address newNode = (address)malloc(sizeof(Node));  // Alokasi memori untuk node baru
    if (newNode != NULL) {  // Jika alokasi berhasil
        newNode->info = nilai;     // Mengisi field info dengan nilai yang diberikan
        newNode->next = NULL;      // Menetapkan pointer next ke NULL karena ini node tunggal/belum dihubungkan
    }
    return newNode;  // Mengembalikan alamat node baru (bisa NULL jika malloc gagal)
}

// Fungsi untuk menambahkan node di akhir linked list
void addAkhir(address *head, infotype nilai) {
    address newNode = buatNode(nilai);  // Membuat node baru dengan nilai yang diberikan
    if (*head == NULL) {  // Jika list masih kosong
        *head = newNode;  // Node baru menjadi head dari list
    } else {
        address temp = *head;  // Mulai dari head
        while (temp->next != NULL) {  // Iterasi sampai node terakhir
            temp = temp->next;
        }
        temp->next = newNode;  // Hubungkan node terakhir dengan node baru
    }
}

// Fungsi untuk menampilkan seluruh isi linked list
void tampilList(address head) {
    address temp = head;  // Mulai dari head
    while (temp != NULL) {
        printf("%s -> ", (char *)temp->info);  // Menampilkan nilai info, diasumsikan sebagai string
    }
    printf("NULL\n");  // Akhiri tampilan list dengan NULL
}


