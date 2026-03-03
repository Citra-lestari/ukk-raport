//ini namanya library

#include <stdio.h>
//ini fungsinya untuk input output,seperti printf, scanf, FILE, fopen, fprintf,fclose

#include <stdlib.h>
//ini fungsinya  untuk sistem windows, kayak system("cls")

#include <string.h>
//ini untuk memanipulasi string contohnya strcpy()

#define MAX 5
/*
ini namanya konstanta
ini mendefinisikan kalau MAX itu memiliki maximal 5 data, ini untuk mapel
klo dia di atas 5 dia tetep akan menampilkan sampai data ke 5
*/

// ===== STRUCT =====
//struct ini beerfungsi untuk menyimpan banyak variabel dalam tipe data yg baru

typedef struct{
    char nama[50];
    int nis;
    char kelas[20];
    char sekolah[50];
} Siswa; //struct ini memiliki nama Siswa / Siswa ini adalah nama dari tipe data yg kita buat

typedef struct{
    char mapel[30];
    int kkm;
    int nilai;
    char status[15];
} Mapel;

// ===== PROTOTYPE =====
//disini kita menjabarkan / memberitau compiler bahwa function ini ada, dan bisa di panggil serta di gunakan di main()

void tampilMapel(Mapel m[]);
/*
kita memiliki function dengan nama tampilMapel
memiliki parameter (...)
parameter adalah data yg dikirim ke dalam function supaya function bisa menggunakannya
*/
int inputAngka();
void simpanFile(Siswa s, Mapel m[], float rata, char predikat);
/*
kenapa siswa tidak memakai kurung siku / [] sedangkan di mapel make?
karena siswa itu nantinya tidak akan menjadi array. sedangkan mapel nantinya akan menjadi array
*/

// ===== FUNCTION =====
void tampilMapel(Mapel m[]){
    printf("=================================================\n");
    printf("| %-3s | %-20s | %-3s |\n","No","Nama Mapel","KKM");
    //dia make %s semua karena ini untuk menampilkan data judul dari atributnya, seperti no, nama mapel, kkm

    printf("=================================================\n");
    for(int i=0;i<MAX;i++)
        printf("| %-3d | %-20s | %-3d |\n",i+1,m[i].mapel,m[i].kkm);
        //sedangkan disini sesuai dengan tipe data yang akan di inputkan karena data nya nanti akan masuk ke sini

    printf("=================================================\n");
}

int inputAngka(){
    int x;
    while(scanf("%d",&x)!=1){
        printf("Masukkan angka yang sesuai : ");
        while(getchar()!='\n');
    }
    return x;
}

// ===== MAIN =====
int main(){

    //ini adalah array
    Mapel m[MAX] = { //strcut Mapel berubah menjadi tipe data dan m menjadi nama variabel
        {"B. Inggris",75},
        {"B. Bali",75},
        {"B. Indonesia",75},
        {"Pemrograman",75},
        {"Basis Data",75}
    };

    Siswa s;  //memanggil struct di atas, Siswa akan berubah menjadi tipe data dan s adalah nama variabel

    //membuat variabel tambahan untuk pilih, i, total, rata, predikat
    char pilih;
    int i, total;
    float rata;
    char predikat;

    system("cls"); //digunakan untuk clear system

    tampilMapel(m); //memanggil function tampilMapel dan memanggil m (nama variabel) / array m di atas

    // INPUT IDENTITAS
    printf("\n===== INPUT DATA SISWA =====\n");
    printf("Nama     : "); scanf("%[^\n]", s.nama);
    printf("NIS      : "); s.nis = inputAngka();
    printf("Kelas    : "); scanf(" %[^\n]", s.kelas);
    printf("Sekolah  : "); scanf(" %[^\n]", s.sekolah);

    do{
        total = 0;

        // INPUT NILAI
        printf("\n===== INPUT NILAI =====\n");
        for(i=0;i<MAX;i++){
            printf("Nilai %-15s : ", m[i].mapel);

            m[i].nilai = inputAngka();   // <-- diperbaiki (bukan s[i].siswa)
            total += m[i].nilai;

            if(m[i].nilai >= m[i].kkm)
                strcpy(m[i].status,"Lulus");
            else
                strcpy(m[i].status,"Tidak Lulus");
        }

        rata = (float)total/MAX;

        if(rata>=90) predikat='A';
        else if(rata>=80) predikat='B';
        else if(rata>=70) predikat='C';
        else if(rata>=60) predikat='D';
        else predikat='E';

        // OUTPUT TABEL
        printf("\n================ HASIL RAPOT =================\n");
        printf("Nama    : %s\n", s.nama);
        printf("NIS     : %d\n", s.nis);
        printf("Kelas   : %s\n", s.kelas);
        printf("Sekolah : %s\n", s.sekolah);

        printf("------------------------------------------------------------\n");
        printf("| %-3s | %-20s | %-5s | %-12s |\n","No","Mata Pelajaran","Nilai","Status");
        printf("------------------------------------------------------------\n");

        for(i=0;i<MAX;i++){
            printf("| %-3d | %-20s | %-5d | %-12s |\n",
                   i+1,m[i].mapel,m[i].nilai,m[i].status);
        }

        printf("============================================================\n");
        printf("| %26s | %27s |\n", "RATA RATA", "PREDIKAT"); //dia ga make - karena supaya rata kanan, sedangkan klo make - itu dia rata kiri
        printf("------------------------------------------------------------\n");
        printf("| %26.2f | %27c |\n", rata, predikat);
        printf("============================================================\n\n");

        printf("Tekan Y jika data sudah sesuai \n");
        printf("Tekan N jika data belum sesuai \n");
        printf("\nData sudah benar? (Y/N): ");
        scanf(" %c",&pilih);

    }while(pilih=='N'||pilih=='n');

    if(pilih=='Y'||pilih=='y'){
        simpanFile(s,m,rata,predikat);
        printf("\nFile berhasil disimpan!\n");
    }

    return 0;
}

