#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct stObat{
    char nama[100], tipe[100];
    double harga;
}data;

struct data{
    char usernameBaru[20], passBaru[20];
    int Saldo;
}datasign, datasign2;

char username[20], pass[20];

int LogInAdmin();
void MenuAdmin();
int dataObatBaru();
int lihatObat();
int seluruhObat();
int tipeObat();
int cariObat();
int urutanObat();
int riwayat();
int seluruhRiwayat();
int riwayatTertentu();
int MenuLoginSignupPembeli();
void loginpembeli();
void signupPembeli();
void menupembeli();
void TopUp();
void CekSaldo();
void CartPembeli();
int lihatObatPem();
int pemesanan();

FILE *dataObat;

int i = 0;

void main(){
    system("cls");

    int pilihan;
    printf("\n======= D'Pharmacy ======\n");
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
        if (MenuLoginSignupPembeli()){
            menupembeli();
        }
        break;

        default:
        break;
    }

}

//admin area=================//

int LogInAdmin(){
    system("cls");

    int repeat;;
    for(repeat = 3; repeat > 0; repeat--){ 
        printf("\n==== Log In Admin ====\n");
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
    system("cls");

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
        riwayat();
        break;
    case 3 :
        lihatObat();
        break;
    case 4 :
        system("exit");
    
    default:
        break;
    }
}
int dataObatBaru(){
    system("cls");

    int tipeO;
    printf("\n=======================================================\n");
    printf("Silahkan pilih tipe obat\n");
    printf("1. Antiseptik\n");
    printf("2. Vitamin\n");
    printf("3. Diare\n");
    printf("4. Demam\n");
    printf("5. Pereda Nyeri\n");
    printf("6. Flu Batuk\n");
    printf("7. Kembali ke menu Admin\n");
    printf("Pilihan : ");
    scanf("%d", &tipeO);
    switch (tipeO)
    {
    case 1 :
        strcpy(data.tipe, "Antiseptik");
        break;
    case 2 : 
        strcpy(data.tipe, "Vitamin");
        break;
    case 3 : 
        strcpy(data.tipe, "Diare");
        break;
    case 4 :
        strcpy(data.tipe, "Demam");
        break;
    case 5 : 
       strcpy(data.tipe, "Pereda Nyeri");
        break;
    case 6 :
        strcpy(data.tipe, "Flu Batuk");
        break;
    case 7 :
        MenuAdmin();
    default:
        break;
    }

    printf("Masukkan nama obat: ");
    scanf("%s", data.nama);
    printf("Masukkan harga obat: ");
    scanf("%lf", &data.harga);

    dataObat = fopen("Daftar_Obat.dat", "ab");
    if(dataObat == NULL) {
        printf("Gagal membuka file.\n");
    }

    fwrite(&data, sizeof(data), 1, dataObat);

    fclose(dataObat);

    MenuAdmin();
}

int lihatObat(){
    system("cls");

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
    case 3 : 
        cariObat();
        break;
    case 4 : 
        urutanObat();
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
    system("cls");
    dataObat = fopen("Daftar_Obat.dat", "rb");
    while (fread(&data, sizeof(data), 1, dataObat)==1)
    {
        printf("\nNama Obat : %s\n", data.nama);
        printf("Tipe Obat : %s\n", data.tipe);
        printf("Harga Obat : %.0f\n", data.harga);
        printf("\n");
    }
    fclose(dataObat);
    system("pause");

    lihatObat();
}

int tipeObat(){
    system("cls");

    int i;
    char cariTipe[20];
    printf("Tipe Obat yang ingin dicari : ");
    gets(cariTipe);
    dataObat = fopen("Daftar_Obat.dat", "rb");
    i = 1;
    while (fread(&data, sizeof(data),1,dataObat)==1)
    {
        if(strcmp(data.tipe, cariTipe)==0){
            printf("Nama obat: %s\nHarga obat: %0.f\n", data.nama, data.harga);
        }
    }
    
    fclose(dataObat);
    system("pause");

    lihatObat();
}

int cariObat(){
    system("cls");

    char namaObat[20];
    printf("Nama obat yang ingin dicari : ");
    scanf("%s", namaObat);

    dataObat = fopen("Daftar_Obat.dat", "rb");

    while (fread(&data, sizeof(data),1, dataObat))
    {
        if(strcmp(data.nama, namaObat)==0){
            printf("Nama obat: %s\nHarga obat: %0.f\n", data.nama, data.harga);
            break;
        }
    }
    fclose(dataObat);
    system("pause");

    lihatObat();
    
}

