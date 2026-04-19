#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct structuraCursaAeriana {
	char* cod;
	char* destinatie;
	char* oraPlecare;
	int nrMinuteIntarziere;
};
//Se definește o listă dublu înlănțuită de CursaAeriana.
//1Scrieți structura nodului.
typedef struct structuraCursaAeriana Cursa;
typedef struct Nod Nod;
typedef struct listaDublaCursaAeriana lista;

//Cursa citireCursadinFisier(FILE * file) {
//	char buffer[100];
//	char 
//
//	return cursa;
//}

struct Nod {
	Cursa info;
	Nod* next;
	Nod* prev;
};

struct listaDublaCursaAeriana {
	Nod* prim;
	Nod* ultim;
};

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

//Scrieți o funcție care :
//șterge din listă toate cursele cu întârziere mai mare decât X.

void stergeCurseIntarziate(lista *lista, int x) {

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

//4Scrieți o funcție care :
//👉 salvează într - un vector toate cursele care pleacă înainte de ora "12:00"
//Cerințe :
//	folosiți varianta cu 2 parcurgeri
//	returnați vectorul + dimensiunea prin parametru

//Functie care salveaza intr - o alta structura anumite noduri care indeplinesc o conditie;
//
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

int main() {

	Nod* lsi = NULL; //lista simplu inalntuita
	lista ldi;
	ldi.prim = NULL;
	ldi.ultim = NULL;
	//functie citire Cursa
	//functie afisare cursa
	//functie citire curse din fisier
	//functie afisare curse

	return 0;
}