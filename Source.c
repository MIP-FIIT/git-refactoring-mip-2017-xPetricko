#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define RIAD_ZAM 6		// poèet riadkov na jedneho zamestnanca

typedef struct polozka {										//Definovanie struktury.
	char name[52];											//Prvky struktury.
	char SPZ[52];
	int type;
	long int price;
	long int date;
	struct polozka *next;
} polozka;

FILE *vypis(FILE *fptr, int *v, int *poc_riad, polozka **beg) {			// funkcia "v"
	char ch;
	char riadok[55];
	polozka *act = NULL, *pom = NULL;
	if (*v == 0) {											// zistuje ci bol subor uz otvoreny
		fptr = fopen("predaj.txt", "r");					// ak nie otvory subor
	}

	if (fptr == NULL) {										//Nepodarilo sa otvorit subor
		printf("Neotvoreny subor\n");
		return(fptr);
	}
	else {													//Podarilo sa otvoit subor
		*v = 1;
		*poc_riad = 1;
		while (!feof(fptr))									//Poèítanie riadkov v subore.
		{
			ch = fgetc(fptr);
			if (ch == '\n')
			{
				(*poc_riad)++;
			}
		}
		rewind(fptr);
		for (int i = 1; i <= (*poc_riad) / 6; i++) {
			pom = (polozka*)malloc(sizeof(polozka));
			if (i == 1) {
				(*beg) = pom;
				act = (*beg);
			}
			else {
				act->next = pom;
				act = act->next;
				act->next = NULL;
			}
		}
		act = (*beg);
		for (int i = 1; i < *poc_riad; i++) {				//Vypis suboru na obrazovku
			if (i % 6 == 1) printf("Meno a priezvysko: ");
			if (i % 6 == 2) printf("SPZ: ");
			if (i % 6 == 3) printf("Typ auta: ");
			if (i % 6 == 4) printf("Cena: ");
			if (i % 6 == 5) printf("Datum: ");
			fgets(riadok, 52, fptr);
			printf("%s", riadok);
			riadok[strlen(riadok) - 1] = '\0';
			if (i % 6 == 1) strcpy(act->name, riadok);
			if (i % 6 == 2) strcpy(act->SPZ, riadok);
			if (i % 6 == 3) act->type = atoi(riadok);
			if (i % 6 == 4) act->price = atof(riadok);
			if (i % 6 == 5) act->date = atol(riadok);
			if (i % 6 == 0) act = act->next;
		}
	}
	rewind(fptr);											//Vracia fptr na zaciatok suboru
	return(fptr);											//Funkcia vracia smernik na subor
}

void odmeny(polozka *beg) {									//Funkcia "o"	
	long int datum;
	scanf("%d", &datum);
	polozka *act;
	act = beg;
	while (act != NULL) {
		if (datum - act->date >= 10000)
			printf("%s %s %.2lf\n", act->name, act->SPZ, (0.022 - (act->type)*0.007)*act->price);
		act = act->next;
	}
}

void vypispol(polozka *beg) {				//Funkcia "s"
	polozka *act;
	act = beg;
	while (act != NULL) {
		for (int i = 0; i < 8; i++) {						//Vsunutie medzery po 2. a 5. znaku
			if (i == 2 || i == 5)
				printf(" ");
			printf("%c", act->SPZ[i]);
		}
		printf("\n");
		act = act->next;
	}
}


void palindrom(polozka *beg)					//Funkcia "p"
{
	polozka *act;
	act = beg;
	while (act != NULL) {
		if (act->SPZ[0] == act->SPZ[6])
			if (act->SPZ[1] == act->SPZ[5])
				if (act->SPZ[2] == act->SPZ[4])
					printf("%s\n", act->SPZ);
		act = act->next;
	}
}

void najpredaj(polozka *beg, int pocetzam) {
	polozka *act,*zac;
	char **pole = (char**)malloc(pocetzam * sizeof(char *)), pom[3]; //Vytvorenie dynam. pola pre rozmer Y
	for (int i = 0; i < pocetzam; i++)						// Vytvorenie dynam. pola pre rozmer X
		pole[i] = (char*)malloc(3 * sizeof(char));

	int *pocetpol = (int*)malloc(pocetzam * sizeof(int)), bolean = 1, riadok = 0;	//Vytvorenie pola s poctom SPZ daneho okresu
	zac = beg;
	for (int j = 0; j < pocetzam; j++) {					//Prechod cez pole so SZP
		act = beg;
		for (int a = 0; a < j; a++)
			zac = act->next;
		act = zac;
		bolean = 1;											//bolean - TRUE/FALSE - ci sa uz nachadza v poli s znackami okresu						//Prepis prvych dvoch znakov SPZ do pomocneho pola
		pom[0] = act->SPZ[0];
		pom[1] = act->SPZ[1];
		pom[2] = '\0';

		for (int i = 0; i <= riadok; i++) {					//Porovnavanie ci sme sa uz stretli s takym okresom
			if (!strcmp(pom, pole[i])) {					//Ak ano bolean=0 - prvok sa uz opakuje
				bolean = 0;
				break;										//netreba porovnavat dalej
			}
		}
		if (bolean) {										//Ak sa prvok este neopakuje
			int count = 0;
			for (int i = j; i < pocetzam; i++) {			//Pocet rovnakych okresov v poli so SPZ
				if (zac->SPZ[0] == act->SPZ[0])
					if (zac->SPZ[1] == act->SPZ[1])
						count++;
				act = act->next;
			}
			pocetpol[riadok] = count;						//Ulozenie poctu daneho okresu
		}

		if (bolean) {										//Ak sa prvok este neopakuje
			strcpy(pole[riadok], pom);						//Ulozenie znacky daneho okresu
			riadok++;									//Ukazovatel na dalsie prazdne miesto
		}
	}
	int max = 0;
	for (int i = 0; i < riadok; i++)						//Najdenie maxima
		if (pocetpol[i] > max)
			max = pocetpol[i];

	for (int i = 0; i < riadok; i++)						//Ak je pocet SPZ daneho okresu == max tak vypise okres a pocet
		if (pocetpol[i] == max)
			printf("%s %d\n", pole[i], pocetpol[i]);

	for (int i = 0; i < pocetzam; i++)						//uvolnenie poli
		free(pole[i]);

	free(pole);
	free(pocetpol);

}

void main()
{
	int v = 0, *poc_riad;
	char znak;
	FILE *subor = NULL;
	polozka *beg = NULL;
	poc_riad = (int*)malloc(sizeof(int));
	*poc_riad = 0;
	do {
		scanf("%c", &znak);											//Nacitanie ovladacieho znaku
		switch (znak) {
		case 'v': subor = vypis(subor, &v, poc_riad, &beg);
			break;
		case 'o': if (v == 1) odmeny(beg);
			break;
		case 's':if (v == 1)
			vypispol(beg);
			break;
		case 'p': if (v == 1)
			palindrom(beg);
			break;
		case 'z':if (v == 1)
			najpredaj(beg, *poc_riad / RIAD_ZAM);
			break;
		}
	} while (znak != 'k');											//Pri stlaceni "k" - koniec programu
	if (subor != NULL)												//Zatvorenie suboru
		fclose(subor);
}