void bubbleSort(struct stObat arr[], int n) {
    struct stObat temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j].nama, arr[j+1].nama) > 0) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int urutanObat(){
    system("cls");

    struct stObat arr[100];
    int n = 0;
    dataObat = fopen("Daftar_obat.dat", "rb");

    while(fread(&arr[n], sizeof(struct stObat), 1, dataObat)) {
        n++;
    }

    fclose(dataObat);

    bubbleSort(arr, n);

    printf("Daftar obat dalam urutan ascending:\n");
    for (int i = 0; i < n; i++){
        printf("%d.   Nama : %s\n", i,  arr[i].nama);
        printf("     Tipe : %s\n", arr[i].tipe);
        printf("     Harga : %0.f\n", arr[i].harga);
        printf("\n");
    }
    system("pause");
    lihatObat();
        
}

int riwayat(){
    system("cls");

    int rwyt;
    printf("\n=======================================================\n");
    printf("1. Seluruh riwayat pembeli.\n");
    printf("2. Pembeli tertentu.\n");
    printf("3. Kembali ke menu Admin.\n");
    printf("Pilihan : ");
    scanf("%d", &rwyt);
    
    switch (rwyt)
    {
    case 1 :
        seluruhRiwayat();
        break;
    case 2 : 
        riwayatTertentu();
        break;
    case 3 : 
        menupembeli();
        break;
    default:
        break;
    }
}

int seluruhRiwayat(){
    system("cls");
}

int riwayatTertentu(){
    system("cls");
}

//area pembeli====================//

int MenuLoginSignupPembeli(){
    system("cls");

    int menu;
    printf("\n=======================================================\n");
    printf("===Pilih Menu===\n");
    printf("1. Log in\n");
    printf("2. Sign Up\n");
    printf("Pilih salah satu : ");
    scanf("%d", &menu);

    switch (menu) {
    case 1:
        loginpembeli();
        break;

    case 2:
        signupPembeli();
        return 1;

    default:
        printf("Pilihan yang anda pilih tidak ada pada opsi yang kami berikan\n");
        break;
    }
    return 0;
}

void loginpembeli() {
    system("cls");

    int repeat;
    FILE *LoginPembeli;
    
    for (repeat = 3; repeat > 0; repeat--) {
        LoginPembeli = fopen("LogSignPembeli.dat", "rb");
        printf("\n=======================================================\n");
        printf("\n==== Log In ====\n");
        fflush(stdin);
        printf("Username : ");
        gets(username);
        printf("Password : ");
        gets(pass);
        while (fread(&datasign, sizeof(datasign), 1, LoginPembeli))
        {
            if (strcmp(username, datasign.usernameBaru) == 0 && strcmp(pass, datasign.passBaru) == 0) {
            printf("Anda berhasil log in, silahkan melanjutkan ke menu utama.\n");
            fclose(LoginPembeli);
            menupembeli();
            }
        
    }
    if (repeat > 1) {
            printf("Username atau Password salah\n");
            printf("Tersisa %d kesempatan lagi\n\n", repeat - 1);
    } else {
            printf("Anda sudah tidak dapat login kembali\n");
            fclose(LoginPembeli);
        }

    }
}

void signupPembeli() {
    system("cls");

    int repeat;

    char opsi[5];

    FILE *SignUpPembeli;

    SignUpPembeli = fopen("LogSignPembeli.dat", "ab");
    printf("\n=======================================================\n");
    printf("\n==== Sign Up ====\n");
    fflush(stdin);

    printf("Username : ");
    fflush(stdin);
    gets(datasign.usernameBaru);
    printf("Password : ");
    fflush(stdin);
    gets(datasign.passBaru);

    datasign.Saldo = 0;

    fwrite(&datasign, sizeof(datasign), 1, SignUpPembeli);

    printf("Anda sudah melakukan Sign up\n");

    printf("Apakah anda ingin Log In sekarang? (y/n): ");
    scanf("%s", &opsi);
    
    if (strcmp(opsi, "y") == 0) {
        fclose(SignUpPembeli);
        loginpembeli();
    } else {
        printf("Silakan log in nanti.\n");
    }

    fclose(SignUpPembeli);
}

void menupembeli() {
    system("cls");

    int menuPembeli;
    fflush(stdin);
    printf("\n=======================================================\n");
    printf("\n=== Selamat datang ===\n");
    printf("\n=== Menu Utama ===\n");
    CekSaldo();
    printf("\nSilahkan pilih menu : \n");
    printf("1. Top up dan cek saldo\n");
    printf("2. Melihat obat & pesan obat\n");
    printf("3. Keranjang pembeli\n");
    printf("4. Keluar\n");
    printf("Menu : ");
    scanf("%d", &menuPembeli);

    switch (menuPembeli) {
        case 1:
            TopUp();
            break;
        case 2:
            lihatObatPem();
            break;
        case 3:
            CartPembeli();
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("Pilihan tidak valid.\n");
            break;
    }
}

