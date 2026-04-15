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

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
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

//STACK
//Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
//putem reprezenta o stiva prin LSI, LDI sau vector

//prin LSI-STIVA:

typedef struct NodSimplu NodSimplu;

struct NodSimplu {
	Masina masina;
	NodSimplu* next;
};

//inserare
void pushStack(NodSimplu ** stack, Masina masina) {
	NodSimplu* nou = malloc(sizeof(NodSimplu));
	nou->masina = masina;
	nou->next = *stack; //nou =top
	*stack = nou; //stack poointezaza spre noul nod
}

//returnez ultimul obiect inserat
//Masina popStack(NodSimplu ** stack) {
//
//	Masina masina;
//	masina.id = -1;
//
//	if (*stack == NULL) {
//		return masina;
//	}
//
//	NodSimplu* aux = *stack;
//	masina = aux->masina;
//	*stack = (*stack)->next;  // top-ul avansează
//	free(aux);                // eliberăm nodul vechi
//	return masina;
//}

Masina popStack(NodSimplu **stack) { //** pt ca modificam
	Masina masina;
	masina.id = -1;
	if (*stack == NULL) {
		return masina;
	}

	NodSimplu* aux = *stack; //retinem ultimul nod
	masina = aux->masina; //preluam info de la ultimul nod
	*stack = (*stack)->next; //stack poiinteaza la al doilea nod de sus in jos
	free(aux); //stergem ultimul nod;
	return masina;
}

int emptyStack(NodSimplu *stack) { //* nu modificam doar veriicam daca e goala
	return !stack;
}

void* citireStackMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	NodSimplu* stack = NULL;

	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		pushStack(&stack, citireMasinaDinFisier(f)); 
	}
	fclose(f);
	return stack;
}



void dezalocareStivaDeMasini(/*stiva*/) {
	//sunt dezalocate toate masinile si stiva de elemente
}

int size(/*stiva*/) {
	//returneaza numarul de elemente din stiva
}

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector

//coada prin ldi
//first in first out

typedef struct Nod Nod;
typedef struct Queue Queue;

struct Nod {
	Masina masina;
	Nod* next;
	Nod* prev;
};
struct Queue {
	Nod* start;
	Nod* end;
};
void enqueue(Queue* queue, Masina masina) {
	//adauga o masina in coada
	Nod* nod = malloc(sizeof(Nod));
	nod->masina = masina;
	nod->next = queue->start;
	nod->prev = NULL;
	if (queue->start != NULL)
	{
		queue->start->prev = nod; // fostul start pointează înapoi spre nou
		
	}
	else {
		queue->end = nod; //dacă coada era goală, end = start = noul nod
	}
	queue->start = nod; // noul nod devine start
}

Masina dequeue(Queue * queue) {
	//extrage o masina din coada
	Masina masina;

	if (queue->start == NULL) {
		masina.id = -1;
		return masina;
	}

	masina = queue->end->masina;  //shallow copy

	if (queue->start == queue->end) {      // queue->end->prev==NULL adica verificam daca exista doua noduri 
		free(queue->start);

		queue->start = NULL;
		queue->end = NULL;
	}//daca are un singur nod care e si start si end il dezalocam pe ala
	else {
		queue->end = queue->end->prev;
		free(queue->end->next);
		queue->end->next = NULL;
	}
	return masina;
}

//Masina dequeue(Queue * queue) {
//	Masina masina;
//	if (queue->start == NULL) {
//		masina.id = -1;
//		return masina;
//	}
//	masina = queue->end->masina; //masina=ultimul nod
//	if (queue->start == queue->end) {
//		free(queue->end);
//
//		queue->start = NULL; //no dangling pointers
//		queue->end = NULL;
//	}
//	else {
//		queue->end = queue->end->prev;
//		free(queue->end->next);
//		queue->end->next = NULL;
//	}
//	return masina;
//}

Queue citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	Queue queue;
	queue.start = NULL;
	queue.end = NULL;

	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		Masina masina = citireMasinaDinFisier(f);
		enqueue(&queue, masina);
	}
	fclose(f);
	return queue;
}

void dezalocareCoadaDeMasini(/*coada*/) {
	//sunt dezalocate toate masinile si coada de elemente
}


//metode de procesare
Masina getMasinaByID(Queue* queue, int id) {
	Queue aux;
	aux.end = NULL;
	aux.start = NULL;

	Masina rezultat;
	rezultat.id = -1;

	while (queue->start != NULL) {
		Masina masina = dequeue(queue);  // scoatem din queue

		if (masina.id == id) { // e mașina căutată?
			rezultat = masina; // o salvăm

			rezultat.model = malloc(sizeof(char) * (strlen(masina.model) + 1));
			strcpy(rezultat.model, masina.model); 

			//deep copy 
			// fără asta, când eliberezi coada, rezultat.model ar pointa spre memorie ștearsă
			//rezultat = masina;  // shallow copy - copiază pointerii, nu datele!


			rezultat.numeSofer = malloc(sizeof(char) * (strlen(masina.numeSofer) + 1));
			strcpy(rezultat.numeSofer, masina.numeSofer);
		}
		enqueue(&aux, masina); //golim coada in una auxiliara
	}

	queue->start = aux.start;
	queue->end = aux.end;

	return rezultat;
}

float calculeazaPretTotal(/*stiva sau coada de masini*/);

int main() {

	Queue queue = citireCoadaDeMasiniDinFisier("masini.txt");
	/*afisareMasina(dequeue(&queue));
	afisareMasina(dequeue(&queue));*/

	Masina masina = getMasinaByID(&queue, 9);
	afisareMasina(masina);
	free(masina.model);
	free(masina.numeSofer);

	return 0;
}