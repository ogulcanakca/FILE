#include <stdio.h>

struct musteriData {
	int musNum;
	char soyad[15];
	char ad[10];
	double balans;
};


int main()
{
	FILE* mfptr;

	struct musteriData ogulcan = { 0,"Akca", "Ogulcan", 10 };
	if ((mfptr = fopen("kredi.txt", "r+")) == NULL) {
		printf("Dosya açýlamadý.\n");
	}
	else {
		printf("Hesap numarasý giriniz");
		scanf("%d", &ogulcan.musNum);
		while (ogulcan.musNum != 0) {
			printf("Soyadý, adý, balansý giriniz. \n");
			fscanf(stdin, "%s %s %lf", ogulcan.soyad, ogulcan.ad, &ogulcan.balans);
			fseek(mfptr, (ogulcan.musNum - 1) * sizeof(struct musteriData), SEEK_SET);
			fwrite(&ogulcan, sizeof(struct musteriData), 1, mfptr);
			printf("Hesap numarasýnýz giriniz.\n");
			scanf("%d", &ogulcan.musNum);

		}
		fclose(mfptr);
	}
	
}


