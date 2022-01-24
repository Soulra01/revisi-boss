#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ll long long
#define ld long double
#define max_limit 256

/* alif ardika - 2501990470
 * jeselyn arviana - 2501966074
 * Kelompok Baru
 * Sistem Menggunakan Linux Ubuntu 20.04
 */

//struct
typedef struct{
    char name[max_limit];
    char pass[max_limit];
    char contact[max_limit];
    char date[max_limit];
    unsigned ll money;
}User;

User nasabah[max_limit];
FILE* fp;
User currUser;
int last = 0;
int in = 0;
//function Declare
void search();
void sort();
void Swap(User*,User*);
void clearBuff();
void Enter();
void Time(char*);
void create();
void read();
void login();
void atmMenu();
void penarikan();
void lainmenu();
void deposito();
void MenuReturn();
void Menuasci();
void rmvlogin();
void removeacc();
void delay();
int Validasi(const char*);
int Select(char []);
ll int tabung(ll int);
ll int ambil(ll int);
//function

/**
 * Description : function validasi akun
 * Author : Alif ardika - 2501990470
 */

int Validasi(const char* nama) {
  FILE* fp = fopen("database.in","r");
  User temp;

  while(!feof(fp)){
    fscanf(fp, "%s %s %s %llu %[^\n]", temp.name, temp.contact, temp.pass, &temp.money, temp.date);
    if(!strcmp(temp.name, nama)){
        char password[10];
        printf("Masukan Password : ");
        scanf("%s", password); getchar();
        if(!strcmp(temp.pass, password)){
            currUser = temp;
            return 2;
        }
        return 1;
    }
  }
  return 0;
  fclose(fp);
}

/**
 * Description : untuk searching menggunakan binary search untuk mencari index
 * Author : Alif ardika - 2501990470
 */

int Select(char key[]){
    int mid = 0;
    int l = 0;
    int r = last-1;
    while(l <= r){
        mid  = (l+r)/2;
        if(strcmp(nasabah[mid].name, key)>0){
            r = mid-1;
        }
        else if(strcmp(nasabah[mid].name, key)<0){
            l = mid+1;
        }
        else{
            return mid;
        }

    }
    return -1;
}

/**
 * Description : function untuk sorting data yang ada
 * Author : Alif ardika - 2501990470
 */

void sort(){
    int min;
    for(int i=0; i < last-1; i++){
    min = i;
    for(int j=i+1; j<last-1; j++){
        if(strcmp(nasabah[j].name, nasabah[min].name) < 0){
        min = j;
        }
    }
    Swap(&nasabah[min], &nasabah[i]);
    }
}

/**
 * Description : pemindahan data melalui proses sorting
 * Author : Alif ardika - 2501990470
 */

void Swap(User *first, User *second){
    User temp = *first;
    *first = *second;
    *second = temp;
}

/**
 * Description : Menghilangkan buffer
 * Author : Alif ardika - 2501990470
 */

void clearBuff() { 
    int c; 
    while ((c = getchar()) != '\n' && c != EOF){} 
}

/**
 * Description : Enter untuk melanjutkan proses pada menu promt 
 * Author : Alif ardika - 2501990470
 */

void Enter(){
    printf("Tekan enter untuk melanjutkan..\n");
    getchar(); clearBuff();
}

/**
 * Description : Pengambilan waktu pada saat pembuatan akun
 * Author : Alif ardika - 2501990470
 */

void Time(char* waktu){
    time_t now;
    time(&now);
    strcpy(waktu, ctime(&now));
}

/**
 * Description : Pembuatan data
 * Author : Alif ardika - 2501990470
 */

void create(){
    User add;
    char temp[max_limit];
    printf("Masukan Nama Anda : ");
    scanf("%s", add.name); getchar();
    printf("Masukan Kontak Anda : ");
    scanf("%s", add.contact); getchar();
    printf("Masukan Password Anda : ");
    scanf("%s", add.pass);
    add.money = 100000;
    Time(add.date);
    fp = fopen("database.in", "a");
    fprintf(fp, "%s %s %s %lld %s", add.name, add.contact, add.pass, add.money, add.date);
    fclose(fp);
    strcpy(temp, add.name);
    printf("Hallo %s :)\n", temp);
    printf("Data telah tersimpan\n");
    Enter();
}

