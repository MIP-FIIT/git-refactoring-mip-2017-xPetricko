#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

typedef struct polozka {										//Definovanie struktury.
	char category[52];											//Prvky struktury.
	char brand[52];
	char owner[102];
	long int price;
	int build_year;
	char state[202];
	struct polozka *dalsi;
} polozka;

void mem_dealoc(polozka **beg, polozka **act);					//Deklaracia funkcie pre dealokáciu pamäte.
void mem_aloc(polozka **beg, polozka **act);					//Deklaracia funkcie "n".
void mem_print(polozka *beg);									//Deklaracia funkcie "v".
void mem_add(polozka **beg);									//Deklaracia funkcie "p".
void mem_del(polozka **beg);										//Deklaracia funkcie "z".
void mem_search(polozka *beg);									//Deklaracia funkcie "h".
void mem_replace(polozka *beg);									//Deklaracia funkcie "a".

void main() {
	char znak;
	polozka *begin = NULL, *actual = NULL;
	printf("Linearny zoznam. Vyber Funkciu.\n");				//Uvodny komentar pre pouzivatela.
	printf("n - nacitanie zoznamu\n");
	printf("v - vypisanie zoznamu\n");
	printf("p - pridanie vlastneho prvku do zoznamu\n");
	printf("z - zmazanie prvku podla znacky\n");
	printf("h - vypisanie poloziek pod konkretnu cenu\n");
	printf("a - aktualizacia prvku v zozname podla znacky a ceny\n");
	printf("k - ukoncenie programu\n");
	printf("\n");

	do {														//Cyklus programu.
		scanf("%c", &znak);										
		switch (znak) {											//Switch na konkretnu funkciu.
		case 'n':												
			if (begin != NULL)									//Dealokacia zoznamu ak uz existuje.
				mem_dealoc(&begin, &actual);					//Funkcia dealokacie.
			mem_aloc(&begin, &actual);							//Volanie funkcie "n".
			break;
		case 'v': if (begin != NULL) mem_print(begin);			//Volanie funkcie "v" ak  zoznam existuje.
				  else printf("Zoznam je prazdny.\n");
			break;
		case 'p': mem_add(&begin);								////Volanie funkcie "p".
			break;
		case 'z': if (begin != NULL) mem_del(&begin);			//Volanie funkcie "z" ak zoznam existuje.
				  else printf("Zoznam je prazdny.\n");
			break;
		case 'h': if (begin != NULL) mem_search(begin);			//Volanie funkcie "h" ak zoznam existuje.
				  else printf("Zoznam je prazdny.\n");
			break;
		case 'a': if (begin != NULL) mem_replace(begin);		//Volanie funkcie "a" ak zoznam existuje.
				  else printf("Zoznam je prazdny.\n");
			break;
		}
	} while (znak != 'k');										//Ukoncenie cyklu ak je zadany znak 'k'.
	if (begin != NULL)											//Funkcia dealokacie zoznamu ak zoznam existuje.
		mem_dealoc(&begin, &actual);
	printf("Program bol ukonceny. Pre zavretie okna stlac ENTER.\n");
	getchar();
	getchar();
}

void mem_dealoc(polozka **beg, polozka **act) {					//Funkcia dealokacie zoznamu.
	do {
		(*act) = (*beg);					//Nasmerovanie ukazovatela na prvu polozku.
		(*beg) = (*act)->dalsi;				//Posunutie zaciatku zoznamu na dalsiu polozku.
		free(*act);							//Uvolnenie prvej polozky.
	} while (*beg != NULL);
	printf("Zoznam bol vymazany.\n");
}			

void mem_aloc(polozka **beg, polozka **act) {					//Funkcia "n"- nacitanie.
	FILE *fptr;
	polozka *pol;
	char pom[202];
	int counter = 0;
	if ((fptr = fopen("auta.txt", "r")) == NULL)			//Otvorenie suboru.
		printf("Subor nebol otvoreny.");
	else {
		while (!feof(fptr)) {
			if (fgets(pom, 202, fptr) == NULL) break;		//postupne nacitavanie riadku.
			if (pom[0] == '$') {							//ak sa najde znak $ vytvori sa polozka v zozname
				pol = (polozka*)malloc(sizeof(polozka));	//vytvorenie pomocnej polozky
				if (counter == 0) {
					(*beg) = pol;							//ak je prva prida sa na zaciatok
					(*act) = (*beg);
				}
				else {
					(*act)->dalsi = pol;					//ak uz prva existuje prida sa na koniec zoznamu
					(*act) = (*act)->dalsi;					//posunie sa ukazovatel na koniec zoznamu
				}
				counter++;									//pocet zaznamov
				(*act)->dalsi = NULL;						//ukoncenie zoznamu

			}
			fgets(pom, 202, fptr);							//Nacitavanie prvkov do vytvvorenej pomocnej polozky
			pom[strlen(pom) - 1] = '\0';			
			strcpy(pol->category, pom);					

			fgets(pom, 202, fptr);
			pom[strlen(pom) - 1] = '\0';
			strcpy(pol->brand, pom);

			fgets(pom, 202, fptr);
			pom[strlen(pom) - 1] = '\0';
			strcpy(pol->owner, pom);

			fgets(pom, 202, fptr);
			pom[strlen(pom) - 1] = '\0';
			pol->price = atol(pom);

			fgets(pom, 202, fptr);
			pom[strlen(pom) - 1] = '\0';
			pol->build_year = atoi(pom);

			fgets(pom, 202, fptr);
			pom[strlen(pom) - 1] = '\0';
			strcpy(pol->state, pom);

			pol = NULL;
		}
		fclose(fptr);
	}
	if (counter == 0)										//Vypis ak sa nevytvorila ziadna polozka.
		printf("Zoznam bol vytvoreny prazdny.");
	else {													//Vypis ak sa vv zozname nachadzaju nejake polozky.
		printf("Zoznam bol vytvoreny, ");			
		if (counter == 1) printf("nacitala sa %d polozka.\n", counter);
		if (counter > 1 && counter < 5) printf("nacitali sa %d polozky.\n", counter);
		if (counter >= 5) printf("nacitalo sa %d poloziek.\n", counter);
	}
}			

