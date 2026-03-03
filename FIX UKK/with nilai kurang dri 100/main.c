#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

typedef struct{
    char nama[50];
    int nis;
    char kelas[20];
    char sekolah[20];
}Siswa;

typedef struct{
    char mapel[50];
    int kkm;
    int nilai;
    char status[15];
}Mapel;

void tampilMapel(Mapel m[]);
int inputAngka();
void simpanFile(Siswa s, Mapel m[], float rata, char predikat);

void tampilMapel(Mapel m[]) {
    printf("============================================\n");
    printf("| %-3s | %-15s | %-5s |\n", "No", "Mata Pelajaran", "KKM");
    printf("--------------------------------------------\n");

    for(int i=0; i<MAX; i++)
        printf("| %-3d | %-15s | %-5d |\n", i+1, m[i].mapel, m[i].kkm);
    printf("============================================\n");
}

int inputAngka() {
    int x;

    while(scanf("%d", &x)!=1){
        printf("Masukkan angka yang sesuai : \n");
        while(getchar()!='\n');
    }
    return x;
}

int main(){
    Mapel m[MAX]={
        {"DDPK", 75},
        {"PPKN", 75},
        {"KIK", 75},
        {"KKPW", 75},
        {"KKPG", 75}
    };

    Siswa s;
    char pilih;
    int i,total;
    float rata;
    char predikat;

    tampilMapel(m);

    //input identitas
    printf("\n========== INPUT IDENTITAS SISWA ==========\n");
    printf("Nama     : "); scanf("%[^\n]", s.nama);
    printf("NIS      : "); s.nis=inputAngka();
    printf("Kelas    : "); scanf(" %[^\n]", s.kelas);
    printf("Sekolah  : "); scanf(" %[^\n]", s.sekolah);

    do{
        total = 0;

        printf("\n========== INPUT NILAI ==========\n");
        for(i=0; i<MAX; i++) {
            do{
                printf("Nilai %s : ", m[i].mapel);
                m[i].nilai = inputAngka();

                if(m[i].nilai < 0 || m[i].nilai > 100){
                    printf("Nilai harus antara 0 - 100!\n");
                }

            }while(m[i].nilai < 0 || m[i].nilai > 100);

            total += m[i].nilai;

            if(m[i].nilai >= m[i].kkm)
                strcpy(m[i].status, "Lulus");
            else
                strcpy(m[i].status, "Tidak Lulus");
        }

        rata=(float)total/MAX;

        if(rata >= 90) predikat='A';
        else if (rata >= 80) predikat='B';
        else if (rata >= 70) predikat='C';
        else if (rata >= 60) predikat='D';
        else predikat='E';

        printf("\n========== HASIL RAPOT ==========\\n");
        printf("Nama     : ", s.nama);
        printf("NIS      : ", s.nis);
        printf("Kelas    : ", s.kelas);
        printf("Sekolah  : ", s.sekolah);

        printf("\n============================================\n");
        printf("| %-3s | %-15s | %-5s | %-10s |\n", "No", "Mata Pelajaran", "Nilai", "Status");
        printf("\n--------------------------------------------\n");

        for(int i=0; i<MAX; i++) {
            printf("| %-3d | %-15s | %-5d | %-10s |\n", i+1, m[i].mapel, m[i].nilai, m[i].status);
        }
        printf("============================================\n");
        printf("| %-20s | %-20s |\n", "RATA RATA", "PREDIKAT");
        printf("--------------------------------------------\n");
        printf("| %-20.2f | %-20c |\n", rata, predikat);
        printf("============================================\n");

        printf("\nTekan Y jika data sudah sesuai\n");
        printf("Tekan N jika data belum sesuai \n");
        printf("\nMasukkan pilihan anda (Y/N) : ");
        scanf(" %c", &pilih);

    }while(pilih=='n'||pilih=='N');

    if(pilih=='y'||pilih=='Y'){
        simpanFile(s,m,rata,predikat);
        printf("\nFile Berhasil Disimpan!!\n");
    }
    return 0;
}

void simpanFile(Siswa s, Mapel m[], float rata, char predikat){
    char file[30];
    sprintf(file, "raport_%d.txt", s.nis);

    FILE *fp=fopen(file, "w");

    fprintf(fp,"\n========== HASIL RAPOT ==========\n");
    fprintf(fp,"Nama     : %s\n", s.nama);
    fprintf(fp,"NIS      : %d\n", s.nis);
    fprintf(fp,"Kelas    : %s\n", s.kelas);
    fprintf(fp,"Sekolah  : %s\n", s.sekolah);

    fprintf(fp,"\n============================================\n");
    fprintf(fp,"| %-3s | %-15s | %-5s | %-10s |\n", "No", "Mata Pelajaran", "Nilai", "Status");
    fprintf(fp,"\n--------------------------------------------\n");

    for(int i=0; i<MAX; i++) {
        fprintf(fp,"| %-3d | %-15s | %-5d | %-10s |\n", i+1, m[i].mapel, m[i].nilai, m[i].status);
    }
    fprintf(fp,"============================================\n");
    fprintf(fp,"| %-20s | %-20s |\n", "RATA RATA", "PREDIKAT");
    fprintf(fp,"--------------------------------------------\n");
    fprintf(fp,"| %-20.2f | %-20c |\n", rata, predikat);
    fprintf(fp,"============================================\n");

    fclose(fp);
}
