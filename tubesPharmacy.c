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
int tipeObat();
void MenuLoginSignupPembeli();
int loginpembeli();
void signupPembeli();
void menupembeli();
void TopUp();
void CekSaldo();
void CartPembeli();


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
//admin area=================//
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
    case 2 :
        tipeObat();
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

int tipeObat(){
    dataObat = fopen("Daftar_Obat.dat", "rb");
    while (fread(&data, sizeof(data), 1, dataObat)==1)
    {
        printf("Tipe Obat : %s\n", data.tipe);
    }
    fclose(dataObat);
    system("pause");

    lihatObat();
}

//area pembeli====================//
// log in masih belum kelar.
int loginpembeli(){
    int repeat;
    char username[20], pass[20];
    FILE *LoginPembeli;

    LoginPembeli = fopen("LogSignPembeli.dat", "rb");

    if (LoginPembeli == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (repeat = 3; repeat > 0; repeat--) {
        printf("\n==== Log In ====\n");
        fflush(stdin);

        printf("Username : ");
        scanf("%s", username);
        printf("Password : ");
        scanf("%s", pass);

        fseek(LoginPembeli, 0, SEEK_SET);
        while (fscanf(LoginPembeli, "%19s %19s", username, pass) == 2) {
            if (strcmp(username, "") == 0 && strcmp(pass, "pembeli") == 0) {
                printf("Anda berhasil log in, silahkan melanjutkan ke menu utama.\n");
                fclose(LoginPembeli);
                return;
            }
        }

        printf("Username atau Password salah\n");

        if (repeat > 1) {
            printf("Tersisa %d kesempatan lagi\n\n", repeat - 1);
        } else {
            printf("Anda sudah tidak dapat login kembali\n");
        }
    }

    fclose(LoginPembeli);
}

void signupPembeli() {
    int repeat;
    char username[20], pass[20];

    FILE *SignUpPembeli;
    SignUpPembeli = fopen("LogSignPembeli.dat", "ab");

    for (repeat = 3; repeat > 0; repeat--) {
        printf("\n==== Sign Up ====\n");
        fflush(stdin);

        printf("Username : ");
        gets(username);
        printf("Password : ");
        gets(pass);

        fprintf(SignUpPembeli, "%s, %s\n", username, pass);

        printf("Sign up successful!\n");

        printf("Apakah anda ingin Log In sekarang? (y/n): ");
        char opsi[5];
        scanf("%s", opsi);

        if (strcmp(opsi, "y") == 0) {
            loginpembeli();
            fclose(SignUpPembeli);
            return 0;
        } else {
            printf("Silakan log in nanti.\n");
        }
    }

    fclose(SignUpPembeli);

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

void MenuLoginSignupPembeli(){
    int menu;

    printf("===Pilih Menu===\n");
    printf("1. Log in\n");
    printf("2. Sign Up\n");
    printf("Pilih salah satu\t: ");
    scanf("%d", &menu);

    switch (menu) {
    case 1:
        login();
        break;

    case 2:
        sign();
        break;

    default:
        printf("Pilihan yang anda pilih tidak ada pada opsi yang kami berikan\n");
        return 1;
    }
}

void TopUp(){

    FILE *TopUpSaldo;
    struct TSaldo
    {
        float saldo1, saldo2, hasil, n;
    }TopUp;

    int i;

    TopUpSaldo = fopen("TopSaldo.dat", "ab");
    printf("Mau TopUp berapa kali?\t: ");
    scanf("%f", &TopUp.n);
    getchar();
    for (i=1; i<=TopUp.n; i++){
        
        printf("Saldo Awal : "); 
        scanf("%f", &TopUp.saldo1);
        printf("Saldo yang ditambahkan : "); 
        scanf("%f", &TopUp.saldo2);
        getchar();
        TopUp.hasil = TopUp.saldo1 + TopUp.saldo2;
        fwrite(&TopUp, sizeof (TopUp), 1, TopUpSaldo);
        printf("Saldo Anda Sekarang =\t%.0f\n", TopUp.hasil);
    }
    fclose(TopUpSaldo);

}

void CekSaldo(){
    FILE *TopUpSaldo;
    struct TSaldo
    {
        float saldo;
        int n;
    }TopUp;
    
    TopUpSaldo = fopen("TopSaldo.dat", "rb");
    fwrite(&TopUp, sizeof(TopUp), 1, TopUpSaldo) == 1;
    printf("Saldo Anda Sekarang =\t%.0f", TopUp.saldo);
    fclose(TopUpSaldo);    
}

void CartPembeli(){
    FILE *shoppingcart;
    struct{ char NamaObat[100];
        float HargaObat2,HargaObat1, TotalHargaObat;
        float Produk;
    }cart;

    shoppingcart = fopen("cart.dat","ab");
    dataObat = fopen("Daftar_Obat.dat", "ab+");
}
