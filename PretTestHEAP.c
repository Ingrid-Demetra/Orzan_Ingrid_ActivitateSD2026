//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct CursaAeriana {
//	char* cod;
//	char* destinatie;
//	short int nrMinuteIntarziere;
//};
//typedef struct CursaAeriana cursa;
//
////un vector de elemente, lungimea vectorului si numarul de elemente din vector
//struct Heap {
//	int lungime;
//	int nrElemente;
//	cursa* curse; //vector alocat dinamic
//};
//
//typedef struct Heap Heap;
//
////functie de numarare cu conditie(toate cursele cu o intarziere mai mare decat x), parcurgerea vectorului de heap
////stergere cu criteriu(toate cursele care au plecat), apelati heapify la fiecare stergere pentru a mentine conditia de heap
////salvare din heap in lista dubla, lista simpla sau vector, cu filtru(ex.toate cursele care au data de plecare inainte de o anumita data specificata de voi);
////parcurgeti vectorul de heap si salvati elementul in structura noua
//
//cursa citireCursaDinFisier(FILE* file) {
//	cursa c;
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//
//	char* aux;
//	aux = strtok(buffer, sep);
//	c.cod = malloc(strlen(aux) + 1);
//	strcpy_s(c.cod, strlen(aux) + 1, aux);
//	aux = strtok(NULL, sep);
//	c.destinatie = malloc(strlen(aux) + 1);
//	strcpy_s(c.destinatie, strlen(aux) + 1, aux);
//
//	c.nrMinuteIntarziere = atoi(strtok(NULL, sep));
//	return c;
//}
//void afisareCursa(cursa c) {
//	printf("\n cod: %s", c.cod);
//	printf("\n destinatie: %s", c.destinatie);
//	printf("\nNr minute intarziere: %d", c.nrMinuteIntarziere);
//
//	/*parinte(i) = (i - 1) / 2!!!!
//		stanga(i) = i * 2 + 1
//		dreapta(i) = i * 2 + 2*/
//}
////INIT HEAP
//Heap initHEap(int lungime) { //primesc doar lungimea ca param
//	//initalizez fiecare element
//	Heap heap;
//	heap.lungime = 0;
//	heap.curse = malloc(sizeof(cursa) * lungime);
//	heap.nrElemente = 0;
//	return heap;
//}
//void filtreazaHeap(Heap heap,int pozNod) { 
//	int pozStanga=pozNod*2+1;
//	int pozDreapta=pozNod*2+2;
//	int pozMax=pozNod;
//
//	//daca pozstanga are un elem mai mare dupa un criteriu devine pozmax
//	if (pozStanga<heap.nrElemente && heap.curse[pozStanga].nrMinuteIntarziere>heap.curse[pozMax].nrMinuteIntarziere) {
//		pozMax = pozStanga;
//	}
//
//	//daca pozdreapta..
//	if (pozDreapta<heap.nrElemente && heap.curse[pozDreapta].nrMinuteIntarziere>heap.curse[pozMax].nrMinuteIntarziere) {
//		pozMax = pozDreapta;
//	}
//
//	if (pozMax != pozNod) { //daca parintele nu e maxim, interschimb elem de pe curse[pozmax} cu cel de pe curse[pozNod]
//		cursa aux = heap.curse[pozMax];
//		heap.curse[pozMax] = heap.curse[pozNod];
//		heap.curse[pozNod] = aux;
//
//		filtreazaHeap(heap, pozMax);//continui in jos
//	}
//
//}
//
//Heap citireHeapDeCurseDinFisier(char * numeFisier) {
//	Heap heap=initHEap(12);
//	FILE* f = fopen(numeFisier, "r");
//	if (f) {
//		while (!feof(f)) {
//			heap.curse[heap.nrElemente++] = citireCursaDinFisier(f);
//		}
//		fclose(f);
//	}
//	for (int i = (heap.nrElemente - 2) / 2;i >= 0;i--) {
//		filtreazaHeap(heap, i);
//	}
//	return heap;
//}
//void afisareHeap(Heap heap) {
//	for (int i = 0;i < heap.lungime;i++) {
//		afisareCursa(heap.curse[i]);
//	}
//}
//int main() {
//	Heap heap;
//	heap=citireHeapDeCurseDinFisier("curse.txt");
//	afisareHeap(heap);
//	cursa c1;
//	c1.cod = 3;
//	c1.destinatie = malloc(strlen("ibiza") + 1);
//	strcpy_s(c1.destinatie, strlen("ibiza") + 1, "ibiza");
//	c1.destinatie = malloc(strlen("ibiza") + 1);
//	strcpy_s(c1.destinatie, strlen("ibiza") + 1, "ibiza");
//
//	return 0;
//}