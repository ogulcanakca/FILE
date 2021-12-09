#include <stdio.h>


struct musData {
    int musNum;
    char soyad[21];
    char ad[21];
    double balans;

};

int secimGir(void);
void textFile(FILE*);
void yenileKayit(FILE*);
void yeniKayit(FILE*);
void silKayit(FILE*);

int secimGir(void) {
    int menuSecim;

    printf("\n Hangi işlemi yapacaksanız, numaralandırmayı ona göre yapınız.\n"
        "1 - Çağırılan hesabın formatlı text dosyasını yükle\n"
        "2 - Hesabı yenile\n"
        "3 - Yeni hesap ekle\n"
        "4 - Hesap sil\n"
        "5 - Çıkış");

    (void)scanf_s("%d", &menuSecim);

    return menuSecim;

}

int main()
{
    FILE* mfPtr;
    int secim;

    if ((mfPtr = fopen("kredi.dat", "r+")) == NULL) {
        printf("Dosya açılamadı, \n");
    }
    else {
        while ((secim = secimGir()) != 5) {
            switch (secim) {
            case 1:
                textFile(mfPtr);
                break;
            case 2:
                yenileKayit(mfPtr);
                break;
            case 3:
                yeniKayit(mfPtr);
                break;
            case 4:
                silKayit(mfPtr);
                break;
            }
        }
        fclose(mfPtr);
    }
    return 0;
}

void textFile(FILE* okuPtr) {
    FILE* yazPtr;

    struct musData musteri = { 0, "", "", 0.0 };

    if ((yazPtr = fopen("hesaplar.txt", "w")) == NULL) {
        printf("Dosya açılamadı. \n");

    }
    else {
        rewind(okuPtr);
        fprintf(yazPtr, "%-6s %-16s %-11s %10s \n", "Hesap", "Soyadı",
            "Adı", "Balans");
        while (!feof(okuPtr)) {
            fread(&musteri, sizeof(struct musData), 1, okuPtr);
            if (musteri.musNum != 0) {
                fprintf(yazPtr, "%-6d %-16s %-11s %10.2f\n", musteri.musNum, musteri.soyad, musteri.ad, musteri.balans);
            }
            
        }
        fclose(yazPtr);
    }
}

void yenileKayit(FILE* fPtr) {
    int hesap;
    double islem;
    struct musData musteri = { 0, "", "", 0.0 };

    printf("Yenilenecek hesap no giriniz (1-100): ");
    (void)scanf_s("%d", &hesap);
    fseek(fPtr, (hesap - 1) * sizeof(struct musData), SEEK_SET);
    fread(&musteri, sizeof(struct musData), 1, fPtr);
    if (musteri.musNum == 0) {
        printf("Hesap #%d hakkında bilgi yok.\n", hesap);
    }
    else {
        printf(" %-6d %-16s %-11s %10.2f\n\n ", musteri.musNum, musteri.soyad,
            musteri.ad, musteri.balans);
        printf("Ekleme (+) veya ödeme (-) için giriniz:");
        (void)scanf_s("%lf", &islem);
        musteri.balans += islem;
        printf("%-6d %-16s %-11s %10.2f\n", musteri.musNum, musteri.soyad,
            musteri.ad, musteri.balans);
        fseek(fPtr, (hesap - 1) * sizeof(struct musData), SEEK_SET);
        fwrite(&musteri, sizeof(struct musData), 1, fPtr);
    }
}

void silKayit(FILE* fPtr) {
    struct musData musteri, bosmusteri = { 0,"","",0 };
    int hesapNum;

    printf("Silinecek hesap numarasını giriniz (1-100) : ");
    (void)scanf_s("%d", &hesapNum);
    fseek(fPtr, (hesapNum - 1) * sizeof(struct musData), SEEK_SET);
    fread(&musteri, sizeof(struct musData), 1, fPtr);
    if (musteri.musNum == 0) {
        printf("Hesap %d yoktur. \n", hesapNum);
    }
    else {
        fseek(fPtr, (hesapNum - 1) * sizeof(struct musData), SEEK_SET);
        fwrite(&bosmusteri, sizeof(struct musData), 1, fPtr);

    }

    
}

void yeniKayit(FILE* fPtr) {
    struct musData musteri = { 0,"", "", 0.0 };
    int hesapNum;
    printf("Yeni hesap no gir (1-100): ");
    (void)scanf("%d", &hesapNum);
    fseek(fPtr, (hesapNum - 1) * sizeof(struct musData), SEEK_SET);
    fread(&musteri, sizeof(struct musData), 1, fPtr);
    if (musteri.musNum != 0) {
        printf("Hesap #%d bir hesaba sahiptir. Yeni no gir \n", musteri.musNum);

    }

    else {
        printf("Soyadı, adı, balansı giriniz. \n");
        (void)scanf("%s %s %lf", &musteri.soyad, &musteri.ad, &musteri.balans);
        musteri.musNum = hesapNum;
        fseek(fPtr, (musteri.musNum - 1) * sizeof(struct musData), SEEK_SET);
        fwrite(&musteri, sizeof(struct musData), 1, fPtr);
    }
}