void simpanFile(Siswa s, Mapel m[], float rata, char predikat){
    char file[30];
    //membuat variabel string untuk menyimpan nama file saat di cetak menjadi struk

    sprintf(file,"raport_%d.txt",s.nis);
    /*
    sprintf (string print formatted) beerfungsi untuk menyimpan hasil format ke dalam variabel
    formatnya itu yang "raport_%d.txt"
    %d itu akan di sesuaikan dengan s.nis / nis siswa
    */

    //membuka file
    FILE *fp=fopen(file,"w");
    /*
    FILE adalah tipe data untuk membuka, membaca, menulis dan menutup file
    *fp itu artinya pointer ke file, pointer berfungsi untuk menyimpan alamat ddari fopen, untuk fp, itu bebas di kasi nama apa aja
    fopen (file open)  berfungsi untuk membuka file
    file ini berasal dari variabel file di atas
    "w" berfungsi untuk melakukan metode write
    */

    fprintf(fp,"================ HASIL RAPOT ================\n"); //mencetak garis dan judul ke file bukan ke layar, karena menggunakan fprintf
    //fprintf (file print formmated)
    //fp itu file print / bisa di ganti dengan apa saja
    fprintf(fp,"Nama    : %s\n", s.nama); //mencetak data yg di ambil dari s.nama, data yang sudah di inputkan di awal
    fprintf(fp,"NIS     : %d\n", s.nis); //mencetak data yg di ambil dari s.nis, data yang sudah di inputkan di awal
    fprintf(fp,"Kelas   : %s\n", s.kelas); //mencetak data yg di ambil dari s.kelas, data yang sudah di inputkan di awal
    fprintf(fp,"Sekolah : %s\n\n", s.sekolah); //mencetak data yg di ambil dari s.sekolah, data yang sudah di inputkan di awal

    fprintf(fp,"---------------------------------------------------------------\n"); //mencetak garis ke file bukan ke layar, karena menggunakan fprintf
    fprintf(fp,"| %-3s | %-20s | %-5s | %-12s |\n","No","Mata Pelajaran","Nilai","Status"); //mencetak judul dari atribut untuk di simpan ke file bukan ke layar, dengan mennggunakan % / format specifier untuk panjang atribut
    fprintf(fp,"---------------------------------------------------------------\n"); //mencetak garis ke file bukan ke layar, karena menggunakan fprintf

    for(int i=0;i<MAX;i++)
        /*
        perulangan for
        mendeklarasikan int i
        i di awal bernilai 0
        i akan terus berulang selama kurang dari MAX
        i akan selalu bertambah 1
        */

        fprintf(fp,"| %-3d | %-20s | %-5d | %-12s |\n",
                i+1,m[i].mapel,m[i].nilai,m[i].status);
        /*
        i+1 itu untuk angka di sebelah kiri / no, dia akan terus bertambah 1
        m[i].mapel mengambil data dari struct Mapel dengan variabel mapel, begitu juga yg lainnya
        */

    fprintf(fp,"============================================================\n"); //mencetak garis ke file
    fprintf(fp,"| %26s | %27s |\n", "RATA RATA", "PREDIKAT"); //mencetak judul rata rata dan predikat sesuai dengan batas yg di berikan
    fprintf(fp,"------------------------------------------------------------\n"); //mencetak garis ke file
    fprintf(fp,"| %26.2f | %27c |\n", rata, predikat); //menampilkan data dari rata rata yg sudah di hitung dan predikat yg sudah di fillter
    fprintf(fp,"============================================================\n"); //mencetak garis ke file

    fclose(fp);
    //menutup file agar data benar benar tersimpan
}





















#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

typedef struct{
    char nama[50];
    int nis;
    char kelas[20];
    char sekolah[50]
}Siswa;

typedef struct{
    char mapel[20];
    int kkm;
    int nilai;
    char status[15];
}Mapel;

