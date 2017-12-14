#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define RIAD_ZAM 6											 // poèet riadkov na jedneho zamestnanca

FILE *vypis(FILE *fptr, int *v, int *poc_riad) {			// funkcia "v"
	char ch;
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
		for (int i = 1; i < *poc_riad; i++) {				//Vypis suboru na obrazovku
			if (i % 6 == 1) printf("Meno a priezvysko: ");
			if (i % 6 == 2) printf("SPZ: ");
			if (i % 6 == 3) printf("Typ auta: ");
			if (i % 6 == 4) printf("Cena: ");
			if (i % 6 == 5) printf("Datum: ");
			while (!feof(fptr))
			{
				ch = fgetc(fptr);
				printf("%c", ch);
				if (ch == '\n')
				{
					break;
				}
			}
		}
	}
	rewind(fptr);											//Vracia fptr na zaciatok suboru
	return(fptr);											//Funkcia vracia smernik na subor
}

void odmeny(FILE *fptr) {									//Funkcia "o"
	int datum, pom, TYP;	
	scanf("%d", &datum);									//Nacitanie datumu 'RRRRMMDD'
	char MENO[55], SPZ[8], CENA[10], znak;;
	long int DATUM;
	float odmena;

	while (!feof(fptr)) {									//Postupne nacitanie udajov
		if (fgets(MENO, 53, fptr) == NULL) break;
		MENO[strlen(MENO) - 1] = '\0';						//Nahradenie znaku'\n' znakom konca retazca
		fgets(SPZ, 8, fptr);
		fscanf(fptr, "%d\n", &TYP);
		fgets(CENA, 10, fptr);
		CENA[strlen(CENA) - 1] = '\0';
		fscanf(fptr, "%li", &DATUM);
		if ((datum - DATUM) >= 10000) {						//Zistenie ci pracuje viac ako rok
			if (TYP == 1) odmena = atof(CENA)*0.015;
			if (TYP == 0) odmena = atof(CENA)*0.022;
			printf("%s %s %.2lf\n", MENO, SPZ, odmena);		//Vypis na obrazovku
		}
		fgets(MENO, 50, fptr);								//Nacitanie prazdneho riadku
		//fgets(MENO, 50, fptr);								
	}
	rewind(fptr);
}

char * npole(FILE *fptr) {									//Funkcia "n"
	
	int pocetzam = 1;
	char ch, RIADOK[55], SPZ[8];
	
	while (!feof(fptr))										//Pocitanie poctu SPZ
	{
		ch = fgetc(fptr);
		if (ch == '\n')
		{
			(pocetzam)++;
		}
	}
	
	pocetzam /= RIAD_ZAM;
	int i, j;
	char **pompol = malloc(pocetzam * sizeof(char*));		//Alokacia dynamickeho pola rozmer Y
	for (i = 0; i < pocetzam; i++)							//Alokacia dynamickeho pola rozmer X
		pompol[i] = (char*)malloc(10 * sizeof(char));

	j = 0;
	rewind(fptr);
	while (!feof(fptr)) {									//Nacitavanie SPZ
		i = 0;
		if (fgets(RIADOK, 55, fptr) == NULL) break;
		ch = fgetc(fptr);
		while (ch != '\n') {								//Prepis SPZ do pola
			pompol[j][i] = ch;
			ch = fgetc(fptr);
			i++;
		}
		pompol[j][i] = '\0';
		fgets(RIADOK, 50, fptr);
		fgets(RIADOK, 50, fptr);
		fgets(RIADOK, 50, fptr);
		fgets(RIADOK, 50, fptr);
		j++;
	}
	rewind(fptr);
	return(pompol);											//Funkcia vracia ukazovatel na adresu pola s SPZ
}

void vypispol(char **polspz, int pocetzam) {				//Funkcia "s"
	pocetzam /= RIAD_ZAM;
	for (int j = 0; j < pocetzam; j++) {					//Vypis SPZ na obrazovku
		for (int i = 0; i < 8; i++) {						//Vsunutie medzery po 2. a 5. znaku
			if (i == 2 || i == 5)
				printf(" ");
			printf("%c", polspz[j][i]);
		}
		printf("\n");										//Odriadkovanie po vypisanej spz
	}
}

