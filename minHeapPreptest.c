#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

struct Pacient {
	char* nume;
	int prioritate;
};
typedef struct Pacient Pacient;
typedef struct Heap Heap;

struct Heap {
	int lungime;
	int nrElemente;
	Pacient* pacienti;
};

Pacient citirePacientDinFisier(FILE* file) {
    Pacient p;
    char buffer[100];
    char sep[] = ",\n\r";
    fgets(buffer, 100, file);
    char* aux;
    aux = strtok(buffer, sep);
    p.nume = malloc(strlen(aux) + 1);
    strcpy_s(p.nume, strlen(aux) + 1, aux);
    p.prioritate = atoi(strtok(NULL, sep));
    return p;
}

void afisarePacient(Pacient p) {
    printf("Nume: %s\n", p.nume);
    printf("Prioritate: %d\n", p.prioritate);
}
Heap initHeap(int lungime) {
    Heap heap;
    heap.lungime = lungime;
    heap.nrElemente = 0;
    heap.pacienti = malloc(sizeof(Pacient) * lungime);


   /* heap.pacienti = NULL;*/ ////NU!!

    return heap;
}
void filtreazaHeap(Heap heap,int pozNod) {
    int pozStanga = pozNod * 2 + 1;
    int pozDreapta = pozNod * 2 + 2;
    int pozMin = pozNod;

    if (pozStanga<heap.nrElemente && heap.pacienti[pozStanga].prioritate<heap.pacienti[pozMin].prioritate) {
        pozMin = pozStanga;
    }
    if (pozDreapta < heap.nrElemente && heap.pacienti[pozDreapta].prioritate < heap.pacienti[pozMin].prioritate) {
        pozMin = pozDreapta;
    }
    if (pozMin != pozNod) {
        Pacient aux = heap.pacienti[pozMin];
        heap.pacienti[pozMin] = heap.pacienti[pozNod];
        heap.pacienti[pozNod] = aux;

        filtreazaHeap(heap, pozMin);
    }
}
Heap citirePacientiDinFisier(char * numeFisier) {
    Heap heap;
    heap=initHeap(12);
    FILE* f = fopen(numeFisier, "r");

    if (f) {
        while (!feof(f)) {
            heap.pacienti[heap.nrElemente++] = citirePacientDinFisier(f);
        }
        fclose(f);
    }
    for (int i = (heap.nrElemente - 2) / 2;i >= 0;i--) {
        filtreazaHeap(heap, i);
    }
    return heap;

}
void afisareHeap(Heap heap) {
    for (int i = 0;i < heap.nrElemente;i++)
        afisarePacient(heap.pacienti[i]);
}
int NumararePrioritate(Heap heap,int prioritate) {
    int cnt = 0;
    if (heap.nrElemente == 0) {
        return cnt;
    }
    for (int i = 0;i < heap.nrElemente;i++) {
        if (heap.pacienti[i].prioritate == prioritate) {
            cnt++;
        }
    }
    return cnt;
}
//extragePacient — extrage pacientul cu prioritatea minima- to do--sterge in loc de extrage

void stergePacientulCuPrioritatea1(Heap  *heap, int prioritate) {
    for (int i = 0;i < heap->nrElemente;i++) {
        if (heap->pacienti[i].prioritate==prioritate) {
            heap->pacienti[i] = heap->pacienti[heap->nrElemente - 1];
            heap->nrElemente--;

            filtreazaHeap(*heap, i);
            i--;
        }
    }
}
int main() {
    Heap heap;
    heap = citirePacientiDinFisier("Pacienti.txt");
    afisareHeap(heap);
    printf("\nnr pacienti cu prioritatea 1: %d", NumararePrioritate(heap, 1));
    stergePacientulCuPrioritatea1(&heap,1);
    afisareHeap(heap);
	return 0;
}