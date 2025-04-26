#include "DLL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int pilihan;
    char namaKota[MAX_NAME_LENGTH];
    char namaWarga[MAX_NAME_LENGTH];
    int indeksKota;
    
    // Inisialisasi array kota
    ArrayKota daftarKota;
    initArrayKota(&daftarKota, 10); // Init dengan batas 10
    
    // Menambahkan 5 kota di awal program
    masukkanKota(&daftarKota, "Bandung");
    masukkanKota(&daftarKota, "Jakarta");
    masukkanKota(&daftarKota, "Bogor");
    masukkanKota(&daftarKota, "Cimahi");
    masukkanKota(&daftarKota, "Padalarang");
    
    // Menambahkan warga di kota nya
    masukkanNama(&daftarKota.data[0], "Zahwa");
    masukkanNama(&daftarKota.data[0], "Nazala");
    masukkanNama(&daftarKota.data[1], "Suci");
    masukkanNama(&daftarKota.data[2], "Sulistiawati");
    masukkanNama(&daftarKota.data[3], "Zena");
    //kota ke 5 kami buat belum ada warga
    do {
        system("cls"); // Untuk Windows
        // Gunakan system("clear") untuk Linux/Mac
        
        /* Menampilkan daftar kota dan warga */
        printf("=================================\n");
        printf("        DATA KOTA & WARGA        \n");
        printf("=================================\n");
        
        for (int i = 0; i < daftarKota.jumlah; i++) {
            printf("%d. Kota %s\n", i+1, daftarKota.data[i].Kota);
            
            // Menampilkan warga di kota ini
            addressWg current = daftarKota.data[i].warga;
            
            if (current == NULL) {
                printf("   - Tidak ada warga\n");
            } else {
                while (current != NULL) {
                    printf("   - %s\n", current->nama);
                    current = current->next;
                }
            }
            printf("\n");
        }
        
        printf("=================================\n");
        printf("             M E N U            \n");
        printf("=================================\n");
        printf("1. Tambah Kota\n");
        printf("2. Hapus Kota\n");
        printf("3. Tambah Warga\n");
        printf("4. Hapus Warga\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar(); // Mengambil karakter newline setelah input angka
        
        switch(pilihan) {
            case 1: // Tambah kota
                printf("Masukkan nama kota baru: ");
                fgets(namaKota, MAX_NAME_LENGTH, stdin);
                namaKota[strcspn(namaKota, "\n")] = 0; // Menghapus newline dari input
                masukkanKota(&daftarKota, namaKota);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 2: // Hapus kota
                printf("Masukkan nama kota yang akan dihapus: ");
                fgets(namaKota, MAX_NAME_LENGTH, stdin);
                namaKota[strcspn(namaKota, "\n")] = 0; // Menghapus newline dari input
                hapusKota(&daftarKota, namaKota);
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 3: // Tambah warga di suatu kota
                // Menampilkan daftar kota
                tampilanKota(daftarKota);
                printf("Pilih nomor kota (1-%d): ", daftarKota.jumlah);
                scanf("%d", &indeksKota);
                getchar(); // Mengambil karakter newline
                
                if (indeksKota < 1 || indeksKota > daftarKota.jumlah) {
                    printf("Nomor kota tidak valid!\n");
                } else {
                    printf("Masukkan nama warga baru: ");
                    fgets(namaWarga, MAX_NAME_LENGTH, stdin);
                    namaWarga[strcspn(namaWarga, "\n")] = 0; // Menghapus newline dari input
                    masukkanNama(&daftarKota.data[indeksKota-1], namaWarga);
                }
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 4: // Hapus nama warga di suatu kota
                // Menampilkan daftar kota
                tampilanKota(daftarKota);
                printf("Pilih nomor kota (1-%d): ", daftarKota.jumlah);
                scanf("%d", &indeksKota);
                getchar(); // Mengambil karakter newline
                
                if (indeksKota < 1 || indeksKota > daftarKota.jumlah) {
                    printf("Nomor kota tidak valid!\n");
                } else {
                    // Menampilkan daftar warga di kota tersebut
                    tampilanNama(&daftarKota.data[indeksKota-1]);
                    printf("Masukkan nama warga yang akan dihapus: ");
                    fgets(namaWarga, MAX_NAME_LENGTH, stdin);
                    namaWarga[strcspn(namaWarga, "\n")] = 0; // Menghapus newline dari input
                    hapusNama(&daftarKota.data[indeksKota-1], namaWarga);
                }
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                break;
                
            case 0: // Keluar
                printf("Terima kasih telah menggunakan program ini!\n");
                // Hapus semua data sebelum keluar
                HapusDataKota(&daftarKota);
                break;
                
            default:
                printf("Pilihan tidak valid!\n");
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
        }
        
    } while (pilihan != 0);
    
    return 0;
}