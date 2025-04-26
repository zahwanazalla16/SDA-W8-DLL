#include "DLL.h"



// Modul untuk inisialisasi array kota
void initArrayKota(ArrayKota *arr, int batas) {
    arr->data = (Kota *)malloc(batas * sizeof(Kota));
    arr->jumlah = 0;
    arr->batas = batas;
    
    // Inisialisasi elemen array
    for (int i = 0; i < batas; i++) {
        arr->data[i].Kota = NULL;
        arr->data[i].warga = NULL;
        arr->data[i].last = NULL; // Inisialisasi pointer last untuk DLL
    }
}

// Modul untuk menambahkan kota 
void masukkanKota(ArrayKota *arr, const char *namaKota) {
    // Cek apakah kota sudah ada
    if (cariKota(arr, namaKota)) {
        printf("Kota %s sudah ada dalam daftar!\n", namaKota);
        return;
    }

    // Cek apakah array sudah penuh
    if (arr->jumlah >= arr->batas) {
        // Menambah alokasi array jika penuh
        arr->batas *= 2;
        arr->data = (Kota *)realloc(arr->data, arr->batas * sizeof(Kota));

        // Inisialisasi elemen baru
        for (int i = arr->jumlah; i < arr->batas; i++) {
            arr->data[i].Kota = NULL;
            arr->data[i].warga = NULL;
            arr->data[i].last = NULL; // Inisialisasi pointer last untuk DLL
        }
    }

    int panjangNama = 0;
    while (namaKota[panjangNama] != '\0') {
        panjangNama++;
    }

    arr->data[arr->jumlah].Kota = (char *)malloc((panjangNama + 1) * sizeof(char));
    int j = 0;
    while (namaKota[j] != '\0') {
        arr->data[arr->jumlah].Kota[j] = namaKota[j];
        j++;
    }
    arr->data[arr->jumlah].Kota[j] = '\0';
    arr->data[arr->jumlah].warga = NULL;
    arr->data[arr->jumlah].last = NULL; // Set pointer last ke NULL
    arr->jumlah++;
    printf("Kota %s berhasil ditambahkan!\n", namaKota);
}

// Modul untuk menghapus kota
void hapusKota(ArrayKota *arr, const char *namaKota) {
    int i;
    boolean found = false;
    
    // Mencari kota yang akan dihapus
    for (i = 0; i < arr->jumlah; i++) {
        if (strcmp(arr->data[i].Kota, namaKota) == 0) {
            found = true;
            break;
        }
    }
    
    if (!found) {
        printf("Kota %s tidak ditemukan!\n", namaKota);
        return;
    }
    hapusDataNama(&arr->data[i]); // Hapus semua data warga di kota tersebut
    free(arr->data[i].Kota); // Hapus nama kota
    
    // Menggeser data setelah dihapus
    for (int j = i; j < arr->jumlah - 1; j++) { 
        arr->data[j] = arr->data[j + 1];
    } 
    // Kurangi jumlah data
    arr->jumlah--;
    
    printf("Kota %s berhasil dihapus!\n", namaKota);
}

// Implementasi fungsi cariKota
boolean cariKota(ArrayKota *arr, const char *namaKota) {
    for (int i = 0; i < arr->jumlah; i++) {
        if (strcmp(arr->data[i].Kota, namaKota) == 0) {
            return true;
        }
    }
    return false;
}

// Implementasi fungsi masukkanNama untuk double linked list
void masukkanNama(Kota *kota, const char *warga) {
    // Alokasi node baru
    addressWg newNode = (addressWg)malloc(sizeof(Warga));
    int length = strlen(warga);
    newNode->nama = (char *)malloc((length + 1) * sizeof(char));
    strcpy(newNode->nama, warga);
    newNode->next = NULL;
    newNode->prev = NULL;  // Set prev pointer ke NULL
    
    // Jika linked list kosong
    if (kota->warga == NULL) {
        kota->warga = newNode;
        kota->last = newNode;  // Set last pointer ke node baru
    } else {
        // Tambahkan di akhir list (menggunakan pointer last untuk efisiensi)
        newNode->prev = kota->last;  // Set prev ke node terakhir saat ini
        kota->last->next = newNode;  // Update next dari node terakhir
        kota->last = newNode;        // Update pointer last ke node baru
    }
    
    printf("Warga %s berhasil ditambahkan di kota %s!\n", warga, kota->Kota);
}


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