/**
 * Description : Pembacaan data
 * Author : Alif ardika - 2501990470
 */

void read(){
    last = 0;
    fp = fopen("database.in", "r");
    while (!feof(fp)){
        fscanf(fp, "%s %s %s %llu %[^\n]", nasabah[last].name, nasabah[last].contact, nasabah[last].pass, &nasabah[last].money, nasabah[last].date);
        last++;
    }

}

/**
 * Description : Pemerosesan data
 * Author : Alif ardika - 2501990470
 */

void ProcesData(){
    fp = fopen("database.in", "r");
    read();
    sort();
    fclose(fp);
}

/**
 * Description : Menu Login
 * Author : Alif ardika - 2501990470
 */

void login(){
    system("clear");
    char name[20];
    int s = 0;
    in = 0;
    while(s < 3){
        printf("Masukan Nama Anda : ");
        scanf("%s", name); getchar();
        switch (Validasi(name)){
        case 0:
            printf("Salah Username\n");
            printf("Maksimal percobaan 3 : %d\n", s+1);
            break;
        case 1:
            printf("Salah Password\n");
            printf("Maksimal percobaan 3 : %d\n", s+1);
            break;
        case 2:
            ProcesData();
            in = Select(name);
            atmMenu();
            s = 3;
            break;
            // break;
        }
        s++;
    }
    if(s == 3 && Validasi(name) != 2){
        printf("Salah Password anda harus mengulang dari awal.\n");
        Enter();
    }
}

/**
 * Description :  menu ATM
 * Author : Alif ardika - 2501990470
 */

void atmMenu(){
    system("clear");
    printf("Hallo %s Selamat Datang\n", currUser.name);
    puts("1. Tarik Tunai");
    puts("2. Setor Tunai");
    int pilih; scanf("%d", &pilih);
    switch(pilih){
        case 1:
            penarikan();
        break;
        case 2:
            deposito();
        break;

    }
}

/**
 * Description : function ini berfungsi untuk melakukan setor manual
 * Author : Alif ardika - 2501990470
 */

void deposito(){
    int x = 0;
    int z = 0;
    while(!x){
        ll int depo=0;
        printf("Masukan Uang Anda : ");
        scanf("%lld", &depo);
        if(depo >= 100000){
            puts("\tSetor Tunai");
            printf("Ke Rek Atas Nama :  %s\n", currUser.name);
            printf("Total \t\t :  %lld\n", depo);
            puts("1. Setor");
            puts("2. Batal");
            scanf("%d", &z);
            switch(z){
                case 1:
                    tabung(depo);
                    MenuReturn();
                    x = 1;
                break;
                case 2:
                    deposito();
                break;


            }
        }
        else{
            printf("Batas minimum deposito Rp100.000\n");
        }

    }
}

/**
 * Description : untuk kalkulasi deposito
 * Author : Alif ardika - 2501990470
 */

ll int tabung(ll int uang){
    ll int temp;
    temp = currUser.money + uang;
    uang = temp;
    FILE* nihh;
    nihh = fopen("database.in", "w");
    for(int i = 0; i < last-1; i++){
        if(i == in){
        fprintf(nihh, "%s %s %s %lld %s\n", nasabah[i].name, nasabah[i].contact, nasabah[i].pass, uang, nasabah[i].date);
        }
        else{
        fprintf(nihh, "%s %s %s %llu %s\n", nasabah[i].name, nasabah[i].contact, nasabah[i].pass, nasabah[i].money, nasabah[i].date);
        }
    }
    printf("sisa saldo : %lld\n", uang);
    fclose(fp);
    return uang;
}

/**
 * Description : function perhitungan penarikan
 * Author : Alif ardika - 2501990470
 */

ll int ambil(ll int uang){
    User ambil;
    ll int temp;
    if(currUser.money <= 100000){
        printf("Saldo Tidak Mencukupi\n");
        printf("Saldo Anda : %llu\n", currUser.money);
        Enter(); //getchar();
        login();
    }
    else if(uang > 5000000){
        puts("Anda Telah Mencapai Limit Sebesar Rp5.000.000\n");
        Enter();
        penarikan();
    }
    else{
        temp = currUser.money - uang;
        uang = temp;
        FILE* nihh;
        nihh = fopen("database.in", "w");
        for(int i = 0; i < last-1; i++){
            if(i == in){
            fprintf(nihh, "%s %s %s %lld %s\n", nasabah[i].name, nasabah[i].contact, nasabah[i].pass, uang, nasabah[i].date);
            }
            else{
            fprintf(nihh, "%s %s %s %llu %s\n", nasabah[i].name, nasabah[i].contact, nasabah[i].pass, nasabah[i].money, nasabah[i].date);
            }
        }
        printf("sisa saldo : %lld\n", uang);
        fclose(fp);
    }
    return uang;
}

