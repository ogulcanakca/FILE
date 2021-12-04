#include<stdio.h>
#include<conio.h>
#include<string.h>
#include <stdlib.h>
int main(void)
{
    FILE* fp;
    FILE *optr;
    fpos_t pos;
    const char* p = "Bilgisayar";
    int id;

    if ((fp = fopen("dosya.txt", "w+")) == NULL) {
        printf("Dosya açma hatası!");
        exit(1);
    }

    while (*p) {
        fgetpos(fp, &pos);
        printf("Dosyanın aktif konumu: %ld", pos);        
        fputc(*p, fp);

        printf(" karakter: %c\n", *p);
        p++;
    }
    printf("\n");

    rewind(fp);

    while ((id = fgetc(fp)) != EOF) { /* Dosya sonuna kadar (EOF) karakter karakter okuma işlemi */
        printf("%c", id);
    }
    
    fclose(fp);
    
    return 0;
}