void TopUp(){
    system("cls");

    FILE *TopUpSaldo, *temp;

    int i;

    TopUpSaldo = fopen("LogSignPembeli.dat", "rb");
    temp = fopen("temp.dat", "wb");
    printf("\n=======================================================\n");
    printf("Mau Top Up berapa banyak? : ");
    scanf("%d", &i);

    while (fread(&datasign, sizeof(datasign), 1, TopUpSaldo) == 1)
    {
        if (strcmp(username ,datasign.usernameBaru) == 0)
        {
            datasign2 = datasign;
            datasign2.Saldo += i;
            fwrite(&datasign2, sizeof(datasign2), 1, temp);
        
            printf("Saldo anda sekarang : %d", datasign2.Saldo);
        }
        
    }
    fclose(TopUpSaldo);
    fclose(temp);
    remove("LogSignPembeli.dat");
    rename("temp.dat", "LogSignPembeli.dat");

    menupembeli();

}

void CekSaldo(){
    system("cls");

    FILE *CekSaldo;
    
    CekSaldo = fopen("LogSignPembeli.dat", "rb");
    while(fread(&datasign, sizeof(datasign), 1, CekSaldo) == 1){
        if (strcmp(datasign.usernameBaru, username) == 0)
        {
            printf("Saldo Anda Sekarang = %d\n", datasign.Saldo);
        }
    }
    fclose(CekSaldo);
}

int lihatObatPem(){
    system("cls");

    int lihat;
    printf("\n=======================================================\n");
    printf("1. Menampilkan seluruh obat.\n");
    printf("2. Menampilan tipe obat tertentu.\n");
    printf("3. Mencari obat tertentu.\n");
    printf("4. List obat terurut (A-Z).\n");
    printf("5. Pemesanan Obat\n");
    printf("6. Kembali ke menu pembeli\n");
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
    case 3 : 
        cariObat();
        break;
    case 4 : 
        urutanObat();
        break;
    case 5 : 
        pemesanan();
        break;
    case 6 : 
        menupembeli();
        break;
    case 7 : 
        system("exit");
    default:
        break;
    }
}

int pemesanan(){
    system("cls");
    char barang[100], konfirm[10];
    FILE *pesan;
    FILE *cart;
    pesan = fopen("Daftar_Obat.dat","rb");
    cart = fopen("Keranjang_Pembeli.dat", "ab");

    printf("Pilih obat yang ingin dibeli : ");
    gets(barang);
    while (fread(&data, sizeof(data), 1, pesan))
    {
        if (strcmp(barang, data.nama)==0)
        {
            printf("Nama obat : %s\n", data.nama);
            printf("Tipe obat: %s\n", data.tipe);
            printf("Harga Obat : %.0f\n", data.harga);
        }
        
    }
    printf("Apakah anda yakin memesan obat ini?\n");
    printf("Ya / Tidak\n");
    printf("Pilihan : ");
    gets(konfirm);
    if (strcmp(konfirm, "Ya")==0)
    {
        fwrite(&data, sizeof(data), 1, cart);
        printf("Obat berhasil ditambahkan.\n");
        fclose(pesan);
        fclose(cart);
        lihatObatPem();
    } else {
        fclose(pesan);
        fclose(cart);
        lihatObatPem();
    }
    

}

void CartPembeli(){
    int total;
    char a[2];
    FILE *shoppingcart, *temp, *TopUpSaldo, *riwayat;

    shoppingcart = fopen("cart.dat","rb");
    TopUpSaldo = fopen("LogSignPembeli.dat", "rb");
    temp = fopen("temp.dat", "wb");
    riwayat = fopen ("riwayat.dat", "rb");
    while (fread(&data ,sizeof(data),1,shoppingcart)){
       printf("\nNama Obat : %s\n", data.nama);
        printf("Tipe Obat : %s\n", data.tipe);
        printf("Harga Obat : %.0f\n", data.harga);
        total += data.harga;
        printf("\n");
    }
    printf("Total harga:%d", total);
    printf("Apakah ingin di check out?\n");
    printf("y/n?\n");
    gets (a);
    if (strcmp(a, "y")== 0){
        while (fread (&datasign ,sizeof(datasign), 1,TopUpSaldo)){
            if (strcmp(username, datasign.usernameBaru)== 0){
                if (total > datasign.Saldo){
                    printf("Saldo tidak mencukupi");
                    menupembeli();
                } else {
                 datasign.Saldo-=total; 
                 datasign2 = datasign;  
                 fwrite(&datasign2, sizeof(datasign2), 1, temp);
                 while (fread(&data ,sizeof(data),1,shoppingcart)){
                    fwrite (&data, sizeof(data),1, riwayat);
                 }
                }
            }
            else {
                fwrite (&datasign, sizeof (datasign2), 1, temp);
            }
        } 
        fclose (TopUpSaldo);
        fclose (temp);
        fclose (shoppingcart);
        fclose (riwayat);
        remove ("shoppingcart.dat");
        remove ("LogSignPembeli.dat");
        rename ("temp", "LogSignPembeli.dat");
        printf("notasi barang sudah terpenuhi");
    }
    else{
        menupembeli();
    }
}
