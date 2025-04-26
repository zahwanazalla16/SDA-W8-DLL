#include "DLL.h"



// isi disini



// Implementasi fungsi hapusNama untuk double linked list
void hapusNama(Kota *kota, const char *warga) {
    addressWg current = kota->warga;
    boolean found = false;
    
    // Cari warga yang akan dihapus
    while (current != NULL) {
        if (strcmp(current->nama, warga) == 0) {
            found = true;
            break;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("Warga %s tidak ditemukan di kota %s!\n", warga, kota->Kota);
        return;
    }
    
    // Jika node yang dihapus adalah node pertama
    if (current->prev == NULL) {
        kota->warga = current->next;
        if (kota->warga != NULL) {
            kota->warga->prev = NULL;
        } else {
            // Jika list menjadi kosong
            kota->last = NULL;
        }
    } 
    // Jika node yang dihapus adalah node terakhir
    else if (current->next == NULL) {
        kota->last = current->prev;
        current->prev->next = NULL;
    }
    // Jika node yang dihapus berada di tengah
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    
    // Hapus node
    free(current->nama);
    free(current);
    
    printf("Warga %s berhasil dihapus dari kota %s!\n", warga, kota->Kota);
}

// Implementasi fungsi tampilanKota
void tampilanKota(ArrayKota arr) {
    printf("Daftar Kota:\n");
    for (int i = 0; i < arr.jumlah; i++) {
        printf("%d. %s\n", i+1, arr.data[i].Kota);
    }
}

// Implementasi fungsi tampilanNama
void tampilanNama(Kota *kota) {
    printf("Daftar Warga di Kota %s:\n", kota->Kota);
    addressWg current = kota->warga;
    int nomor = 1;
    
    if (current == NULL) {
        printf("Tidak ada warga terdaftar.\n");
        return;
    }
    
    while (current != NULL) {
        printf("%d. %s\n", nomor++, current->nama);
        current = current->next;
    }
}

// Modul untuk menghapus semua data nama di kota
void hapusDataNama(Kota *kota) {
    addressWg current = kota->warga;
    addressWg temp;
    
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->nama);
        free(temp);
    }
    
    kota->warga = NULL;
    kota->last = NULL;  // Reset pointer last
}

// Modul untuk menghapus semua data kota
void HapusDataKota(ArrayKota *arr) {
    for (int i = 0; i < arr->jumlah; i++) {
        hapusDataNama(&arr->data[i]);
        free(arr->data[i].Kota);
    }
    free(arr->data);
    arr->data = NULL;
    arr->jumlah = 0;
    arr->batas = 0;
}
