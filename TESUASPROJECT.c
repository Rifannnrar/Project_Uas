#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TRIES 3
#define MAX_COURSES 10
#define MAX_STUDENTS 50

typedef struct {
    char nama[50];
    float nilai[MAX_COURSES];
    int sks[MAX_COURSES];  // Array untuk menyimpan bobot SKS setiap mata kuliah
    int jumlah_mk;
} Mahasiswa;

void login() {
    const char dosen_benar[] = "normaningsih";
    const char password_benar[] = "dosen12";
    char input_dosen[100];
    char input_password[100];
    int percobaan = 0;

    while (percobaan < MAX_TRIES) {
        printf("Masukkan Dosen: ");
        scanf("%s", input_dosen);
        printf("Masukkan Password: ");
        scanf("%s", input_password);

        if (strcmp(input_dosen, dosen_benar) == 0 && strcmp(input_password, password_benar) == 0) {
            printf("Login berhasil!\n");
            return;
        } else {
            printf("Dosen atau password salah. Coba lagi.\n");
            percobaan++;
        }
    }

    printf("Terlalu banyak percobaan yang salah. Anda diblokir.\n");
    exit(0);
}

void inputNilai(Mahasiswa mahasiswa[], int jumlah_mahasiswa) {
    for (int i = 0; i < jumlah_mahasiswa; i++) {
        printf("Memasukkan nilai untuk %s\n", mahasiswa[i].nama);
        printf("Masukkan jumlah mata kuliah: ");
        scanf("%d", &mahasiswa[i].jumlah_mk);

        for (int j = 0; j < mahasiswa[i].jumlah_mk; j++) {
            printf("Masukkan nilai untuk mata kuliah %d: ", j + 1);
            scanf("%f", &mahasiswa[i].nilai[j]);
            printf("Masukkan bobot SKS untuk mata kuliah %d: ", j + 1);
            scanf("%d", &mahasiswa[i].sks[j]);
        }
    }
}

float hitungIPS(float nilai[], int sks[], int jumlah_mk) {
    float total_nilai = 0.0;
    int total_sks = 0;
    for (int i = 0; i < jumlah_mk; i++) {
        total_nilai += nilai[i] * sks[i];
        total_sks += sks[i];
    }

    float rataRata = total_nilai / total_sks;

    // Konversi rata-rata ke indeks nilai menggunakan if-else
    if (rataRata >= 81.0) return 4.0;   // 81-100
    if (rataRata >= 61.0) return 3.0 + (rataRata - 60) / 20.0;   // 61-80
    if (rataRata >= 41.0) return 2.0 + (rataRata - 40) / 20.0;   // 41-60
    if (rataRata >= 21.0) return 1.0 + (rataRata - 20) / 20.0;   // 21-40
    return rataRata / 20.0;                      // 0-20
}

int main() {
    Mahasiswa mahasiswa[MAX_STUDENTS];
    int jumlah_mahasiswa;

    login();

    printf("Masukkan jumlah mahasiswa: ");
    scanf("%d", &jumlah_mahasiswa);

    for (int i = 0; i < jumlah_mahasiswa; i++) {
        printf("Masukkan nama mahasiswa %d: ", i + 1);
        scanf("%s", mahasiswa[i].nama);
    }

    inputNilai(mahasiswa, jumlah_mahasiswa);

    for (int i = 0; i < jumlah_mahasiswa; i++) {
        float ips = hitungIPS(mahasiswa[i].nilai, mahasiswa[i].sks, mahasiswa[i].jumlah_mk);
        printf("IPS dari %s: %.2f\n", mahasiswa[i].nama, ips);
    }

    return 0;
}
