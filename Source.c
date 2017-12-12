#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

typedef struct polozka {										
	char kategoria[52];											
	char znacka_vozidla[52];
	char majitel_vozidla[102];
	long int cena_vozidla;
	int rok_vyroby;
	char stav_vozidla[202];
	struct polozka *dalsi;
} polozka;

void cistenie_pamate(polozka **beg, polozka **act);					
void vytvorenie_pamate(polozka **beg, polozka **act);					
void vypisanie_zoznamu(polozka *beg);								
void pridanie_polozky_do_zoznamu(polozka **beg);								
void zmazanie_zo_zoznamu(polozka **beg);									
void hladanie_v_zozname(polozka *beg);								
void nahradenie_v_zozname(polozka *beg);								

void main() {
	char znak;
	polozka *zaciatok_zoznamu = NULL, *aktualne_v_zozname = NULL;
	printf("Linearny zoznam. Vyber Funkciu.\n");
	printf("n - nacitanie zoznamu\n");
	printf("v - vypisanie zoznamu\n");
	printf("p - pridanie vlastneho prvku do zoznamu\n");
	printf("z - zmazanie prvku podla znacky\n");
	printf("h - vypisanie poloziek pod konkretnu cenu\n");
	printf("a - aktualizacia prvku v zozname podla znacky a ceny\n");
	printf("k - ukoncenie programu\n");
	printf("\n");

	do {														
		scanf("%c", &znak);										
		switch (znak) {											
		case 'n':												
			if (zaciatok_zoznamu != NULL)									
				cistenie_pamate(&zaciatok_zoznamu, &aktualne_v_zozname);					
			vytvorenie_pamate(&zaciatok_zoznamu, &aktualne_v_zozname);							
			break;
		case 'v': if (zaciatok_zoznamu != NULL) vypisanie_zoznamu(zaciatok_zoznamu);		
				  else printf("Zoznam je prazdny.\n");
			break;
		case 'p': pridanie_polozky_do_zoznamu(&zaciatok_zoznamu);								
			break;
		case 'z': if (zaciatok_zoznamu != NULL) zmazanie_zo_zoznamu(&zaciatok_zoznamu);		
				  else printf("Zoznam je prazdny.\n");
			break;
		case 'h': if (zaciatok_zoznamu != NULL) hladanie_v_zozname(zaciatok_zoznamu);			
				  else printf("Zoznam je prazdny.\n");
			break;
		case 'a': if (zaciatok_zoznamu != NULL) nahradenie_v_zozname(zaciatok_zoznamu);		
				  else printf("Zoznam je prazdny.\n");
			break;
		}
	} while (znak != 'k');										
	if (zaciatok_zoznamu != NULL)											
		cistenie_pamate(&zaciatok_zoznamu, &aktualne_v_zozname);
	printf("Program bol ukonceny. Pre zavretie okna stlac ENTER.\n");
	getchar();
	getchar();
}

void cistenie_pamate(polozka **beg, polozka **act) {					
	do {
		(*act) = (*beg);					
		(*beg) = (*act)->dalsi;				
		free(*act);							
	} while (*beg != NULL);
	printf("Zoznam bol vymazany.\n");
}			

void vytvorenie_pamate(polozka **beg, polozka **act) {					
	FILE *fptr;
	polozka *pol;
	char pom[202];
	int pocitadlo = 0;
	if ((fptr = fopen("auta.txt", "r")) == NULL)			
		printf("Subor nebol otvoreny.");
	else {
		while (!feof(fptr)) {
			if (fgets(pom, 202, fptr) == NULL) break;		
			if (pom[0] == '$') {							
				pol = (polozka*)malloc(sizeof(polozka));	
				if (pocitadlo == 0) {
					(*beg) = pol;							
					(*act) = (*beg);
				}
				else {
					(*act)->dalsi = pol;					
					(*act) = (*act)->dalsi;					
				}
				pocitadlo++;									
				(*act)->dalsi = NULL;						
			}


			fgets(pom, 202, fptr);							
			pom[strlen(pom) - 1] = '\0';			
			strcpy(pol->kategoria, pom);					

			fgets(pom, 202, fptr);
			pom[strlen(pom) - 1] = '\0';
			strcpy(pol->znacka_vozidla, pom);

			fgets(pom, 202, fptr);
			pom[strlen(pom) - 1] = '\0';
			strcpy(pol->majitel_vozidla, pom);

			fgets(pom, 202, fptr);
			pom[strlen(pom) - 1] = '\0';
			pol->cena_vozidla = atol(pom);

			fgets(pom, 202, fptr);
			pom[strlen(pom) - 1] = '\0';
			pol->rok_vyroby = atoi(pom);

			fgets(pom, 202, fptr);
			pom[strlen(pom) - 1] = '\0';
			strcpy(pol->stav_vozidla, pom);

			pol = NULL;
		}
		fclose(fptr);
	}
	if (pocitadlo == 0)										
		printf("Zoznam bol vytvoreny prazdny.");
	else {													
		printf("Zoznam bol vytvoreny, ");			
		printf("nacitalo sa %d poloziek.\n", pocitadlo);
	}
}			

