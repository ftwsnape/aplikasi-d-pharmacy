#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct 
{
    char nama[100], tipe[100];
    double harga;
}data;

int LogInAdmin();
void MenuAdmin();
int dataObatBaru();
int lihatObat();
int seluruhObat();
int loginpembeli();
void menupembeli();

FILE *dataObat;

int i = 0;

void main(){
    int pilihan;
    printf("======= D'Pharmacy ======\n");
    printf("Pilih Role : \n");
    printf("1. Admin.\n");
    printf("2. Pembeli.\n");
    printf("Pilihan anda : ");
    scanf("%d", &pilihan);
    getchar();

    switch (pilihan)
    {
    case  1 :
        if(LogInAdmin()){ 
            MenuAdmin();
        }
        break;
        case 2 :
        if (loginpembeli()){
            menupembeli();
        }
        break;

        default:
        break;
    }

}

int LogInAdmin(){
    int repeat;
    char username[20], pass[20];
    for(repeat = 3; repeat > 0; repeat--){ 
        printf("\n==== Log In ====\n");
        fflush(stdin);
        printf("username : ");
        gets(username);
        printf("Password : ");
        gets(pass);
        if (strcmp(username,"admin")==0 && strcmp(pass,"admin")==0){
            printf("Anda berhasil log in sebagai admin, silahkan melanjutkan ke menu admin.\n"); 
            return 1;
        }
        else{
            printf("Username atau Password salah\n");
            if(repeat > 1){
                printf("Tersisa %d kesempatan lagi\n\n", repeat-1);
            }
            else{
                printf("Anda sudah tidak dapat login kembali\n");
            }
        }
    }
    return 0;
}

void MenuAdmin(){
    int menuAdmin;
    printf("\n=== Selamat datang Admin ===\n");
    printf("Silahkan pilih menu : \n");
    printf("1. Membuat data obat baru.\n");
    printf("2. Melihat riwayat pembelian.\n");
    printf("3. Melihat daftar obat.\n");
    printf("4. Keluar\n");
    printf("Menu : ");
    scanf("%d", &menuAdmin);
   
    switch (menuAdmin)
    {
    case 1 : 
        dataObatBaru();
        break;
    case 2 : 
        // riwayat();
        break;
    case 3 :
        if(lihatObat()){ 
            seluruhObat();
        }
    case 4 :
        system("exit");
    
    default:
        break;
    }
}

int dataObatBaru(){
    int banyak;
    dataObat = fopen("Daftar_Obat.dat", "ab+");
    printf("\n=======================================================\n");
    printf("Banyaknya data obat : ");
    scanf("%d", &banyak);
    getchar();
    for ( i = 0; i < banyak; i++)
    {
        fflush(stdin);
        printf("\nNama Obat : ");
        gets(data.nama);
        printf("Tipe Obat : ");
        gets(data.tipe);
        printf("Harga Obat : ");
        scanf("%lf", &data.harga);
        fwrite(&data, sizeof(data), 1, dataObat);
    }
    fclose(dataObat);
    system("pause");

    MenuAdmin();
}

int lihatObat(){
    int lihat;
    printf("\n=======================================================\n");
    printf("1. Menampilkan seluruh obat.\n");
    printf("2. Menampilan tipe obat tertentu.\n");
    printf("3. Mencari obat tertentu.\n");
    printf("4. List obat terurut (A-Z).\n");
    printf("5. Kembali ke menu admin.\n");
    printf("Pilihan : ");
    scanf("%d", &lihat);
    getchar();

    switch (lihat)
    {
    case 1 :
        seluruhObat();
        break;
    case 5 : 
        MenuAdmin();
    case 6 : 
        system("exit");
    default:
        break;
    }
}

int seluruhObat(){
    dataObat = fopen("Daftar_Obat.dat", "rb");
    while (fread(&data, sizeof(data), 1, dataObat)==1)
    {
        printf("\nNama Obat : %s\n", data.nama);
        printf("Tipe Obat : %s\n", data.tipe);
        printf("Harga Obat : %.0f\n", data.harga);
    }
    fclose(dataObat);
    system("pause");

    lihatObat();
}

int loginpembeli(){
    int repeat;
    char username[20], pass[20];
    for(repeat = 3; repeat > 0; repeat--){ 
        printf("\n==== Log In ====\n");
        fflush(stdin);
        printf("username : ");
        gets(username);
        printf("Password : ");
        gets(pass);
        if (strcmp(username,"pembeli")==0 && strcmp(pass,"pembeli")==0){
            printf("Anda berhasil log in, silahkan melanjutkan ke menu utama.\n"); 
            return 1;
        }
        else{
            printf("Username atau Password salah\n");
            if(repeat > 1){
                printf("Tersisa %d kesempatan lagi\n\n", repeat-1);
            }
            else{
                printf("Anda sudah tidak dapat login kembali\n");
            }
        }
    }
    return 0;
}

void menupembeli(){
    int menupembeli;
    printf("\n=== Selamat datang ===\n");
    printf("\n=== Menu Utama ===\n");
    printf("Silahkan pilih menu : \n");
    printf("1. Top up dan cek saldo\n");
    printf("2. Melihat obat.\n");
    printf("3. keranjang pembeli\n");
    printf("4. Keluar\n");
    printf("Menu : ");
    scanf("%d", &menupembeli);
   
    switch (menupembeli)
    {
    case 1 : 
        //top up pembeli
        break;
    case 2 :
    //melihat obat 
        if(lihatObat()){
            seluruhObat();
        }
        break;
    case 3 :
    //keranjang pembeli
    case 4 :
    //keluar
        system("exit");
    
    default:
        break;
    }
}