#include <stdio.h>

struct musteriData {
        int Id;
        char soyad[20];
        char adi[15];

    };
int main()
{
    int i;
    struct musteriData ogulcanAkca = { 0, "ogulcan", "akca" };
    FILE* fptr;
    FILE* fptr1 = fopen("musterii.txt", "w");
    if ((fptr = fopen("musteri.txt", "w")) == NULL) {
        printf("Dosya açýlamadý|n");
    
    }
    else {
        for (i = 1; i <= 1; i++) {
            fwrite(&ogulcanAkca, sizeof(struct musteriData), 1, fptr);
            fread(&ogulcanAkca, sizeof(struct musteriData), 1, fptr1);
            fwrite(&ogulcanAkca, sizeof(struct musteriData), 1, fptr1);
        }
        fclose(fptr);
    }
    return 0;
}