void vypisanie_zoznamu(polozka *beg) {									
	polozka *act;
	int pocitadlo = 1;
	act = beg;
	while (act != NULL) {									
		printf("%d.\n", pocitadlo);							
		printf("kategoria: %s\n", act->kategoria);
		printf("znacka: %s\n", act->znacka_vozidla);
		printf("predajca: %s\n", act->majitel_vozidla);
		printf("cena: %ld\n", act->cena_vozidla);
		printf("rok_vyroby: %d\n", act->rok_vyroby);
		printf("stav_vozidla: %s\n", act->stav_vozidla);
		act = act->dalsi;
		pocitadlo++;
	}											
}

void pridanie_polozky_do_zoznamu(polozka **beg) {									
	polozka *act, *poms;
	char riadok[202];
	int pos;
	act = (*beg);
	printf("Zadaj poziciu polozky v zozname: ");	
	scanf("%d", &pos);										
	fgets(riadok, 50, stdin);
	poms = (polozka*)malloc(sizeof(polozka));				

	printf("Zadaj typ vozidla: ");							
	fgets(riadok, 50, stdin);
	riadok[strlen(riadok) - 1] = '\0';
	strcpy(poms->kategoria, riadok);

	printf("Zadaj znacku vozidla: ");
	fgets(riadok, 50, stdin);
	riadok[strlen(riadok) - 1] = '\0';
	strcpy(poms->znacka_vozidla, riadok);

	printf("Zadaj predajcu: ");
	fgets(riadok, 100, stdin);
	riadok[strlen(riadok) - 1] = '\0';
	strcpy(poms->majitel_vozidla, riadok);

	printf("Zadaj cenu vozidla: ");
	fgets(riadok, 200, stdin);
	riadok[strlen(riadok) - 1] = '\0';
	poms->cena_vozidla = atol(riadok);

	printf("Zadaj rok vyroby vozidla: ");
	fgets(riadok, 200, stdin);
	riadok[strlen(riadok) - 1] = '\0';
	poms->rok_vyroby = atoi(riadok);

	printf("Zadaj stav vozidla: ");
	fgets(riadok, 200, stdin);
	riadok[strlen(riadok) - 1] = '\0';
	strcpy(poms->stav_vozidla, riadok);
	if ((*beg) == NULL) {									
		(*beg) = poms;
		poms->dalsi = NULL;
	}
	else {
		if (pos == 1) {										
			poms->dalsi = (*beg);
			(*beg) = poms;
		}
		else {
			for (int i = 2; i < pos; i++) {				
				act = act->dalsi;
				if (act->dalsi == NULL) break;				
			}
			if (act->dalsi == NULL) {						
				act->dalsi = poms;
				poms->dalsi = NULL;
			}
			else {											
				poms->dalsi = act->dalsi;
				act->dalsi = poms;
			}
		}
	}
	
}

void zmazanie_zo_zoznamu(polozka **beg) {								
	char search[50];
	polozka *akt, *prev;
	char znacka_vozidla_h[52];
	int pocitadlo = 0;
	int prv = 1;
	printf("Zadaj hladane znaky: ");						
	fgets(search, 50, stdin);
	fgets(search, 50, stdin);
	_strupr(search);										
	akt = (*beg);
	prev = (*beg);
	search[strlen(search) - 1] = '\0';
	do {													
		strcpy(znacka_vozidla_h, akt->znacka_vozidla);						
		_strupr(znacka_vozidla_h);									
		if (strstr(znacka_vozidla_h, search) != NULL) {				
			if (prv==1) {								
				(*beg) = akt->dalsi;						
				prev = akt->dalsi;
				free(akt);
				akt = prev;
				prv++;

			}
			else {											
				if (akt->dalsi == NULL) {					
					free(akt);
					akt = NULL;
					prev->dalsi = NULL;
				}
				else {										
					prev->dalsi = akt->dalsi;
					free(akt);
					akt = prev->dalsi;
				}
			}
			pocitadlo++;
			prv--;
		}
		else {												
			if (akt!=(*beg))								
				prev = prev->dalsi;
			akt = akt->dalsi;								
			
		}
	} while (akt != NULL);
	printf("Zmazalo sa %d poloziek", pocitadlo);					
}