void tampilMapel(Mapel m[]);
int inputAngka();
void simpanFile(Siswa s, Mapel m[], float rata, char predikat);

void tampilMapel(Mapel m[]) {
    printf("=====================================================\n");
    printf("| %-3s | %-15s | %-3s |\n", "No", "Mata Pelajaran", "KKM");
    printf("=====================================================\n");

    for(int i=0; i<MAX; i++)
        printf("%-3d | %-15s | %-3d |\n", i+1, m[i].mapel, m[i].kkm);
    printf("=====================================================\n");
}

int inputAngka() {
    int x;

    while(scanf("%d", &x)!=1){
        printf("Masukkan angka yg sesuai : \n");
        while(getchar()!='\n');
    }
    return x;
}

int main() {

    Mapel m[MAX]={
        {"Matematika", 75},
        {"PPKN", 75},
        {"KKPG", 75},
        {"KIK", 75},
        {"MPP", 75}
    };

    Siswa s;
    int i,total;
    char pilih;
    float rata;
    char predikat;

    system("cls");

    tampilMapel(m);

    //input identitas
    printf("\n========== INPUT DATA SISWA ==========\n");
    printf("Nama    : "); scanf("%[^\n]", s.nama);
    printf("NIS     : "); s.nis=inputAngka();
    printf("Kelas   : "); scanf(" %[^\n]", s.kelas);
    printf("Sekolah : "); scanf(" %[^\n]", s.sekolah);

    do{
        total = 0;

        printf("========== INPUT NILAI ==========\n");
        for(i=0; i<MAX; i++) {
            printf("Masukkan Nilai %-10s : ", m[i].mapel);

            m[i].nilai = inputAngka();
            total+=m[i].nilai;

            if(m[i].nilai >= m[i].kkm)
                strcpy(m[i].status, "LULUS");
            else
                strcpy(m[i].status, "TIDAK LULUS");
        }

        rata = (float)total/MAX;

        if(rata >= 80) predikat='A';
        else if(rata >= 75) predikat='B';
        else if(rata >= 70) predikat='C';
        else if(rata >= 60) predikat='D';
        else predikat='E';

        //OUTPUT TABEL
        //identitas siswa
        printf("\n========== HASIL RAPOT ==========\n");
        printf("Nama    : %s\n", s.nama);
        printf("NIS     : %d\n", s.nis);
        printf("Kelas   : %s\n", s.kelas);
        printf("Sekolah : %s\n", s.sekolah);

        //tabel
        printf("\n============================================\n");
        printf("| %-3s | %-15s | %-5s | %-11s |\n", "No", "Mata Pelajaran", "Nilai", "Status");
        printf("\n-------------------------------------------\n");
        for(i=0; i<MAX; i++) {
            printf("| %-3d | %-15s | %-5d | %-11s |\n", i+1, m[i].mapel, m[i].nilai, m[i].status);
        }

        printf("\n===========================================\n");
        printf("| %-20s | %-20s |\n", "RATA RATA", "PREDIKAT");
        printf("\n-------------------------------------=------\n");
        printf("| %-20.2f | %-20c |\n", rata, predikat);
        printf("\n===========================================\n");

        printf("Tekan Y jika data sudah sesuai\n");
        printf("Tekan N jika data belum sesuai\n");
        printf("\nMasukkan pilihan anda (Y/N) : ");
        scanf(" %c", &pilih);
    }while(pilih=='n'||pilih=='Y');

    if(pilih=='y'||pilih=='Y'){
        simpanFile(s,m,rata,predikat);
        printf("\nFile Berhasil Di Simpan!!\n");
    }

    return 0;
}

void simpanFile(Siswa s, Mapel m[], float rata, char predikat){
    char file[30];
    sprintf(file, "raport_%d.txt", s.nis);

    FILE *fp=fopen(file, "w");

    fprintf(fp,"\n========== HASIL RAPOT ==========\n");
    fprintf(fp,"Nama    : %s\n", s.nama);
    fprintf(fp,"NIS     : %d\n", s.nis);
    fprintf(fp,"Kelas   : %s\n", s.kelas);
    fprintf(fp,"Sekolah : %s\n", s.sekolah);

        //tabel
    fprintf(fp,"\n====================================\n");
    fprintf(fp,"| %-3s | %-15s | %-3s | %-15s |\n", "No", "Mata Pelajaran", "Nilai", "Status");
    fprintf(fp,"\n------------------------------------\n");
    for(int i=0; i<MAX; i++) {
        fprintf(fp,"| %-3d | %-15s | %-3d | %-15s |\n", i+1, m[i].mapel, m[i].nilai, m[i].status);
    }

    fprintf(fp,"\n====================================\n");
    fprintf(fp,"| %-20s | %-20s |\n", "RATA RATA", "PREDIKAT");
    fprintf(fp,"\n------------------------------------\n");
    fprintf(fp,"| %-20.2f | %-20c |\n", rata, predikat);
    fprintf(fp,"\n====================================\n");

    fclose(fp);
}