void palindrom(char **spztky, int pocetzam)					//Funkcia "p"
{
	pocetzam /= RIAD_ZAM;
	int i, j, bol;											// bol- TRUE/FALSE palindrom
	for (j = 0; j < pocetzam; j++) {						//Prechadzanie pola s SPZ
		bol = 1;											//Predpoklad ze SPZ je palindrom
		for (i = 0; i < 3; i++)
			if (spztky[j][i] != spztky[j][6 - i]) {			//Ak neni tak bol=FALSE
				bol = 0;
			}
		if (bol == 1)										//Ak je to palindrom tak ho vypise
			printf("%c%c\n", spztky[j][0], spztky[j][1]);	
	}
}

void najpredaj(char **spztky, int pocetzam) {				//Funkcia "z" - BONUS
	char **pole = malloc(pocetzam * sizeof(char *)), pom[3]; //Vytvorenie dynam. pola pre rozmer Y
	for (int i = 0; i < pocetzam; i++)						// Vytvorenie dynam. pola pre rozmer X
		pole[i] = (char*)malloc(3 * sizeof(char));

	int *pocetpol = malloc(pocetzam * sizeof(int)),bolean=1,riadok=0;	//Vytvorenie pola s poctom SPZ daneho okresu

	for (int j = 0; j < pocetzam; j++) {					//Prechod cez pole so SZP
		bolean = 1;											//bolean - TRUE/FALSE - ci sa uz nachadza v poli s znackami okresu
		for (int i = 0; i < 2; i++)							//Prepis prvych dvoch znakov SPZ do pomocneho pola
			pom[i] = spztky[j][i];
		pom[2] = '\0';
		
		for (int i = 0; i <= riadok; i++) {					//Porovnavanie ci sme sa uz stretli s takym okresom
			if (!strcmp(pom, pole[i])) {					//Ak ano bolean=0 - prvok sa uz opakuje
				bolean = 0;
				break;										//netreba porovnavat dalej
			}
		}
		if (bolean) {										//Ak sa prvok este neopakuje
			int count = 0;
			for (int i = 0; i < pocetzam; i++) {			//Pocet rovnakych okresov v poli so SPZ
					if (spztky[j][0]==spztky[i][0])
						if (spztky[j][1]==spztky[i][1])
							count++;
			}
			pocetpol[riadok] = count;						//Ulozenie poctu daneho okresu
		}

		if (bolean) {										//Ak sa prvok este neopakuje
			strcpy(pole[riadok], pom);						//Ulozenie znacky daneho okresu
				riadok++;									//Ukazovatel na dalsie prazdne miesto
		}
	}
	int max=0;										
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
	char znak, **spztky = NULL;
	FILE *subor = NULL;
	poc_riad = (int*)malloc(sizeof(int));
	*poc_riad = 0;
	do {
		scanf("%c", &znak);											//Nacitanie ovladacieho znaku
		switch (znak) {
		case 'v': subor = vypis(subor, &v, poc_riad);
			break;
		case 'o': if (v == 1) odmeny(subor);
			break;
		case 'n': {
			if (v == 1) {
				if (spztky != NULL)									//Ak je pole uz vytvorene tak ho dealokuje
					for (int i = 0; i < *poc_riad/RIAD_ZAM; i++)
						free(spztky[i]);
				free(spztky);
				spztky = npole(subor);
			}
		}
			break;
		case 's':if (spztky != NULL)
			vypispol(spztky, *poc_riad);
			break;
		case 'p': if (spztky != NULL)
			palindrom(spztky, *poc_riad);
			break;
		case 'z':if (spztky != NULL)
			najpredaj(spztky,*poc_riad/RIAD_ZAM);
			break;
		}
	} while (znak != 'k');											//Pri stlaceni "k" - koniec programu
	if (subor != NULL)												//Zatvorenie suboru
		fclose(subor);
}