void hladanie_v_zozname(polozka *beg) {								
	int cena, bol = 1, pocitadlo = 1;
	printf("Zadaj maximalnu cenu: ");					
	scanf("%d", &cena);
	polozka *poms;
	poms = beg;
	do {
		if ((poms->cena_vozidla) <= cena) {						
			printf("%d.\n%s\n%s\n%s\n%li\n%d\n%s\n", pocitadlo, poms->kategoria, poms->znacka_vozidla, poms->majitel_vozidla, poms->cena_vozidla, poms->rok_vyroby, poms->stav_vozidla);
			pocitadlo++;
			bol = 0;
		}
		poms = poms->dalsi;

	} while (poms != NULL);

	if (bol)												
		printf("V ponuke su len auta s vyssou cenou.\n");

}

void nahradenie_v_zozname(polozka *beg) {			
	char znacka_vozidla_h[52], riadok[202];
	long int cena_vozidla_h;
	int pocitadlo = 0, first = 0;
	polozka *act, *novy = NULL;
	printf("Zadaj presnu znacku vozidla: ");	
	fgets(znacka_vozidla_h, 50, stdin);
	fgets(znacka_vozidla_h, 50, stdin);
	znacka_vozidla_h[strlen(znacka_vozidla_h) - 1] = '\0';
	printf("Zadaj presnu cenu vozidla: ");
	cena_vozidla_h = atol(fgets(riadok, 50, stdin));		
	act = beg;
	int prv = 1;
	do {											
		if (first)
			act = act->dalsi;
		if (strcmp(act->znacka_vozidla, znacka_vozidla_h) == 0) {		
			if (act->cena_vozidla == cena_vozidla_h) {
				if (novy == NULL) {				
					printf("Zadaj typ vozidla: ");
					fgets(riadok, 50, stdin);
					riadok[strlen(riadok) - 1] = '\0';
					strcpy(act->kategoria, riadok);

					printf("Zadaj znacku vozidla: ");
					fgets(riadok, 50, stdin);
					riadok[strlen(riadok) - 1] = '\0';
					strcpy(act->znacka_vozidla, riadok);

					printf("Zadaj predajcu: ");
					fgets(riadok, 100, stdin);
					riadok[strlen(riadok) - 1] = '\0';
					strcpy(act->majitel_vozidla, riadok);

					printf("Zadaj cenu vozidla: ");
					fgets(riadok, 200, stdin);
					riadok[strlen(riadok) - 1] = '\0';
					act->cena_vozidla = atol(riadok);

					printf("Zadaj rok vyroby vozidla: ");
					fgets(riadok, 200, stdin);
					riadok[strlen(riadok) - 1] = '\0';
					act->rok_vyroby = atoi(riadok);

					printf("Zadaj stav vozidla: ");
					fgets(riadok, 200, stdin);
					riadok[strlen(riadok) - 1] = '\0';
					strcpy(act->stav_vozidla, riadok);
					novy = act;
					prv++;
				}
				else {										
					strcpy(act->kategoria, novy->kategoria);
					strcpy(act->znacka_vozidla, novy->znacka_vozidla);
					strcpy(act->majitel_vozidla, novy->majitel_vozidla);
					act->cena_vozidla = novy->cena_vozidla;
					act->rok_vyroby = novy->rok_vyroby;
					strcpy(act->stav_vozidla, novy->stav_vozidla);
				}
				pocitadlo++;
			}
		}
		first = 1;
	} while (act->dalsi != NULL);
	
	if (pocitadlo > 0) {										
		printf("Bolo zmenenych %d poloziek. ", pocitadlo);
		
	}
	else
		printf("Nebola najdena zhoda v zozname.\n");
}