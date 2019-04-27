#define _CRT_SECURE_NO_WARNINGS
#define BUF 127
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct album {
	char eloado[25];
	char album[25];
	char kiado[15];
	int ev;
	struct album *kov;
}album;

int getline(char *s, int lim);
int pozitivegesze(char s[]);
album* Beszur(album* horgony, char *eloado, char *albumcim, char *kiado, int ev);
void Kiir(album* horgony);
void felszabadit(album* horgony);

int main(void) {
	SetConsoleCP(1250);
	SetConsoleOutputCP(1250);
	printf("A program zenei albumok adatait tárolja láncolt lista adatszerkezetben\n");
	album* horgony = NULL;
	char sor[BUF+1];
	int melyikElem = 0;
	int hossz = 0;
	char nev[25];
	char albumcim[25];
	char kiado[25];
	int megjelenes;
	int i = 0;
	do{
		switch (melyikElem){
		case 0:
			printf("Írja be az album elõadóját:\n");
			hossz = getline(sor,BUF);
			if (hossz > 0 && hossz < 25) {
				strcpy(nev,sor);
				melyikElem++;
			}
			break;
		case 1:
			printf("Írja be az album címét:\n");
			hossz = getline(sor, BUF);
			if (hossz > 0 && hossz < 25) {
				strcpy(albumcim, sor);
				melyikElem++;
			}
			break;
		case 2:
			printf("Írja be az album kiadóját:\n");
			hossz = getline(sor, BUF);
			if (hossz > 0 && hossz < 15) {
				strcpy(kiado, sor);
				melyikElem++;
			}
			break;
		case 3:
			printf("Írja be az megjelenés éve:\n");
			hossz = getline(sor, BUF);
			if (pozitivegesze(sor)) {
				megjelenes = atoi(sor);
				if (megjelenes > 1950 && megjelenes < 2018) {
					melyikElem++;
				}
			}
			break;
		}
		if (melyikElem == 4) {
			horgony=Beszur(horgony,nev, albumcim, kiado, megjelenes);
			melyikElem = 0;
			i++;
		}
	} while (hossz!=0 || i<5);
	Kiir(horgony);
	felszabadit(horgony);
	return 0;
}
int getline(char *s, int lim) {
	int c;
	char *t = s;
	while (--lim>0 && (c = getchar()) != EOF && c != '\n') *s++ = c;
	*s = '\0';
	while (c != EOF && c != '\n')
		c = getchar();
	return s - t;
}
int pozitivegesze(char s[]) {
	int i = 0;
	int kezd;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') ++i;
	if (s[i] == '+')++i;
	else if (s[i] == '-')return 0;
	kezd = i;
	while (s[i] >= '0' && s[i] <= '9') ++i;
	if (kezd != i && (s[i] == 0 || s[i] == '\t' || s[i] == '\n' || s[i] == ' ')) return 1;
	else	return 0;
}

album* Beszur(album* horgony,char *eloado, char *albumcim, char *kiado, int ev) {
	if (horgony == NULL) {
		if (horgony = (album*)malloc(sizeof(album))){
			strcpy(horgony->eloado,eloado);
			strcpy(horgony->album, albumcim);
			strcpy(horgony->kiado,kiado);
			horgony->ev = ev;
			horgony->kov = NULL;
		}
		else return NULL;
	}
	else{
		album* seged = horgony;
		album* uj;
		while (seged->kov!=NULL){
			seged = seged->kov;
		}
		if (uj = (album*)malloc(sizeof(album))) {
			strcpy(uj->eloado, eloado);
			strcpy(uj->album, albumcim);
			strcpy(uj->kiado, kiado);
			uj->ev = ev;
			uj->kov = NULL;
			seged->kov = uj;
		}
		else return NULL;
	}
	return horgony;
}
void Kiir(album* horgony) {
	printf("Elõadó                   Cím                      Kidadó         Megjelenés\n");
	printf("----------------------------------------------------------------------------\n");
	album* seged = horgony;
	while (seged!=NULL){
		printf("%-25s%-25s%-10s     %d\n",seged->eloado,seged->album,seged->kiado,seged->ev);
		seged = seged->kov;
	}
}
void felszabadit(album* horgony) {
	album* seged;
	while (horgony != NULL) {
		seged = horgony;
		horgony = horgony->kov;
		free(seged);
	}
}