/**
 * Description : function menu penarikan uang
 * Author : Alif ardika - 2501990470
 */

void penarikan(){
    system("clear");
    puts("1.<= 100000\t\t1000000 =>4.");
    puts("2.<= 300000\t\t1500000 =>5.");
    puts("3.<= 500000\t\t2000000 =>6.");
    puts("7.<= Transaksi lain ");
    int pilih = 0;
    scanf("%d", &pilih);
    switch (pilih){
    case 1:
        ambil(100000);
        break;
    case 2:
        ambil(300000);
        break;
    case 3:
        ambil(500000);
        break;
    case 4:
        ambil(1000000);
        break;
    case 5:
        ambil(1500000);
        break;
    case 6:
        ambil(2000000);
        break;
    case 7:
        lainmenu();
        break;
    }
}

/**
 * Description : menu transaksi lain...
 * Author : Alif ardika - 2501990470
 */

void lainmenu(){
    ll int uang;
    system("clear");
    puts("1. Informasi saldo");
    puts("2. Penarikan Tunai");
    int pilih = 0; scanf("%d", &pilih);
    switch(pilih){
        case 1:
            printf("%llu\n", nasabah[in].money);
            MenuReturn();
        break; 
        case 2:
            printf("Maksimal Rp5.000.000\n");
            printf("Masukan Nominal : ");
            scanf("%lld", &uang);
            ambil(uang);
        break;

        default:
            lainmenu();
            break;

    }
}

/**
 * Description : untuk menanyakan user apakah lanjut transaksi atau tidak
 * Author : Alif ardika - 2501990470
 */

void MenuReturn(){
    char m;
    puts("Ingin melanjutkan transaksi? y/n: ");
    scanf(" %c", &m); clearBuff();
    switch (m){
    case 'y':
        login();
        break;
    case 'n':
        exit(1);
        break;
    }
}

/**
 * Description : menghapus data user
 * Author : Alif ardika - 2501990470
 */

void rmvlogin(){
    char name[20];
    printf("Masukan Nama Anda : ");
    scanf("%s", name);
    int s = 0;
    in = 0;
    while(s < 3){
        switch (Validasi(name)){
        case 0:
            printf("Salah Username\n");
            break;
        case 1:
            printf("Salah Password\n");
            printf("Maksimal percobaan 3 : %d\n", s+1);
            break;
        case 2:
            ProcesData();
            in = Select(name);
            removeacc();
            s = 3;
            break;
            // break;
        }
        s++;
    }
}

/**
 * Description : menghapus data pada file stream
 * Author : Alif ardika - 2501990470
 */

void removeacc(){
    fp = fopen("database.in", "w");
    for(int i = 0; i < last-1;i++){
        if(i == in){
            continue;
        }
        else{
            fprintf(fp, "%s %s %s %llu %s\n", nasabah[i].name, nasabah[i].contact, nasabah[i].pass, nasabah[i].money, nasabah[i].date);
        }
    }
    fclose(fp);
    printf("Data atas nama %s telah di hapus\n", currUser.name);
    puts("Terimakasih.....");

}

/**
 * Description : untuk efek delay
 * Author : Alif ardika - 2501990470
 */

void delay(){ for (int i=0; i<1.5e8; i++){} }

int main(){
    system("clear");
    int menu = 0;
    while(!menu){
        puts("Halo Selamat Datang di Bank Sunib");
        puts("Silahkan Pilih");
        puts("1.Buat akun");
        puts("2.Masuk");
        puts("3.Hapus akun");
        int z;
        scanf("%d", &z);
        switch (z){
        case 1:
            create();
            break;
        case 2:
            login();
            menu = 1;
            break;
        case 3:
            rmvlogin();
            break;
        default:
            printf("Input Invalid\n");
            printf("COBA LAGI!!!\n");
            break;
        }
    }

    return 0;
}