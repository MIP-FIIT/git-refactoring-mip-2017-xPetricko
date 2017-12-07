#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct polozka {
	char category[52];
	char brand[52];
	char owner[102];
	long int price;
	int build1_year;
	char state[202];
	struct polozka *dalsi;
} polozka;

void mem_dealoc(polozka **beg, polozka **act);
void mem_aloc(polozka **beg, polozka **act);

void main() {
	char znak;
	polozka *begin=NULL, *actual=NULL;
	do {
		scanf("%c", &znak);
		switch (znak) {
		case 'n': 
			if (begin != NULL)
				mem_dealoc(&begin, &actual);
			mem_aloc(&begin, &actual);
			break;
		case 'v': printf("n");
			break;
		case 'z': printf("n");
			break;
		case 'p': printf("n");
			break;
		case 'h': printf("n");
			break;
		case 'a': printf("n");
			break;
		}
	} while (znak != 'k');
	
	if (begin!=NULL)
		mem_dealoc(begin, actual);
}

void mem_dealoc(polozka **beg, polozka **act) {
	do {
		*act = *beg;
		*beg = (*act)->dalsi;
		free(*act);
	} while (*beg != NULL);
}

void mem_aloc(polozka **beg, polozka **act) {
	FILE *fptr;
	char pom[202], ch;
	long int cena;
	int counter = 0;
	if ((fptr = fopen("auta.txt", "r")) == NULL)
		printf("Subor nebol otvoreny.");
	else {
		printf("Subor bol otvoreny");
		do {
			ch = fgetc(fptr);
			if (ch == '$') {
				counter++;
			}


		} while (ch != EOF);
		fclose(fptr);
	}
	printf("vytvorilo sa %d\n", counter);
}