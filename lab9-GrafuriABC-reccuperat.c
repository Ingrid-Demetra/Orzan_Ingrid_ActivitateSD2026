#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
//
////creare structura pentru un nod dintr-un arbore binar de cautare
//
typedef struct Nod Nod;
struct Nod
{
	Masina info;
	Nod* stanga;
	Nod* dreapta;
};
Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}


void adaugaMasinaInArbore(Nod ** radacina, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiippile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID
	Nod* nodNou = malloc(sizeof(Nod));
	nodNou->dreapta = NULL;
	nodNou->stanga = NULL;

	nodNou->info = masinaNoua;

	if (*radacina == NULL) {
		*radacina = nodNou;
		return;
	}

	Nod* aux = *radacina;
	while (aux->stanga != NULL || aux->dreapta != NULL) { //cica e gresita conditia
		if (nodNou->info.id < aux->info.id) {
			if (aux->stanga != NULL) {
				aux = aux->stanga; //mai cobor o pozitie
			}
			else {
				aux->stanga = nodNou;
				return;
			}
		}
		if (nodNou->info.id > aux->info.id) {
			if (aux->dreapta != NULL) {
				aux = aux->dreapta;
			}
			else {
				aux->dreapta = nodNou;
				return;
			}
		}
	} 
}

void adaugaMasinaInArboreRecursiv(Nod** radacina, Masina masinaNoua) {
	if (*radacina == NULL) {
		Nod* nou = malloc(sizeof(Nod));
		nou->stanga = NULL;
		nou->dreapta = NULL;
		nou->info = masinaNoua;

		*radacina = nou;
	}
	else {
		if (masinaNoua.id < (*radacina)->info.id) {
			adaugaMasinaInArboreRecursiv(&(*radacina)->stanga, masinaNoua);
		}
		else {
			adaugaMasinaInArboreRecursiv(&(*radacina)->dreapta, masinaNoua);
		}
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* f = fopen(numeFisier, "r");
	Nod* radacina = NULL; // doar nul nu aloc spatiu aici
	while (!feof(f)) {
		
		adaugaMasinaInArboreRecursiv(&radacina, citireMasinaDinFisier(f));
	}
	fclose(f);
	return radacina;
}

void afisareMasiniDinArbore(Nod * radacina) { //inordinea afișează elementele sortate crescător!!!

	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere


	//inordine
	if (radacina != NULL) { 
		afisareMasiniDinArbore(radacina->stanga); //stanga
		afisareMasina(radacina->info);//radacina
		afisareMasiniDinArbore(radacina->dreapta);//dreapta
	}
}
void afisaremasiniDinArborePorstOrdine(Nod* radacina) { //Părintele se procesează ultimul.
	if (radacina != NULL) { //postordine
		afisaremasiniDinArborePorstOrdine(radacina->stanga);
		afisaremasiniDinArborePorstOrdine(radacina->dreapta);
		afisareMasina(radacina->info);
	}
}

void dezalocareArboreDeMasini(Nod ** radacina) {
	//sunt dezalocate toate masinile si arborele de elemente
	if (*radacina != NULL) {
		Nod * auxStanga = (*radacina)->stanga;
		Nod* auxDreapta = (*radacina)->dreapta;

		free((*radacina)->info.model);
		free((*radacina)->info.numeSofer);

		free(*radacina);
		*radacina = NULL;

		dezalocareArboreDeMasini(&auxStanga);
		dezalocareArboreDeMasini(&auxDreapta);
	}
}

Masina getMasinaByID(Nod * radacina, int  id) {
	Masina m;

	if (radacina == NULL) { //daca e gola arborele
		m.id = -1;
		return m;
	}
	if (radacina->info.id == id) {
		m = radacina->info; //daca as lasa doar asa ar fi shallow copy!! aloc spatiu pt campurile alocate dinamic

		m.model = malloc(strlen(radacina->info.model) + 1);
		strcpy_s(m.model, strlen(radacina->info.model) + 1, radacina->info.model);

		m.numeSofer = malloc(strlen(radacina->info.numeSofer) + 1);
		strcpy_s(m.numeSofer, strlen(radacina->info.numeSofer) + 1, radacina->info.numeSofer);
		return m;
	}
	//daca n am gasit-o, reapelez:
	if (id < radacina->info.id) {
		getMasinaByID(radacina->stanga, id);

	}
	else {
		getMasinaByID(radacina->dreapta, id);
	}

}

int determinaNumarNoduri(/*arborele de masini*/) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	return 0;
}

int calculeazaInaltimeArbore(/*arbore de masini*/) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	return 0;
}

float calculeazaPretTotal(/*arbore de masini*/) {
	//calculeaza pretul tuturor masinilor din arbore.
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {


	return 0;
}