void mem_print(polozka *beg) {									//Funkcia "v" - vypis
	polozka *act;
	int counter = 1;
	act = beg;
	while (act != NULL) {									//Cyklus na prejdenie zoznamu.
		printf("%d.\n", counter);							//Vypis prvkov zoznamu.
		printf("kategoria: %s\n", act->category);
		printf("znacka: %s\n", act->brand);
		printf("predajca: %s\n", act->owner);
		printf("cena: %ld\n", act->price);
		printf("rok_vyroby: %d\n", act->build_year);
		printf("stav_vozidla: %s\n", act->state);
		act = act->dalsi;
		counter++;
	}											
}

void mem_add(polozka **beg) {									//Funkcia "p" - pridanie do zoznamu
	polozka *act, *poms;
	char riadok[202];
	int pos;
	act = (*beg);
	printf("Zadaj poziciu polozky v zozname: ");	
	scanf("%d", &pos);										//Nacitanie pozicie.
	fgets(riadok, 50, stdin);
	poms = (polozka*)malloc(sizeof(polozka));				//Vytvorenie pomocnej polozky.

	printf("Zadaj typ vozidla: ");							//Nacitanie udajov do pomocnej polozky.
	fgets(riadok, 50, stdin);
	riadok[strlen(riadok) - 1] = '\0';
	strcpy(poms->category, riadok);

	printf("Zadaj znacku vozidla: ");
	fgets(riadok, 50, stdin);
	riadok[strlen(riadok) - 1] = '\0';
	strcpy(poms->brand, riadok);

	printf("Zadaj predajcu: ");
	fgets(riadok, 100, stdin);
	riadok[strlen(riadok) - 1] = '\0';
	strcpy(poms->owner, riadok);

	printf("Zadaj cenu vozidla: ");
	fgets(riadok, 200, stdin);
	riadok[strlen(riadok) - 1] = '\0';
	poms->price = atol(riadok);

	printf("Zadaj rok vyroby vozidla: ");
	fgets(riadok, 200, stdin);
	riadok[strlen(riadok) - 1] = '\0';
	poms->build_year = atoi(riadok);

	printf("Zadaj stav vozidla: ");
	fgets(riadok, 200, stdin);
	riadok[strlen(riadok) - 1] = '\0';
	strcpy(poms->state, riadok);
	if ((*beg) == NULL) {									//Ak Zoznam neni vytvoreny polozka sa prida na zaciatok.
		(*beg) = poms;
		poms->dalsi = NULL;
	}
	else {
		if (pos == 1) {										//Ak je pozicia 1 tak sa zoznam posunie.
			poms->dalsi = (*beg);
			(*beg) = poms;
		}
		else {
			for (int i = 2; i < pos; i++) {					//Ak je pozicia>=2 hlada sa kam sa umiestni v zozname.
				act = act->dalsi;
				if (act->dalsi == NULL) break;				//Ak cyklus dojde na koniec tak sa ukonci
			}
			if (act->dalsi == NULL) {						//Ak sa ma prvok pridat na koniec
				act->dalsi = poms;
				poms->dalsi = NULL;
			}
			else {											//ak sa ma prvok pridat niekde do stredu zoznamu
				poms->dalsi = act->dalsi;
				act->dalsi = poms;
			}
		}
	}
	
}

