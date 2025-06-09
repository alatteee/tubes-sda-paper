#include "stack.h"

// Inisialisasi stack dengan top di-set ke NULL
void initStack(Stack *s) {
    s->top = NULL;  // Stack kosong pada awalnya
}

// Fungsi untuk menambahkan elemen ke atas stack
void push(Stack *s, infotype nilai) {
    address newNode = buatNode(nilai);  // Buat node baru dengan nilai yang diberikan
    newNode->next = s->top;             // Node baru menunjuk ke elemen teratas saat ini
    s->top = newNode;                   // Node baru menjadi elemen teratas
}

// Fungsi untuk menghapus dan mengembalikan elemen teratas dari stack
infotype pop(Stack *s) {
    if (s->top == NULL) {  // Cek apakah stack kosong
        printf("Stack kosong!\n");
        return NULL;       // Jika kosong, kembalikan NULL (asumsi infotype adalah pointer)
    }

    infotype nilai = s->top->info;  // Simpan nilai elemen teratas
    address temp = s->top;          // Simpan alamat node teratas untuk dibebaskan
    s->top = s->top->next;          // Geser top ke node berikutnya
    free(temp);                     // Bebaskan memori node sebelumnya
    return nilai;                   // Kembalikan nilai dari node yang di-pop
}

// Fungsi untuk memeriksa apakah stack kosong
bool isStackEmpty(Stack *s) {
    return (s->top == NULL);  // Mengembalikan true jika stack kosong
}

// Fungsi untuk mencetak isi stack dari atas ke bawah
void printStack(Stack *s) {
    address temp = s->top;  // Mulai dari top
    while (temp != NULL) {
        printf("%s -> ", (char *)temp->info);  // Tampilkan info node, diasumsikan bertipe string
        temp = temp->next;                     // Lanjut ke node berikutnya
    }
    printf("NULL\n");  // Penanda akhir stack
}

