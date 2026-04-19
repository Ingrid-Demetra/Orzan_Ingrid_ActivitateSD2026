#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//functie citire Cursa- done
//functie afisare cursa -done
//functie citire curse din fisier -done !! trb sa fac si adaugare cursa!
//functie afisare curse LD -done
//fuctie adaugareCusra LD done
//functie adaugareCursa LS done
//functie adaugae vector done

struct structuraCursaAeriana {
	char* cod;
	char* destinatie;
	char* oraPlecare;
	int nrMinuteIntarziere;
};

typedef struct structuraCursaAeriana Cursa;
typedef struct Nod Nod;
typedef struct listaDublaCursaAeriana lista;

Cursa citireCursadinFisier(FILE * file) {
	char buffer[100];
	char sep[5] = ",\n";
	fgets(buffer, 100, file);
	
	Cursa c;
	char* aux;

	//cod:
	aux = strtok(buffer, sep);
	//aloc spatiu:
	c.cod = malloc(strlen(aux) + 1); //+1!
	strcpy_s(c.cod, strlen(aux) + 1, aux);

	//destinatie:
	aux = strtok(NULL, sep);
	c.destinatie = malloc(strlen(aux) + 1); 
	strcpy_s(c.destinatie, strlen(aux) + 1, aux);

	//oraPlecare:
	aux = strtok(NULL, sep);
	c.oraPlecare = malloc(strlen(aux) + 1);
	strcpy_s(c.oraPlecare, strlen(aux) + 1, aux);

	//nrMinuteIntarziere:
	aux = strtok(NULL, sep);
	c.nrMinuteIntarziere = atoi(aux);

	//pt char sau unsigned char: direct ...=*strtok(NULL,sep);
	return c;
}

void afisareCursa(Cursa cursa) {

	printf("cod: %s\n", cursa.cod);
	printf("destinatie: %s\n", cursa.destinatie);
	printf("ora plecare: %s\n", cursa.nrMinuteIntarziere);
	printf("nr minute intarziere: %s\n", cursa.nrMinuteIntarziere);
}

struct Nod {
	Cursa info;
	Nod* next;
	Nod* prev;
};

struct listaDublaCursaAeriana {
	Nod* prim;
	Nod* ultim;
};

lista citireListaCurseDinFisier(const char * numefisier) {

	FILE* f = fopen(numefisier, "r"); //deschudem fisierul
	if (f) {
		lista ld;
		ld.prim = NULL;
		ld.ultim = NULL;
		while (!feof(f)) {
			adaugaCursaLD(&ld, citireCursadinFisier(f));
		}
		fclose(f);
		return ld;
	}
	
}
void afisareLDMasini(lista ld) {
	Nod* p = ld.prim;
	while (p) {
		afisareCursa(p->info);
		p = p->next;
	}
}
//2Scrieți o funcție care :
//numără câte curse au întârziere mai mare decât o valoare X.

int countIntarzieri(lista lista, int x) {
	int cnt = 0;
	Nod* p = lista.prim;
	while (p) {
		if (p->info.nrMinuteIntarziere > x) {
			cnt++;
		}
		p = p->next;
	}
	return cnt;
}
//////////////////////////////////////////////////////////////STERGERE LD////////////////////////////////////////////////
//Scrieți o funcție care :
//șterge din listă toate cursele cu întârziere mai mare decât X.

void stergeCurseIntarziateLD(lista *lista, int x) {

	Nod* p = lista->prim;

	while (p) {
		Nod* deSters = p;
		p = p->next; 
		//dc am nevoie de deSters:
		/*if (conditie) {
			free(p);
		}
		p = p->next;
		💥 Problema :

		După free(p), tu mai încerci :
		p->next*/

		if (deSters->info.nrMinuteIntarziere > x) {
			//refacem legaturi:
			if (deSters->next) {
				deSters->next->prev = deSters->prev;
			}
			else { //daca era ultimul nod
				lista->ultim = deSters->prev;
			}
			if (deSters->prev) {
				deSters->prev->next = deSters->next;
			}
			else { //daca era primul nod
				lista->prim = deSters->next;
			}
			//ELIBERAM nodul deSters:
			free(deSters->info.cod);
			free(deSters->info.destinatie);
			free(deSters->info.oraPlecare);
			free(deSters);
		}
	}
}
//Functie care salveaza intr - o alta structura anumite noduri care indeplinesc o conditie;
//Exemplu: salvati intr - un vector toate cursele care pleaca pana in 12 : 00;
//Exemplus: salvati intr - o lista simpla / dubla cursele care pleaca dupa 12 : 00;
//ca si implementare in cazul vectorului aveti doua optiuni :
//parcurgeti lista cu functia de numarare de mai sus si numarati toate nodurile care indeplinesc conditia iar apoi cu valoarea respectiva initializati vectorul, 
// apoi mai parcurgeti o data lista si salvati elementele in vector; in total veti avea doua parcurgeri
//declarati un vector si setati - l pe NULL, parcurgeti lista o singura data iar la fiecare match apelati realloc(); 
// la fiecare pas veti mari vectorul cu un element;
//in cazul listei e mai usor pentru ca doar va declarati o lista noua si apelati un insert de fiecare data cand gasiti un match

//void adaugaCursaVector()
//{
//
//}
///////////////////////////////////////////////////////////////////ADAUGARE LD & LI///////////////////////////////////////////////////
void adaugaCursaLD(lista * lista, Cursa cursaNoua) {
	//aloc loc in memorie:
	Nod* nou = malloc(sizeof(Nod));
	nou->info = cursaNoua;
	nou->next = NULL;
	nou->prev = lista->ultim;

	//la ld nu mai trb sa parcurg tot, am deja adresa ultimului!-pt inserare la final
	if (lista->ultim != NULL) {
		lista->ultim->next = nou; //leg pe ultimul de nou
	}
	else {
		lista->prim = nou; //il fac pr primul nou
	}
	lista->ultim = nou; //ultimul primeste nou!!
}

void adaugaCursaLSI(Nod ** head, Cursa cursaNoua ) {

	//aloc spatiu!!
	Nod* nou = malloc(sizeof(Nod));
	nou->info = cursaNoua;
	nou->next = NULL;

	Nod* aux = *head; //aux pt parcurgere ca sa nu pierd capul listei 
	if (*head != NULL) //daca lista nu e goala
	{
		while (aux != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*head = nou;
	}
}
void adaugaDupaOra(Nod** head,Cursa Cursa, int ora) {
	if (Cursa.oraPlecare > ora)
		adaugaCursaLSI(&head, Cursa);
}

void adaugaDupaOraLD(lista * lista, Cursa Cursa, int ora) {
	if (Cursa.oraPlecare > ora)
		adaugaCursaLD(&lista, Cursa);
}

int main() {

	Nod* lsi = NULL; //lista simplu inalntuita
	lista ldi;
	ldi.prim = NULL;
	ldi.ultim = NULL;


	return 0;
}