void mem_del(polozka **beg) {									//Funkcia "z" - zmazat.
	char search[50];
	polozka *akt, *prev;
	char brand_h[52];
	int counter = 0;
	printf("Zadaj hladane znaky: ");						//Nacitanie hladanych znakov.
	fgets(search, 50, stdin);
	fgets(search, 50, stdin);
	_strupr(search);										//Zmena vsetkych pismen na velke.
	akt = (*beg);
	prev = (*beg);
	search[strlen(search) - 1] = '\0';
	do {													//Cyklus prejdenia zoznamu.
		strcpy(brand_h, akt->brand);						//Nacitanie znacky do pomocnej premmenej.
		_strupr(brand_h);									//Zdvihnutie znakov na velke.
		if (strstr(brand_h, search) != NULL) {				//Ak sa nachadza hladany vyraz v znacke.
			if (akt==(*beg)) {								//Ak sa nachadzame na zaciatku zoznamu.
				(*beg) = akt->dalsi;						//Zmazanie prvej polozky v zozname.
				prev = akt->dalsi;
				free(akt);
				akt = prev;

			}
			else {											//Ak to nie je prva polozka.
				if (akt->dalsi == NULL) {					//Zmazanie poslednej polozky.
					free(akt);
					akt = NULL;
					prev->dalsi = NULL;
				}
				else {										//Zmazanie polozky uprostred zoznamu.
					prev->dalsi = akt->dalsi;
					free(akt);
					akt = prev->dalsi;
				}
			}
			counter++;										//Pocet zmazanych poloziek.
		}
		else {												//V pripade ak sa polozka nemaze.
			if (akt!=(*beg))								//Prvy krat sa smernik neposuva aby ukazoval na predchadzajucu polozku
				prev = prev->dalsi;
			akt = akt->dalsi;								//Posun na dalsiu polozku.
			
		}
	} while (akt != NULL);
	printf("Zmazalo sa %d ", counter);						//Vypis vysledkov.
	if (counter == 1) printf("polozka.\n");
	if (counter>1&&counter<5) printf("polozky.\n");
	if (counter >4|| counter==0) printf("poloziek.\n");
}

void mem_search(polozka *beg) {									//Funkcia "h" - hladanie podla ceny.
	int cena, bol = 1, counter = 1;
	printf("Zadaj maximalnu cenu: ");						//Nacitanie maximalnej ceny.
	scanf("%d", &cena);
	polozka *poms;
	poms = beg;
	do {
		if ((poms->price) <= cena) {						//ak je cena polozky<=maximalna cena tak polozku vypise.
			printf("%d.\n%s\n%s\n%s\n%li\n%d\n%s\n", counter, poms->category, poms->brand, poms->owner, poms->price, poms->build_year, poms->state);
			counter++;
			bol = 0;
		}
		poms = poms->dalsi;

	} while (poms != NULL);

	if (bol)												//Vypis ak sa nenajsla ziadna polozka.
		printf("V ponuke su len auta s vyssou cenou.\n");

}

void mem_replace(polozka *beg) {								//Funkcia "a" - aktualizacia zoznamu.
	char brand_h[52], riadok[202];
	long int price_h;
	int counter = 0, first = 0;
	polozka *act, *update = NULL;
	printf("Zadaj presnu znacku vozidla: ");				//Nacitanie hladanej znacky.
	fgets(brand_h, 50, stdin);
	fgets(brand_h, 50, stdin);
	brand_h[strlen(brand_h) - 1] = '\0';
	printf("Zadaj presnu cenu vozidla: ");
	price_h = atol(fgets(riadok, 50, stdin));				//Nacitanie hladanej ceny.
	act = beg;
	do {													//Cyklus na prejdenie zoznamu.
		if (first)
			act = act->dalsi;
		if (strcmp(act->brand, brand_h) == 0) {				//Porovanvanie znacky.
			if (act->price == price_h) {
				if (update == NULL) {						//Vytvorenie aktualizovanej polozky.
					printf("Zadaj typ vozidla: ");
					fgets(riadok, 50, stdin);
					riadok[strlen(riadok) - 1] = '\0';
					strcpy(act->category, riadok);

					printf("Zadaj znacku vozidla: ");
					fgets(riadok, 50, stdin);
					riadok[strlen(riadok) - 1] = '\0';
					strcpy(act->brand, riadok);

					printf("Zadaj predajcu: ");
					fgets(riadok, 100, stdin);
					riadok[strlen(riadok) - 1] = '\0';
					strcpy(act->owner, riadok);

					printf("Zadaj cenu vozidla: ");
					fgets(riadok, 200, stdin);
					riadok[strlen(riadok) - 1] = '\0';
					act->price = atol(riadok);

					printf("Zadaj rok vyroby vozidla: ");
					fgets(riadok, 200, stdin);
					riadok[strlen(riadok) - 1] = '\0';
					act->build_year = atoi(riadok);

					printf("Zadaj stav vozidla: ");
					fgets(riadok, 200, stdin);
					riadok[strlen(riadok) - 1] = '\0';
					strcpy(act->state, riadok);
					update = act;
				}
				else {											//prepis aktualizovanej polozky do polozky v zozname
					strcpy(act->category, update->category);
					strcpy(act->brand, update->brand);
					strcpy(act->owner, update->owner);
					act->price = update->price;
					act->build_year = update->build_year;
					strcpy(act->state, update->state);
				}
				counter++;
			}
		}
		first = 1;
	} while (act->dalsi != NULL);
	
	if (counter > 0) {											//Vypis vysledkov.
		printf("Bolo zmenenych %d ", counter);
		if (counter == 1) printf("polozka.\n");
		if (counter > 1 || counter < 5) printf("polozky.\n");
		if (counter > 5) printf("poloziek.\n");
	}
	else
		printf("Nebola najdena zhoda v zozname.\n");
}